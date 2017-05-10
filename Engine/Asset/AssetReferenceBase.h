#pragma once


class Asset;

class ENGINE_EXPORT AssetReferenceBase
{
public:
  AssetReferenceBase();
  AssetReferenceBase(const AssetReferenceBase & rhs) noexcept;
  AssetReferenceBase(AssetReferenceBase && rhs) noexcept;
  ~AssetReferenceBase();

  AssetReferenceBase & operator = (const AssetReferenceBase & rhs) noexcept;
  AssetReferenceBase & operator = (AssetReferenceBase && rhs) noexcept;

  void Clear();

protected:

  friend class Asset;
  friend class GenericLoadCallbackLink;

  AssetReferenceBase(Asset * asset);

  NullOptPtr<Asset> m_Asset;
};
