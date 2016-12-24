#pragma once


enum class WebSocketPacketType
{
  kContinuation,
  kText,
  kBinary,
  kClose = 0x08,
  kPing = 0x09,
  kPong = 0x10,
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
  WebSocket(const char * host, int port, const char * uri, const char * origin);
  WebSocket(const WebSocket & rhs) = delete;
  WebSocket(WebSocket && rhs)  noexcept;
  ~WebSocket();

  WebSocket & operator = (const WebSocket & rhs) = delete;
  WebSocket & operator = (WebSocket && rhs) noexcept;

  bool Connect(const char * host, int port, const char * uri, const char * origin, int timeout = 0);
  bool IsConnected();
  void Close();

  Optional<WebsocketPacket> RecvPacket();
  Optional<WebsocketPacket> PollPacket();

  void SendPacket(const Buffer & buffer, WebSocketPacketType type);
  void SendPacket(const std::string & data, WebSocketPacketType type);
  void SendPacket(const void * data, std::size_t data_len, WebSocketPacketType type);

  void SendString(const std::string & str);

private:
  bool RecvData(void * data, std::size_t len);

  volatile int m_Socket;

  Buffer m_RemainderBuffer;
  std::size_t m_RemainderBufferPos = 0;
};
