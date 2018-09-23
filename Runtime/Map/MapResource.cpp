
#include "Runtime/RuntimeCommon.h"
#include "Runtime/Map/MapResource.h"
#include "Runtime/Map/MapDef.refl.meta.h"
#include "Runtime/Map/MapTileJson.h"
#include "Runtime/Animation/AnimationState.h"

#include "StormData/StormDataJson.h"

#include <sb/vector.h>

MapResource::MapResource(Any && load_data, uint32_t path_hash) :
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

Map MapResource::Find(uint32_t file_path_hash)
{
  auto resource = FindDocumentResource(file_path_hash);
  if (resource)
  {
    auto p_this = static_cast<MapResource *>(resource);
    return Map(DocumentResourceReference<MapResource>(p_this));
  }

  return {};
}

Map MapResource::Load(czstr file_path)
{
  auto resource = LoadDocumentResource(file_path,
    [](Any && load_data, uint32_t path_hash) -> std::unique_ptr<DocumentResourceBase> { return std::make_unique<MapResource>(std::move(load_data), path_hash); });
  auto p_this = static_cast<MapResource *>(resource);
  return Map(DocumentResourceReference<MapResource>(p_this));
}

MapLoadLink MapResource::LoadWithCallback(czstr file_path, Delegate<void, NotNullPtr<MapResource>> && callback)
{
  auto resource = LoadDocumentResource(file_path,
    [](Any && load_data, uint32_t path_hash) -> std::unique_ptr<DocumentResourceBase> { return std::make_unique<MapResource>(std::move(load_data), path_hash); });
  auto p_this = static_cast<MapResource *>(resource);

  return p_this->AddLoadCallback(std::move(callback));
}

void MapResource::OnDataLoadComplete(const std::string & resource_data)
{
  StormReflParseJson(m_Data, resource_data.data());

  for(auto elem : m_Data.m_Anchors)
  {
    if(elem.second.m_GUID == 0U)
    {
      elem.second.m_GUID = GetRandomNumber();
    }
  }

  for(auto elem : m_Data.m_Paths)
  {
    if(elem.second.m_GUID == 0U)
    {
      elem.second.m_GUID = GetRandomNumber();
    }
  }

  for(auto elem : m_Data.m_Volumes)
  {
    if(elem.second.m_GUID == 0U)
    {
      elem.second.m_GUID = GetRandomNumber();
    }
  }

  for(auto layer : m_Data.m_EntityLayers)
  {
    for(auto elem : layer.second.m_Entities)
    {
      if (elem.second.m_GUID == 0U)
      {
        elem.second.m_GUID = GetRandomNumber();
      }
    }
  }

  for(auto layer : m_Data.m_ServerObjectLayers)
  {
    for(auto elem : layer.second.m_Objects)
    {
      if (elem.second.m_GUID == 0U)
      {
        elem.second.m_GUID = GetRandomNumber();
      }
    }
  }

  m_Loaded = true;
}

void MapResource::CallAssetLoadCallbacks()
{
  m_LoadCallbacks.Call(this);
}

