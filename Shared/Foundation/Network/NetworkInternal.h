
#pragma once

#include <queue>

#include "Foundation/Allocator/IdAllocator.h"
#include "Foundation/Buffer/Buffer.h"
#include "Foundation/Optional/Optional.h"
#include "Foundation/Network/WebSocket.h"
#include "Foundation/Network/HttpRequest.h"

#ifndef _WEB

#include "StormSockets/StormSocketBackend.h"
#include "StormSockets/StormSocketClientFrontendWebsocket.h"
#include "StormSockets/StormSocketClientFrontendHttp.h"

enum class NetworkConnectionState
{
  kConnecting,
  kConnected,
  kDisconnected,
};

struct NetworkWebsocketData
{
  StormSockets::StormSocketConnectionId m_ConnectionId = StormSockets::StormSocketConnectionId::InvalidConnectionId;
  volatile NetworkConnectionState m_State = NetworkConnectionState::kDisconnected;
  std::queue<WebsocketPacket> m_Packets;

  bool m_Freed = false;
  bool m_Disconnected = false;
};

struct NetworkHttpData
{
  StormSockets::StormSocketConnectionId m_ConnectionId = StormSockets::StormSocketConnectionId::InvalidConnectionId;
  NetworkConnectionState m_State = NetworkConnectionState::kDisconnected;

  Delegate<void, const HttpRequest &> m_Callback;
  HttpRequest * m_Request = nullptr;

  std::string m_Response;
  std::string m_ResponseHeaders;
  int m_ResponseCode = 0;

  bool m_Freed = false;
  bool m_Disconnected = false;
};

static const int kBackendMaxConnections = 64;

extern std::unique_ptr<StormSockets::StormSocketBackend> g_NetworkBackend;
extern std::unique_ptr<StormSockets::StormSocketClientFrontendWebsocket> g_NetworkFrontendWebsocket;
extern std::unique_ptr<StormSockets::StormSocketClientFrontendHttp> g_NetworkFrontendHttp;

extern IdAllocator g_WebsocketIdAllocator;
extern NetworkWebsocketData g_WebsocketData[];

extern IdAllocator g_HttpIdAllocator;
extern NetworkHttpData g_HttpData[];

#endif