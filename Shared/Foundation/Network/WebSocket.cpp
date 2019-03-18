
#include "Foundation/Common.h"
#include "Foundation/Network/WebSocket.h"
#include "Foundation/Network/Network.h"
#include "Foundation/Network/NetworkInternal.h"

#ifndef _WEB

WebSocket::WebSocket()
{
}

WebSocket::WebSocket(const char * host, int port, const char * uri, const char * origin, char * protocol)
{
  StartConnect(host, port, uri, origin, protocol);
}

WebSocket::WebSocket(WebSocket && rhs) noexcept
{
  m_WebsocketId = rhs.m_WebsocketId;
  rhs.m_WebsocketId = -1;
}

WebSocket::~WebSocket()
{
  Cleanup();
}

WebSocket & WebSocket::operator = (WebSocket && rhs) noexcept
{
  Cleanup();

  m_WebsocketId = rhs.m_WebsocketId;
  rhs.m_WebsocketId = -1;
  return *this;
}

void WebSocket::StartConnect(const char * host, int port, const char * uri, const char * origin, char * protocol, int timeout)
{
  Cleanup();
  m_WebsocketId = (int)g_WebsocketIdAllocator.Allocate();

  auto & ws = g_WebsocketData[m_WebsocketId];

  StormSockets::StormSocketClientFrontendWebsocketRequestData req;
  req.m_Uri = uri;
  req.m_Origin = origin;
  req.m_Protocol = protocol;
  req.m_Host = host;
  req.m_UseSSL = false;

  ws.m_ConnectionId = g_NetworkFrontendWebsocket->RequestConnect(host, port, req);
  ws.m_State = NetworkWebsocketDataState::kConnecting;
}

bool WebSocket::IsConnected()
{
  if(m_WebsocketId == -1)
  {
    return false;
  }

  auto & ws = g_WebsocketData[m_WebsocketId];
  return ws.m_State == NetworkWebsocketDataState::kConnected;
}

bool WebSocket::IsConnecting()
{
  if(m_WebsocketId == -1)
  {
    return false;
  }

  auto & ws = g_WebsocketData[m_WebsocketId];
  return ws.m_State == NetworkWebsocketDataState::kConnecting;
}

void WebSocket::Close()
{
  Cleanup();
}

Optional<WebsocketPacket> WebSocket::RecvPacket()
{
  if(m_WebsocketId == -1)
  {
    return {};
  }

  auto & ws = g_WebsocketData[m_WebsocketId];
  while(ws.m_Packets.size() == 0)
  {
    if(ws.m_Disconnected)
    {
      return {};
    }

    NetworkUpdate();
  }

  auto packet = std::move(ws.m_Packets.front());
  ws.m_Packets.pop();
  return packet;
}

Optional<WebsocketPacket> WebSocket::PollPacket()
{
  if(m_WebsocketId == -1)
  {
    return {};
  }

  auto & ws = g_WebsocketData[m_WebsocketId];
  if(ws.m_Packets.size() == 0)
  {
    return {};
  }

  auto packet = std::move(ws.m_Packets.front());
  ws.m_Packets.pop();
  return packet;
}

void WebSocket::SendPacket(const Buffer & buffer, WebSocketPacketType type)
{
  SendPacket(buffer.Get(), buffer.GetSize(), type);
}

void WebSocket::SendPacket(const std::string & data, WebSocketPacketType type)
{
  SendPacket(data.data(), data.length(), type);
}

void WebSocket::SendPacket(const void * data, std::size_t data_len, WebSocketPacketType type)
{
  if(m_WebsocketId == -1)
  {
    return;
  }

  auto & ws = g_WebsocketData[m_WebsocketId];
  if(ws.m_Disconnected)
  {
    return;
  }

  StormSockets::StormSocketWebsocketDataType::Index ws_type;
  switch(type)
  {
  case WebSocketPacketType::kText:
    ws_type = StormSockets::StormSocketWebsocketDataType::Text;
    break;

  case WebSocketPacketType::kBinary:
    ws_type = StormSockets::StormSocketWebsocketDataType::Binary;
    break;
  }

  auto packet = g_NetworkFrontendWebsocket->CreateOutgoingPacket(ws_type, true);
  packet.WriteByteBlock(data, 0, data_len);

  g_NetworkFrontendWebsocket->FinalizeOutgoingPacket(packet);
  g_NetworkFrontendWebsocket->SendPacketToConnection(packet, ws.m_ConnectionId);
  g_NetworkFrontendWebsocket->FreeOutgoingPacket(packet);
}

void WebSocket::SendString(const std::string & str)
{
  SendPacket(str.data(), str.length(), WebSocketPacketType::kText);
}

void WebSocket::Cleanup()
{
  if(m_WebsocketId == -1)
  {
    return;
  }

  auto & ws = g_WebsocketData[m_WebsocketId];
  ws.m_Freed = true;

  if(ws.m_Disconnected)
  {
    g_WebsocketIdAllocator.Release((std::size_t)m_WebsocketId);
    ws = {};
  }
  else
  {
    g_NetworkFrontendWebsocket->ForceDisconnect(ws.m_ConnectionId);
  }

  m_WebsocketId = -1;
}

#endif
