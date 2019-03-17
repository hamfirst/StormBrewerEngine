
#include "Foundation/Common.h"
#include "Foundation/Network/WebSocket.h"
#include "Foundation/Allocator/IdAllocator.h"

#ifdef _WEB

#include <emscripten/html5.h>
#include <emscripten/emscripten.h>

static bool s_WebsocketInit = false;
struct WebsocketAllocatorData
{
  WebsocketAllocatorData()
  {
    s_WebsocketInit = true;
  }

  ~WebsocketAllocatorData()
  {
    s_WebsocketInit = false;
  }

  IdAllocator m_WebsocketIdAllocator;
};

WebsocketAllocatorData s_WebsocketAllocInfo;
std::vector<WebSocket *> s_Websockets;

extern "C"
{
  void HandleWebsocketConnect(int index)
  {
    s_Websockets[index]->SetConnected(true);
  }

  void HandleWebsocketMessage(int index, NotNullPtr<uint8_t> message, int length, int binary)
  {
    s_Websockets[index]->GotMessage(message, length, binary != 0);
  }

  void HandleWebsocketClose(int index)
  {
    s_Websockets[index]->SetConnected(false);
  }
}

#define INVALID_SOCKET -1

WebSocket::WebSocket() :
  m_Socket((int)INVALID_SOCKET),
  m_Connected(false),
  m_Connecting(false)
{

}

WebSocket::WebSocket(const char * host, int port, const char * uri, const char * origin) :
  m_Socket((int)INVALID_SOCKET),
  m_Connected(false),
  m_Connecting(false)
{
  StartConnect(host, port, uri, origin);
}

WebSocket::~WebSocket()
{
  Close();
}

WebSocket::WebSocket(WebSocket && rhs) noexcept
{
  m_Socket = rhs.m_Socket;
  m_Connected = rhs.m_Connected;
  m_Connecting = rhs.m_Connecting;

  rhs.m_Socket = (int)INVALID_SOCKET;
  rhs.m_Connected = false;
  rhs.m_Connecting = false;
}

WebSocket & WebSocket::operator = (WebSocket && rhs) noexcept
{
  Close();

  m_Socket = rhs.m_Socket;
  m_Connected = rhs.m_Connected;
  m_Connecting = rhs.m_Connecting;

  rhs.m_Socket = (int)INVALID_SOCKET;
  rhs.m_Connected = false;
  rhs.m_Connecting = false;
  return *this;
}

void WebSocket::StartConnect(const char * host, int port, const char * uri, const char * origin, int timeout)
{
  Close();

  if (s_WebsocketInit == false)
  {
    return;
  }

  m_Socket = s_WebsocketAllocInfo.m_WebsocketIdAllocator.Allocate();
  while ((int)s_Websockets.size() <= m_Socket)
  {
    s_Websockets.push_back(nullptr);
  }

  s_Websockets[m_Socket] = this;
  EM_ASM_ARGS({ FoundationCreateWebsocket($0, $1, $2, $3); }, m_Socket, host, port, uri);
  m_Connecting = true;
}

bool WebSocket::IsConnected()
{
  return m_Connected;
}

bool WebSocket::IsConnecting()
{
  return m_Connecting;
}

void WebSocket::Close()
{
  m_Connected = false;
  m_Connecting = false;

  if (s_WebsocketInit == false)
  {
    return;
  }

  if (m_Socket == (int)INVALID_SOCKET)
  {
    return;
  }

  s_Websockets[m_Socket] = nullptr;
  s_WebsocketAllocInfo.m_WebsocketIdAllocator.Release(m_Socket);
  EM_ASM_ARGS({ FoundationDestroyWebsocket($0); }, m_Socket);

  m_Socket = (int)INVALID_SOCKET;
}

Optional<WebsocketPacket> WebSocket::RecvPacket()
{
  return PollPacket();
}

Optional<WebsocketPacket> WebSocket::PollPacket()
{
  if (m_PendingPackets.size() == 0)
  {
    return{};
  }

  Optional<WebsocketPacket> packet = std::move(m_PendingPackets.front());
  m_PendingPackets.pop();
  return packet;
}

void WebSocket::SendPacket(const Buffer & buffer, WebSocketPacketType type)
{
  SendPacket(buffer.Get(), buffer.GetSize(), type);
}

void WebSocket::SendPacket(const std::string & data, WebSocketPacketType type)
{
  SendPacket(data.data(), data.size(), type);
}

void WebSocket::SendPacket(const void * data, std::size_t data_len, WebSocketPacketType type)
{
  if (m_Connected == false)
  {
    return;
  }

  if (type == WebSocketPacketType::kBinary)
  {
    EM_ASM_ARGS({ FoundationHandleWebsocketSendBinaryMessage($0, $1, $2); }, m_Socket, data, data_len);
  }
  else
  {
    EM_ASM_ARGS({ FoundationHandleWebsocketSendTextMessage($0, $1); }, m_Socket, data);
  }
}

void WebSocket::SendString(const std::string & str)
{
  SendPacket(str.data(), str.length(), WebSocketPacketType::kText);
}

void WebSocket::SetConnected(bool connected)
{
  //printf("Connection status: %s\n", connected ? "true" : "false");
  m_Connected = connected;
  m_Connecting = false;
}

void WebSocket::GotMessage(NotNullPtr<uint8_t> message, int length, bool binary)
{
  WebsocketPacket packet;
  packet.m_Buffer = Buffer(message, length);
  packet.m_Type = binary ? WebSocketPacketType::kBinary : WebSocketPacketType::kText;
  packet.m_Fin = true;
  m_PendingPackets.push(std::move(packet));
}

#endif