
#include "FileNameDatabase.h"

#include <hash/Hash.h>
#include <sb/vector.h>

void FileNameDatabase::Insert(czstr file_path, czstr file_name)
{
  FileNameInfo file_info;

  const char * ext = "";
  const char * fsearch = file_name;
  while (true)
  {
    auto slash = strchr(fsearch, '/');
    if (slash)
    {
      fsearch = slash + 1;
    }
    else
    {
      break;
    }
  }

  while (true)
  {
    auto period = strchr(fsearch, '.');
    if (period)
    {
      ext = period + 1;
      fsearch = period + 1;
    }
    else
    {
      break;
    }
  }

  file_info.m_ExtHash = crc32(ext);
  file_info.m_FileNameHash = crc32lowercase(file_path);
  file_info.m_FileName = file_name;
  file_info.m_FullPath = file_path;

  auto key = GetKeyForFileName(file_path);

  auto itr = m_FileNameDatabase.find(key);
  if (itr != m_FileNameDatabase.end())
  {
    itr->second.emplace_back(std::move(file_info));
  }
  else
  {
    m_FileNameDatabase.emplace(std::make_pair(key, std::vector<FileNameInfo> { std::move(file_info) }));
  }
}

void FileNameDatabase::Remove(czstr file_path, czstr file_name)
{
  auto file_path_hash = crc32lowercase(file_path);
  auto key = GetKeyForFileName(file_path);

  auto itr = m_FileNameDatabase.find(key);
  if (itr != m_FileNameDatabase.end())
  {
    for (std::size_t index = 0, len = itr->second.size(); index < len; index++)
    {
      if (itr->second[index].m_FileNameHash == file_path_hash)
      {
        vremove_index_quick(itr->second, index);
        return;
      }
    }
  }
}

std::vector<FileNameInfo> FileNameDatabase::SearchForFiles(czstr partial_path, czstr extension)
{
  std::vector<FileNameInfo> file_list;

  if (strlen(partial_path) == 0)
  {
    return file_list;
  }

  auto ext_hash = crc32lowercase(extension);

  auto key = GetKeyForFileName(partial_path);

  auto itr = m_FileNameDatabase.find(key);
  if (itr != m_FileNameDatabase.end())
  {
    for (auto & elem : itr->second)
    {
      bool match = true;
      auto path_check = partial_path;

      for (auto c : elem.m_FullPath)
      {
        if (c != *path_check)
        {
          match = false;
          break;
        }

        if (*path_check == 0)
        {
          break;
        }

        path_check++;
      }

      if (match)
      {
        file_list.emplace_back(elem);
      }
    }
  }

  return file_list;
}

uint16_t FileNameDatabase::GetKeyForFileName(czstr file_path)
{
  if (file_path[0] == 0)
  {
    return 0;
  }

  char lower_key[2];
  lower_key[0] = tolower(file_path[0]);
  lower_key[1] = tolower(file_path[1]);

  uint16_t * key = (uint16_t *)lower_key;
  return *key;
}
