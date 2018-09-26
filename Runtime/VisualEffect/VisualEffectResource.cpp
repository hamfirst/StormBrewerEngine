
#include "Runtime/RuntimeCommon.h"
#include "Runtime/VisualEffect/VisualEffectResource.h"
#include "Runtime/VisualEffect/VisualEffectDef.refl.meta.h"

#include "StormData/StormDataJson.h"

#include <sb/vector.h>

Any CreateVisualEffectEngineData(VisualEffectDef & visual_effect);

VisualEffectResource::VisualEffectResource(Any && load_data, uint32_t path_hash) :
  DocumentResourceBase(std::move(load_data), path_hash)
{

}

NotNullPtr<VisualEffectDef> VisualEffectResource::GetData()
{
  return &m_Data;
}

DocumentResourceLoadCallbackLink<VisualEffectDef, VisualEffectResource> VisualEffectResource::AddLoadCallback(Delegate<void, NotNullPtr<VisualEffectResource>> && callback)
{
  if (m_Loaded)
  {
    callback(this);
  }

  return DocumentResourceLoadCallbackLink<VisualEffectDef, VisualEffectResource>(
    DocumentResourceReference<VisualEffectResource>(this), m_LoadCallbacks.AddDelegate(std::move(callback)));
}

VisualEffectResourcePtr VisualEffectResource::Find(uint32_t file_path_hash)
{
  auto resource = FindDocumentResource(file_path_hash);
  if (resource)
  {
    auto p_this = static_cast<VisualEffectResource *>(resource);
    return VisualEffectResourcePtr(DocumentResourceReference<VisualEffectResource>(p_this));
  }

  return {};
}

VisualEffectResourcePtr VisualEffectResource::Load(czstr file_path)
{
  if(file_path == nullptr || file_path[0] == 0)
  {
    return {};
  }

  auto resource = LoadDocumentResource(file_path,
    [](Any && load_data, uint32_t path_hash) -> std::unique_ptr<DocumentResourceBase> { return std::make_unique<VisualEffectResource>(std::move(load_data), path_hash); });
  auto p_this = static_cast<VisualEffectResource *>(resource);
  return VisualEffectResourcePtr(DocumentResourceReference<VisualEffectResource>(p_this));
}

DocumentResourceLoadCallbackLink<VisualEffectDef, VisualEffectResource> VisualEffectResource::LoadWithCallback(czstr file_path, Delegate<void, NotNullPtr<VisualEffectResource>> && callback)
{
  if(file_path == nullptr || file_path[0] == 0)
  {
    return {};
  }

  auto resource = LoadDocumentResource(file_path,
    [](Any && load_data, uint32_t path_hash) -> std::unique_ptr<DocumentResourceBase> { return std::make_unique<VisualEffectResource>(std::move(load_data), path_hash); });
  auto p_this = static_cast<VisualEffectResource *>(resource);

  return p_this->AddLoadCallback(std::move(callback));
}

void VisualEffectResource::OnDataLoadComplete(const std::string & resource_data)
{
  StormReflParseJson(m_Data, resource_data.data());

  m_EngineData = CreateVisualEffectEngineData(m_Data);
  m_Loaded = true;
}

void VisualEffectResource::CallAssetLoadCallbacks()
{
  m_LoadCallbacks.Call(this);
}

