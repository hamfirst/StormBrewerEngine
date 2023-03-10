#pragma once

#include <memory>
#include <mutex>
#include <thread>
#include <string>
#include <queue>
#include <unordered_map>
#include <chrono>
#include <filesystem>

#include "Foundation/Optional/NullOpt.h"
#include "Foundation/Optional/Optional.h"
#include "Foundation/Thread/Semaphore.h"

enum class FileSystemOperation
{
  kAdd,
  kModify,
  kDelete,
};

struct FileSystemWatcherData;

struct FileSystemDirectory
{
  std::unordered_map<std::string, std::time_t> m_Files;
  std::unordered_map<std::string, std::unique_ptr<FileSystemDirectory>> m_Directories;

  FileSystemDirectory * m_Parent = nullptr;

#ifdef _LINUX
  int m_NotifyWatch;
#endif

  using FileIterator = std::unordered_map<std::string, std::time_t>::iterator;
};

class FileSystemWatcher
{
public:
  FileSystemWatcher(const std::string & root_path, Delegate<void> && notify);
  ~FileSystemWatcher();

  Optional<std::tuple<FileSystemOperation, std::string, std::string, std::time_t>> GetFileChange();

private:

  bool IsInvisibleFile(const std::string & filename);
  bool IsInvisiblePath(const std::string & path);

  void IterateDirectory(const std::string & local_path, const std::string & full_path, FileSystemDirectory & dir);
  NullOptPtr<FileSystemDirectory> GetDirectoryAtPath(const char * path, FileSystemDirectory & base);
  Optional<std::pair<FileSystemDirectory *, FileSystemDirectory::FileIterator>> GetFileOrDirectoryAtPath(const char * path, FileSystemDirectory & base);

  void TriggerOperationForFile(const std::string & filename, const std::string & path, FileSystemOperation op, std::time_t last_write);
  void TriggerOperationForDirectoryFiles(FileSystemDirectory & base, const std::string & base_path, FileSystemOperation op);

  void NotifyThread();

private:

  std::unique_ptr<FileSystemWatcherData> m_Data;

  std::string m_RootPath;
  FileSystemDirectory m_RootDirectory;

  Delegate<void> m_Notify;

  std::mutex m_QueueMutex;
  std::thread m_NotifyThread;

  std::queue<std::tuple<FileSystemOperation, std::string, std::string, std::time_t>> m_FilesChanged;

  bool m_ExitThread;
};
