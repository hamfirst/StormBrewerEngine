
#include "FileSystemWatcher.h"

#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;

#ifdef _MSC_VER

#include <Windows.h>

#include <codecvt>


struct FileSystemWatcherData
{
  HANDLE m_DirectoryHandle;
};

#else

struct FileSystemWatcherData
{

};

#endif

FileSystemWatcher::FileSystemWatcher(const std::string & root_path, StormSockets::StormSemaphore & semaphore) :
  m_RootPath(root_path),
  m_Data(std::make_unique<FileSystemWatcherData>()),
  m_Semaphore(semaphore),
  m_ExitThread(false)
{
#ifdef _MSC_VER
  m_Data->m_DirectoryHandle = CreateFile(
    m_RootPath.data(),
    FILE_LIST_DIRECTORY,
    FILE_SHARE_WRITE | FILE_SHARE_READ | FILE_SHARE_DELETE,
    NULL,
    OPEN_EXISTING,
    FILE_FLAG_BACKUP_SEMANTICS,
    NULL);
#endif

  m_NotifyThread = std::thread(&FileSystemWatcher::NotifyThread, this);
}

FileSystemWatcher::~FileSystemWatcher()
{
  m_ExitThread = true;
  m_NotifyThread.join();

#ifdef _MSC_VER
  CloseHandle(m_Data->m_DirectoryHandle);
#endif
}

Optional<std::tuple<FileSystemOperation, std::string, std::string, std::chrono::system_clock::time_point>> FileSystemWatcher::GetFileChange()
{
  std::lock_guard<std::mutex> lock(m_QueueMutex);

  if (m_FilesChanged.size() == 0)
  {
    return{};
  }

  auto ret_val = m_FilesChanged.front();
  m_FilesChanged.pop();

  return ret_val;
}

void FileSystemWatcher::IterateDirectory(const std::string & local_path, const std::string & full_path, FileSystemDirectory & dir)
{
  for (fs::directory_iterator dir_itr = fs::directory_iterator(full_path), end = fs::directory_iterator(); dir_itr != end; ++dir_itr)
  {
    auto info = dir_itr->status();
    if (fs::is_regular_file(info))
    {
      std::error_code ec;
      dir.m_Files.emplace(std::make_pair(dir_itr->path().filename().string(), fs::last_write_time(dir_itr->path(), ec)));
    }
    else if (fs::is_directory(info))
    {
      FileSystemDirectory sub_dir;
      IterateDirectory(local_path + dir_itr->path().filename().string() + "/", full_path + dir_itr->path().filename().string() + "/", sub_dir);

      dir.m_Directories.emplace(std::make_pair(dir_itr->path().filename().string(), std::make_unique<FileSystemDirectory>(std::move(sub_dir))));
    }
  }
}

NullOptPtr<FileSystemDirectory> FileSystemWatcher::GetDirectoryAtPath(const char * path, FileSystemDirectory & base)
{
  std::string path_segment;
  bool got_dir = false;
  while(true)
  {
    auto c = *path;

    if (c == '/' || c == '\\')
    {
      path++;
      got_dir = true;
      break;
    }

    if (c == 0)
    {
      break;
    }

    path_segment += c;
    path++;
  }

  if (path_segment.length() == 0)
  {
    return &base;
  }

  if (path_segment == ".")
  {
    return GetDirectoryAtPath(path, base);
  }

  if (path_segment == "..")
  {
    if (base.m_Parent == nullptr)
    {
      return nullptr;
    }

    return GetDirectoryAtPath(path, *base.m_Parent);
  }

  auto itr = base.m_Directories.find(path_segment);
  if (itr == base.m_Directories.end())
  {
    return nullptr;
  }

  return GetDirectoryAtPath(path, *itr->second.get());
}

Optional<std::pair<FileSystemDirectory *, FileSystemDirectory::FileIterator>> FileSystemWatcher::GetFileOrDirectoryAtPath(const char * path, FileSystemDirectory & base)
{
  std::string path_segment;
  bool got_dir = false;
  while (true)
  {
    auto c = *path;

    if (c == '/' || c == '\\')
    {
      path++;
      got_dir = true;
      break;
    }

    if (c == 0)
    {
      break;
    }

    path_segment += c;
    path++;
  }

  if (path_segment.length() == 0)
  {
    Optional<std::pair<FileSystemDirectory *, FileSystemDirectory::FileIterator>> return_val = std::make_pair(&base, base.m_Files.end());
    return return_val;
  }

  if (path_segment == ".")
  {
    return GetFileOrDirectoryAtPath(path, base);
  }

  if (path_segment == "..")
  {
    if (base.m_Parent == nullptr)
    {
      return {};
    }

    return GetFileOrDirectoryAtPath(path, *base.m_Parent);
  }

  auto itr = base.m_Directories.find(path_segment);
  if (itr == base.m_Directories.end())
  {
    auto file_itr = base.m_Files.find(path_segment);
    if (file_itr == base.m_Files.end())
    {
      return{};
    }

    Optional<std::pair<FileSystemDirectory *, FileSystemDirectory::FileIterator>> return_val = std::make_pair(&base, file_itr);
    return return_val;
  }

  return GetFileOrDirectoryAtPath(path, *itr->second.get());
}

void FileSystemWatcher::TriggerOperationForFile(const std::string & path, const std::string & filename, FileSystemOperation op, std::chrono::system_clock::time_point last_write)
{
  std::unique_lock<std::mutex> lock(m_QueueMutex);
  m_FilesChanged.emplace(std::make_tuple(op, path, filename, last_write));

  lock.unlock();

  m_Semaphore.Release(1);
}

