
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

  int max_teams = GetMaxTeams(map_props, settings);
  int max_players_based_on_teams = 0;

  for(int team = 0; team < max_teams; ++team)
  {
    max_players_based_on_teams += GetMaxTeamSize(team, map_props, settings);
  }

  return std::min(max_players, max_players_based_on_teams);
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
  return kMaxPlayers / GetMaxTeams(map_props, settings);
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

bool IsGameFull(const std::vector<int> & team_counts, const std::vector<int> & max_team_sizes,
        const MapPropertiesDef & map_props, const GameInitSettings & settings)
{
  assert(GetMaxTeams(map_props, settings) == team_counts.size());
  assert(team_counts.size() == max_team_sizes.size());

  for(auto index = 0; index < team_counts.size(); ++index)
  {
    if(team_counts[index] != max_team_sizes[index])
    {
      return false;
    }
  }

  return true;
}

bool IsGameFullEnoughToStart(const std::vector<int> & team_counts, const std::vector<int> & max_team_sizes,
        const MapPropertiesDef & map_props, const GameInitSettings & settings)
{
  return IsGameFull(team_counts, max_team_sizes, map_props, settings);
}
