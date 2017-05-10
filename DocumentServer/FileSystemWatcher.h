#pragma once

#include <memory>
#include <mutex>
#include <thread>
#include <string>
#include <queue>
#include <unordered_map>
#include <chrono>

#include <StormSockets/StormSemaphore.h>

#include <Foundation/Optional/NullOpt.h>
#include <Foundation/Optional/Optional.h>

enum class FileSystemOperation
{
  kAdd,
  kModify,
  kDelete,
};

struct FileSystemWatcherData;

struct FileSystemDirectory
{
  std::unordered_map<std::string, std::chrono::system_clock::time_point> m_Files;
  std::unordered_map<std::string, std::unique_ptr<FileSystemDirectory>> m_Directories;

  FileSystemDirectory * m_Parent = nullptr;

  using FileIterator = std::unordered_map<std::string, std::chrono::system_clock::time_point>::iterator;
};

class FileSystemWatcher
{
public:
  FileSystemWatcher(StormSockets::StormSemaphore & semaphore);
  ~FileSystemWatcher();

  Optional<std::tuple<FileSystemOperation, std::string, std::string, std::chrono::system_clock::time_point>> GetFileChange();

private:

  void IterateDirectory(const std::string & path, FileSystemDirectory & dir);
  NullOptPtr<FileSystemDirectory> GetDirectoryAtPath(const char * path, FileSystemDirectory & base);
  Optional<std::pair<FileSystemDirectory *, FileSystemDirectory::FileIterator>> GetFileOrDirectoryAtPath(const char * path, FileSystemDirectory & base);

  void TriggerOperationForFile(const std::string & path, const std::string & filename, FileSystemOperation op, std::chrono::system_clock::time_point last_write);
  void TriggerOperationForDirectoryFiles(FileSystemDirectory & base, const std::string & base_path, FileSystemOperation op);

  void NotifyThread();

private:

  std::unique_ptr<FileSystemWatcherData> m_Data;

  FileSystemDirectory m_RootDirectory;

  StormSockets::StormSemaphore & m_Semaphore;

  std::mutex m_QueueMutex;
  std::thread m_NotifyThread;

  std::queue<std::tuple<FileSystemOperation, std::string, std::string, std::chrono::system_clock::time_point>> m_FilesChanged;

  bool m_ExitThread;
};
