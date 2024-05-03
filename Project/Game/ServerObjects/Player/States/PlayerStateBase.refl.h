#pragma once

#include "StormNet/NetReflectionStruct.h"
#include "StormNet/NetReflectionTypeDatabase.h"

#include "Game/GameCommon.h"
#include "Game/GameTypes.h"
#include "GameShared/GameLogicContainer.h"

#include "Game/ServerObjects/Player/Config/PlayerConfig.refl.h"

#include "Runtime/Event/EventHandler.h"
#include "Runtime/Config/ConfigResource.h"

#include "StormRefl/StormReflMetaInfoBase.h"


#define DECLARE_PLAYER_STATE \
        NET_REFL; \
        STORM_REFL_FUNCS;

class PlayerServerObject;

class PlayerStateBase
{
public:
  DECLARE_PLAYER_STATE;
  NET_DECLARE_BASE_TYPE;

  virtual void Init(PlayerServerObject & player, GameLogicContainer & game_container) {};
  virtual void PreUpdate(PlayerServerObject & player, GameLogicContainer & game_container) {};

  virtual void Move(PlayerServerObject & player, GameLogicContainer & game_container) {};
  virtual void Transition(PlayerServerObject & player, GameLogicContainer & game_container) {};
  virtual void Animate(PlayerServerObject & player, GameLogicContainer & game_container) {};

  virtual void PostUpdate(PlayerServerObject & player, GameLogicContainer & game_container) {};

  virtual void Cleanup(PlayerServerObject & player, GameLogicContainer & game_container) {};
  virtual void Destroy(PlayerServerObject & player, GameLogicContainer & game_container) {};

};

template <typename T>
using PlayerStateEventHandler = EventHandler<T>;
