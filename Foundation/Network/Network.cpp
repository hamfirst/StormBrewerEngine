
#include "Foundation/Common.h"


#ifdef _MSC_VER
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <winsock2.h>

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#endif

#ifdef _LINUX
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netdb.h>
#endif

void NetworkInit()
{
#ifdef _MSC_VER
  WSADATA wsaData = {};
  WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif
}

void NetworkShutdown()
{
#ifdef _MSC_VER
  WSACleanup();
#endif
}


bool ProbePort(const char * host, int port, int timeout)
{
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
  ioctl(sock, FIONBIO, &on);
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
    if (FD_ISSET(sock, &fdset))
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
}
