#pragma once

#include <StormRefl/StormRefl.h>
#include <StormData/StormDataTypes.h>

#include <HurricaneDDS/DDSDataObject.h>
#include <HurricaneDDS/DDSKey.h>

#include "SharedTypes.refl.h"
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

  void AssignGameServer(DDSKey game_id, int zone);

  void STORM_REFL_FUNC RequestNewCloudToken();
  void STORM_REFL_FUNC HandleCloudTokenResponse(bool success, std::string body, std::string headers);

  void STORM_REFL_FUNC CreateServerInstance(int zone_index);
  void STORM_REFL_FUNC HandleCreateServerResponse(int zone_index, bool success, std::string body, std::string headers);

  void StopServerInstance(const std::string & zone, const std::string & resource_id);
  void STORM_REFL_FUNC HandleStopServerResponse(bool success, std::string body, std::string headers);

  void STORM_REFL_FUNC CheckForServerRequests();
  void STORM_REFL_FUNC CheckForTimedOutServers();

private:

  std::string GetCloudTokenAssertion();

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
