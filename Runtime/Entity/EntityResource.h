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
  EntityResource(Any && load_data, uint64_t path_hash);

  NotNullPtr<EntityDef> GetData();
  DocumentResourceLoadCallbackLink<EntityDef, EntityResource> AddLoadCallback(Delegate<void, NotNullPtr<EntityResource>> && callback);

  static EntityResourcePtr Load(czstr file_path);
  static DocumentResourceLoadCallbackLink<EntityDef, EntityResource> LoadWithCallback(czstr file_path, Delegate<void, NotNullPtr<EntityResource>> && callback);

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
