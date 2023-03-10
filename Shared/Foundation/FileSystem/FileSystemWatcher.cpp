
#include "Foundation/Common.h"
#include "Foundation/FileSystem/FileSystemWatcher.h"
#include "Foundation/FileSystem/Path.h"
#include "Foundation/FileSystem/File.h"

#include <filesystem>
namespace fs = std::filesystem;

#ifdef _MSC_VER

#include <Windows.h>


struct FileSystemWatcherData
{
  HANDLE m_DirectoryHandle;
};

#elif defined(_LINUX)

#include <unistd.h>
#include <dirent.h>
#include <sys/inotify.h>

#include <unordered_map>
#include <string>

struct FileSystemWatcherData
{
  int m_NotifyHandle;
  std::unordered_map<int, std::string> m_DirectoryLookup;
};

#else

struct FileSystemWatcherData
{

};

#endif

FileSystemWatcher::FileSystemWatcher(const std::string & root_path, Delegate<void> && notify) :
  m_RootPath(root_path),
  m_Data(std::make_unique<FileSystemWatcherData>()),
  m_Notify(notify),
  m_ExitThread(false)
{

#ifdef _MSC_VER

  printf("Starting file system watcher in directory %s\n", root_path.c_str());
  fs::path root_fs_path(root_path.data());

  m_Data->m_DirectoryHandle = CreateFile(
    root_fs_path.c_str(),
    FILE_LIST_DIRECTORY,
    FILE_SHARE_WRITE | FILE_SHARE_READ | FILE_SHARE_DELETE,
    NULL,
    OPEN_EXISTING,
    FILE_FLAG_BACKUP_SEMANTICS,
    NULL);

#elif defined(_LINUX)
  m_Data->m_NotifyHandle = inotify_init();
  if(m_Data->m_NotifyHandle == -1)
  {
    printf("Error creating notofy handle\n");
  }
#endif

  m_NotifyThread = std::thread(&FileSystemWatcher::NotifyThread, this);
}

FileSystemWatcher::~FileSystemWatcher()
{
  m_ExitThread = true;

#ifdef _MSC_VER
  CancelIoEx(m_Data->m_DirectoryHandle, nullptr);
  CloseHandle(m_Data->m_DirectoryHandle);
#elif defined(_LINUX)
  close(m_Data->m_NotifyHandle);
#endif

  m_NotifyThread.join();
}

Optional<std::tuple<FileSystemOperation, std::string, std::string, std::time_t>> FileSystemWatcher::GetFileChange()
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

bool FileSystemWatcher::IsInvisibleFile(const std::string & filename)
{
  return filename.size() > 1 && filename[0] == '.' && filename[1] != '.';
}

bool FileSystemWatcher::IsInvisiblePath(const std::string & path)
{
  auto fs_path = fs::path(path);
  for(auto & sec : fs_path)
  {
    if(IsInvisibleFile(sec.string()))
    {
      return true;
    }
  }

  return false;
}

