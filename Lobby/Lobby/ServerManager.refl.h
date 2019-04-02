#pragma once

#include <StormRefl/StormRefl.h>
#include <StormData/StormDataTypes.h>

#include <HurricaneDDS/DDSDataObject.h>
#include <HurricaneDDS/DDSKey.h>

#include "LobbyConfig.h"
#include "GooglePlatform.refl.h"

#include <mbedtls/pk.h>

class StormBootstrap;

struct PendingServer
{
  std::string m_Zone;
  int m_ZoneIndex = -1;
  std::string m_InstanceName;
  std::string m_ResourceId;
  time_t m_StartTime;
};

struct ActiveServerGame
{
  DDSKey m_GameId;

};

struct ActiveServer
{
  int m_ZoneIndex = -1;

  uint32_t m_RemoteIp;
  uint16_t m_RemotePort;
  std::vector<ActiveServerGame> m_ActiveGames;
};

struct GameRequest
{
  int m_Zone;
  DDSKey m_GameId;
};

struct ServerManager
{
public:
  DDS_SHARED_OBJECT;

  ServerManager(DDSObjectInterface & iface);
  ~ServerManager();

  void Initialize();
  void RequestServerList(const std::string & zone, const std::string & page_token, StormBootstrap & bootstrap);
  void HandleServerListResponse(const std::string & response_data, const std::string & zone, StormBootstrap & bootstrap);

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

  void STORM_REFL_FUNC CreateServerInstance(int zone_index);
  void STORM_REFL_FUNC HandleCreateServerResponse(int zone_index, bool success, std::string body, std::string headers);

  void StopServerInstance(const std::string & zone, const std::string & resource_id);
  void STORM_REFL_FUNC HandleStopServerResponse(bool success, std::string body, std::string headers);

  void STORM_REFL_FUNC CheckForServerRequests();
  void STORM_REFL_FUNC CheckForTimedOutServers();

private:

  std::string GetTokenAssertion();

public:


private:
  STORM_REFL_IGNORE DDSObjectInterface & m_Interface;
  STORM_REFL_IGNORE GoogleCredentialsInfo m_CredentialsInfo;

  STORM_REFL_IGNORE mbedtls_pk_context m_PKContext;
  STORM_REFL_IGNORE std::string m_AuthorizationHeader;
  STORM_REFL_IGNORE GooglePlatformSettings m_Settings;
  STORM_REFL_IGNORE std::string m_ProjectNameLowercase;

  STORM_REFL_IGNORE std::string m_CreateInstanceTemplate;

  STORM_REFL_IGNORE std::vector<GameRequest> m_GameRequests;

  STORM_REFL_IGNORE std::vector<int> m_RequestedServersInZone;
  STORM_REFL_IGNORE std::vector<PendingServer> m_PendingServers;

};
