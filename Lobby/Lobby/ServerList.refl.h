#pragma once

#include <StormRefl/StormRefl.h>
#include <StormData/StormDataTypes.h>

#include <HurricaneDDS/DDSDataObject.h>

#include "LobbyConfig.h"

#ifdef ENABLE_SERVER_LIST

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

struct ServerListServer
{
  STORM_DATA_DEFAULT_CONSTRUCTION(ServerListServer);

  std::string m_Name;
  std::string m_Location;
  std::string m_Host;
  int m_PingPort;
  
  RMergeList<ServerListGame> m_Games;
};


struct ServerList
{
public:
  DDS_SHARED_OBJECT;

  ServerList(DDSObjectInterface & iface);

  void STORM_REFL_FUNC AddServer(DDSKey server_key, std::string server_name, std::string location, std::string server_host, int ping_port);
  void STORM_REFL_FUNC RemoveServer(DDSKey server_key);

  void STORM_REFL_FUNC AddGame(DDSKey server_key, int game_id, std::string name, std::string map, int cur_players, int max_players, bool password);
  void STORM_REFL_FUNC UpdateGame(DDSKey server_key, int game_id, int cur_players, int cur_observer);
  void STORM_REFL_FUNC StartGame(DDSKey server_key, int game_id);
  void STORM_REFL_FUNC RemoveGame(DDSKey server_key, int game_id);

  void STORM_REFL_FUNC HangUpAllServers();

public:

  RMap<DDSKey, ServerListServer> m_ServerList;

private:
  STORM_REFL_IGNORE DDSObjectInterface & m_Interface;
};

#endif