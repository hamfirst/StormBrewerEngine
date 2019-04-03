#pragma once

#include <StormRefl/StormRefl.h>
#include <StormData/StormDataTypes.h>

#include <HurricaneDDS/DDSDataObject.h>

#include "LobbyConfig.h"

#ifdef ENABLE_GAME_LIST

struct ServerListGame
{
  STORM_DATA_DEFAULT_CONSTRUCTION(ServerListGame);

  int m_MaxPlayers;
  RInt m_CurPlayers;
  RInt m_CurObservers;
  RBool m_Started;
  std::string m_Name;
  std::string m_Map;
  bool m_PasswordProtected;
};


struct ServerList
{
public:
  DDS_SHARED_OBJECT;

  ServerList(DDSObjectInterface & iface);

  void STORM_REFL_FUNC AddGame(DDSKey game_key, std::string name, std::string map, int cur_players, int max_players, bool password);
  void STORM_REFL_FUNC UpdateGame(DDSKey game_key, int cur_players, int cur_observer);
  void STORM_REFL_FUNC StartGame(DDSKey game_key);
  void STORM_REFL_FUNC RemoveGame(DDSKey game_key);

public:

  RMap<DDSKey, ServerListGame> m_GameList;

private:
  STORM_REFL_IGNORE DDSObjectInterface & m_Interface;
};

#endif
