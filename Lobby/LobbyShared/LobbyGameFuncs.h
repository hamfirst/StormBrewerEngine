
#pragma once

#include <cstdint>
#include <vector>

struct GameInitSettings;

struct LobbyMapProperties;
struct MapPropertiesDef;

int GetRandomTeam(const std::vector<int> & team_counts, uint32_t random_number);
int GetMaxPlayers(const MapPropertiesDef & map_props, const GameInitSettings & settings);
int GetMaxTeams(const MapPropertiesDef & map_props, const GameInitSettings & settings);
int GetMaxTeamSize(int team, const MapPropertiesDef & map_props, const GameInitSettings & settings);
bool DoAllTeamsHavePlayers(const std::vector<int> & team_counts, const MapPropertiesDef & map_props, const GameInitSettings & settings);
bool IsGameFull(const std::vector<int> & team_counts, const MapPropertiesDef & map_props, const GameInitSettings & settings);
bool IsGameFullEnoughToStart(const std::vector<int> & team_counts, const MapPropertiesDef & map_props, const GameInitSettings & settings);
