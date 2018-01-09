#pragma once

#include "Runtime/Asset/Asset.h"

class EngineClientAssetLoader : public ClientAssetLoader
{
public:
  virtual void BeginLoad(Any & asset, czstr path, ClientAssetType type) override;
  virtual void Unload(Any & asset, ClientAssetType type) override;
  virtual bool IsLoaded(Any & asset, ClientAssetType type) override;
  virtual bool IsError(Any & asset, ClientAssetType type) override;
  virtual bool LoadingFinished(Any & asset, ClientAssetType type) override;
};

extern EngineClientAssetLoader g_EngineClientAssetLoader;
