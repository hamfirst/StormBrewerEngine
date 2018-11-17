#pragma once

#include "Engine/Asset/AssetReferenceBase.h"

template <class AssetDataType>
class AssetReference : public AssetReferenceBase
{
public:
  using AssetType = AssetDataType;

  AssetReference() = default;

  AssetReference(AssetType * asset) :
    AssetReferenceBase(asset)
  {

  }

  AssetReference(const AssetReference & rhs) = default;
  AssetReference(AssetReference && rhs) noexcept = default;

  AssetReference & operator = (const AssetReference & rhs) = default;
  AssetReference & operator = (AssetReference && rhs) noexcept = default;

  bool operator == (const AssetReference<AssetType> & rhs) const
  {
    return m_Asset == rhs.m_Asset;
  }

  NullOptPtr<AssetType> Resolve()
  {
    return static_cast<AssetType *>(m_Asset);
  }

  NullOptPtr<const AssetType> Resolve() const
  {
    return static_cast<const AssetType *>(m_Asset);
  }

  operator bool() const
  {
    return m_Asset != 0;
  }

  AssetType & operator * ()
  {
    return *Resolve();
  }

  const AssetType & operator * () const
  {
    return *Resolve();
  }

  AssetType * operator -> ()
  {
    return Resolve();
  }

  const AssetType * operator -> () const
  {
    return Resolve();
  }
};

