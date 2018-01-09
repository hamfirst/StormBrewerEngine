
#include "Engine/EngineCommon.h"
#include "Engine/Asset/ClientAssetLoader.h"
#include "Engine/Asset/AudioAsset.h"

#include "Runtime/VisualEffect/VisualEffectResource.h"

EngineClientAssetLoader g_EngineClientAssetLoader;

void EngineClientAssetLoader::BeginLoad(Any & asset, czstr path, ClientAssetType type)
{
  switch (type)
  {
  case kAudio:
    asset = Any(AudioAsset::Load(path));
    break;
  case kVfx:
    asset = Any(VisualEffectResource::Load(path));
    break;
  default:
    break;
  }
}

void EngineClientAssetLoader::Unload(Any & asset, ClientAssetType type)
{
  asset.Clear();
}

bool EngineClientAssetLoader::IsLoaded(Any & asset, ClientAssetType type)
{
  switch (type)
  {
  case kAudio:
    {
      auto asset_ptr = asset.Get<AssetReference<AudioAsset>>();
      if (asset_ptr)
      {
        return asset_ptr->IsLoaded();
      }

      return false;
    }
  break;
  case kVfx:
    {
      auto asset_ptr = asset.Get<VisualEffectResourcePtr>();
      if (asset_ptr)
      {
        return asset_ptr->IsLoaded();
      }

      return false;
    }
    break;
  default:
    break;
  }

  return false;
}

bool EngineClientAssetLoader::IsError(Any & asset, ClientAssetType type)
{
  switch (type)
  {
  case kAudio:
    {
      auto asset_ptr = asset.Get<AssetReference<AudioAsset>>();
      if (asset_ptr)
      {
        return asset_ptr->IsError();
      }

      return true;
    }
  break;
  case kVfx:
    {
      auto asset_ptr = asset.Get<VisualEffectResourcePtr>();
      if (asset_ptr)
      {
        return asset_ptr->IsError();
      }

      return true;
    }
    break;
  default:
    break;
  }

  return true;
}

bool EngineClientAssetLoader::LoadingFinished(Any & asset, ClientAssetType type)
{
  switch (type)
  {
  case kAudio:
    {
      auto asset_ptr = asset.Get<AssetReference<AudioAsset>>();
      if (asset_ptr)
      {
        return asset_ptr->LoadingFinished();
      }

      return false;
    }
  break;
  case kVfx:
    {
      auto asset_ptr = asset.Get<VisualEffectResourcePtr>();
      if (asset_ptr)
      {
        return asset_ptr->LoadingFinished();
      }

      return false;
    }
    break;
  default:
    break;
  }

  return false;
}
