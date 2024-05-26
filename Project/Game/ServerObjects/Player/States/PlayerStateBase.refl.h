#pragma once

#include "StormNet/NetReflectionStruct.h"
#include "StormNet/NetReflectionTypeDatabase.h"

#include "Game/GameCommon.h"
#include "Game/GameTypes.h"
#include "GameShared/GameWorld.h"

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

  virtual void Init(PlayerServerObject & player, GameWorld & world) {};
  virtual void PreUpdate(PlayerServerObject & player, GameWorld & world) {};

  virtual void Move(PlayerServerObject & player, GameWorld & world) {};
  virtual void Transition(PlayerServerObject & player, GameWorld & world) {};
  virtual void Animate(PlayerServerObject & player, GameWorld & world) {};

  virtual void PostUpdate(PlayerServerObject & player, GameWorld & world) {};

  virtual void Cleanup(PlayerServerObject & player, GameWorld & world) {};
  virtual void Destroy(PlayerServerObject & player, GameWorld & world) {};

};

template <typename T>
using PlayerStateEventHandler = EventHandler<T>;
