#pragma once

#include "Runtime/RuntimeCommon.h"

class BinaryResourceBase;

class RUNTIME_EXPORT BinaryResourceReferenceBase
{
public:
  BinaryResourceReferenceBase();
  BinaryResourceReferenceBase(const BinaryResourceReferenceBase & rhs) noexcept;
  BinaryResourceReferenceBase(BinaryResourceReferenceBase && rhs) noexcept;
  ~BinaryResourceReferenceBase();

  BinaryResourceReferenceBase & operator = (const BinaryResourceReferenceBase & rhs) noexcept;
  BinaryResourceReferenceBase & operator = (BinaryResourceReferenceBase && rhs) noexcept;

  void Clear();

protected:

  friend class BinaryResource;
  friend class BinaryResourceManager;

  BinaryResourceReferenceBase(BinaryResourceBase * resource);

  NullOptPtr<BinaryResourceBase> m_Resource;
};