void FileSystemWatcher::IterateDirectory(const std::string & local_path, const std::string & root_dir, FileSystemDirectory & dir)
{
  auto full_path = JoinPath(root_dir, local_path);

#ifdef _LINUX

  auto actual_path = GetFullPath(full_path, root_dir);

  dir.m_NotifyWatch = inotify_add_watch(m_Data->m_NotifyHandle, actual_path.c_str(), IN_CREATE | IN_MODIFY | IN_DELETE);
  if(dir.m_NotifyWatch < 0)
  {
    printf("Error bad watch id returned (%s) %d\n", full_path.c_str(), errno);
  }
  else
  {
    m_Data->m_DirectoryLookup.emplace(std::make_pair(dir.m_NotifyWatch, local_path));
  }
#endif

  for (fs::directory_iterator dir_itr = fs::directory_iterator(full_path), end = fs::directory_iterator(); dir_itr != end; ++dir_itr)
  {
    auto info = dir_itr->status();
    auto itr_path = dir_itr->path();
    auto itr_filename = itr_path.filename().string();

    if(IsInvisibleFile(itr_filename))
    {
      continue;
    }

    if (fs::is_regular_file(info))
    {
      dir.m_Files.emplace(std::make_pair(itr_filename, GetLastWriteTime(itr_path.string().c_str())));
    }
    else if (fs::is_directory(info))
    {      
      auto sub_dir_local_path = local_path + itr_filename + "/";
      auto sub_dir_full_path = full_path + itr_filename + "/";

      auto sub_dir = std::make_unique<FileSystemDirectory>();
      sub_dir->m_Parent = &dir;

      IterateDirectory(sub_dir_local_path, root_dir, *sub_dir);

      dir.m_Directories.emplace(std::make_pair(itr_filename, std::move(sub_dir)));
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

Optional<std::pair<FileSystemDirectory *, FileSystemDirectory::FileIterator>> FileSystemWatcher::GetFileOrDirectoryAtPath(
  const char * path, FileSystemDirectory & base)
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

void FileSystemWatcher::TriggerOperationForFile(const std::string & filename, const std::string & path,
  FileSystemOperation op, std::time_t last_write)
{
  std::unique_lock<std::mutex> lock(m_QueueMutex);
  m_FilesChanged.emplace(std::make_tuple(op, path, filename, last_write));

  lock.unlock();

  m_Notify();
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

  m_Notify();

  while (m_ExitThread == false)
  {
#ifdef _LINUX

    fd_set rfds, errfds;
    FD_ZERO(&rfds); FD_ZERO(&errfds);
    FD_SET(m_Data->m_NotifyHandle, &rfds);
    FD_SET(m_Data->m_NotifyHandle, &errfds);

    timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 10000;
    auto num_fds = select(FD_SETSIZE, &rfds, NULL, &errfds, &tv);

    if(num_fds == 0)
    {
      continue;
    }

    char buffer[8092];
    auto result = read(m_Data->m_NotifyHandle, &buffer, sizeof(buffer));
    auto notify_info = reinterpret_cast<inotify_event *>(buffer);
    
    while(result > 0)
    {      
      bool is_file = (notify_info->mask & IN_ISDIR) == 0;
      
      auto itr = m_Data->m_DirectoryLookup.find(notify_info->wd);
      if(itr != m_Data->m_DirectoryLookup.end())
      {
        auto dir_path = itr->second;
        auto file_name = notify_info->name;

        auto local_file_path = dir_path + file_name;
        auto full_path = GetFullPath(local_file_path, m_RootPath);

        if (IsInvisiblePath(local_file_path) == false)
        {
          if (notify_info->mask & IN_CREATE)
          {
            if (is_file)
            {
              auto dir = GetDirectoryAtPath(dir_path.c_str(), m_RootDirectory);
              if (dir)
              {
                auto last_write = GetLastWriteTime(full_path.c_str());

                dir->m_Files.emplace(std::make_pair(file_name, last_write));
                TriggerOperationForFile(file_name, local_file_path, FileSystemOperation::kAdd, last_write);
              }
            }
            else
            {
              auto dir = GetDirectoryAtPath(dir_path.c_str(), m_RootDirectory);
              if (dir)
              {
                auto sub_dir = std::make_unique <FileSystemDirectory>();
                sub_dir->m_Parent = dir;

                auto sub_dir_path = local_file_path + "/";
                IterateDirectory(sub_dir_path.c_str(), m_RootPath.data(), *sub_dir);

                TriggerOperationForDirectoryFiles(*sub_dir, sub_dir_path, FileSystemOperation::kAdd);
                dir->m_Directories.emplace(std::make_pair(file_name, std::move(sub_dir)));

                m_Notify();
              }
            }

          }
          else if (notify_info->mask & IN_MODIFY)
          {
            auto dir = GetDirectoryAtPath(dir_path.data(), m_RootDirectory);
            if (is_file && dir)
            {
              auto itr = dir->m_Files.find(file_name);
              if (itr != dir->m_Files.end())
              {
                auto last_write = GetLastWriteTime(full_path.data());
                auto cached_last_write = itr->second;

                if (last_write > cached_last_write)
                {
                  itr->second = last_write;
                  TriggerOperationForFile(file_name, local_file_path, FileSystemOperation::kModify, last_write);

                  m_Notify();
                }
              }
            }
          }
          else if (notify_info->mask & IN_DELETE)
          {
            auto file_info = GetFileOrDirectoryAtPath(local_file_path.data(), m_RootDirectory);
            if (file_info)
            {
              auto dir = file_info->first;
              auto file_itr = file_info->second;

              if (file_itr != dir->m_Files.end())
              {
                dir->m_Files.erase(file_itr);
                TriggerOperationForFile(file_name, local_file_path, FileSystemOperation::kDelete, {});
              }
              else
              {
                TriggerOperationForDirectoryFiles(*dir, local_file_path, FileSystemOperation::kDelete);

                std::vector <FileSystemDirectory *> dead_dirs;
                dead_dirs.push_back(dir);

                while (dead_dirs.size() > 0)
                {
                  auto dead_dir = dead_dirs.back();
                  dead_dirs.pop_back();

                  inotify_rm_watch(m_Data->m_NotifyHandle, dead_dir->m_NotifyWatch);
                  m_Data->m_DirectoryLookup.erase(dead_dir->m_NotifyWatch);

                  for (auto & dead_sub_dir : dead_dir->m_Directories)
                  {
                    dead_dirs.push_back(dead_sub_dir.second.get());
                  }
                }

                if (dir->m_Parent)
                {
                  auto parent = dir->m_Parent;
                  auto dir_itr = parent->m_Directories.find(file_name);
                  if (dir_itr != parent->m_Directories.end())
                  {
                    parent->m_Directories.erase(dir_itr);
                  }
                }

                m_Notify();
              }
            }
          }
        }
      }

      result -= sizeof(inotify_event) + notify_info->len;
      notify_info++;
    }
#endif

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

        int size_needed = WideCharToMultiByte(CP_UTF8, 0, &filename[0], (int)filename.size(), nullptr, 0, nullptr, nullptr);
        std::string conv_filename(size_needed, 0);
        WideCharToMultiByte(CP_UTF8, 0, &filename[0], (int)filename.size(), &conv_filename[0], size_needed, nullptr, nullptr);

        std::string changed_filename("./" + conv_filename);
        std::string full_path = (fs::path(m_RootPath) / fs::path(conv_filename)).string();

        auto path = fs::path(changed_filename);
        auto status = fs::status(full_path);

        bool is_deleted = fs::exists(status) == false;
        bool is_file = fs::is_regular_file(status);

        if (IsInvisiblePath(changed_filename) == false)
        {
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
                auto last_write = GetLastWriteTime(full_path.c_str());

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

                m_Notify();
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
                  auto last_write = GetLastWriteTime(full_path.c_str());

                  if (last_write > itr->second)
                  {
                    itr->second = last_write;
                    TriggerOperationForFile(changed_filename, path.filename().string(), FileSystemOperation::kModify, last_write);

                    m_Notify();
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

                m_Notify();
              }
            }
          }
          break;
          }
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