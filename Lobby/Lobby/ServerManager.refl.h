#pragma once

#include <StormRefl/StormRefl.h>
#include <StormData/StormDataTypes.h>

#include <HurricaneDDS/DDSDataObject.h>
#include <HurricaneDDS/DDSKey.h>

#include "SharedTypes.refl.h"
#include "LobbyConfig.h"
#include "GooglePlatform.refl.h"

#ifdef ENABLE_GOOGLE_CLOUD
#include <mbedtls/pk.h>
#else
#include "Foundation/Allocator/IdAllocator.h"
#endif

#ifdef _LINUX
using ProcessIdentifier = pid_t;
#else
using ProcessIdentifier = void *;
#endif


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
  void Update();

#ifdef ENABLE_GOOGLE_CLOUD

  void RequestServerList(const std::string & zone, const std::string & page_token, StormBootstrap & bootstrap);
  void HandleServerListResponse(const std::string & response_data, const std::string & zone, StormBootstrap & bootstrap);

  void STORM_REFL_FUNC RequestNewCloudToken();
  void STORM_REFL_FUNC HandleCloudTokenResponse(bool success, std::string body, std::string headers);

  void CreateServerInstance(int zone_index);
  void STORM_REFL_FUNC HandleCreateServerResponse(int zone_index, bool success, std::string body, std::string headers);

  void StopServerInstance(const std::string & zone, const std::string & resource_id);
  void STORM_REFL_FUNC HandleStopServerResponse(bool success, std::string body, std::string headers);

#else

  void CreateServerInstance(int zone_index);
  void StopServerInstance(int zone_index, const std::string & resource_id);

#endif


  void STORM_REFL_FUNC AssignGameServer(DDSKey game_id, int zone);
  void STORM_REFL_FUNC CheckForServerRequests();
  void STORM_REFL_FUNC CheckForTimedOutServers();

private:

#ifdef ENABLE_GOOGLE_CLOUD
  std::string GetCloudTokenAssertion();
#endif

  void CreateDebugServer();
  void StopDebugServer(std::size_t server_id);

private:
  DDSObjectInterface & m_Interface;

#ifdef ENABLE_GOOGLE_CLOUD
  GoogleCredentialsInfo m_CredentialsInfo;

  mbedtls_pk_context m_PKContext;
  std::string m_AuthorizationHeader;
  GooglePlatformSettings m_Settings;
  std::string m_ProjectNameLowercase;

  std::string m_CreateInstanceTemplate;
#else
  IdAllocator m_ServerIdAllocator;
  std::map<int, ProcessIdentifier> m_DebugServers;
#endif

  std::vector<GameRequest> m_GameRequests;

  std::vector<int> m_RequestedServersInZone;
  std::vector<PendingServer> m_PendingServers;
  std::vector<ActiveServer> m_ActiveServers;
};
