#pragma once

#include "Foundation/Delegate/DelegateList.h"

#include "Runtime/BinaryResource/BinaryResourceBase.h"
#include "Runtime/BinaryResource/BinaryResourcePtr.h"

class ScriptResource;

using ScriptResourcePtr = BinaryResourcePtr<ScriptResource>;
using ScriptLoadLink = BinaryResourceLoadCallbackLink<ScriptResource>;

class ScriptResource : public BinaryResourceBase
{
public:
  ScriptResource(Any && load_data, uint32_t path_hash, czstr path);


  BinaryResourceLoadCallbackLink<ScriptResource> AddLoadCallback(Delegate<void, NotNullPtr<ScriptResource>> && callback);

  static ScriptResourcePtr Find(uint32_t file_path_hash);
  static ScriptResourcePtr Load(czstr file_path);
  static BinaryResourceLoadCallbackLink<ScriptResource> LoadWithCallback(czstr file_path, Delegate<void, NotNullPtr<ScriptResource>> && callback);

protected:
  virtual void OnDataLoadComplete(const void * data, std::size_t length) override;
  virtual void CallAssetLoadCallbacks() override;

private:

  std::string_view m_ScriptData;

  DelegateList<void, NotNullPtr<ScriptResource>> m_LoadCallbacks;
};
