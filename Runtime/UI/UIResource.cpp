
#include "Runtime/RuntimeCommon.h"
#include "Runtime/UI/UIResource.h"
#include "Runtime/UI/UIDef.refl.meta.h"

#include "StormData/StormDataJson.h"

#include <sb/vector.h>

UIResource::UIResource(Any && load_data, uint32_t path_hash) :
  DocumentResourceBase(std::move(load_data), path_hash)
{

}

NotNullPtr<UIDef> UIResource::GetData()
{
  return &m_Data;
}

DocumentResourceLoadCallbackLink<UIDef, UIResource> UIResource::AddLoadCallback(Delegate<void, NotNullPtr<UIResource>> && callback)
{
  if (m_Loaded)
  {
    callback(this);
  }

  return DocumentResourceLoadCallbackLink<UIDef, UIResource>(
    DocumentResourceReference<UIResource>(this), m_LoadCallbacks.AddDelegate(std::move(callback)));
}

UIResourcePtr UIResource::Find(uint32_t file_path_hash)
{
  auto resource = FindDocumentResource(file_path_hash);
  if (resource)
  {
    auto p_this = static_cast<UIResource *>(resource);
    return UIResourcePtr(DocumentResourceReference<UIResource>(p_this));
  }

  return {};
}

UIResourcePtr UIResource::Load(czstr file_path)
{
  auto resource = LoadDocumentResource(file_path,
    [](Any && load_data, uint32_t path_hash) -> std::unique_ptr<DocumentResourceBase> { return std::make_unique<UIResource>(std::move(load_data), path_hash); });
  auto p_this = static_cast<UIResource *>(resource);
  return UIResourcePtr(DocumentResourceReference<UIResource>(p_this));
}

DocumentResourceLoadCallbackLink<UIDef, UIResource> UIResource::LoadWithCallback(czstr file_path, Delegate<void, NotNullPtr<UIResource>> && callback)
{
  auto resource = LoadDocumentResource(file_path,
    [](Any && load_data, uint32_t path_hash) -> std::unique_ptr<DocumentResourceBase> { return std::make_unique<UIResource>(std::move(load_data), path_hash); });
  auto p_this = static_cast<UIResource *>(resource);

  return p_this->AddLoadCallback(std::move(callback));
}

void UIResource::OnDataLoadComplete(const std::string & resource_data)
{
  StormReflParseJson(m_Data, resource_data.data());
  m_Loaded = true;
}

void UIResource::CallAssetLoadCallbacks()
{
  m_LoadCallbacks.Call(this);
}

