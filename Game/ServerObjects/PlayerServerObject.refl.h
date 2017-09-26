
#pragma once

#include "Foundation/Common.h"

#include "Game/GameServerTypes.h"
#include "Game/GameLogicContainer.h"

#include "Server/ServerObject/ServerObject.h"
#include "Server/ServerObject/ServerObjectInitData.refl.h"
#include "Server/ServerObject/ServerObjectRegistrationMacros.h"

struct PlayerServerObjectInitData : public ServerObjectInitData
{
  STORM_DATA_DEFAULT_CONSTRUCTION(PlayerServerObjectInitData);
};

class PlayerServerObject : public ServerObject
{
public:
  DECLARE_SERVER_OBJECT;
  STORM_REFL;

  PlayerServerObject() = default;
  PlayerServerObject(const PlayerServerObject & rhs) = default;
  PlayerServerObject(PlayerServerObject && rhs) = default;

  PlayerServerObject & operator = (const PlayerServerObject & rhs) = default;
  PlayerServerObject & operator = (PlayerServerObject && rhs) = default;

  void Init(const PlayerServerObjectInitData & init_data);
  void UpdateFirst(GameLogicContainer & game_container);

  virtual czstr GetEntityBinding() override;

public:
  GameNetVec2 m_Position = {};
  GameNetVec2 m_Velocity = {};

  GameNetVal m_InputAngle = GameNetVal(0);
  GameNetVal m_InputStrength = GameNetVal(0);
  uint8_t m_Controls = 0;
};
