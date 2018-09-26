
#pragma once

#include "Foundation/Delegate/DelegateList.h"

#include "Runtime/DocumentResource/DocumentResourceBase.h"
#include "Runtime/DocumentResource/DocumentResourcePtr.h"

#include "StormRefl/StormReflJson.h"

template <typename ResourceData>
class GenericResource : public DocumentResourceBase
{
public:

  GenericResource(Any && load_data, uint32_t path_hash) :
    DocumentResourceBase(std::move(load_data), path_hash)
  {

  }

  NotNullPtr<ResourceData> GetData()
  {
    return &m_Data;
  }

  DocumentResourceLoadCallbackLink<ResourceData, GenericResource<ResourceData>> AddLoadCallback(Delegate<void, NotNullPtr<GenericResource<ResourceData>>> && callback)
  {
    if (m_Loaded)
    {
      callback(this);
    }

    return DocumentResourceLoadCallbackLink<ResourceData, GenericResource<ResourceData>>(
      DocumentResourceReference<GenericResource<ResourceData>>(this), m_LoadCallbacks.AddDelegate(std::move(callback)));
  }

  static DocumentResourcePtr<ResourceData, GenericResource<ResourceData>> Load(czstr file_path)
  {
    if(file_path == nullptr || file_path[0] == 0)
    {
      return {};
    }

    auto resource = LoadDocumentResource(file_path,
      [](Any && load_data, uint32_t path_hash) -> std::unique_ptr<DocumentResourceBase> { return std::make_unique<GenericResource<ResourceData>>(std::move(load_data), path_hash); });
    auto p_this = static_cast<GenericResource<ResourceData> *>(resource);
    return DocumentResourcePtr<ResourceData, GenericResource<ResourceData>>(DocumentResourceReference<GenericResource<ResourceData>>(p_this));
  }

  static DocumentResourceLoadCallbackLink<ResourceData, GenericResource<ResourceData>> LoadWithCallback(czstr file_path, Delegate<void, NotNullPtr<GenericResource<ResourceData>>> && callback)
  {
    if(file_path == nullptr || file_path[0] == 0)
    {
      return {};
    }

    auto resource = LoadDocumentResource(file_path,
      [](Any && load_data, uint32_t path_hash) -> std::unique_ptr<DocumentResourceBase> { return std::make_unique<GenericResource<ResourceData>>(std::move(load_data), path_hash); });
    auto p_this = static_cast<GenericResource<ResourceData> *>(resource);

    return p_this->AddLoadCallback(std::move(callback));
  }

protected:
  virtual void OnDataLoadComplete(const std::string & resource_data) override
  {
    StormReflParseJson(m_Data, resource_data.data());
    m_Loaded = true;
  }

  virtual void CallAssetLoadCallbacks() override
  {
    m_LoadCallbacks.Call(this);
  }

private:

  ResourceData m_Data;
  DelegateList<void, NotNullPtr<GenericResource<ResourceData>>> m_LoadCallbacks;
};

template <typename ResourceData>
using GenericResourcePtr = DocumentResourcePtr<ResourceData, GenericResource<ResourceData>>;

template <typename ResourceData>
using GenericResourceLoadLink = DocumentResourceLoadCallbackLink<ResourceData, GenericResource<ResourceData>>;

