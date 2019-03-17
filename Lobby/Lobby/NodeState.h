#pragma once

#include <HurricaneDDS/DDSNodeState.h>

<<<<<<< HEAD
std::unique_ptr<DDSNodeState> CreateNodeState(const char * html_path,
  const char * coordinator_host_addr = "localhost", int coordinator_port = 9001, 
  const char * database_host_addr = "localhost", int database_port = 27017,
  int node_network_port = 8000, int user_port = 7999, int game_server_port = 8001, int bot_endpoint_port = 8002,
  int http_port = 80, int http_ticket_port = 8080);
=======
#include "LobbyConfig.h"

struct NodeSettings
{
  const char * m_HTMLPath = nullptr;

  const char * m_CoordinatorHostAddress = "localhost";
  int m_CoordinatorPort = 9001;

  const char * m_DatabaseHost = "localhost";
  int m_DatabasePort = 27017;

  int m_NodeNetworkPort = 8000;
  int m_UserPort = 7999;
  int m_GameServerPort = 8001;

#ifdef ENABLE_BOTS
  int m_BotEndpointPort = 8002;
#endif

  int m_HTTPPort = 80;
  int m_HTTPTicketPort = 8080;
};

std::unique_ptr<DDSNodeState> CreateNodeState(const NodeSettings & settings);
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c

