
#include "Game/GameCommon.h"
#include "Game/AI/PlayerAI.h"
#include "Game/Stage/GameStage.h"
#include "Game/ServerObjects/Player/PlayerServerObject.refl.h"

#include "Runtime/ServerObject/ServerObjectManager.h"

static GameNetVal kBallRadius = GameNetVal("7");

auto kRandDashAngleMax = GameNetVal("0.2");
auto kRandDashAngleMin = GameNetVal(-kRandDashAngleMax);

void PlayerAI::InitAI(GameWorld & game, std::size_t player_index)
{
  auto & ai_info = game.GetInstanceData().m_AIPlayerInfo[player_index];
  auto player_obj = game.GetObjectManager().GetReservedSlotObjectAs<PlayerServerObject>(player_index);

}

void PlayerAI::UpdateAI(GameWorld & game, std::size_t player_index)
{
  auto & player_info = game.GetLowFrequencyInstanceData().m_Players[player_index];
  auto & ai_info = game.GetInstanceData().m_AIPlayerInfo[player_index];
  auto player_obj = game.GetObjectManager().GetReservedSlotObjectAs<PlayerServerObject>(player_index);

  if (player_obj == nullptr)
  {
    return;
  }
}
