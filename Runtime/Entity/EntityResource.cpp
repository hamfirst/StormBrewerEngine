
#include "Runtime/RuntimeCommon.h"
#include "Runtime/Entity/EntityResource.h"
#include "Runtime/Entity/EntityDef.refl.meta.h"

#include "StormData/StormDataJson.h"

#include <sb/vector.h>

EntityResource::EntityResource(Any && load_data, uint64_t path_hash) :
  DocumentResourceBase(std::move(load_data), path_hash)
{

}

NotNullPtr<EntityDef> EntityResource::GetData()
{
  return &m_Data;
}

DocumentResourceLoadCallbackLink<EntityDef, EntityResource> EntityResource::AddLoadCallback(Delegate<void, NotNullPtr<EntityResource>> && callback)
{
  if (m_Loaded)
  {
    callback(this);
  }

  return DocumentResourceLoadCallbackLink<EntityDef, EntityResource>(
    DocumentResourceReference<EntityResource>(this), m_LoadCallbacks.AddDelegate(std::move(callback)));
}

EntityResourcePtr EntityResource::Load(czstr file_path)
{
  auto resource = LoadDocumentResource(file_path,
    [](Any && load_data, uint64_t path_hash) -> std::unique_ptr<DocumentResourceBase> { return std::make_unique<EntityResource>(std::move(load_data), path_hash); });
  auto p_this = static_cast<EntityResource *>(resource);
  return EntityResourcePtr(DocumentResourceReference<EntityResource>(p_this));
}

DocumentResourceLoadCallbackLink<EntityDef, EntityResource> EntityResource::LoadWithCallback(czstr file_path, Delegate<void, NotNullPtr<EntityResource>> && callback)
{
  auto resource = LoadDocumentResource(file_path,
    [](Any && load_data, uint64_t path_hash) -> std::unique_ptr<DocumentResourceBase> { return std::make_unique<EntityResource>(std::move(load_data), path_hash); });
  auto p_this = static_cast<EntityResource *>(resource);

  return p_this->AddLoadCallback(std::move(callback));
}

const SpritePtr & EntityResource::GetSprite() const
{
  return m_Sprite;
}

void EntityResource::OnDataLoadComplete(const std::string & resource_data)
{
  StormReflParseJson(m_Data, resource_data.data());

  if (m_Data.m_Sprite.length() > 0)
  {
    m_Sprite = SpriteResource::Load(m_Data.m_Sprite.data());
  }
  else
  {
    m_Sprite = {};
  }

  m_Loaded = true;
}

void EntityResource::CallAssetLoadCallbacks()
{
  m_LoadCallbacks.Call(this);
}

