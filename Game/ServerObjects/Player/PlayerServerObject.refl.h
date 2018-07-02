
#pragma once

#include "Game/GameCommon.h"
#include "Game/GameServerTypes.h"
#include "Game/GameLogicContainer.h"
#include "Game/GameNetworkData.refl.h"

#include "Game/ServerObjects/Player/States/PlayerStateBase.refl.h"

#include "Game/GameplayEvents/PlaceholderEvent.h"
#include "Runtime/Sprite/SpriteResource.h"

#include "Runtime/ServerObject/ServerObject.h"
#include "Runtime/ServerObject/ServerObjectInitData.refl.h"
#include "Runtime/ServerObject/ServerObjectRegistrationMacros.h"

#include "StormNet/NetReflectionPolymorphic.h"


enum STORM_REFL_ENUM class PlayerFacing
{
  kLeft,
  kRight,
#ifndef PLATFORMER_MOVEMENT
  kDown,
  kUp,
#endif
};


struct PlayerServerObjectInitData : public ServerObjectInitData
{
  STORM_DATA_DEFAULT_CONSTRUCTION(PlayerServerObjectInitData);
};

class PlayerServerObject : public ServerObject
{
public:
  DECLARE_SERVER_OBJECT;

  PlayerServerObject() = default;
  PlayerServerObject(const PlayerServerObject & rhs) = default;
  PlayerServerObject(PlayerServerObject && rhs) = default;

  PlayerServerObject & operator = (const PlayerServerObject & rhs) = default;
  PlayerServerObject & operator = (PlayerServerObject && rhs) = default;

  void Init(const PlayerServerObjectInitData & init_data);
  void UpdateFirst(GameLogicContainer & game_container);

  MoverResult MoveCheckCollisionDatabase(GameLogicContainer & game_container);
  void MoveCheckIntersectionDatabase(GameLogicContainer & game_container, GameNetVal player_radius, GameNetVal move_threshold);

  bool FrameAdvance(uint32_t anim_name_hash, bool loop = true, int frames = 1);

#ifdef PLATFORMER_MOVEMENT
  void Jump(GameLogicContainer & game_container);
#endif

  bool SERVER_OBJECT_EVENT_HANDLER HandlePlaceholderEvent(PlaceholderEvent & ev, const EventMetaData & meta);

  SpriteResource & GetSprite();
  virtual czstr GetDefaultEntityBinding() override;

  template <typename Target>
  void TriggerAnimationEvents(GameLogicContainer & game_container, Target & target)
  {
    GetSprite().SendEventsTo(target, *this, game_container);
  }

  template <typename State, typename ... Args>
  NullOptPtr<State> TransitionToState(GameLogicContainer & game_container)
  {
    NetPolymorphic<PlayerStateBase> new_state(NetPolymorphicTypeInit<State>{});
    new_state->Init(*this, game_container);
    m_State->Deinit(*this, game_container);
    m_State = std::move(new_state);

    if (m_Retransition)
    {
      m_State->Transition(*this, game_container);
    }

    return m_State.Get<State>();
  }


public:
  GameNetVec2 m_Position = {};
  GameNetVec2 m_Velocity = {};

#ifdef PLATFORMER_MOVEMENT
  bool m_OnGround;
#endif

  NetRangedNumber<int, -1, 30> m_AnimIndex = -1;
  NetRangedNumber<int, 0, 31> m_AnimFrame = 0;
  NetRangedNumber<int, 0, 63> m_AnimDelay = 0;
  NetEnum<PlayerFacing> m_Facing = PlayerFacing::kRight;

  ClientInput m_Input;

  NetPolymorphic<PlayerStateBase> m_State;

private:
  Box m_MoveBox;
  bool m_Retransition = false;
};
