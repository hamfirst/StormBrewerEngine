
#pragma once

#include "Game/GameCommon.h"
#include "Game/GameTypes.h"
#include "GameShared/GameWorld.h"

#include "Game/ServerObjects/GameServerObjectBase.refl.h"
#include "Game/ServerObjects/Player/States/PlayerStateBase.refl.h"

#include "Game/GameplayEvents/PlaceholderEvent.h"
#include "Game/AnimationEvents/DealDamageAnimationEvent.refl.h"

#include "Game/ServerObjects/Player/Config/PlayerConfig.refl.h"

#include "Runtime/Sprite/SpriteResource.h"
#include "Runtime/Config/ConfigResource.h"

#include "Runtime/ServerObject/ServerObject.h"
#include "Runtime/ServerObject/ServerObjectInitData.refl.h"
#include "Runtime/ServerObject/ServerObjectRegistrationMacros.h"

#include "StormNet/NetReflectionPolymorphic.h"
#include "StormNet/NetReflectionArrayList.h"
#include "StormNet/NetReflectionBitBuffer.h"
#include "StormNet/NetReflectionStaticList.h"

struct PlayerServerObjectInitData : public GameServerObjectBaseInitData
{
  STORM_DATA_DEFAULT_CONSTRUCTION_DERIVED(PlayerServerObjectInitData);
};

EXTERN_GLOBAL_ASSET_ARRAY(ConfigPtr<PlayerConfig>, g_PlayerConfig);
DECLARE_STATIC_LIST_TYPE(PlayerConfigPtr, g_PlayerConfig);

class PlayerServerObject : public GameServerObjectBase
{
public:
  DECLARE_SERVER_OBJECT;

  PlayerServerObject() = default;
  PlayerServerObject(const PlayerServerObject & rhs) = default;
  PlayerServerObject(PlayerServerObject && rhs) = default;

  PlayerServerObject & operator = (const PlayerServerObject & rhs) = default;
  PlayerServerObject & operator = (PlayerServerObject && rhs) = default;

  void Init(const PlayerServerObjectInitData & init_data, GameWorld & world);
  void UpdateFirst(GameWorld & world);
  void UpdateMiddle(GameWorld & world);
  void UpdateLast(GameWorld & world);

  void ResetState(GameWorld & world);

  MoverResult MoveCheckCollisionDatabase(GameWorld & world, const GameNetVec2 & extra_movement = {});

#ifdef PLATFORMER_MOVEMENT
  void Jump(GameWorld & world);
#endif

  bool SERVER_OBJECT_EVENT_HANDLER HandlePlaceholderEvent(const PlaceholderEvent & ev, const EventMetaData & meta);
  bool SERVER_OBJECT_EVENT_HANDLER HandleDamageEvent(const DamageEvent & ev, const EventMetaData & meta);
  bool SERVER_OBJECT_EVENT_HANDLER HandleDealDamageEvent(const DealDamageAnimationEvent & ev, const EventMetaData & meta);

  virtual Optional<AnimationState> GetAnimationState() const override;
  virtual void SetAnimationState(const AnimationState & anim_state) override;
  virtual Optional<int> GetAssociatedPlayer(GameWorld & world) const override;
  virtual int GetTeam(GameWorld & world) const;

  virtual const SpritePtr & GetSprite() const override;
  virtual Optional<CharacterFacing> GetFacing() const override;

  const ConfigPtr<PlayerConfig> & GetConfig() const;
  virtual czstr GetEntityBinding() const override;
  virtual czstr GetDefaultEntityBinding() const override;

  template <typename State>
  NullOptPtr<State> TransitionToState(GameWorld & world)
  {
    NetPolymorphic<PlayerStateBase> new_state(NetPolymorphicTypeInit<State>{});
    m_State->Cleanup(*this, world);
    new_state->Init(*this, world);
    m_State->Destroy(*this, world);
    m_State = std::move(new_state);

    if (m_Retransition)
    {
      m_State->Transition(*this, world);
    }

    return m_State.Get<State>();
  }

public:
  GameNetVec2 m_Velocity = {};

#ifdef PLATFORMER_MOVEMENT
  bool m_OnGround = true;

#ifdef MOVER_ONE_WAY_COLLISION
  bool m_FallThrough = false;
  bool m_OnOneWayCollision = false;
#endif
#endif

  NetRangedNumber<int, -1, 30> m_AnimIndex = -1;
  NetRangedNumber<int, 0, 31> m_AnimFrame = 0;
  NetRangedNumber<int, 0, 63> m_AnimDelay = 0;
  NetEnum<CharacterFacing> m_Facing = CharacterFacing::kRight;

  uint8_t m_Health = 255;

  NetRangedNumber<int, 0, 31> m_AttackId = 0;
  bool m_Invulnerable = false;

  NetRangedNumber<int, 0, 20> m_RefireTime = 0;

  ClientInput m_Input;

  NetPolymorphic<PlayerStateBase> m_State;
  PlayerConfigPtr m_Config;

private:
  bool m_Retransition = false;
  std::vector<uint32_t> m_ProcessedAttacks;
};