void FileSystemWatcher::TriggerOperationForDirectoryFiles(FileSystemDirectory & base, const std::string & base_path, FileSystemOperation op)
{
  std::unique_lock<std::mutex> lock(m_QueueMutex);
  for (auto elem : base.m_Files)
  {
    m_FilesChanged.emplace(std::make_tuple(op, base_path + elem.first, elem.first, elem.second));
  }

  lock.unlock();

  for (auto & elem : base.m_Directories)
  {
    TriggerOperationForDirectoryFiles(*elem.second.get(), base_path + elem.first + "/", op);
  }
}

void FileSystemWatcher::NotifyThread()
{
  std::string last_change;
  uint32_t last_change_time = 0;

  IterateDirectory("./", m_RootPath.data(), m_RootDirectory);
  TriggerOperationForDirectoryFiles(m_RootDirectory, "./", FileSystemOperation::kAdd);

  m_Semaphore.Release(1);

  while (m_ExitThread == false)
  {
#ifdef _MSC_VER
    char buffer[8092] = {};

    FILE_NOTIFY_INFORMATION * notify_info = reinterpret_cast<FILE_NOTIFY_INFORMATION *>(buffer);
    DWORD bytes_returned = 0;

    DWORD flags = FILE_NOTIFY_CHANGE_ATTRIBUTES | FILE_NOTIFY_CHANGE_CREATION | FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_DIR_NAME | FILE_NOTIFY_CHANGE_LAST_WRITE;

    if(ReadDirectoryChangesW(m_Data->m_DirectoryHandle, notify_info, sizeof(buffer), true, flags, &bytes_returned, nullptr, nullptr))
    {
      FILE_NOTIFY_INFORMATION * notification = notify_info;
      while (notification)
      {
        std::wstring filename(notification->FileName, notification->FileName + (notification->FileNameLength / 2));
        for (std::size_t index = 0, len = filename.size(); index < len; index++)
        {
          if (filename[index] == '\\')
          {
            filename[index] = '/';
          }
        }

        std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
        std::string conv_filename = conv.to_bytes(filename);

        std::string changed_filename("./" + conv_filename);
        std::string full_path = m_RootPath + conv_filename;

        auto path = fs::path(changed_filename);
        auto status = fs::status(full_path);

        bool is_deleted = fs::exists(status) == false;
        bool is_file = fs::is_regular_file(status);

        switch (notification->Action)
        {
        case FILE_ACTION_ADDED:
        case FILE_ACTION_RENAMED_NEW_NAME:
          if (is_deleted)
          {
            break;
          }

          if (is_file)
          {
            auto dir = GetDirectoryAtPath(path.parent_path().string().c_str(), m_RootDirectory);
            if (dir)
            {
              std::error_code ec;
              auto last_write = fs::last_write_time(full_path, ec);

              dir->m_Files.emplace(std::make_pair(path.filename().string(), last_write));
              TriggerOperationForFile(changed_filename, path.filename().string(), FileSystemOperation::kAdd, last_write);
            }
          }
          else
          {
            auto dir = GetDirectoryAtPath(path.parent_path().string().c_str(), m_RootDirectory);
            if (dir)
            {
              FileSystemDirectory sub_dir;
              IterateDirectory(changed_filename.c_str(), m_RootPath.data(), sub_dir);

              TriggerOperationForDirectoryFiles(sub_dir, changed_filename + "/", FileSystemOperation::kAdd);
              dir->m_Directories.emplace(std::make_pair(path.filename().string(), std::make_unique<FileSystemDirectory>(std::move(sub_dir))));

              m_Semaphore.Release(1);
            }
          }
          break;
        case FILE_ACTION_MODIFIED:
          if (is_deleted == false && is_file)
          {
            auto dir = GetDirectoryAtPath(path.parent_path().string().c_str(), m_RootDirectory);
            if (dir)
            {
              auto itr = dir->m_Files.find(path.filename().string());
              if (itr != dir->m_Files.end())
              {
                std::error_code ec;
                auto last_write = fs::last_write_time(full_path, ec);

                if (last_write > itr->second)
                {
                  itr->second = last_write;
                  TriggerOperationForFile(changed_filename, path.filename().string(), FileSystemOperation::kModify, last_write);
                }
              }
            }
          }
          break;
        case FILE_ACTION_REMOVED:
        case FILE_ACTION_RENAMED_OLD_NAME:
          {
            auto file_info = GetFileOrDirectoryAtPath(path.string().c_str(), m_RootDirectory);
            if (file_info)
            {
              auto dir = file_info->first;
              auto file_itr = file_info->second;

              if (file_itr != dir->m_Files.end())
              {
                dir->m_Files.erase(file_itr);
                TriggerOperationForFile(changed_filename, path.filename().string(), FileSystemOperation::kDelete, {});
              }
              else
              {
                TriggerOperationForDirectoryFiles(*dir, changed_filename + "/", FileSystemOperation::kDelete);

                if (dir->m_Parent)
                {
                  auto parent = dir->m_Parent;
                  auto dir_itr = parent->m_Directories.find(path.filename().string());
                  if (dir_itr != parent->m_Directories.end())
                  {
                    parent->m_Directories.erase(dir_itr);
                  }
                }

                m_Semaphore.Release(1);
              }
            }
          }
          break;
        }

        //last_change = changed_filename;
        //last_change_time = cur_time;


        notification = notification->NextEntryOffset == 0 ? nullptr :
          reinterpret_cast<FILE_NOTIFY_INFORMATION *>(reinterpret_cast<uint8_t *>(notification) + notification->NextEntryOffset);
      }
    }
#endif
  }
}