#pragma once

#include "Foundation/Delegate/DelegateList.h"

#include "Runtime/DocumentResource/DocumentResourceBase.h"
#include "Runtime/DocumentResource/DocumentResourcePtr.h"
#include "Runtime/ServerObject/ServerObjectDef.refl.h"
#include "Runtime/Sprite/SpriteResource.h"

class ServerObjectResource;

using ServerObjectResourcePtr = DocumentResourcePtr<ServerObjectDef, ServerObjectResource>;
using ServerObjectLoadLink = DocumentResourceLoadCallbackLink<ServerObjectDef, ServerObjectResource>;

class ServerObjectResource : public DocumentResourceBase
{
public:
  ServerObjectResource(Any && load_data, uint32_t path_hash);

  NotNullPtr<ServerObjectDef> GetData();
  ServerObjectLoadLink AddLoadCallback(Delegate<void, NotNullPtr<ServerObjectResource>> && callback);
  void AddLoadCallback(Delegate<void, NotNullPtr<ServerObjectResource>> && callback, ServerObjectLoadLink & link);

  static ServerObjectResourcePtr Find(uint32_t file_path_hash);
  static ServerObjectResourcePtr Load(czstr file_path);
  static ServerObjectLoadLink LoadWithCallback(czstr file_path, Delegate<void, NotNullPtr<ServerObjectResource>> && callback);
  static void LoadWithCallback(czstr file_path, Delegate<void, NotNullPtr<ServerObjectResource>> && callback, ServerObjectLoadLink & link);

protected:
  virtual void OnDataLoadComplete(const std::string & resource_data) override;
  virtual void CallAssetLoadCallbacks() override;

private:

  ServerObjectDef m_Data;
  DelegateList<void, NotNullPtr<ServerObjectResource>> m_LoadCallbacks;
};
