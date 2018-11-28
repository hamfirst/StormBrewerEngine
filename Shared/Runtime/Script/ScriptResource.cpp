
#include "Runtime/RuntimeCommon.h"
#include "Runtime/Script/ScriptResource.h"

#include "StormData/StormDataJson.h"

#include <sb/vector.h>

ScriptResource::ScriptResource(Any && load_data, uint32_t path_hash, czstr path) :
        BinaryResourceBase(std::move(load_data), path_hash, path)
{

}

BinaryResourceLoadCallbackLink<ScriptResource> ScriptResource::AddLoadCallback(Delegate<void, NotNullPtr<ScriptResource>> && callback)
{
  if (m_Loaded)
  {
    callback(this);
  }

  return BinaryResourceLoadCallbackLink<ScriptResource>(
          BinaryResourceReference<ScriptResource>(this), m_LoadCallbacks.AddDelegate(std::move(callback)));
}

ScriptResourcePtr ScriptResource::Find(uint32_t file_path_hash)
{
  auto resource = FindBinaryResource(file_path_hash);
  if (resource)
  {
    auto p_this = static_cast<ScriptResource *>(resource);
    return ScriptResourcePtr(BinaryResourceReference<ScriptResource>(p_this));
  }

  return {};
}

ScriptResourcePtr ScriptResource::Load(czstr file_path)
{
  if(file_path == nullptr || file_path[0] == 0)
  {
    return {};
  }

  auto resource = LoadBinaryResource(file_path, [](Any && load_data, uint32_t path_hash, czstr path) -> std::unique_ptr<BinaryResourceBase>
  { return std::make_unique<ScriptResource>(std::move(load_data), path_hash, path); });
  auto p_this = static_cast<ScriptResource *>(resource);
  return ScriptResourcePtr(BinaryResourceReference<ScriptResource>(p_this));
}

BinaryResourceLoadCallbackLink<ScriptResource> ScriptResource::LoadWithCallback(czstr file_path, Delegate<void, NotNullPtr<ScriptResource>> && callback)
{
  if(file_path == nullptr || file_path[0] == 0)
  {
    return {};
  }

  auto resource = LoadBinaryResource(file_path, [](Any && load_data, uint32_t path_hash, czstr path) -> std::unique_ptr<BinaryResourceBase>
  { return std::make_unique<ScriptResource>(std::move(load_data), path_hash, path); });
  auto p_this = static_cast<ScriptResource *>(resource);

  return p_this->AddLoadCallback(std::move(callback));
}

void ScriptResource::OnDataLoadComplete(const void * data, std::size_t length)
{
  m_ScriptData = std::string_view(static_cast<const char *>(data), length);
  m_Loaded = true;
}

void ScriptResource::CallAssetLoadCallbacks()
{
  m_LoadCallbacks.Call(this);
}

