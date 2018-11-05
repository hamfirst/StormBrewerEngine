#pragma once

#include "Foundation/Delegate/DelegateList.h"

#include "Runtime/DocumentResource/DocumentResourceBase.h"
#include "Runtime/DocumentResource/DocumentResourcePtr.h"
#include "Runtime/Entity/EntityDef.refl.h"
#include "Runtime/Sprite/SpriteResource.h"

class EntityResource;
class AnimationState;

using EntityResourcePtr = DocumentResourcePtr<EntityDef, EntityResource>;
using EntityLoadLink = DocumentResourceLoadCallbackLink<EntityDef, EntityResource>;

class EntityResource : public DocumentResourceBase
{
public:
  EntityResource(Any && load_data, uint32_t path_hash, czstr path);

  NotNullPtr<EntityDef> GetData();
  EntityLoadLink AddLoadCallback(Delegate<void, NotNullPtr<EntityResource>> && callback);
  void AddLoadCallback(Delegate<void, NotNullPtr<EntityResource>> && callback, EntityLoadLink & link);

  static EntityResourcePtr Find(uint32_t file_path_hash);
  static EntityResourcePtr Load(czstr file_path);
  static EntityLoadLink LoadWithCallback(czstr file_path, Delegate<void, NotNullPtr<EntityResource>> && callback);
  static void LoadWithCallback(czstr file_path, Delegate<void, NotNullPtr<EntityResource>> && callback, EntityLoadLink & link);

  SpritePtr & GetSprite();
  const SpritePtr & GetSprite() const;

protected:
  virtual void OnDataLoadComplete(const std::string & resource_data) override;
  virtual void CallAssetLoadCallbacks() override;

private:

  friend class EntitySystem;

  EntityDef m_Data;
  DelegateList<void, NotNullPtr<EntityResource>> m_LoadCallbacks;

  SpritePtr m_Sprite;
};
