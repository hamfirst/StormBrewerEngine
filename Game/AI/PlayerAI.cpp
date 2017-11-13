
#include "Game/GameCommon.h"
#include "Game/AI/PlayerAI.h"
#include "Game/GameStage.h"
#include "Game/ServerObjects/Player/PlayerServerObject.refl.h"

#include "Runtime/ServerObject/ServerObjectManager.h"

static GameNetVal kBallRadius = GameNetVal("7");

auto kRandDashAngleMax = GameNetVal("0.2");
auto kRandDashAngleMin = GameNetVal(-kRandDashAngleMax);

void PlayerAI::InitAI(GameLogicContainer & game, std::size_t player_index)
{
  auto & ai_info = game.GetInstanceData().m_Players[player_index].m_AIPlayerInfo.Value();
  auto player_obj = game.GetObjectManager().GetReservedSlotObjectAs<PlayerServerObject>(player_index);

}

void PlayerAI::UpdateAI(GameLogicContainer & game, std::size_t player_index)
{
  auto & player_info = game.GetInstanceData().m_Players[player_index];
  auto & ai_info = player_info.m_AIPlayerInfo.Value();
  auto player_obj = game.GetObjectManager().GetReservedSlotObjectAs<PlayerServerObject>(player_index);

  if (player_obj == nullptr)
  {
    return;
  }
}
