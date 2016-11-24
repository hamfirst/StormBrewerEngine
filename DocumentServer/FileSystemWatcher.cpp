
#include "FileSystemWatcher.h"

#ifdef _MSC_VER

#include <Windows.h>

#include <codecvt>

struct FileSystemWatcherData
{
  HANDLE m_DirectoryHandle;
};

#endif

FileSystemWatcher::FileSystemWatcher(StormSockets::StormSemaphore & semaphore) :
  m_Data(std::make_unique<FileSystemWatcherData>()),
  m_Semaphore(semaphore),
  m_ExitThread(false)
{
#ifdef _MSC_VER
  m_Data->m_DirectoryHandle = CreateFile(
    ".",
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

Optional<std::pair<FileSystemOperation, std::string>> FileSystemWatcher::GetFileChange()
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

void FileSystemWatcher::NotifyThread()
{
  std::string last_change;
  uint32_t last_change_time = 0;

  while (m_ExitThread == false)
  {
#ifdef _MSC_VER
    char buffer[8092] = {};

    FILE_NOTIFY_INFORMATION * notify_info = reinterpret_cast<FILE_NOTIFY_INFORMATION *>(buffer);
    DWORD bytes_returned = 0;

    DWORD flags = FILE_NOTIFY_CHANGE_ATTRIBUTES | FILE_NOTIFY_CHANGE_CREATION | FILE_NOTIFY_CHANGE_FILE_NAME;

    if(ReadDirectoryChangesW(m_Data->m_DirectoryHandle, notify_info, sizeof(buffer), true, flags, &bytes_returned, nullptr, nullptr))
    {
      FILE_NOTIFY_INFORMATION * notification = notify_info;
      while (notification)
      {
        std::wstring filename(notification->FileName, notification->FileName + (notification->FileNameLength / 2));
        std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;

        std::string changed_filename(conv.to_bytes(filename));

        bool is_deleted = GetFileAttributes(changed_filename.data()) == INVALID_FILE_ATTRIBUTES;
        bool is_file = (GetFileAttributes(changed_filename.data()) & FILE_ATTRIBUTE_DIRECTORY) == 0;

        if (is_deleted || is_file)
        {
          uint32_t cur_time = GetTickCount();
          if (last_change != changed_filename || cur_time - last_change_time > 5)
          {
            last_change = changed_filename;
            last_change_time = cur_time;

            FileSystemOperation operation = is_deleted ? FileSystemOperation::kDelete : FileSystemOperation::kModify;

            std::unique_lock<std::mutex> lock(m_QueueMutex);
            m_FilesChanged.emplace(std::make_pair(operation, std::move(changed_filename)));
            lock.unlock();

            m_Semaphore.Release();
          }
        }

        notification = notification->NextEntryOffset == 0 ? nullptr :
          reinterpret_cast<FILE_NOTIFY_INFORMATION *>(reinterpret_cast<uint8_t *>(notification) + notification->NextEntryOffset);
      }
    }
#endif
  }
}