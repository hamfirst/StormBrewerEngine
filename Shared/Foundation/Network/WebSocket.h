#pragma once

#include <queue>

enum class WebSocketPacketType
{
  kText,
  kBinary,
};

struct WebsocketPacket
{
  Buffer m_Buffer;
  WebSocketPacketType m_Type;
  bool m_Fin;
};

class WebSocket
{
public:
  WebSocket();
  WebSocket(const char * host, int port, const char * uri, const char * origin, const char * protocol = nullptr);
  WebSocket(const WebSocket & rhs) = delete;
  WebSocket(WebSocket && rhs)  noexcept;
  ~WebSocket();

  WebSocket & operator = (const WebSocket & rhs) = delete;
  WebSocket & operator = (WebSocket && rhs) noexcept;

  void StartConnect(const char * host, int port, const char * uri, const char * origin, const char * protocol = nullptr, int timeout = 0);

  bool IsConnected();
  bool IsConnecting();
  void Close();

  Optional<WebsocketPacket> RecvPacket();
  Optional<WebsocketPacket> PollPacket();

  void SendPacket(const Buffer & buffer, WebSocketPacketType type);
  void SendPacket(const std::string & data, WebSocketPacketType type);
  void SendPacket(const void * data, std::size_t data_len, WebSocketPacketType type);

  void SendString(const std::string & str);

private:

  void Cleanup();

#ifdef _WEB

  int m_Socket;
  int m_Connected;
  int m_Connecting;

  std::queue<WebsocketPacket> m_PendingPackets;

public:
  void SetConnected(bool connected);
  void GotMessage(NotNullPtr<uint8_t> message, int length, bool binary);

#else

  int m_WebsocketId = -1;

#endif
};
