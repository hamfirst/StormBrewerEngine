#pragma once

#include "Foundation/Common.h"
#include "Foundation/Delegate/Delegate.h"
#include "Engine/Asset/AssetReferenceBase.h"

class Asset;

class GenericAssetReference
{
public:
  GenericAssetReference();
  GenericAssetReference(const GenericAssetReference & rhs) noexcept;
  GenericAssetReference(GenericAssetReference && rhs) noexcept;

  ~GenericAssetReference();

  GenericAssetReference & operator = (const GenericAssetReference & rhs);
  GenericAssetReference & operator = (GenericAssetReference && rhs);

  void Clear();
  NullOptPtr<Asset> Resolve();

private:
  
  template <typename AssetType>
  friend GenericAssetReference InitGenericAssetReference(czstr file_path);

  void(*Deleter)(void *);
  void *(*Copier)(const void *);
  NullOptPtr<Asset>(*Resolver)(void *);

  void * m_AssetLink;
};

GenericAssetReference LoadAsset(czstr asset_path);
