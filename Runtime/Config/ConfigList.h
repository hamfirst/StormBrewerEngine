#pragma once

#include "Foundation/FileSystem/Directory.h"
#include "Foundation/FileSystem/Path.h"

#include "Runtime/RuntimeCommon.h"
#include "Runtime/GenericResource/GenericResource.h"

template <typename ConfigType>
class ConfigList
{
public:
  void LoadFromDirectory(czstr directory_path, czstr extension, bool load_deps = true)
  {
    auto files = GetFilesInDirectory(directory_path);

    for (auto & elem : files)
    {
      if (GetFileExtensionForCanonicalPath(elem) == extension)
      {
        m_Configs.emplace_back(GenericResource<ConfigType>::Load(elem, load_deps));
      }
    }
  }

  bool IsLoaded() const
  {
    for (auto & elem : m_Configs)
    {
      if (elem.IsLoaded() == false)
      {
        return false;
      }
    }

    return true;
  }

  std::size_t GetNumConfigs()
  {
    return m_Configs.size();
  }

  int GetConfigIndex(czstr canonical_path)
  {
    auto hash = crc64(canonical_path);

    for (std::size_t index = 0, end = m_Configs.size(); index < end; ++index)
    {
      if (m_Configs[index].GetFileNameHash() == hash)
      {
        return (int)index;
      }
    }

    return -1;
  }

private:

  std::vector<GenericResourcePtr<ConfigType>> m_Configs;
};
