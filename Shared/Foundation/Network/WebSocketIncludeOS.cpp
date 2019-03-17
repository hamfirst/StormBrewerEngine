
#include "Foundation/Common.h"
#include "Foundation/Network/WebSocket.h"

#ifdef _INCLUDEOS

WebSocket::WebSocket()
{

}

WebSocket::WebSocket(const char * host, int port, const char * uri, const char * origin, char * protocol)
{

}

WebSocket::WebSocket(WebSocket && rhs) noexcept
{

}

WebSocket::~WebSocket()
{

}

WebSocket & WebSocket::operator = (WebSocket && rhs) noexcept
{
  return *this;
}

void WebSocket::StartConnect(const char * host, int port, const char * uri, const char * origin, char * protocol, int timeout)
{

}

bool WebSocket::IsConnected()
{
  return false;
}

bool WebSocket::IsConnecting()
{
  return false;
}

void WebSocket::Close()
{

}

Optional<WebsocketPacket> WebSocket::RecvPacket()
{
  return {};
}

Optional<WebsocketPacket> WebSocket::PollPacket()
{
  return {};
}

void WebSocket::SendPacket(const Buffer & buffer, WebSocketPacketType type)
{

}

void WebSocket::SendPacket(const std::string & data, WebSocketPacketType type)
{

}

void WebSocket::SendPacket(const void * data, std::size_t data_len, WebSocketPacketType type)
{

}

void WebSocket::SendString(const std::string & str)
{

}

#endif

