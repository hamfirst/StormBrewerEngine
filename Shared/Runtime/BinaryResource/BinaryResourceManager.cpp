
#include "Foundation/FileSystem/Path.h"

#include "Runtime/RuntimeCommon.h"
#include "Runtime/BinaryResource/BinaryResourceManager.h"

extern BinaryResourceLoader * g_BinaryResourceLoader;
BinaryResourceManager g_BinaryResourceManager;

BinaryResourceManager::BinaryResourceManager() :
  m_PendingBinaryLoad(0)
{

}

BinaryResourceManager::~BinaryResourceManager()
{
  ASSERT(m_BinaryResources.size() == 0, "Not all binary resources have unloaded properly");
}

NullOptPtr<BinaryResourceBase> BinaryResourceManager::FindBinaryResource(uint32_t file_path_hash)
{
  auto itr = m_BinaryResources.find(file_path_hash);
  if (itr != m_BinaryResources.end())
  {
    return itr->second.get();
  }

  return nullptr;
}

NotNullPtr<BinaryResourceBase> BinaryResourceManager::LoadBinaryResource(czstr file_path,
        std::unique_ptr<BinaryResourceBase>(*ResourceCreator)(Any &&, uint32_t, czstr))
{
  uint32_t path_hash = crc32lowercase(file_path);

  auto itr = m_BinaryResources.find(path_hash);
  if (itr == m_BinaryResources.end())
  {
    m_PendingBinaryLoad = path_hash;
    m_PendingBinaryLoaded = false;

    auto load_data = g_BinaryResourceLoader->LoadResource(file_path,
      [](uint32_t path_hash, const void * data, std::size_t length, void * user_ptr)
      { 
        auto p_this = static_cast<BinaryResourceManager *>(user_ptr);
        p_this->HandleResourceLoadResult(path_hash, data, length);
      }, this);

    auto resource = ResourceCreator(std::move(load_data), path_hash, file_path);
    resource->m_ResourceManager = this;

    auto result = m_BinaryResources.emplace(std::make_pair(path_hash, std::move(resource)));

    m_PendingBinaryLoad = 0;
    if (m_PendingBinaryLoaded)
    {
      HandleResourceLoadResult(path_hash, m_PendingBinaryData, m_PendingBinaryLength);
      m_PendingBinaryData = nullptr;
    }

    return result.first->second.get();
  }
  else
  {
    return itr->second.get();
  }
}

void BinaryResourceManager::HandleResourceLoadResult(uint32_t path_hash, const void * data, std::size_t length)
{
  if (path_hash == m_PendingBinaryLoad)
  {
    m_PendingBinaryData = data;
    m_PendingBinaryLength = length;

    m_PendingBinaryLoaded = true;
    return;
  }

  auto itr = m_BinaryResources.find(path_hash);
  if (itr == m_BinaryResources.end())
  {
    return;
  }

  itr->second->OnDataLoadComplete(data, length);
  itr->second->CallAssetLoadCallbacks();
}

void BinaryResourceManager::DestroyBinary(uint32_t path_hash)
{
  auto itr = m_BinaryResources.find(path_hash);
  if (itr == m_BinaryResources.end())
  {
    ASSERT(false, "Could not find binary to destroy");
    return;
  }

  g_BinaryResourceLoader->UnloadResource(path_hash, std::move(itr->second->m_LoadData));
  m_BinaryResources.erase(itr);
}
