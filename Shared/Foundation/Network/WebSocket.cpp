
#include "Foundation/Common.h"
#include "Foundation/Network/WebSocket.h"

#if !defined(_INCLUDEOS) && !defined(_WEB)

#ifdef _MSC_VER
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <winsock2.h>
#include <ws2tcpip.h>

#else

#ifdef __APPLE__

#else
#include <endian.h>
#define htonll htobe64
#endif

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

#define INVALID_SOCKET -1

#endif

static void CloseSocket(volatile int & sock)
{
#ifdef _MSC_VER
  closesocket(sock);
#else
  shutdown(sock, SHUT_RDWR);
  close(sock);
#endif

  sock = (int)INVALID_SOCKET;
}

static bool CompareStringSpan(const gsl::string_span<> & inp, const char * match)
{
  for (auto c : inp)
  {
    if (*match == 0)
    {
      return true;
    }

    if (c != *match)
    {
      return false;
    }

    match++;
  }

  return true;
}

static const char * kRequestStr =
"GET %s HTTP/1.1\r\n"
"Host: %s:%d\r\n"
"Origin: %s\r\n"
"Upgrade: websocket\r\n"
"Connection: Upgrade\r\n"
"Sec-WebSocket-Key: dGhlIHNhbXBsZSBub25jZQ==\r\n"
"Sec-WebSocket-Version: 13\r\n\r\n";



WebSocket::WebSocket()
  : m_Socket((int)INVALID_SOCKET)
{
}

WebSocket::WebSocket(const char * host, int port, const char * uri, const char * origin, char * protocol)
  : m_Socket((int)INVALID_SOCKET)
{
  StartConnect(host, port, uri, origin, protocol);
}

WebSocket::~WebSocket()
{
  Close();
}

WebSocket::WebSocket(WebSocket && rhs) noexcept
{
  m_Socket = rhs.m_Socket;
  m_RemainderBuffer = std::move(rhs.m_RemainderBuffer);
  m_RemainderBufferPos = rhs.m_RemainderBufferPos;
  rhs.m_Socket = (int)INVALID_SOCKET;
}

WebSocket & WebSocket::operator = (WebSocket && rhs) noexcept
{
  Close();

  m_Socket = rhs.m_Socket;
  m_RemainderBuffer = std::move(rhs.m_RemainderBuffer);
  m_RemainderBufferPos = rhs.m_RemainderBufferPos;
  rhs.m_Socket = (int)INVALID_SOCKET;
  return *this;
}

