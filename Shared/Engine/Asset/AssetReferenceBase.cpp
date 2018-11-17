
#include "Engine/EngineCommon.h"
#include "Engine/Asset/Asset.h"
#include "Engine/Asset/AssetReferenceBase.h"

AssetReferenceBase::AssetReferenceBase() :
  m_Asset(nullptr)
{

}

AssetReferenceBase::AssetReferenceBase(Asset * asset) :
  m_Asset(asset)
{
  m_Asset->IncRef();
}

AssetReferenceBase::AssetReferenceBase(const AssetReferenceBase & rhs) noexcept
{
  m_Asset = nullptr;
  if (rhs.m_Asset)
  {
    m_Asset = rhs.m_Asset;
    m_Asset->IncRef();
  }
}

AssetReferenceBase::AssetReferenceBase(AssetReferenceBase && rhs) noexcept
{
  m_Asset = rhs.m_Asset;
  rhs.m_Asset = nullptr;
}

AssetReferenceBase::~AssetReferenceBase()
{
  Clear();
}

AssetReferenceBase & AssetReferenceBase::operator = (const AssetReferenceBase & rhs) noexcept
{
  Clear();

  if (rhs.m_Asset)
  {
    m_Asset = rhs.m_Asset;
    m_Asset->IncRef();
  }

  return *this;
}

AssetReferenceBase & AssetReferenceBase::operator = (AssetReferenceBase && rhs) noexcept
{
  Clear();

  m_Asset = rhs.m_Asset;
  rhs.m_Asset = nullptr;

  return *this;
}

bool AssetReferenceBase::IsLoaded() const
{
  return m_Asset && m_Asset->IsLoaded();
}

bool AssetReferenceBase::IsError() const
{
  return m_Asset && m_Asset->IsError();
}

bool AssetReferenceBase::LoadingFinished() const
{
  return m_Asset && (m_Asset->IsError() || m_Asset->IsLoaded());
}

void AssetReferenceBase::Clear()
{
  if (m_Asset)
  {
    m_Asset->DecRef();
    m_Asset = nullptr;
  }
}

