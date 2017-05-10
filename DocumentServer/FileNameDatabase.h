#pragma once

#include "Foundation/Common.h"

#include <unordered_map>

struct FileNameInfo
{
  uint32_t m_ExtHash;
  uint32_t m_FileNameHash;
  std::string m_FileName;
  std::string m_FullPath;
};

class FileNameDatabase
{
public:
  void Insert(czstr file_path, czstr file_name);
  void Remove(czstr file_path, czstr file_name);

  std::vector<FileNameInfo> SearchForFiles(czstr partial_path, czstr extension);

private:

  uint16_t GetKeyForFileName(czstr file_path);

private:
  std::unordered_map<uint16_t, std::vector<FileNameInfo>> m_FileNameDatabase;
};


