#pragma once

#include "Runtime/RuntimeCommon.h"

class DocumentResourceBase;

class RUNTIME_EXPORT DocumentResourceReferenceBase
{
public:
  DocumentResourceReferenceBase();
  DocumentResourceReferenceBase(const DocumentResourceReferenceBase & rhs) noexcept;
  DocumentResourceReferenceBase(DocumentResourceReferenceBase && rhs) noexcept;
  ~DocumentResourceReferenceBase();

  DocumentResourceReferenceBase & operator = (const DocumentResourceReferenceBase & rhs) noexcept;
  DocumentResourceReferenceBase & operator = (DocumentResourceReferenceBase && rhs) noexcept;

  void Clear();

protected:

  friend class DocumentResource;
  friend class DocumentResourceManager;

  DocumentResourceReferenceBase(DocumentResourceBase * resource);

  NullOptPtr<DocumentResourceBase> m_Resource;
};
