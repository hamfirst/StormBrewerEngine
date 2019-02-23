
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

std::unique_ptr<DDSNodeState> CreateNodeState(const char * html_path, 
  const char * coordinator_host_addr, int coordinator_port,
  const char * database_host_addr, int database_port,
  int node_network_port, int user_port, int game_server_port, int bot_endpoint_port,
  int http_port, int http_ticket_port)
{
  StormSockets::StormSocketInitSettings backend_settings;
  backend_settings.NumIOThreads = 1;
  backend_settings.NumSendThreads = 1;
  backend_settings.MaxConnections = 20000;

  DDSDatabaseSettings database_settings;
  database_settings.DatabaseHostName = database_host_addr;
  database_settings.DatabasePort = database_port;
  database_settings.DatabaseName = kDatabaseName;
  database_settings.NumThreads = 1;

  StormSockets::StormSocketClientFrontendHttpSettings http_client_settings;

  StormSockets::StormSocketServerFrontendWebsocketSettings node_server_settings;
  StormSockets::StormSocketClientFrontendWebsocketSettings node_client_settings;
  DDSCoordinatorClientSettings coordinator_client_settings;

  if (coordinator_host_addr)
  {
    coordinator_client_settings.CoordinatorIpAddr = coordinator_host_addr;
  }

  if (coordinator_port)
  {
    coordinator_client_settings.CoordinatorPort = coordinator_port;
  }

  node_server_settings.ListenSettings.Port = node_network_port;

  StormSockets::StormSocketServerFrontendWebsocketSettings user_endpoint_settings;
  user_endpoint_settings.ListenSettings.Port = user_port;
  user_endpoint_settings.MaxConnections = 20000;
  StormSockets::StormSocketServerFrontendWebsocketSettings server_endpoint_settings;
  server_endpoint_settings.ListenSettings.Port = game_server_port;
  StormSockets::StormSocketServerFrontendWebsocketSettings bot_endpoint_settings;
  bot_endpoint_settings.ListenSettings.Port = bot_endpoint_port;

  StormSockets::StormSocketServerFrontendHttpSettings steam_validation_page_settings;
  steam_validation_page_settings.ListenSettings.Port = http_ticket_port;

  if (html_path)
  {
    DDSWebsiteFilesystemBuilder fs_builder;
    fs_builder.AddDirectory(html_path, "/");

    StormSockets::StormSocketServerFrontendHttpSettings static_content_settings;
    static_content_settings.ListenSettings.Port = http_port;

    return std::make_unique<DDSNodeState>(
      DataObjectList{}, SharedObjectList{}, backend_settings, node_server_settings, node_client_settings,
      http_client_settings, coordinator_client_settings, database_settings,
      DDSCreateEndpointType<UserEndpoint>(user_endpoint_settings),
      DDSCreateEndpointType<GameServerEndpoint>(server_endpoint_settings),
      DDSCreateEndpointType<BotEndpoint>(bot_endpoint_settings),
      DDSCreateWebsiteType<SteamOpenIdValidatorPage>(steam_validation_page_settings),
      DDSCreateWebsiteStaticContentType(static_content_settings, fs_builder));
  }
  else
  {
    return std::make_unique<DDSNodeState>(
      DataObjectList{}, SharedObjectList{}, backend_settings, node_server_settings, node_client_settings,
      http_client_settings, coordinator_client_settings, database_settings,
      DDSCreateEndpointType<UserEndpoint>(user_endpoint_settings),
      DDSCreateEndpointType<GameServerEndpoint>(server_endpoint_settings),
      DDSCreateEndpointType<BotEndpoint>(bot_endpoint_settings),
      DDSCreateWebsiteType<SteamOpenIdValidatorPage>(steam_validation_page_settings));
  }
}

