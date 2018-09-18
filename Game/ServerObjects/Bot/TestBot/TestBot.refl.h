#pragma once

#include "Game/GameCommon.h"

#include "Game/GameLogicContainer.h"
#include "Game/GameServerEventSender.h"
#include "Game/GameStage.h"
#include "Game/Systems/GameLogicSystems.h"
#include "Game/ServerObjects/Bot/BotServerObject.refl.h"

#include "Runtime/ServerObject/ServerObject.h"
#include "Runtime/ServerObject/ServerObjectInitData.refl.h"
#include "Runtime/ServerObject/ServerObjectRegistrationMacros.h"

struct TestBotInitData : public BotServerObjectInitData
{
  STORM_DATA_DEFAULT_CONSTRUCTION_DERIVED(TestBotInitData);
};

class TestBot : public BotServerObject
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

  virtual czstr GetDefaultEntityBinding() const override;
  virtual SpritePtr GetSprite() const override;

  virtual NullOptPtr<BotBehaviorTree> GetBehaviorTree() override;
public:

  BotBehaviorTree m_Tree;

};
