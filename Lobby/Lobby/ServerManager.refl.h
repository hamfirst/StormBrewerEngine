#pragma once

#include <StormRefl/StormRefl.h>
#include <StormData/StormDataTypes.h>

#include <HurricaneDDS/DDSDataObject.h>

#include "LobbyConfig.h"

struct GoogleCredentialsInfo
{
  STORM_REFL;

  std::string type;
  std::string project_id;
  std::string private_key_id;
  std::string private_key;
  std::string client_email;
  std::string client_id;
  std::string auth_uri;
  std::string token_uri;
  std::string auth_provider_x509_cert_url;
  std::string client_x509_cert_url;
};

struct GoogleAssertionHeader
{
  STORM_REFL;

  std::string alg;
  std::string kid;
  std::string typ;
};

struct GoogleAssertionPayload
{
  STORM_REFL;

  std::string iss;
  std::string scope;
  std::string aud;
  std::string iat;
  std::string exp;
};


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


struct ServerManager
{
public:
  DDS_SHARED_OBJECT;

  ServerManager(DDSObjectInterface & iface);

  void STORM_REFL_FUNC AddServer(DDSKey server_key, std::string server_name, std::string location, std::string server_host, int ping_port);
  void STORM_REFL_FUNC RemoveServer(DDSKey server_key);

  void STORM_REFL_FUNC AddGame(DDSKey server_key, int game_id, std::string name, std::string map, int cur_players, int max_players, bool password);
  void STORM_REFL_FUNC UpdateGame(DDSKey server_key, int game_id, int cur_players, int cur_observer);
  void STORM_REFL_FUNC StartGame(DDSKey server_key, int game_id);
  void STORM_REFL_FUNC RemoveGame(DDSKey server_key, int game_id);

  void STORM_REFL_FUNC HangUpAllServers();

private:

  void RequestNewToken();

public:

  RMap<DDSKey, ServerListServer> m_ServerList;

private:
  STORM_REFL_IGNORE DDSObjectInterface & m_Interface;
  STORM_REFL_IGNORE GoogleCredentialsInfo m_CredentialsInfo;
};
