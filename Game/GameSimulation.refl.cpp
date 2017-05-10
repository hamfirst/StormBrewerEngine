
#include "GameSimulation.refl.meta.h"

void GameSimulation::Init(GameStage & stage)
{

}

bool GameSimulation::Step(GameStage & stage, GameInputState & input, NullOptPtr<SimEventHandler> event_hander, bool authority)
{
  return false;
}

void GameSimulation::AddPlayer(GameStage & stage, int player_index, const std::string & name, int team, uint32_t seed)
{
  GamePlayer player;
  player.m_Name = name;
  player.m_Team = team;

  m_Players.EmplaceAt(player_index, std::move(player));
}

void GameSimulation::RemovePlayer(int player_index)
{
  m_Players.RemoveAt(player_index);
}
