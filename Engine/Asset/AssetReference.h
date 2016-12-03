#pragma once

#include "AssetReferenceBase.h"

template <class AssetType>
class AssetReference : public AssetReferenceBase
{
public:
  AssetReference() = default;

  AssetReference(AssetType * asset) :
    AssetReferenceBase(asset)
  {

  }

  AssetReference(const AssetReference & rhs) = default;
  AssetReference(AssetReference && rhs) = default;

  AssetReference & operator = (const AssetReference & rhs) = default;
  AssetReference & operator = (AssetReference && rhs) = default;

  NullOptPtr<AssetType> Resolve()
  {
    return static_cast<AssetType *>(m_Asset);
  }

  const NullOptPtr<AssetType> Resolve() const
  {
    return static_cast<AssetType *>(m_Asset);
  }
};

