
#pragma once

#include "Game/GameCommon.h"
#include "Game/GameServerTypes.h"
#include "Game/GameLogicContainer.h"

#include "Game/ServerObjects/GameServerObjectBase.refl.h"
#include "Game/ServerObjects/Player/States/PlayerStateBase.refl.h"

#include "Game/GameplayEvents/PlaceholderEvent.h"
#include "Game/Data/DealDamageAnimationEvent.refl.h"

#include "Game/Configs/PlayerConfig.refl.h"

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

extern ConfigPtr<PlayerConfig> g_PlayerConfig[];
extern int g_PlayerConfigCount;

using PlayerConfigPtr = NetReflectionStaticListPtr<ConfigPtr<PlayerConfig>, g_PlayerConfig, &g_PlayerConfigCount>;

class PlayerServerObject : public GameServerObjectBase
{
public:
  DECLARE_SERVER_OBJECT;

  PlayerServerObject() = default;
  PlayerServerObject(const PlayerServerObject & rhs) = default;
  PlayerServerObject(PlayerServerObject && rhs) = default;

  PlayerServerObject & operator = (const PlayerServerObject & rhs) = default;
  PlayerServerObject & operator = (PlayerServerObject && rhs) = default;

  void Init(const PlayerServerObjectInitData & init_data, GameLogicContainer & game_container);
  void UpdateFirst(GameLogicContainer & game_container);
  void UpdateMiddle(GameLogicContainer & game_container);
  void UpdateLast(GameLogicContainer & game_container);

  void ResetState(GameLogicContainer & game_container);

  MoverResult MoveCheckCollisionDatabase(GameLogicContainer & game_container, const GameNetVec2 & extra_movement = {});

#ifdef PLATFORMER_MOVEMENT
  void Jump(GameLogicContainer & game_container);
#endif

  bool SERVER_OBJECT_EVENT_HANDLER HandlePlaceholderEvent(PlaceholderEvent & ev, const EventMetaData & meta);
  bool SERVER_OBJECT_EVENT_HANDLER HandleDamageEvent(DamageEvent & ev, const EventMetaData & meta);
  bool SERVER_OBJECT_EVENT_HANDLER HandleDealDamageEvent(DealDamageAnimationEvent & ev, const EventMetaData & meta);

  virtual Optional<AnimationState> GetAnimationState() const override;
  virtual void SetAnimationState(const AnimationState & anim_state) override;
  virtual Optional<int> GetAssociatedPlayer() const override;

  virtual SpritePtr GetSprite() const override;
  virtual Optional<CharacterFacing> GetFacing() const override;

  const ConfigPtr<PlayerConfig> & GetConfig() const;
  virtual czstr GetDefaultEntityBinding() const override;

  template <typename State>
  NullOptPtr<State> TransitionToState(GameLogicContainer & game_container)
  {
    NetPolymorphic<PlayerStateBase> new_state(NetPolymorphicTypeInit<State>{});
    m_State->Cleanup(*this, game_container);
    new_state->Init(*this, game_container);
    m_State->Destroy(*this, game_container);
    m_State = std::move(new_state);

    if (m_Retransition)
    {
      m_State->Transition(*this, game_container);
    }

    return m_State.Get<State>();
  }


public:
  GameNetVec2 m_Velocity = {};

#ifdef PLATFORMER_MOVEMENT
  bool m_OnGround = true;

  bool m_FallThrough = false;
  bool m_OnOneWayCollision = false;
#endif

  NetRangedNumber<int, -1, 30> m_AnimIndex = -1;
  NetRangedNumber<int, 0, 31> m_AnimFrame = 0;
  NetRangedNumber<int, 0, 63> m_AnimDelay = 0;
  NetEnum<CharacterFacing> m_Facing = CharacterFacing::kRight;

  uint8_t m_Health = 255;

  NetRangedNumber<int, 0, 31> m_AttackId = 0;
  bool m_Invulnerable = false;

  ClientInput m_Input;

#ifdef MOVER_ONE_WAY_COLLISION
  bool m_FallThrough = false;
#endif

  NetPolymorphic<PlayerStateBase> m_State;
  PlayerConfigPtr m_Config;

private:
  bool m_Retransition = false;
  std::vector<uint32_t> m_ProcessedAttacks;
};
