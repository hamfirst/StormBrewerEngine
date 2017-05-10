
#include "Engine/EngineCommon.h"
#include "Engine/Asset/DocumentAssetLoader.h"
#include "Engine/Asset/DocumentAsset.h"

DocumentAssetLoader g_DocumentAssetLoader;
DocumentResourceLoader * g_ResourceLoader = &g_DocumentAssetLoader;

Any DocumentAssetLoader::LoadResource(czstr path, DocumentResourceLoaderCallback load_callback, void * user_ptr)
{
  auto del = DocumentAsset::LoadCallback([load_callback, user_ptr, path_hash = crc64(path)](NullOptPtr<DocumentAsset> asset) 
  {
    load_callback(path_hash, asset->IsLoaded() ? &asset->GetAssetData() : nullptr, user_ptr);
  });

  return Any(DocumentAsset::LoadWithCallback(path, std::move(del)));
}

void DocumentAssetLoader::UnloadResource(uint64_t path_hash, Any && load_data)
{
  load_data.Clear();
}
