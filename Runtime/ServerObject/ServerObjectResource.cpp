
#include "Runtime/RuntimeCommon.h"
#include "Runtime/ServerObject/ServerObjectResource.h"
#include "Runtime/ServerObject/ServerObjectDef.refl.meta.h"

#include "StormData/StormDataJson.h"

#include <sb/vector.h>

ServerObjectResource::ServerObjectResource(Any && load_data, uint32_t path_hash, czstr path) :
  DocumentResourceBase(std::move(load_data), path_hash, path)
{

}

NotNullPtr<ServerObjectDef> ServerObjectResource::GetData()
{
  return &m_Data;
}

ServerObjectLoadLink ServerObjectResource::AddLoadCallback(Delegate<void, NotNullPtr<ServerObjectResource>> && callback)
{
  if (m_Loaded)
  {
    callback(this);
  }

  return DocumentResourceLoadCallbackLink<ServerObjectDef, ServerObjectResource>(
    DocumentResourceReference<ServerObjectResource>(this), m_LoadCallbacks.AddDelegate(std::move(callback)));
}

void ServerObjectResource::AddLoadCallback(Delegate<void, NotNullPtr<ServerObjectResource>> && callback, ServerObjectLoadLink & link)
{
  link = DocumentResourceLoadCallbackLink<ServerObjectDef, ServerObjectResource>(
    DocumentResourceReference<ServerObjectResource>(this), m_LoadCallbacks.AddDelegate(callback));

  if (m_Loaded)
  {
    callback(this);
  }
}

ServerObjectResourcePtr ServerObjectResource::Find(uint32_t file_path_hash)
{
  auto resource = FindDocumentResource(file_path_hash);
  if (resource)
  {
    auto p_this = static_cast<ServerObjectResource *>(resource);
    return ServerObjectResourcePtr(DocumentResourceReference<ServerObjectResource>(p_this));
  }

  return {};
}

ServerObjectResourcePtr ServerObjectResource::Load(czstr file_path)
{
  auto resource = LoadDocumentResource(file_path, [](Any && load_data, uint32_t path_hash, czstr path) -> std::unique_ptr<DocumentResourceBase>
          { return std::make_unique<ServerObjectResource>(std::move(load_data), path_hash, path); });
  auto p_this = static_cast<ServerObjectResource *>(resource);
  return ServerObjectResourcePtr(DocumentResourceReference<ServerObjectResource>(p_this));
}

ServerObjectLoadLink ServerObjectResource::LoadWithCallback(czstr file_path, Delegate<void, NotNullPtr<ServerObjectResource>> && callback)
{
  auto resource = LoadDocumentResource(file_path, [](Any && load_data, uint32_t path_hash, czstr path) -> std::unique_ptr<DocumentResourceBase>
          { return std::make_unique<ServerObjectResource>(std::move(load_data), path_hash, path); });
  auto p_this = static_cast<ServerObjectResource *>(resource);

  return p_this->AddLoadCallback(std::move(callback));
}

void ServerObjectResource::LoadWithCallback(czstr file_path, Delegate<void, NotNullPtr<ServerObjectResource>> && callback, ServerObjectLoadLink & link)
{
  auto resource = LoadDocumentResource(file_path, [](Any && load_data, uint32_t path_hash, czstr path) -> std::unique_ptr<DocumentResourceBase>
          { return std::make_unique<ServerObjectResource>(std::move(load_data), path_hash, path); });
  auto p_this = static_cast<ServerObjectResource *>(resource);

  p_this->AddLoadCallback(std::move(callback), link);
}

void ServerObjectResource::OnDataLoadComplete(const std::string & resource_data)
{
  StormReflParseJson(m_Data, resource_data.data());
  m_Loaded = true;
}

void ServerObjectResource::CallAssetLoadCallbacks()
{
  m_LoadCallbacks.Call(this);
}

