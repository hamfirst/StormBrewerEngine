
#pragma once

#include "Game/GameCommon.h"

#include "Game/GameTypes.h"
#include "GameShared/GameWorld.h"
#include "Game/NetworkEvents/GameNetworkData.refl.h"

#include "Game/ServerObjects/CharacterFacing.refl.h"
#include "Game/GameplayEvents/DamageEvent.h"

#include "Runtime/Animation/AnimationState.h"
#include "Runtime/ServerObject/ServerObject.h"
#include "Runtime/ServerObject/ServerObjectInitData.refl.h"
#include "Runtime/ServerObject/ServerObjectRegistrationMacros.h"

#include "Runtime/Sprite/SpriteResource.h"


struct GameServerObjectBaseInitData : public ServerObjectInitData
{
  STORM_DATA_DEFAULT_CONSTRUCTION_DERIVED(GameServerObjectBaseInitData);
};

class GameServerObjectBase : public ServerObject
{
public:
  DECLARE_SERVER_OBJECT;

  GameServerObjectBase() = default;
  GameServerObjectBase(const GameServerObjectBase & rhs) = default;
  GameServerObjectBase(GameServerObjectBase && rhs) = default;

  GameServerObjectBase & operator = (const GameServerObjectBase & rhs) = default;
  GameServerObjectBase & operator = (GameServerObjectBase && rhs) = default;

  void Init(const GameServerObjectBaseInitData & init_data, GameWorld & world);
  void UpdateFirst(GameWorld & container);

  virtual void InitPosition(const Vector2 & pos) override;

  virtual GameNetVec2 GetPosition() const;
  virtual void SetPosition(const GameNetVec2 & pos);

  virtual Optional<AnimationState> GetAnimationState() const;
  virtual void SetAnimationState(const AnimationState & anim_state);
  virtual void SetAssociatedPlayer(int associated_player) const;

  bool FrameAdvance(uint32_t anim_name_hash, bool loop = true, int frames = 1);
  void ResetAnimState();

  void PushDealDamageEventBox(const Box & b, const DamageEvent & damage_event, GameWorld & world);
  void PushDealDamageEventBox(uint32_t box_name_hash, const DamageEvent & damage_event, GameWorld & world);
  void PushDealDamageEventBoxes(uint32_t multi_box_name_hash, const DamageEvent & damage_event, GameWorld & world);
  void PushReceiveDamageEventBox(const Box & b, GameWorld & world);
  void PushReceiveDamageEventBox(uint32_t box_name_hash, GameWorld & world);
  void PushReceiveDamageEventBoxes(uint32_t multi_box_name_hash, GameWorld & world);
  void PushReceiveDamageCollisionBox(const Box & b, GameWorld & world);
  void PushReceiveDamageCollisionBox(uint32_t box_name_hash, GameWorld & world);
  void PushReceiveDamageCollisionBoxes(uint32_t multi_box_name_hash, GameWorld & world);
  void PushCVCBox(const Box & b, GameWorld & world);
  void PushCVCBox(uint32_t box_name_hash, GameWorld & world);

#ifdef MOVER_ONE_WAY_COLLISION
  MoverResult MoveCheckCollisionDatabase(GameWorld & world, const GameNetVec2 & velocity, bool fallthrough = false);
#else
  MoverResult MoveCheckCollisionDatabase(GameWorld & world, const GameNetVec2 & velocity);
#endif

  GameNetVec2 MoveCheckIntersectionDatabase(GameWorld & world, const GameNetVec2 & velocity, GameNetVal player_radius, GameNetVal move_threshold);

  virtual const SpritePtr & GetSprite() const;
  virtual Optional<CharacterFacing> GetFacing() const;
  virtual Optional<int> GetCollisionId() const;

  template <typename Target>
  void TriggerAnimationEvents(GameWorld & world, Target & target)
  {
    auto anim_state = GetAnimationState();
    if (anim_state)
    {
      GetSprite()->SendEventsTo(target, anim_state.Value(), EventMetaData(this, &world));
    }
  }

private:

  friend class GameServerObjectOverlapSystem;
  Optional<int> m_CollisionId;

public:
  GameNetVec2 m_Position = {};
};
