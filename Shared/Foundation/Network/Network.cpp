
#include "Foundation/Common.h"
#include "Foundation/Network/NetworkInternal.h"


#ifdef _MSC_VER
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")

#elif !defined(_WEB)

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <fcntl.h>
#endif

#ifdef _INCLUDEOS

#include <kernel/events.hpp>

#endif

#ifndef _WEB

std::unique_ptr<StormSockets::StormSocketBackend> g_NetworkBackend;
std::unique_ptr<StormSockets::StormSocketClientFrontendWebsocket> g_NetworkFrontendWebsocket;
std::unique_ptr<StormSockets::StormSocketClientFrontendHttp> g_NetworkFrontendHttp;

IdAllocator g_WebsocketIdAllocator(kBackendMaxConnections, false);
NetworkWebsocketData g_WebsocketData[kBackendMaxConnections];

#endif

void NetworkInit()
{
#ifdef _MSC_VER
  WSADATA wsaData = {};
  WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif

#ifndef _WEB
  StormSockets::StormSocketInitSettings backend_settings;
  backend_settings.MaxConnections = kBackendMaxConnections;
  backend_settings.NumIOThreads = 1;
  backend_settings.NumSendThreads = 1;
  backend_settings.HeapSize = 0;
  backend_settings.LoadSystemCertificates = true;
  g_NetworkBackend = std::make_unique<StormSockets::StormSocketBackend>(backend_settings);

  StormSockets::StormSocketClientFrontendWebsocketSettings websocket_settings;
  websocket_settings.MaxConnections = kBackendMaxConnections;
  g_NetworkFrontendWebsocket = std::make_unique<StormSockets::StormSocketClientFrontendWebsocket>(websocket_settings, g_NetworkBackend.get());

  StormSockets::StormSocketClientFrontendHttpSettings http_settings;
  http_settings.MaxConnections = kBackendMaxConnections;
  g_NetworkFrontendHttp = std::make_unique<StormSockets::StormSocketClientFrontendHttp>(http_settings, g_NetworkBackend.get());
#endif
}

void NetworkUpdate()
{
#ifndef _WEB

#ifdef _INCLUDEOS
  Events::get().process_events();
#endif

  StormSockets::StormSocketEventInfo event;
  while(g_NetworkFrontendWebsocket->GetEvent(event))
  {
    NetworkWebsocketData * ws_data = nullptr;
    int websocket_id = 0;
    for(int index = 0; index < kBackendMaxConnections; ++index)
    {
      if(g_WebsocketData[index].m_ConnectionId == event.ConnectionId)
      {
        ws_data = &g_WebsocketData[index];
        websocket_id = index;
        break;
      }
    }

    ASSERT(ws_data != nullptr, "Could not find proper websocket data");

    switch(event.Type)
    {
    case StormSockets::StormSocketEventType::ClientConnected:
      break;
    case StormSockets::StormSocketEventType::ClientHandShakeCompleted:
      ws_data->m_State = NetworkWebsocketDataState::kConnected;
      break;
    case StormSockets::StormSocketEventType::Data:
    {
      auto reader = event.GetWebsocketReader();
      if(reader.GetDataType() == StormSockets::StormSocketWebsocketDataType::Binary ||
         reader.GetDataType() == StormSockets::StormSocketWebsocketDataType::Text)
      {
        WebsocketPacket packet;
        packet.m_Buffer = Buffer(reader.GetDataLength());
        packet.m_Fin = reader.GetFinalInSequence();
        packet.m_Type = reader.GetDataType() == StormSockets::StormSocketWebsocketDataType::Binary ?
            WebSocketPacketType::kBinary : WebSocketPacketType::kText;
        reader.ReadByteBlock(packet.m_Buffer.Get(), reader.GetDataLength());

        ws_data->m_Packets.emplace(std::move(packet));
      }

      g_NetworkFrontendWebsocket->FreeIncomingPacket(reader);
      break;
    }
    case StormSockets::StormSocketEventType::Disconnected:
      ws_data->m_Disconnected = true;
      if(ws_data->m_Freed)
      {
        g_WebsocketIdAllocator.Release((std::size_t)websocket_id);
        *ws_data = {};
      }

      g_NetworkFrontendWebsocket->FinalizeConnection(event.ConnectionId);
      break;
    }
  }

  while(g_NetworkFrontendHttp->GetEvent(event))
  {
    switch(event.Type)
    {
    case StormSockets::StormSocketEventType::ClientConnected:
      break;
    case StormSockets::StormSocketEventType::ClientHandShakeCompleted:
      break;
    case StormSockets::StormSocketEventType::Data:
      break;
    case StormSockets::StormSocketEventType::Disconnected:
      break;
    }
  }
#endif
}

void NetworkShutdown()
{
#ifndef _WEB
  g_NetworkFrontendWebsocket.reset();
  g_NetworkFrontendHttp.reset();
  g_NetworkBackend.reset();
#endif

#ifdef _MSC_VER
  WSACleanup();
#endif
}


bool ProbePort(const char * host, int port, int timeout)
{
#if defined(_WEB) || defined(_INCLUDEOS)
  return false;
#else
  auto host_info = gethostbyname(host);
  if (host_info == nullptr)
  {
    return false;
  }

  int sock = (int)socket(AF_INET, SOCK_STREAM, 0);

  sockaddr_in serv_addr = {};
  serv_addr.sin_family = AF_INET;
  memcpy(&serv_addr.sin_addr, host_info->h_addr, host_info->h_length);
  serv_addr.sin_port = htons(port);

  unsigned long on = 1;
#ifdef _MSC_VER
  ioctlsocket(sock, FIONBIO, &on);
#else
  fcntl(sock, F_SETFL, O_NONBLOCK);
#endif

  connect(sock, (sockaddr *)&serv_addr, sizeof(serv_addr));

  fd_set fdset;
  FD_ZERO(&fdset);
  FD_SET(sock, &fdset);

  timeval tv;
  tv.tv_sec = 0;             /* 10 second timeout */
  tv.tv_usec = timeout * 1000;

  bool result = false;
  if (select(sock + 1, NULL, &fdset, NULL, &tv) == 1)
  {
    int so_error;
    socklen_t len = sizeof(so_error);

    getsockopt(sock, SOL_SOCKET, SO_ERROR, (char *)&so_error, &len);
    if (so_error == 0) 
    {
      result = true;
    }
  }

#ifdef _MSC_VER
  closesocket(sock);
#else
  close(sock);
#endif

  return result;
#endif
}
