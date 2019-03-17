#pragma once

#include <StormRefl/StormRefl.h>
#include <StormData/StormDataTypes.h>

#include <HurricaneDDS/DDSDataObject.h>

#include "LobbyConfig.h"
#include "GooglePlatform.refl.h"

#include <mbedtls/pk.h>


struct ServerManager
{
public:
  DDS_SHARED_OBJECT;

  ServerManager(DDSObjectInterface & iface);
  ~ServerManager();

  void Initialize();

//  void STORM_REFL_FUNC AddServer(DDSKey server_key, std::string server_name, std::string location, std::string server_host, int ping_port);
//  void STORM_REFL_FUNC RemoveServer(DDSKey server_key);
//
//  void STORM_REFL_FUNC AddGame(DDSKey server_key, int game_id, std::string name, std::string map, int cur_players, int max_players, bool password);
//  void STORM_REFL_FUNC UpdateGame(DDSKey server_key, int game_id, int cur_players, int cur_observer);
//  void STORM_REFL_FUNC StartGame(DDSKey server_key, int game_id);
//  void STORM_REFL_FUNC RemoveGame(DDSKey server_key, int game_id);
//
//
//  void STORM_REFL_FUNC HangUpAllServers();


  void STORM_REFL_FUNC RequestNewToken();
  void STORM_REFL_FUNC HandleTokenResponse(bool success, std::string body, std::string headers);

  void CreateServerInstance(const std::string & zone);

private:


public:


private:
  STORM_REFL_IGNORE DDSObjectInterface & m_Interface;
  STORM_REFL_IGNORE GoogleCredentialsInfo m_CredentialsInfo;

  STORM_REFL_IGNORE mbedtls_pk_context m_PKContext;
  STORM_REFL_IGNORE std::string m_AuthorizationHeader;
  STORM_REFL_IGNORE GooglePlatformSettings m_Settings;
  STORM_REFL_IGNORE std::string m_ProjectName;

  STORM_REFL_IGNORE std::string m_CreateInstanceTemplate;
};
