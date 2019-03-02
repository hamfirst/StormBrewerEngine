#pragma once

#include <HurricaneDDS/DDSNodeState.h>

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

