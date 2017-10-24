
#pragma once

#include "Game/GameCommon.h"
#include "Game/GameServerTypes.h"
#include "Game/GameLogicContainer.h"
#include "Game/GameNetworkData.refl.h"

#include "Game/ServerObjects/Player/States/PlayerStateDefault.refl.h"

#include "Game/GameplayEvents/PlaceholderEvent.h"

#include "Server/ServerObject/ServerObject.h"
#include "Server/ServerObject/ServerObjectInitData.refl.h"
#include "Server/ServerObject/ServerObjectRegistrationMacros.h"

#include "StormNet/NetReflectionPolymorphic.h"

class PlayerStateDefault;

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

  void Jump(GameLogicContainer & game_container);

  MoverResult MoveCheckCollisionDatabase(GameLogicContainer & game_container);
  void MoveCheckIntersectionDatabase(GameLogicContainer & game_container);

  void SERVER_OBJECT_EVENT_HANDLER HandlePlaceholderEvent(const PlaceholderEvent & ev, GameLogicContainer & game_container);

  virtual czstr GetEntityBinding() override;

public:
  GameNetVec2 m_Position = {};
  GameNetVec2 m_Velocity = {};

  bool m_OnGround = false;

  ClientInput m_Input;

  NetPolymorphic<PlayerStateDefault> m_State;

private:
  Box m_MoveBox;
};
