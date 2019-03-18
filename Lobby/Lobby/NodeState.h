#pragma once

#include <HurricaneDDS/DDSNodeState.h>

#include "ProjectSettings/ProjectPorts.h"

#include "LobbyConfig.h"

struct NodeSettings
{
  const char * m_HTMLPath = nullptr;

  const char * m_CoordinatorHostAddress = "localhost";
  int m_CoordinatorPort = COORDINATOR_PORT;

  const char * m_DatabaseHost = "localhost";
  int m_DatabasePort = 27017;

  int m_NodeNetworkPort = NODE_NETWORK_PORT;
  int m_UserPort = LOBBY_USER_PORT;
  int m_GameServerPort = LOBBY_GAME_PORT;

#ifdef ENABLE_BOTS
  int m_BotEndpointPort = LOBBY_BOT_PORT;
#endif

  int m_HTTPPort = 80;
  int m_HTTPTicketPort = 8080;
};

std::unique_ptr<DDSNodeState> CreateNodeState(const NodeSettings & settings);

