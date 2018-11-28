#pragma once

#include "Runtime/BinaryResource/BinaryResourceReferenceBase.h"

template <class ResourceType>
class BinaryResourceReference : public BinaryResourceReferenceBase
{
public:
  BinaryResourceReference() = default;

  BinaryResourceReference(ResourceType * asset) :
    BinaryResourceReferenceBase(asset)
  {

  }

  BinaryResourceReference(const BinaryResourceReference<ResourceType> & rhs) = default;
  BinaryResourceReference(BinaryResourceReference<ResourceType> && rhs) = default;

  BinaryResourceReference & operator = (const BinaryResourceReference<ResourceType> & rhs) = default;
  BinaryResourceReference & operator = (BinaryResourceReference<ResourceType> && rhs) = default;

  NullOptPtr<ResourceType> Resolve()
  {
    return static_cast<ResourceType *>(m_Resource);
  }

  NullOptPtr<const ResourceType> Resolve() const
  {
    return static_cast<const ResourceType *>(m_Resource);
  }

  explicit operator bool() const
  {
    return m_Resource != 0;
  }

  ResourceType & operator * ()
  {
    return *Resolve();
  }

  const ResourceType & operator * () const
  {
    return *Resolve();
  }

  ResourceType * operator -> ()
  {
    return Resolve();
  }

  const ResourceType * operator -> () const
  {
    return Resolve();
  }

  bool operator == (const BinaryResourceReference<ResourceType> & rhs) const
  {
    return Resolve() == rhs.Resolve();
  }
};

