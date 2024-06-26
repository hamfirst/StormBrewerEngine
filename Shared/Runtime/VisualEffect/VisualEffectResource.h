#pragma once

#include "Foundation/Delegate/DelegateList.h"

#include "Runtime/DocumentResource/DocumentResourceBase.h"
#include "Runtime/DocumentResource/DocumentResourcePtr.h"
#include "Runtime/VisualEffect/VisualEffectDef.refl.h"
#include "Runtime/Sprite/SpriteResource.h"

class VisualEffectResource;

using VisualEffectResourcePtr = DocumentResourcePtr<VisualEffectDef, VisualEffectResource>;
using VisualEffectLoadLink = DocumentResourceLoadCallbackLink<VisualEffectDef, VisualEffectResource>;

class VisualEffectResource : public DocumentResourceBase
{
public:
  VisualEffectResource(Any && load_data, uint32_t path_hash, czstr path);

  NotNullPtr<VisualEffectDef> GetData();
  DocumentResourceLoadCallbackLink<VisualEffectDef, VisualEffectResource> AddLoadCallback(Delegate<void, NotNullPtr<VisualEffectResource>> && callback);

  static VisualEffectResourcePtr Find(uint32_t file_path_hash);
  static VisualEffectResourcePtr Load(czstr file_path);
  static DocumentResourceLoadCallbackLink<VisualEffectDef, VisualEffectResource> LoadWithCallback(czstr file_path, Delegate<void, NotNullPtr<VisualEffectResource>> && callback);

protected:
  virtual void OnDataLoadComplete(const std::string & resource_data) override;
  virtual void CallAssetLoadCallbacks() override;

private:

  friend class VisualEffectSystem;
  friend class VisualEffectInstance;

  VisualEffectDef m_Data;
  DelegateList<void, NotNullPtr<VisualEffectResource>> m_LoadCallbacks;

  Any m_EngineData;
};