void WebSocket::StartConnect(const char * host, int port, const char * uri, const char * origin, char * protocol, int timeout)
{
  Close();

  addrinfo * host_info;
  addrinfo hints = {};

  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = IPPROTO_TCP;

  auto error = getaddrinfo(host, nullptr, &hints, &host_info);  
  if(error != 0)
  {
    return;
  }

  if(host_info->ai_family != AF_INET)
  {
    freeaddrinfo(host_info);
    return;
  }

  sockaddr_in sin = {};
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  memcpy(&sin.sin_addr, &((sockaddr_in *)host_info->ai_addr)->sin_addr, sizeof(sin.sin_addr));

  freeaddrinfo(host_info);

  m_Socket = (int)socket(AF_INET, SOCK_STREAM, 0);

  int one = 1;
  int return_val = setsockopt(m_Socket, IPPROTO_TCP, TCP_NODELAY, (const char *)&one, sizeof(one));

  if (timeout == 0)
  {
    auto result = connect(m_Socket, (sockaddr *)&sin, sizeof(sin));

    if (result < 0)
    {
      CloseSocket(m_Socket);
      return;
    }
  }
  else
  {
    unsigned long on = 1;
#ifdef _MSC_VER
    ioctlsocket(m_Socket, FIONBIO, &on);
#else
    fcntl(m_Socket, F_SETFL, O_NONBLOCK);
#endif

    auto result = connect(m_Socket, (sockaddr *)&sin, sizeof(sin));

    fd_set fdset;
    FD_ZERO(&fdset);
    FD_SET(m_Socket, &fdset);

    timeval tv;
    tv.tv_sec = timeout / 1000;
    tv.tv_usec = (timeout % 1000) * 1000;

    if (select(m_Socket + 1, NULL, &fdset, NULL, &tv) != 1)
    {
      CloseSocket(m_Socket);
      return;
    }

    int so_error;
    socklen_t len = sizeof(so_error);

    getsockopt(m_Socket, SOL_SOCKET, SO_ERROR, (char *)&so_error, &len);
    if (so_error != 0) 
    {
      CloseSocket(m_Socket);
      return;
    }

    unsigned long off = 0;
#ifdef _MSC_VER
    ioctlsocket(m_Socket, FIONBIO, &off);
#else
    fcntl(m_Socket, F_SETFL, 0);
#endif
  }

  std::size_t bufflen = strlen(kRequestStr) + strlen(uri) + strlen(origin) + strlen(host) + 20;
  std::unique_ptr<char[]> buffer = std::make_unique<char[]>(bufflen);

  int request_len = snprintf(buffer.get(), bufflen, kRequestStr, uri, host, port, origin);
  int send_len = send(m_Socket, buffer.get(), request_len, 0);

  if (send_len != request_len)
  {
    CloseSocket(m_Socket);
    return;
  }

  Buffer recv_buffer(8092);
  int recv_len = recv(m_Socket, (char *)recv_buffer.Get(), (int)recv_buffer.GetSize(), 0);

  if (recv_len <= 0)
  {
    CloseSocket(m_Socket);
    return;
  }

  while (true)
  {
    if (strstr((char *)recv_buffer.Get(), "\r\n\r\n"))
    {
      break;
    }

    if (recv_len == 8092)
    {
      CloseSocket(m_Socket);
      return;
    }

    int len = recv(m_Socket, (char *)recv_buffer.Get() + recv_len, (int)recv_buffer.GetSize() - recv_len, 0);
    if (len <= 0)
    {
      CloseSocket(m_Socket);
      return;
    }

    recv_len += len;
  }

  char * recv_data = (char *)recv_buffer.Get();
  char * header_start = recv_data;
  char * header_end = recv_data;

  bool got_status_line = false;
  bool got_upgrade = false;
  bool got_connection = false;
  bool got_sec_key = false;

  while (true)
  {
    if (*header_end == 0)
    {
      CloseSocket(m_Socket);
      return;
    }
    if (header_end[0] == '\r' && header_end[1] == '\n')
    {
      if (header_start == header_end)
      {
        header_end += 2;
        break;
      }

      gsl::string_span<> header = gsl::make_span(header_start, header_end);

      if (got_status_line == false)
      {
        if (!CompareStringSpan(header, "HTTP/1.1 101"))
        {
          CloseSocket(m_Socket);
          return;
        }

        got_status_line = true;
      }
      else
      {
        if (CompareStringSpan(header, "Upgrade: websocket"))
        {
          got_upgrade = true;
        }
        else if (CompareStringSpan(header, "Connection: Upgrade"))
        {
          got_connection = true;
        }
        else if (CompareStringSpan(header, "Sec-WebSocket-Accept: s3pPLMBiTxaQ9kYGzzhZRbK+xOo="))
        {
          got_sec_key = true;
        }
      }

      header_start = header_end = header_end + 2;
    }
    else
    {
      header_end++;
    }

  }

  std::size_t parsed_size = header_end - recv_data;
  if (parsed_size != recv_len)
  {
    m_RemainderBuffer = Buffer(recv_len - parsed_size);
    m_RemainderBufferPos = 0;

    memcpy(m_RemainderBuffer.Get(), recv_buffer.Get() + parsed_size, recv_len - parsed_size);
  }
}

bool WebSocket::IsConnected()
{
  return m_Socket != (int)INVALID_SOCKET;
}

bool WebSocket::IsConnecting()
{
  return false;
}

void WebSocket::Close()
{
  if (m_Socket != (int)INVALID_SOCKET)
  {
    CloseSocket(m_Socket);
  }
}

Optional<WebsocketPacket> WebSocket::RecvPacket()
{
  if (m_Socket == (int)INVALID_SOCKET)
  {
    return{};
  }

  uint8_t header[2];
  if (RecvData(header, 2) == false)
  {
    return{};
  }

  bool fin = (header[0] & 0x80) != 0;
  int opcode = header[0] & 0x0F;

  WebSocketPacketType type = (WebSocketPacketType)opcode;


  uint64_t len = header[1] & 0x7F;
  if (len == 126)
  {
    uint16_t actual_len;
    if (RecvData(&actual_len, 2) == false)
    {
      return{};
    }

    len = htons(actual_len);
  }
  else if (len == 127)
  {
    if (RecvData(&len, 8) == false)
    {
      return{};
    }

    len = htonll(len);
  }

  uint32_t mask = 0;
  if (header[1] & 0x80)
  {
    if (RecvData(&len, 4) == false)
    {
      return{};
    }
  }

  Buffer packet_buffer((std::size_t)len);
  if (len > 0)
  {
    if (RecvData(packet_buffer.Get(), (std::size_t)len) == false)
    {
      return{};
    }
  }

  if (mask != 0)
  {
    uint32_t * mask_ptr = (uint32_t *)packet_buffer.Get();
    while (len >= 4)
    {
      *mask_ptr ^= mask;
      mask_ptr++;
      len -= 4;
    }

    uint8_t * mask_byte_ptr = (uint8_t *)mask_ptr;
    uint8_t * mask_src_ptr = (uint8_t *)&mask;

    while (len > 0)
    {
      *mask_byte_ptr = *mask_src_ptr;
      mask_byte_ptr++;
      mask_src_ptr++;
      len--;
    }
  }

  return WebsocketPacket{ std::move(packet_buffer), type, fin };
}

