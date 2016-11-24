#pragma once


class Asset;

class AssetReferenceBase
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

  AssetReferenceBase(Asset * asset);

  Asset * m_Asset;
};
