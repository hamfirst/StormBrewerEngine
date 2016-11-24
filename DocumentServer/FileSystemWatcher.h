#pragma once

#include <memory>
#include <mutex>
#include <thread>
#include <string>
#include <queue>

#include <StormSockets/StormSemaphore.h>

#include <Foundation/Optional/Optional.h>

enum class FileSystemOperation
{
  kModify,
  kDelete,
};

struct FileSystemWatcherData;

class FileSystemWatcher
{
public:
  FileSystemWatcher(StormSockets::StormSemaphore & semaphore);
  ~FileSystemWatcher();

  Optional<std::pair<FileSystemOperation, std::string>> GetFileChange();

private:
  void NotifyThread();

private:

  std::unique_ptr<FileSystemWatcherData> m_Data;
  StormSockets::StormSemaphore & m_Semaphore;

  std::mutex m_QueueMutex;
  std::thread m_NotifyThread;

  std::queue<std::pair<FileSystemOperation, std::string>> m_FilesChanged;

  bool m_ExitThread;
};
