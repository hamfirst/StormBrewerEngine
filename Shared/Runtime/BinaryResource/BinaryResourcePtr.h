#pragma once

#include "BinaryResourceReference.h"

template <typename ReturnType, typename ... Args>
class DelegateLink;

template <typename ResourceType>
class BinaryResourcePtr
{
public:
  using AssetType = ResourceType;

  BinaryResourcePtr()
  {

  }

  BinaryResourcePtr(BinaryResourceReference<ResourceType> && ref) :
    m_Resource(std::move(ref))
  {

  }

  BinaryResourcePtr(const BinaryResourcePtr<ResourceType> & rhs) :
    m_Resource(rhs.m_Resource)
  {

  }

  BinaryResourcePtr(BinaryResourcePtr<ResourceType> && rhs) :
    m_Resource(std::move(rhs.m_Resource))
  {

  }

  ~BinaryResourcePtr()
  {
    m_Resource.Clear();
  }

  BinaryResourcePtr<ResourceType> & operator = (const BinaryResourcePtr<ResourceType> & rhs)
  {
    m_Resource = rhs.m_Resource;
    return *this;
  }

  BinaryResourcePtr<ResourceType> & operator = (BinaryResourcePtr<ResourceType> && rhs)
  {
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

  virtual void Clear()
  {
    m_Resource.Clear();
  }

  operator bool() const
  {
    return IsLoaded();
  }

protected:
  BinaryResourceReference<ResourceType> m_Resource;
};

template <typename ResourceType>
class BinaryResourceLoadCallbackLink : public BinaryResourcePtr<ResourceType>
{
public:
  BinaryResourceLoadCallbackLink() = default;
  ~BinaryResourceLoadCallbackLink()
  {
    m_Link.Clear();
  }

  BinaryResourceLoadCallbackLink(BinaryResourceReference<ResourceType> && ref, DelegateLink<void, NotNullPtr<ResourceType>> && link) :
    BinaryResourcePtr<ResourceType>(std::move(ref)),
    m_Link(std::move(link))
  {

  }

  BinaryResourceLoadCallbackLink(const BinaryResourceLoadCallbackLink<ResourceType> & rhs) = delete;

  BinaryResourceLoadCallbackLink(BinaryResourceLoadCallbackLink<ResourceType> && rhs) noexcept :
    BinaryResourcePtr<ResourceType>(std::move(rhs))
  {
    m_Link = std::move(rhs.m_Link);
  }

  BinaryResourceLoadCallbackLink<ResourceType> & operator = (const BinaryResourceLoadCallbackLink<ResourceType> & rhs) = delete;

  BinaryResourceLoadCallbackLink<ResourceType> & operator = (BinaryResourceLoadCallbackLink<ResourceType> && rhs) noexcept
  {
    m_Link = std::move(rhs.m_Link);
    BinaryResourcePtr<ResourceType>::operator = (std::move(rhs));
    return *this;
  }

  void Clear()
  {
    BinaryResourcePtr<ResourceType>::Clear();
    m_Link.Clear();
    BinaryResourcePtr<ResourceType>::Clear();
  }

private:
  DelegateLink<void, NotNullPtr<ResourceType>> m_Link;
};


