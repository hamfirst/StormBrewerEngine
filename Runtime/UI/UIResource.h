#pragma once

#include "Foundation/Delegate/DelegateList.h"

#include "Runtime/DocumentResource/DocumentResourceBase.h"
#include "Runtime/DocumentResource/DocumentResourcePtr.h"
#include "Runtime/UI/UIDef.refl.h"
#include "Runtime/Sprite/SpriteResource.h"

class UIResource;

using UIResourcePtr = DocumentResourcePtr<UIDef, UIResource>;
using UILoadLink = DocumentResourceLoadCallbackLink<UIDef, UIResource>;

class UIResource : public DocumentResourceBase
{
public:
  UIResource(Any && load_data, uint32_t path_hash);

  NotNullPtr<UIDef> GetData();
  DocumentResourceLoadCallbackLink<UIDef, UIResource> AddLoadCallback(Delegate<void, NotNullPtr<UIResource>> && callback);

  static UIResourcePtr Find(uint32_t file_path_hash);
  static UIResourcePtr Load(czstr file_path);
  static DocumentResourceLoadCallbackLink<UIDef, UIResource> LoadWithCallback(czstr file_path, Delegate<void, NotNullPtr<UIResource>> && callback);

protected:
  virtual void OnDataLoadComplete(const std::string & resource_data) override;
  virtual void CallAssetLoadCallbacks() override;

private:

  friend class UISystem;

  UIDef m_Data;
  DelegateList<void, NotNullPtr<UIResource>> m_LoadCallbacks;

  SpritePtr m_Sprite;
};
