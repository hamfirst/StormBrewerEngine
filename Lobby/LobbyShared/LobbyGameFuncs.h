
#pragma once

#include <cstdint>
#include <vector>

struct GameInitSettings;

struct LobbyMapProperties;
struct MapPropertiesDef;

int GetRandomTeam(const std::vector<int> & team_counts, uint32_t random_number, const MapPropertiesDef & map_props, const GameInitSettings & settings);
int GetMaxPlayers(const MapPropertiesDef & map_props, const GameInitSettings & settings);
int GetMaxTeams(const MapPropertiesDef & map_props, const GameInitSettings & settings);
int GetMaxTeamSize(int team, const MapPropertiesDef & map_props, const GameInitSettings & settings);
bool DoAllTeamsHavePlayers(const std::vector<int> & team_counts, const MapPropertiesDef & map_props, const GameInitSettings & settings);
bool IsGameFull(const std::vector<int> & team_counts, const std::vector<int> & max_team_sizes, const MapPropertiesDef & map_props, const GameInitSettings & settings);
bool IsGameFullEnoughToStart(const std::vector<int> & team_counts, const std::vector<int> & max_team_sizes, const MapPropertiesDef & map_props, const GameInitSettings & settings);
