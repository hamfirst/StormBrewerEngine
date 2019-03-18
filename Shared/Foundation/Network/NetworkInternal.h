
#pragma once

#include <queue>

#include "Foundation/Allocator/IdAllocator.h"
#include "Foundation/Buffer/Buffer.h"
#include "Foundation/Network/WebSocket.h"

#ifndef _WEB

#include "StormSockets/StormSocketBackend.h"
#include "StormSockets/StormSocketClientFrontendWebsocket.h"
#include "StormSockets/StormSocketClientFrontendHttp.h"

enum class NetworkWebsocketDataState
{
  kConnecting,
  kConnected,
  kDisconnected,
};

struct NetworkWebsocketData
{
  StormSockets::StormSocketConnectionId m_ConnectionId = StormSockets::StormSocketConnectionId::InvalidConnectionId;
  NetworkWebsocketDataState m_State = NetworkWebsocketDataState::kDisconnected;
  std::queue<WebsocketPacket> m_Packets;

  bool m_Freed = false;
  bool m_Disconnected = false;
};

static const int kBackendMaxConnections = 64;

extern std::unique_ptr<StormSockets::StormSocketBackend> g_NetworkBackend;
extern std::unique_ptr<StormSockets::StormSocketClientFrontendWebsocket> g_NetworkFrontendWebsocket;
extern std::unique_ptr<StormSockets::StormSocketClientFrontendHttp> g_NetworkFrontendHttp;

extern IdAllocator g_WebsocketIdAllocator;
extern NetworkWebsocketData g_WebsocketData[];


#endif