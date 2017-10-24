#pragma once

#include "DocumentResourceReference.h"

template <typename ReturnType, typename ... Args>
class DelegateLink;

template <typename DataType, typename ResourceType>
class DocumentResourcePtr
{
public:
  using AssetType = ResourceType;

  DocumentResourcePtr() :
    m_Data(nullptr)
  {

  }

  DocumentResourcePtr(DocumentResourceReference<ResourceType> && ref) :
    m_Resource(std::move(ref))
  {
    auto resource = m_Resource.Resolve();
    m_Data = resource ? resource->GetData() : nullptr;
  }

  DocumentResourcePtr(const DocumentResourcePtr<DataType, ResourceType> & rhs) :
    m_Data(rhs.m_Data),
    m_Resource(rhs.m_Resource)
  {

  }

  DocumentResourcePtr(DocumentResourcePtr<DataType, ResourceType> && rhs) :
    m_Data(std::move(rhs.m_Data)),
    m_Resource(std::move(rhs.m_Resource))
  {

  }

  ~DocumentResourcePtr()
  {
    m_Resource.Clear();
  }

  DocumentResourcePtr<DataType, ResourceType> & operator = (const DocumentResourcePtr<DataType, ResourceType> & rhs)
  {
    m_Data = rhs.m_Data;
    m_Resource = rhs.m_Resource;
    return *this;
  }

  DocumentResourcePtr<DataType, ResourceType> & operator = (DocumentResourcePtr<DataType, ResourceType> && rhs)
  {
    m_Data = std::move(rhs.m_Data);
    m_Resource = std::move(rhs.m_Resource);
    return *this;
  }

  NullOptPtr<ResourceType> GetResource()
  {
    return m_Resource.Resolve();
  }

  NotNullPtr<const ResourceType> GetResource() const
  {
    return m_Resource.Resolve();
  }

  NotNullPtr<DataType> GetData()
  {
    return m_Data;
  }

  NotNullPtr<const DataType> GetData() const
  {
    return m_Data;
  }

  NotNullPtr<ResourceType> operator *()
  {
    return m_Resource.Resolve();
  }

  NotNullPtr<const ResourceType> operator *() const
  {
    return m_Resource.Resolve();
  }

  NotNullPtr<ResourceType> operator ->()
  {
    return m_Resource.Resolve();
  }

  NotNullPtr<const ResourceType> operator ->() const
  {
    return m_Resource.Resolve();
  }

  bool IsLoaded() const
  {
    return m_Resource && m_Resource->IsLoaded();
  }

  bool IsError() const
  {
    return m_Resource && m_Resource->IsError();
  }

  bool LoadingFinished() const
  {
    return m_Resource && (m_Resource->IsError() || m_Resource->IsLoaded());
  }

  void Clear()
  {
    m_Data = nullptr;
    m_Resource.Clear();
  }

protected:
  NotNullPtr<DataType> m_Data;
  DocumentResourceReference<ResourceType> m_Resource;
};

template <typename DataType, typename ResourceType>
class DocumentResourceLoadCallbackLink : public DocumentResourcePtr<DataType, ResourceType>
{
public:
  DocumentResourceLoadCallbackLink() = default;
  ~DocumentResourceLoadCallbackLink()
  {
    m_Link.Clear();
  }

  DocumentResourceLoadCallbackLink(DocumentResourceReference<ResourceType> && ref, DelegateLink<void, NotNullPtr<ResourceType>> && link) :
    DocumentResourcePtr<DataType, ResourceType>(std::move(ref)),
    m_Link(std::move(link))
  {

  }

  DocumentResourceLoadCallbackLink(const DocumentResourceLoadCallbackLink<DataType, ResourceType> & rhs) :
    DocumentResourcePtr<DataType, ResourceType>(rhs)
  {
    m_Link = rhs.m_Link;
  }

  DocumentResourceLoadCallbackLink(DocumentResourceLoadCallbackLink<DataType, ResourceType> && rhs) :
    DocumentResourcePtr<DataType, ResourceType>(std::move(rhs))
  {
    m_Link = std::move(rhs.m_Link);
  }

  DocumentResourceLoadCallbackLink<DataType, ResourceType> & operator = (const DocumentResourceLoadCallbackLink<DataType, ResourceType> & rhs)
  {
    m_Link = rhs.m_Link;
    DocumentResourcePtr<DataType, ResourceType>::operator = (rhs);
    return *this;
  }

  DocumentResourceLoadCallbackLink<DataType, ResourceType> & operator = (DocumentResourceLoadCallbackLink<DataType, ResourceType> && rhs)
  {
    m_Link = std::move(rhs.m_Link);
    DocumentResourcePtr<DataType, ResourceType>::operator = (std::move(rhs));
    return *this;
  }

  void Clear()
  {
    m_Link.Clear();
    DocumentResourcePtr<DataType, ResourceType>::Clear();
  }

private:
  DelegateLink<void, NotNullPtr<ResourceType>> m_Link;
};


