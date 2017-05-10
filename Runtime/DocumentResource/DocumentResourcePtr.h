#pragma once

#include "DocumentResourceReference.h"

template <typename ReturnType, typename ... Args>
class DelegateLink;

template <typename DataType, typename ResourceType>
class DocumentResourcePtr
{
public:
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

  DocumentResourcePtr(const DocumentResourcePtr<DataType, ResourceType> & rhs) = default;
  DocumentResourcePtr(DocumentResourcePtr<DataType, ResourceType> && rhs) = default;

  ~DocumentResourcePtr()
  {
    m_Resource = {};
  }

  DocumentResourcePtr<DataType, ResourceType> & operator = (const DocumentResourcePtr<DataType, ResourceType> & rhs) = default;
  DocumentResourcePtr<DataType, ResourceType> & operator = (DocumentResourcePtr<DataType, ResourceType> && rhs) = default;

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

  NotNullPtr<DataType> operator *()
  {
    return m_Data;
  }

  NotNullPtr<const DataType> operator *() const
  {
    return m_Data;
  }

  NotNullPtr<DataType> operator ->()
  {
    return m_Data;
  }

  NotNullPtr<const DataType> operator ->() const
  {
    return m_Data;
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
    m_Link = {};
    m_Resource = {};
  }

  DocumentResourceLoadCallbackLink(DocumentResourceReference<ResourceType> && ref, DelegateLink<void, NotNullPtr<ResourceType>> && link) :
    DocumentResourcePtr<DataType, ResourceType>(std::move(ref)),
    m_Link(std::move(link))
  {

  }

  DocumentResourceLoadCallbackLink(const DocumentResourceLoadCallbackLink<DataType, ResourceType> & rhs)
  {
    m_Data = rhs.m_Data;
    m_Link = rhs.m_Link;
    m_Resource = rhs.m_Resource;
  }

  DocumentResourceLoadCallbackLink(DocumentResourceLoadCallbackLink<DataType, ResourceType> && rhs)
  {
    m_Data = rhs.m_Data;
    m_Link = std::move(rhs.m_Link);
    m_Resource = std::move(rhs.m_Resource);
  }

  DocumentResourceLoadCallbackLink<DataType, ResourceType> & operator = (const DocumentResourceLoadCallbackLink<DataType, ResourceType> & rhs)
  {
    m_Data = rhs.m_Data;
    m_Link = rhs.m_Link;
    m_Resource = rhs.m_Resource;
    return *this;
  }

  DocumentResourceLoadCallbackLink<DataType, ResourceType> & operator = (DocumentResourceLoadCallbackLink<DataType, ResourceType> && rhs)
  {
    m_Data = rhs.m_Data;
    m_Link = std::move(rhs.m_Link);
    m_Resource = std::move(rhs.m_Resource);
    return *this;
  }

private:
  DelegateLink<void, NotNullPtr<ResourceType>> m_Link;
};


