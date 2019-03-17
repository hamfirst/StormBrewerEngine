
#include "NodeState.h"
#include "DataTypes.h"

#include "UserEndpoint.h"
#include "GameServerEndpoint.h"
#include "BotEndpoint.h"
#include "SteamOpenIdValidatorPage.h"
#include "LobbyConfig.h"

#include <HurricaneDDS/DDSDatabaseConnection.h>
#include <HurricaneDDS/DDSDatabaseConnectionPool.h>
#include <HurricaneDDS/DDSDatabaseSetup.h>
#include <HurricaneDDS/DDSEndpointFactoryList.h>
#include <HurricaneDDS/DDSWebsiteFactoryList.h>
#include <HurricaneDDS/DDSWebsiteFilesystemBuilder.h>


std::unique_ptr<DDSNodeState> CreateNodeState(const NodeSettings & settings)
{
  StormSockets::StormSocketInitSettings backend_settings;
  backend_settings.NumIOThreads = 1;
  backend_settings.NumSendThreads = 1;
  backend_settings.MaxConnections = 20000;

  DDSDatabaseSettings database_settings;
  database_settings.DatabaseHostName = settings.m_DatabaseHost;
  database_settings.DatabasePort = settings.m_DatabasePort;
  database_settings.DatabaseName = DATABASE_NAME;
  database_settings.NumThreads = 1;

  StormSockets::StormSocketClientFrontendHttpSettings http_client_settings;

  StormSockets::StormSocketServerFrontendWebsocketSettings node_server_settings;
  StormSockets::StormSocketClientFrontendWebsocketSettings node_client_settings;
  DDSCoordinatorClientSettings coordinator_client_settings;


  if (settings.m_CoordinatorHostAddress)
  {
    coordinator_client_settings.CoordinatorIpAddr = settings.m_CoordinatorHostAddress;
  }

  if (settings.m_CoordinatorPort)
  {
    coordinator_client_settings.CoordinatorPort = settings.m_CoordinatorPort;
  }

  node_server_settings.ListenSettings.Port = settings.m_NodeNetworkPort;

  StormSockets::StormSocketServerFrontendWebsocketSettings user_endpoint_settings;
  user_endpoint_settings.ListenSettings.Port = settings.m_UserPort;
  user_endpoint_settings.MaxConnections = 20000;
  StormSockets::StormSocketServerFrontendWebsocketSettings server_endpoint_settings;
  server_endpoint_settings.ListenSettings.Port = settings.m_GameServerPort;
#ifdef ENABLE_BOTS
  StormSockets::StormSocketServerFrontendWebsocketSettings bot_endpoint_settings;
  bot_endpoint_settings.ListenSettings.Port = settings.m_BotEndpointPort;
#endif

  StormSockets::StormSocketServerFrontendHttpSettings steam_validation_page_settings;
  steam_validation_page_settings.ListenSettings.Port = settings.m_HTTPTicketPort;

  if (settings.m_HTMLPath)
  {
    DDSWebsiteFilesystemBuilder fs_builder;
    fs_builder.AddDirectory(settings.m_HTMLPath, "/");

    StormSockets::StormSocketServerFrontendHttpSettings static_content_settings;
    static_content_settings.ListenSettings.Port = settings.m_HTTPPort;

    return std::make_unique<DDSNodeState>(
      DataObjectList{}, SharedObjectList{}, backend_settings, node_server_settings, node_client_settings,
      http_client_settings, coordinator_client_settings, database_settings,

#ifdef ENABLE_BOTS
      DDSCreateEndpointType<BotEndpoint>(bot_endpoint_settings),
#endif
#ifdef ENABLE_AUTH_STEAM
      DDSCreateWebsiteType<SteamOpenIdValidatorPage>(steam_validation_page_settings),
#endif
      DDSCreateEndpointType<UserEndpoint>(user_endpoint_settings),
      DDSCreateEndpointType<GameServerEndpoint>(server_endpoint_settings),
      DDSCreateWebsiteStaticContentType(static_content_settings, fs_builder));
  }
  else
  {
    return std::make_unique<DDSNodeState>(
      DataObjectList{}, SharedObjectList{}, backend_settings, node_server_settings, node_client_settings,
      http_client_settings, coordinator_client_settings, database_settings,
#ifdef ENABLE_BOTS
      DDSCreateEndpointType<BotEndpoint>(bot_endpoint_settings),
#endif
#ifdef ENABLE_AUTH_STEAM
      DDSCreateWebsiteType<SteamOpenIdValidatorPage>(steam_validation_page_settings),
#endif
      DDSCreateEndpointType<UserEndpoint>(user_endpoint_settings),
      DDSCreateEndpointType<GameServerEndpoint>(server_endpoint_settings));

  }
}

