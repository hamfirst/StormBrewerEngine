
#include "Runtime/RuntimeCommon.h"
#include "Runtime/BinaryResource/GenericBinaryResource.h"

GenericBinaryResource::GenericBinaryResource(Any && load_data, uint32_t path_hash, czstr path) :
        BinaryResourceBase(std::move(load_data), path_hash, path)
{

}

const void * GenericBinaryResource::GetData() const
{
  return m_Data;
}

std::size_t GenericBinaryResource::GetLength() const
{
  return m_Length;
}

GenericBinaryResourceLoadLink GenericBinaryResource::AddLoadCallback(Delegate<void, NotNullPtr<GenericBinaryResource>> && callback)
{
  if (m_Loaded)
  {
    callback(this);
  }

  return BinaryResourceLoadCallbackLink<GenericBinaryResource>(
          BinaryResourceReference<GenericBinaryResource>(this), m_LoadCallbacks.AddDelegate(std::move(callback)));
}

void GenericBinaryResource::AddLoadCallback(Delegate<void, NotNullPtr<GenericBinaryResource>> && callback, BinaryResourceLoadCallbackLink<GenericBinaryResource> & load_link)
{
  load_link = BinaryResourceLoadCallbackLink<GenericBinaryResource>(
          BinaryResourceReference<GenericBinaryResource>(this), m_LoadCallbacks.AddDelegate(callback));

  if (m_Loaded)
  {
    callback(this);
  }
}

GenericBinaryResourcePtr GenericBinaryResource::Find(uint32_t file_path_hash)
{
  auto resource = FindBinaryResource(file_path_hash);
  if (resource)
  {
    auto p_this = static_cast<GenericBinaryResource *>(resource);
    return BinaryResourcePtr(BinaryResourceReference<GenericBinaryResource>(p_this));
  }

  return {};
}

GenericBinaryResourcePtr GenericBinaryResource::Load(czstr file_path)
{
  if(file_path == nullptr || file_path[0] == 0)
  {
    return {};
  }

  auto resource = LoadBinaryResource(file_path, [](Any && load_data, uint32_t path_hash, czstr path) -> std::unique_ptr<BinaryResourceBase>
  { return std::make_unique<GenericBinaryResource>(std::move(load_data), path_hash, path); });
  auto p_this = static_cast<GenericBinaryResource *>(resource);
  return BinaryResourcePtr(BinaryResourceReference<GenericBinaryResource>(p_this));
}

GenericBinaryResourceLoadLink GenericBinaryResource::LoadWithCallback(czstr file_path, Delegate<void, NotNullPtr<GenericBinaryResource>> && callback)
{
  if(file_path == nullptr || file_path[0] == 0)
  {
    return {};
  }

  auto resource = LoadBinaryResource(file_path, [](Any && load_data, uint32_t path_hash, czstr path) -> std::unique_ptr<BinaryResourceBase>
  { return std::make_unique<GenericBinaryResource>(std::move(load_data), path_hash, path); });
  auto p_this = static_cast<GenericBinaryResource *>(resource);

  return p_this->AddLoadCallback(std::move(callback));
}

void GenericBinaryResource::LoadWithCallback(czstr file_path, Delegate<void, NotNullPtr<GenericBinaryResource>> && callback, GenericBinaryResourceLoadLink & load_link)
{
  if(file_path == nullptr || file_path[0] == 0)
  {
    return;
  }

  auto resource = LoadBinaryResource(file_path, [](Any && load_data, uint32_t path_hash, czstr path) -> std::unique_ptr<BinaryResourceBase>
  { return std::make_unique<GenericBinaryResource>(std::move(load_data), path_hash, path); });
  auto p_this = static_cast<GenericBinaryResource *>(resource);

  p_this->AddLoadCallback(std::move(callback), load_link);
}

void GenericBinaryResource::OnDataLoadComplete(const void * data, std::size_t length)
{
  m_Data = data;
  m_Length = length;
  m_Loaded = true;
}

void GenericBinaryResource::CallAssetLoadCallbacks()
{
  m_LoadCallbacks.Call(this);
}

