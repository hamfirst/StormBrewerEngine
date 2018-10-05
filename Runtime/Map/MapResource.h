#pragma once

#include "Foundation/Delegate/DelegateList.h"

#include "Runtime/DocumentResource/DocumentResourceBase.h"
#include "Runtime/DocumentResource/DocumentResourcePtr.h"
#include "Runtime/Map/MapDef.refl.h"

class MapResource;
class AnimationState;


using Map = DocumentResourcePtr<MapDef, MapResource>;
using MapLoadLink = DocumentResourceLoadCallbackLink<MapDef, MapResource>;

class MapResource : public DocumentResourceBase
{
public:
  MapResource(Any && load_data, uint32_t path_hash, czstr path);

  NotNullPtr<MapDef> GetData() const;
  const std::shared_ptr<MapDef> & GetMapPtr() const;
  DocumentResourceLoadCallbackLink<MapDef, MapResource> AddLoadCallback(Delegate<void, NotNullPtr<MapResource>> && callback);

  static Map Find(uint32_t file_path_hash);
  static Map Load(czstr file_path);
  static MapLoadLink LoadWithCallback(czstr file_path, Delegate<void, NotNullPtr<MapResource>> && callback);

protected:
  virtual void OnDataLoadComplete(const std::string & resource_data) override;
  virtual void CallAssetLoadCallbacks() override;

private:

  friend class SpriteEngineData;

  std::shared_ptr<MapDef> m_Data;
  DelegateList<void, NotNullPtr<MapResource>> m_LoadCallbacks;
};
