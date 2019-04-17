
#include "LobbyShared/LobbyGameFuncs.h"

#include "Game/GameNetworkData.refl.h"
#include "Runtime/Map/MapPropertiesDef.refl.h"

int GetRandomTeam(const std::vector<int> & team_counts, uint32_t random_number, const MapPropertiesDef & map_props, const GameInitSettings & settings)
{
  assert(GetMaxTeams(map_props, settings) == team_counts.size());

  std::vector<int> best_teams;
  int best_team_count = 100000;

  for (std::size_t index = 0, end = team_counts.size(); index < end; ++index)
  {
    if (team_counts[index] < best_team_count && team_counts[index] < GetMaxTeamSize(index, map_props, settings))
    {
      best_teams.clear();
      best_teams.push_back((int)index);
      best_team_count = team_counts[index];
    }
    else if (team_counts[index] == best_team_count)
    {
      best_teams.push_back((int)index);
    }
  }

  if(best_teams.empty())
  {
    return -1;
  }

  return best_teams[random_number % best_teams.size()];
}

int GetMaxPlayers(const MapPropertiesDef & map_props, const GameInitSettings & settings)
{
  int max_players = kMaxPlayers;

#ifdef NET_USE_PLAYER_LIMIT
  if(map_props.m_PlayerCount != 0)
  {
    max_players = std::min(map_props.m_PlayerCount, max_players);
  }

  if(settings.m_PlayerCount != 0)
  {
    max_players = std::min((int)settings.m_PlayerCount, max_players);
  }
#endif

  return max_players;
}

int GetMaxTeams(const MapPropertiesDef & map_props, const GameInitSettings & settings)
{
  if(map_props.m_MaxTeams != 0)
  {
    return std::min(map_props.m_MaxTeams, kMaxTeams);
  }

  return kMaxTeams;
}

int GetMaxTeamSize(int team, const MapPropertiesDef & map_props, const GameInitSettings & settings)
{
  return GetMaxPlayers(map_props, settings) / GetMaxTeams(map_props, settings);
}

bool DoAllTeamsHavePlayers(const std::vector<int> & team_counts, const MapPropertiesDef & map_props, const GameInitSettings & settings)
{
  assert(GetMaxTeams(map_props, settings) == team_counts.size());
  for(auto & team_size : team_counts)
  {
    if (team_size == 0)
    {
      return false;
    }
  }

  return true;
}

bool IsGameFull(const std::vector<int> & team_counts, const MapPropertiesDef & map_props, const GameInitSettings & settings)
{
  assert(GetMaxTeams(map_props, settings) == team_counts.size());

  int total_players = 0;
  for(auto & team_size : team_counts)
  {
    total_players += (int)team_size;
  }

  return total_players == GetMaxPlayers(map_props, settings);
}

bool IsGameFullEnoughToStart(const std::vector<int> & team_counts, const MapPropertiesDef & map_props, const GameInitSettings & settings)
{
  return DoAllTeamsHavePlayers(team_counts, map_props, settings);
}
