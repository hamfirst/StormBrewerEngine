
#include "Runtime/RuntimeCommon.h"
#include "Runtime/Atlas/AtlasResource.h"
#include "Runtime/Atlas/AtlasDef.refl.meta.h"
#include "Runtime/Animation/AnimationState.h"

#include "StormRefl/StormReflJson.h"
#include "StormData/StormDataJson.h"

#include "Foundation/BasicTypes/BasicTypes.refl.meta.h"

#include <sb/vector.h>

Any CreateAtlasEngineData(AtlasDef & atlas);
void UpdateAtlasEngineData(Any & engine_data);
void RenderAtlas(Any & engine_data, RenderState & render_state, czstr name, const Box & position, const Color & color);

AtlasResource::AtlasResource(Any && load_data, uint32_t path_hash, czstr path) :
        DocumentResourceBase(std::move(load_data), path_hash, path)
{

}

NotNullPtr<AtlasDef> AtlasResource::GetData()
{
  return &m_Data;
}

AtlasLoadLink AtlasResource::AddLoadCallback(Delegate<void, NotNullPtr<AtlasResource>> && callback)
{
  if (m_Loaded)
  {
    callback(this);
  }

  return DocumentResourceLoadCallbackLink<AtlasDef, AtlasResource>(
          DocumentResourceReference<AtlasResource>(this), m_LoadCallbacks.AddDelegate(std::move(callback)));
}

void AtlasResource::AddLoadCallback(Delegate<void, NotNullPtr<AtlasResource>> && callback, DocumentResourceLoadCallbackLink<AtlasDef, AtlasResource> & load_link)
{
  load_link = DocumentResourceLoadCallbackLink<AtlasDef, AtlasResource>(
          DocumentResourceReference<AtlasResource>(this), m_LoadCallbacks.AddDelegate(callback));

  if (m_Loaded)
  {
    callback(this);
  }
}

AtlasPtr AtlasResource::Find(uint32_t file_path_hash)
{
  auto resource = FindDocumentResource(file_path_hash);
  if (resource)
  {
    auto p_this = static_cast<AtlasResource *>(resource);
    return AtlasPtr(DocumentResourceReference<AtlasResource>(p_this));
  }

  return {};
}

AtlasPtr AtlasResource::Load(czstr file_path)
{
  if(file_path == nullptr || file_path[0] == 0)
  {
    return {};
  }

  auto resource = LoadDocumentResource(file_path, [](Any && load_data, uint32_t path_hash, czstr path) -> std::unique_ptr<DocumentResourceBase>
  { return std::make_unique<AtlasResource>(std::move(load_data), path_hash, path); });
  auto p_this = static_cast<AtlasResource *>(resource);
  return AtlasPtr(DocumentResourceReference<AtlasResource>(p_this));
}

AtlasLoadLink AtlasResource::LoadWithCallback(czstr file_path, Delegate<void, NotNullPtr<AtlasResource>> && callback)
{
  if(file_path == nullptr || file_path[0] == 0)
  {
    return {};
  }

  auto resource = LoadDocumentResource(file_path, [](Any && load_data, uint32_t path_hash, czstr path) -> std::unique_ptr<DocumentResourceBase>
  { return std::make_unique<AtlasResource>(std::move(load_data), path_hash, path); });
  auto p_this = static_cast<AtlasResource *>(resource);

  return p_this->AddLoadCallback(std::move(callback));
}

void AtlasResource::LoadWithCallback(czstr file_path, Delegate<void, NotNullPtr<AtlasResource>> && callback, AtlasLoadLink & load_link)
{
  if(file_path == nullptr || file_path[0] == 0)
  {
    return;
  }

  auto resource = LoadDocumentResource(file_path, [](Any && load_data, uint32_t path_hash, czstr path) -> std::unique_ptr<DocumentResourceBase>
  { return std::make_unique<AtlasResource>(std::move(load_data), path_hash, path); });
  auto p_this = static_cast<AtlasResource *>(resource);

  p_this->AddLoadCallback(std::move(callback), load_link);
}

void AtlasResource::Render(RenderState & render_state, czstr name, const Box & pos, const Color & color)
{
  RenderAtlas(m_EngineData, render_state, name, pos, color);
}

void AtlasResource::Render(RenderState & render_state, czstr name, const Vector2 & pos, const Color & color)
{
  RenderAtlas(m_EngineData, render_state, name, Box::FromPoint(pos), color);
}

void AtlasResource::OnDataLoadComplete(const std::string & resource_data)
{
  StormReflParseJson(m_Data, resource_data.data());

  if (!m_EngineData)
  {
    m_EngineData = CreateAtlasEngineData(m_Data);
  }

  UpdateAtlasEngineData(m_EngineData);
  m_Loaded = true;
}

void AtlasResource::CallAssetLoadCallbacks()
{
  m_LoadCallbacks.Call(this);
}

