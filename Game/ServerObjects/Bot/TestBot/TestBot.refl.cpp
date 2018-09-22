
#include "Game/GameCommon.h"

#include "Game/GameController.refl.h"
#include "Game/GameServerEventSender.h"

#include "Game/ServerObjects/Bot/BotBehaviorTree.h"
#include "Game/ServerObjects/Bot/TestBot/TestBot.refl.h"
#include "Game/ServerObjects/Bot/TestBot/TestBot.refl.meta.h"

#include "Runtime/Entity/EntityResource.h"

GLOBAL_ASSET(EntityResourcePtr, "./Entities/TestBot.entity", g_TestBotEntity);

static StormBehaviorTreeTemplate<BotServerObject, GameLogicContainer> BehaviorTreeTemplate =
  SELECT()
    .AddChild(
            STATE<PlayAnimationBotState>(COMPILE_TIME_CRC32_STR("Idle"))
            )
;

std::vector<void *> s_MemoryPtrs;

TestBot::TestBot() :
  BotServerObject()
{
  s_MemoryPtrs.push_back(this);
}

TestBot::TestBot(const TestBot & rhs) :
  BotServerObject(rhs)
{
  s_MemoryPtrs.push_back(this);
  m_Tree = rhs.m_Tree;
}

TestBot::TestBot(TestBot && rhs) :
  BotServerObject(rhs)
{
  s_MemoryPtrs.push_back(this);
  m_Tree = std::move(rhs.m_Tree);
}

TestBot::~TestBot()
{
  if(vremove_quick(s_MemoryPtrs, (void *)this) == false)
  {
    assert(false);
  }
}

void TestBot::Init(const TestBotInitData & init_data)
{
  m_Tree.SetBehaviorTree(&BehaviorTreeTemplate);
}

void TestBot::UpdateFirst(GameLogicContainer & game_container)
{
  BotServerObject::UpdateFirst(game_container);
}

void TestBot::UpdateMiddle(GameLogicContainer & game_container)
{
  BotServerObject::UpdateMiddle(game_container);
}

czstr TestBot::GetDefaultEntityBinding() const
{
  return "./Entities/TestBot.entity";
}

SpritePtr TestBot::GetSprite() const
{
  return g_TestBotEntity->GetSprite();
}

NullOptPtr<BotBehaviorTree> TestBot::GetBehaviorTree()
{
  return &m_Tree;
}
