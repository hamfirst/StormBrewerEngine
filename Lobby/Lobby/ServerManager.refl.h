#pragma once

#include "StormRefl/StormRefl.h"
#include "StormData/StormDataTypes.h"

#include "HurricaneDDS/DDSDataObject.h"
#include "HurricaneDDS/DDSKey.h"

#include "Foundation/Allocator/IdAllocator.h"

#include "LobbyShared/SharedTypes.refl.h"

#include "LobbyConfig.h"
#include "GooglePlatform.refl.h"
#include "GameServerMessages.refl.h"

//#define ENABLE_GOOGLE_CLOUD

#ifdef ENABLE_GOOGLE_CLOUD
#include <mbedtls/pk.h>
#endif

#ifdef _LINUX
using ProcessIdentifier = pid_t;
#else
using ProcessIdentifier = void *;
#endif


class StormBootstrap;

struct PendingServer
{
  int m_ZoneIndex = -1;
  std::string m_ResourceId;
  time_t m_StartTime;
};

struct ActiveServer
{
  DDSKey m_ConnectionKey = 0;
  int m_ZoneIndex = -1;

  std::string m_Name;
  std::string m_ResourceId;
  std::string m_RemoteIp;
  uint16_t m_RemotePort = 0;
  int m_ActiveGames = 0;
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

  explicit ServerManager(DDSObjectInterface & iface);
  ~ServerManager();

  void Initialize();
  void Update();

  void CreateServerInstance(int zone_index);
  void StopServerInstance(const std::string & zone, const std::string & resource_id);
  void StopServerInstance(int zone_index, const std::string & resource_id);

#ifdef ENABLE_GOOGLE_CLOUD

  void RequestServerList(const std::string & zone, const std::string & page_token, StormBootstrap & bootstrap);
  void HandleServerListResponse(const std::string & response_data, const std::string & zone, StormBootstrap & bootstrap);

  void STORM_REFL_FUNC RequestNewCloudToken();
  void STORM_REFL_FUNC HandleCloudTokenResponse(bool success, std::string body, std::string headers);

  void CreateCloudServerInstance(int zone_index);
  void STORM_REFL_FUNC HandleCreateServerResponse(int zone_index, bool success, std::string body, std::string headers);

  void StopCloudServerInstance(const std::string & zone, const std::string & resource_id);
  void STORM_REFL_FUNC HandleStopServerResponse(bool success, std::string body, std::string headers);

#endif

  void STORM_REFL_FUNC AssignGameServer(DDSKey game_id, int zone);

  void STORM_REFL_FUNC HandleServerConnected(DDSKey game_server_key, const GameServerInfo & server_info, int num_active_games);
  void STORM_REFL_FUNC HandleServerDisconnected(DDSKey game_server_key);
  void STORM_REFL_FUNC HandleGameEnded(DDSKey game_server_key);

  void STORM_REFL_FUNC CheckForTimedOutServers();
  void STORM_REFL_FUNC CheckForAssignableGames();

private:

#ifdef ENABLE_GOOGLE_CLOUD
  std::string GetCloudTokenAssertion();
#endif

  void CreateDebugServer();
  void StopDebugServer(std::size_t server_id);

private:
  DDSObjectInterface & m_Interface;

#ifdef ENABLE_GOOGLE_CLOUDE
  GoogleCredentialsInfo m_CredentialsInfo;
  mbedtls_pk_context m_PKContext;

  std::string m_AuthorizationHeader;
  GooglePlatformSettings m_Settings;
  std::string m_ProjectNameLowercase;

  std::string m_CreateInstanceTemplate;
#endif

  IdAllocator m_ServerIdAllocator;

  std::map<int, ProcessIdentifier> m_DebugServers;

  std::vector<GameRequest> m_GameRequests;

  std::vector<int> m_RequestedServersInZone;
  std::vector<PendingServer> m_PendingServers;
  std::vector<ActiveServer> m_ActiveServers;
};
