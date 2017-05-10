
#include "Runtime/RuntimeCommon.h"
#include "Runtime/Map/MapResource.h"
#include "Runtime/Map/MapDef.refl.meta.h"
#include "Runtime/Map/MapTileJson.h"
#include "Runtime/Animation/AnimationState.h"

#include "StormData/StormDataJson.h"

#include <sb/vector.h>

MapResource::MapResource(Any && load_data, uint64_t path_hash) :
  DocumentResourceBase(std::move(load_data), path_hash)
{

}

NotNullPtr<MapDef> MapResource::GetData()
{
  return &m_Data;
}

DocumentResourceLoadCallbackLink<MapDef, MapResource> MapResource::AddLoadCallback(Delegate<void, NotNullPtr<MapResource>> && callback)
{
  if (m_Loaded)
  {
    callback(this);
  }

  return DocumentResourceLoadCallbackLink<MapDef, MapResource>(
    DocumentResourceReference<MapResource>(this), m_LoadCallbacks.AddDelegate(std::move(callback)));
}

Map MapResource::Load(czstr file_path)
{
  auto resource = LoadDocumentResource(file_path,
    [](Any && load_data, uint64_t path_hash) -> std::unique_ptr<DocumentResourceBase> { return std::make_unique<MapResource>(std::move(load_data), path_hash); });
  auto p_this = static_cast<MapResource *>(resource);
  return Map(DocumentResourceReference<MapResource>(p_this));
}

MapLoadLink MapResource::LoadWithCallback(czstr file_path, Delegate<void, NotNullPtr<MapResource>> && callback)
{
  auto resource = LoadDocumentResource(file_path,
    [](Any && load_data, uint64_t path_hash) -> std::unique_ptr<DocumentResourceBase> { return std::make_unique<MapResource>(std::move(load_data), path_hash); });
  auto p_this = static_cast<MapResource *>(resource);

  return p_this->AddLoadCallback(std::move(callback));
}

void MapResource::OnDataLoadComplete(const std::string & resource_data)
{
  StormReflParseJson(m_Data, resource_data.data());
  m_Loaded = true;
}

void MapResource::CallAssetLoadCallbacks()
{
  m_LoadCallbacks.Call(this);
}

