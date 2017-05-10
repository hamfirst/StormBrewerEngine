
#include "Engine/EngineCommon.h"
#include "Engine/Asset/AssetLoad.h"
#include "Engine/Asset/AssetReference.h"
#include "Engine/Asset/TextureAsset.h"
#include "Engine/Asset/AudioAsset.h"
#include "Engine/Asset/MusicAsset.h"
#include "Engine/Asset/FontAsset.h"
#include "Engine/Asset/DocumentAsset.h"

#include "Foundation/FileSystem/Path.h"

std::string s_RootPath = GetCanonicalRootPath();

GenericAssetReference::GenericAssetReference() :
  m_AssetLink(nullptr)
{

}

GenericAssetReference::GenericAssetReference(const GenericAssetReference & rhs) noexcept
{
  if (rhs.m_AssetLink)
  {
    Deleter = rhs.Deleter;
    Copier = rhs.Copier;
    Resolver = rhs.Resolver;
    m_AssetLink = Copier(rhs.m_AssetLink);
  }
}

GenericAssetReference::GenericAssetReference(GenericAssetReference && rhs) noexcept
{
  m_AssetLink = rhs.m_AssetLink;
  rhs.m_AssetLink = nullptr;

  Deleter = rhs.Deleter;
  Copier = rhs.Copier;
  Resolver = rhs.Resolver;
}

GenericAssetReference::~GenericAssetReference()
{
  Clear();
}

GenericAssetReference & GenericAssetReference::operator = (const GenericAssetReference & rhs)
{
  Clear();
  if (rhs.m_AssetLink)
  {
    Deleter = rhs.Deleter;
    Copier = rhs.Copier;
    Resolver = rhs.Resolver;
    m_AssetLink = Copier(rhs.m_AssetLink);
  }

  return *this;
}

GenericAssetReference & GenericAssetReference::operator = (GenericAssetReference && rhs)
{
  Clear();
  m_AssetLink = rhs.m_AssetLink;
  rhs.m_AssetLink = nullptr;

  Deleter = rhs.Deleter;
  Copier = rhs.Copier;
  Resolver = rhs.Resolver;
  return *this;
}

void GenericAssetReference::Clear()
{
  if (m_AssetLink)
  {
    Deleter(m_AssetLink);
    m_AssetLink = nullptr;
  }
}

NullOptPtr<Asset> GenericAssetReference::Resolve()
{
  return m_AssetLink ? Resolver(m_AssetLink) : nullptr;
}

template <typename AssetType>
GenericAssetReference InitGenericAssetReference(czstr file_path)
{
  using AssetRefType = typename AssetReference<AssetType>;
  GenericAssetReference asset;

  asset.m_AssetLink = new AssetRefType(AssetType::Load(file_path));
  asset.Deleter = [](void * ptr) { AssetRefType * val = static_cast<AssetRefType *>(ptr); delete val; };
  asset.Copier = [](const void * src) -> void * { return new AssetRefType(*static_cast<const AssetRefType *>(src)); };
  asset.Resolver = [](void * ptr) -> NullOptPtr<Asset> { auto val = static_cast<AssetRefType *>(ptr); return val->Resolve(); };
  return asset;
}

GenericAssetReference LoadAsset(czstr file_path)
{
  std::string extension;
  if (file_path[0] != '.' || file_path[1] != '/')
  {
    std::string path = file_path;
    if (ConvertToCanonicalPath(path, s_RootPath) == false)
    {
      return{};
    }

    extension = GetFileExtensionForCanonicalPath(path);
  }
  else
  {
    extension = GetFileExtensionForCanonicalPath(file_path);
  }

  if (extension == "png")
  {
    return InitGenericAssetReference<TextureAsset>(file_path);
  }

  if (extension == "ttf")
  {
    return InitGenericAssetReference<FontAsset>(file_path);
  }

  if (extension == "wav")
  {
    return InitGenericAssetReference<AudioAsset>(file_path);
  }

  if (extension == "ogg")
  {
    return InitGenericAssetReference<MusicAsset>(file_path);
  }

  return InitGenericAssetReference<DocumentAsset>(file_path);
}
