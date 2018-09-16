
#include "Game/GameCommon.h"

#include "Game/GameController.refl.h"
#include "Game/GameServerEventSender.h"

#include "Game/ServerObjects/Bot/TestBot/TestBot.refl.h"
#include "Game/ServerObjects/Bot/TestBot/TestBot.refl.meta.h"

void TestBot::Init(const TestBotInitData & init_data)
{

}

void TestBot::UpdateFirst(GameLogicContainer & game_container)
{

}

void TestBot::UpdateMiddle(GameLogicContainer & game_container)
{

}

void TestBot::InitPosition(const Vector2 & pos)
{
  m_Position = GameNetVec2(pos.x, pos.y);
}

Vector2 TestBot::GetPosition(GameLogicContainer & game_container) const
{
  return m_Position;
}

czstr TestBot::GetDefaultEntityBinding() const
{
  return {entity_binding};
}
