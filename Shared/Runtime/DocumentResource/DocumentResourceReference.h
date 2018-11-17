#pragma once

#include "Runtime/DocumentResource/DocumentResourceReferenceBase.h"

template <class ResourceType>
class DocumentResourceReference : public DocumentResourceReferenceBase
{
public:
  DocumentResourceReference() = default;

  DocumentResourceReference(ResourceType * asset) :
    DocumentResourceReferenceBase(asset)
  {

  }

  DocumentResourceReference(const DocumentResourceReference<ResourceType> & rhs) = default;
  DocumentResourceReference(DocumentResourceReference<ResourceType> && rhs) = default;

  DocumentResourceReference & operator = (const DocumentResourceReference<ResourceType> & rhs) = default;
  DocumentResourceReference & operator = (DocumentResourceReference<ResourceType> && rhs) = default;

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

  bool operator == (const DocumentResourceReference<ResourceType> & rhs) const
  {
    return Resolve() == rhs.Resolve();
  }
};

