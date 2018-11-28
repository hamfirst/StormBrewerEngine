
#include "Engine/EngineCommon.h"
#include "Engine/Asset/BinaryAssetLoader.h"
#include "Engine/Asset/BinaryAsset.h"

BinaryAssetLoader g_BinaryAssetLoader;
BinaryResourceLoader * g_BinaryResourceLoader = &g_BinaryAssetLoader;

Any BinaryAssetLoader::LoadResource(czstr path, BinaryResourceLoaderCallback load_callback, void * user_ptr)
{
  auto del = BinaryAsset::LoadCallback([load_callback, user_ptr, path_hash = crc32lowercase(path)](NullOptPtr<BinaryAsset> asset)
  {
    load_callback(path_hash, asset->IsLoaded() ? asset->GetAssetData() : nullptr, asset->IsLoaded() ? asset->GetAssetLength() : 0, user_ptr);
  });

  return Any(BinaryAsset::LoadWithCallback(path, std::move(del)));
}

void BinaryAssetLoader::UnloadResource(uint32_t path_hash, Any && load_data)
{
  load_data.Clear();
}