Optional<WebsocketPacket> WebSocket::PollPacket()
{
  if (m_Socket == INVALID_SOCKET)
  {
    return{};
  }

  fd_set recv_set;

  FD_ZERO(&recv_set);
  FD_SET(m_Socket, &recv_set);

  timeval t = {};
  select(FD_SETSIZE, &recv_set, NULL, NULL, &t);

  if (FD_ISSET(m_Socket, &recv_set))
  {
    return RecvPacket();
  }

  return{};
}

void WebSocket::WaitForData(int ms)
{
  if (m_Socket == INVALID_SOCKET)
  {
    return;
  }

  fd_set recv_set, err_set;

  FD_ZERO(&recv_set);
  FD_SET(m_Socket, &recv_set);

  FD_ZERO(&err_set);
  FD_SET(m_Socket, &err_set);

  timeval t = {};
  t.tv_usec = ms * 1000;
  select(FD_SETSIZE, &recv_set, NULL, &err_set, &t);
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
  std::size_t header_len = 6;
  if (data_len > 65535)
  {
    header_len = 14;
  }
  else if(data_len > 125)
  {
    header_len = 8;
  }

  Buffer send_buffer(header_len + data_len);
  uint8_t * header = send_buffer.Get();

  *header = (uint8_t)type;
  *header |= 0x80;

  header++;

  *header = 0x80;
  
  if (data_len > 65535)
  {
    *header |= 127;
    header++;

    uint64_t * len_ptr = (uint64_t *)header;
    *len_ptr = htonll((uint64_t)data_len);

    header += 8;
  }
  else if (data_len > 125)
  {
    *header |= 126;
    header++;

    uint16_t * len_ptr = (uint16_t *)header;
    *len_ptr = htons((uint16_t)data_len);

    header += 2;
  }
  else
  {
    *header |= (uint8_t)data_len;
    header++;
  }

  uint32_t mask = rand();
  uint32_t * mask_ptr = (uint32_t *)header;
  *mask_ptr = mask;

  header += 4;
  memcpy(header, data, data_len);

  if (mask != 0)
  {
    uint32_t * mask_ptr = (uint32_t *)header;
    std::size_t len = data_len;
    while (len >= 4)
    {
      *mask_ptr ^= mask;
      mask_ptr++;
      len -= 4;
    }

    uint8_t * mask_byte_ptr = (uint8_t *)mask_ptr;
    uint8_t * mask_src_ptr = (uint8_t *)&mask;

    while (len > 0)
    {
      *mask_byte_ptr ^= *mask_src_ptr;
      mask_byte_ptr++;
      mask_src_ptr++;
      len--;
    }
  }

  send(m_Socket, (char *)send_buffer.Get(), (int)send_buffer.GetSize(), 0);
}

bool WebSocket::RecvData(void * data, std::size_t len)
{
  char * buffer = (char *)data;

  if (m_RemainderBufferPos < m_RemainderBuffer.GetSize())
  {
    std::size_t available_data = m_RemainderBuffer.GetSize() - m_RemainderBufferPos;
    if (available_data >= len)
    {
      memcpy(data, m_RemainderBuffer.Get() + m_RemainderBufferPos, len);
      m_RemainderBufferPos += len;
      return true;
    }
    else
    {
      memcpy(data, m_RemainderBuffer.Get() + m_RemainderBufferPos, available_data);
      m_RemainderBufferPos += available_data;

      buffer += available_data;
      len -= available_data;
    }
  }

  if (len == 0)
  {
    return true;
  }

  int recv_len = recv(m_Socket, buffer, (int)len, MSG_WAITALL);
  if (recv_len <= 0)
  {
    CloseSocket(m_Socket);
  }

  if (recv_len != len)
  {
    return false;
  }

  return true;
}

void WebSocket::SendString(const std::string & str)
{
  SendPacket(str.data(), str.length(), WebSocketPacketType::kText);
}

#endif
