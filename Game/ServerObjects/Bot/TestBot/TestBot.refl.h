#pragma once

#include "Game/GameCommon.h"

#include "Game/GameLogicContainer.h"
#include "Game/GameServerEventSender.h"
#include "Game/GameStage.h"
#include "Game/Systems/GameLogicSystems.h"

#include "Runtime/ServerObject/ServerObject.h"
#include "Runtime/ServerObject/ServerObjectInitData.refl.h"
#include "Runtime/ServerObject/ServerObjectRegistrationMacros.h"

struct TestBotInitData : public ServerObjectInitData
{
  STORM_DATA_DEFAULT_CONSTRUCTION_DERIVED(TestBotInitData);
};

class TestBot : public ServerObject
{
public:
  DECLARE_SERVER_OBJECT;

  TestBot() = default;
  TestBot(const TestBot & rhs) = default;
  TestBot(TestBot && rhs) = default;

  TestBot & operator = (const TestBot & rhs) = default;
  TestBot & operator = (TestBot && rhs) = default;

  void Init(const TestBotInitData & init_data);
  void UpdateFirst(GameLogicContainer & game_container);
  void UpdateMiddle(GameLogicContainer & game_container);
  
  virtual void InitPosition(const Vector2 & pos) override;
  virtual Vector2 GetPosition(GameLogicContainer & game_container) const override;

  virtual czstr GetDefaultEntityBinding() const override;
public:
  // Serialized variables
  GameNetVec2 m_Position = {};
};
