

#ifdef _MSC_VER
#define SECURITY_WIN32

#include <winsock2.h>
#include <ws2tcpip.h>
#include <sspi.h>
#include <schnlsp.h>
#include <ntsecapi.h>

#pragma comment(lib, "Crypt32.lib")
#pragma comment(lib, "Secur32.lib")

#else

#include <cstdio>
#include <dirent.h>

#define INVALID_SOCKET -1

#define closesocket(s) close(s)

#endif

#include "StormWebrtcClientNative.h"

#include <vector>
#include <string>

StormWebrtcClientNative::StormWebrtcClientNative(const StormWebrtcClientChannelList & in_channels, const StormWebrtcClientChannelList & out_channels) :
  m_Socket((int)INVALID_SOCKET),
  m_Connected(false),
  m_Connecting(false),
  m_State(StormWebrtcClientNativeState::kDisconnected),
  m_InChannels(in_channels),
  m_OutChannels(out_channels),
  m_SctpSocket(nullptr)
{

  mbedtls_entropy_init(&m_Entropy);
  mbedtls_ctr_drbg_init(&m_CtrDrbg);

  const char *pers = "stormwebrtc";
  auto error = mbedtls_ctr_drbg_seed(&m_CtrDrbg, mbedtls_entropy_func, &m_Entropy, (uint8_t *)pers, strlen(pers));

  mbedtls_ssl_config_init(&m_SSLConfig);

  error = mbedtls_ssl_config_defaults(&m_SSLConfig,
    MBEDTLS_SSL_IS_CLIENT,
    MBEDTLS_SSL_TRANSPORT_DATAGRAM,
    MBEDTLS_SSL_PRESET_DEFAULT);

  mbedtls_ssl_conf_rng(&m_SSLConfig, mbedtls_ctr_drbg_random, &m_CtrDrbg);

  auto debug_func = [](void *ctx, int level, const char *file, int line, const char *str)
  {
    fprintf((FILE *)ctx, "%s:%04d: %s", file, line, str);
    fflush((FILE *)ctx);
  };

  mbedtls_x509_crt_init(&m_CA);
#ifdef _MSC_VER

  auto cert_store = CertOpenSystemStore(NULL, L"ROOT");
  PCCERT_CONTEXT cert_context = nullptr;

  while ((cert_context = CertEnumCertificatesInStore(cert_store, cert_context)) != nullptr)
  {
    if ((cert_context->dwCertEncodingType & X509_ASN_ENCODING) != 0)
    {
      mbedtls_x509_crt_parse(&m_CA, cert_context->pbCertEncoded, cert_context->cbCertEncoded);
    }
  }

  CertCloseStore(cert_store, 0);

#else

  auto dir = opendir("/etc/ssl/certs");
  if (dir != nullptr)
  {
    while (true)
    {
      auto ent = readdir(dir);
      if (ent == nullptr)
      {
        closedir(dir);
        break;
      }

      if (ent->d_type == DT_LNK || ent->d_type == DT_REG || ent->d_type == DT_UNKNOWN)
      {
        if (strstr(ent->d_name, ".crt"))
        {
          std::string crt_filename = std::string("/etc/ssl/certs/") + ent->d_name;

          auto fp = fopen(crt_filename.c_str(), "rb");
          if (fp == nullptr)
          {
            continue;
          }

          fseek(fp, 0, SEEK_END);
          auto len = ftell(fp);
          fseek(fp, 0, SEEK_SET);

          auto buffer = std::make_unique<uint8_t[]>(len + 1);
          fread(buffer.get(), 1, len, fp);
          fclose(fp);

          buffer[len] = 0;

          mbedtls_x509_crt_parse(&ssl_data.m_CA, buffer.get(), len + 1);
        }
      }
    }
  }
#endif

  mbedtls_ssl_conf_ca_chain(&m_SSLConfig, &m_CA, nullptr);

  mbedtls_ssl_conf_dbg(&m_SSLConfig, debug_func, stdout);
  mbedtls_ssl_conf_authmode(&m_SSLConfig, MBEDTLS_SSL_VERIFY_NONE);
}

StormWebrtcClientNative::StormWebrtcClientNative(const StormWebrtcClientChannelList & in_channels, const StormWebrtcClientChannelList & out_channels, const char * ipaddr, int port, const char * fingerprint) :
  StormWebrtcClientNative(in_channels, out_channels)
{
  StartConnect(ipaddr, port, fingerprint);
}

StormWebrtcClientNative::~StormWebrtcClientNative()
{
  Close();

  mbedtls_x509_crt_free(&m_CA);
  mbedtls_ssl_config_free(&m_SSLConfig);
  mbedtls_ctr_drbg_free(&m_CtrDrbg);
  mbedtls_entropy_free(&m_Entropy);
}

void StormWebrtcClientNative::StartConnect(const char * ipaddr, int port, const char * fingerprint)
{
  Close();

  addrinfo hints;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_DGRAM;
  hints.ai_protocol = IPPROTO_UDP;

  auto port_str = std::to_string(port);

  addrinfo *addr_list;
  if (getaddrinfo(ipaddr, port_str.data(), &hints, &addr_list) != 0)
  {
    return;
  }

  if (addr_list == nullptr)
  {
    return;
  }

  m_Socket = (int)socket(AF_INET, SOCK_DGRAM, 0);
  if (m_Socket == INVALID_SOCKET)
  {
    return;
  }

  sockaddr_in sin;
  memset(&sin, 0, sizeof(sin));
  sin.sin_family = AF_INET;
  sin.sin_addr.s_addr = htonl(INADDR_ANY); 

  if (bind(m_Socket, (sockaddr *)&sin, sizeof(sockaddr_in)) == -1)
  {
    closesocket(m_Socket);
    m_Socket = (int)INVALID_SOCKET;
    return;
  }

  if (connect(m_Socket, addr_list->ai_addr, (int)addr_list->ai_addrlen) == -1)
  {
    closesocket(m_Socket);
    m_Socket = (int)INVALID_SOCKET;
    return;
  }

  mbedtls_ssl_init(&m_SSLContext);
  int error = mbedtls_ssl_setup(&m_SSLContext, &m_SSLConfig);
  if (error != 0)
  {
    closesocket(m_Socket);

    mbedtls_ssl_free(&m_SSLContext);
    m_Socket = (int)INVALID_SOCKET;
    return;
  }

  mbedtls_ssl_set_timer_cb(&m_SSLContext, &m_Timer, mbedtls_timing_set_delay, mbedtls_timing_get_delay);
  mbedtls_ssl_session_reset(&m_SSLContext);

  auto send_callback = [](void * ctx, const unsigned char * data, size_t size) -> int
  {
    auto client = (StormWebrtcClientNative *)ctx;
    return (int)send(client->m_Socket, (const char *)data, (int)size, 0);
  };

  auto recv_callback = [](void * ctx, unsigned char * data, size_t size) -> int
  {
    auto client = (StormWebrtcClientNative *)ctx;
    auto result = (int)recv(client->m_Socket, (char *)data, (int)size, 0);

    if (result <= 0)
    {
      return MBEDTLS_ERR_SSL_WANT_READ;
    }

    return result;
  };

  auto recv_timeout_callback = [](void * ctx, unsigned char * data, size_t size, uint32_t timeout) -> int
  {
    auto client = (StormWebrtcClientNative *)ctx;

    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(client->m_Socket, &readfds);

    timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = timeout;

    int ret = select(client->m_Socket + 1, &readfds, NULL, NULL, &tv);
    if (ret == -1)
    {
      return MBEDTLS_ERR_SSL_WANT_READ;
    }

    return (int)recv(client->m_Socket, (char *)data, (int)size, 0);
  };

  mbedtls_ssl_set_bio(&m_SSLContext,
    this,
    send_callback,
    recv_callback,
    recv_timeout_callback);

  m_State = StormWebrtcClientNativeState::kInitialHello;
  m_Connecting = true;
}

void StormWebrtcClientNative::Update()
{
  //static const int kRecvBufferSize = 4096;
  //uint8_t packet[kRecvBufferSize];

  if (m_State == StormWebrtcClientNativeState::kInitialHello)
  {
    auto result = mbedtls_ssl_handshake_step(&m_SSLContext);

    if (result == 0)
    {
      if (m_SSLContext.state == MBEDTLS_SSL_HANDSHAKE_OVER)
      {
        StartSctpConnect();
      }
    }
    else if (result != MBEDTLS_ERR_SSL_WANT_READ && result != MBEDTLS_ERR_SSL_WANT_WRITE)
    {
      Close();
    }
  }
}

bool StormWebrtcClientNative::IsConnected()
{
  return m_Connected;
}

bool StormWebrtcClientNative::IsConnecting()
{
  return m_Connecting;
}

void StormWebrtcClientNative::Close()
{
  m_Connected = false;
  m_Connecting = false;
  m_State = StormWebrtcClientNativeState::kDisconnected;

  if (m_Socket == (int)INVALID_SOCKET)
  {
    return;
  }

  if (m_SctpSocket != nullptr)
  {
    usrsctp_close(m_SctpSocket);
    m_SctpSocket = nullptr;
  }

  closesocket(m_Socket);
  mbedtls_ssl_free(&m_SSLContext);
}

void StormWebrtcClientNative::SendPacket(int stream, bool sender_channel, const void * data, std::size_t data_len)
{
  if (m_Connected == false)
  {
    return;
  }


}

bool StormWebrtcClientNative::PollPacket(StormWebrtcClientPacket & out_packet)
{
  if (m_PendingPackets.size() == 0)
  {
    return false;
  }

  out_packet = std::move(m_PendingPackets.front());
  m_PendingPackets.pop();
  return true;
}

void StormWebrtcClientNative::StartSctpConnect()
{
  auto sctp_receive_cb = [](struct socket *sock, union sctp_sockstore addr, void *data,
    size_t datalen, struct sctp_rcvinfo rcv, int flags, void *ulp_info) -> int
  {
    auto & connection = *static_cast<StormWebrtcClientNative *>(addr.sconn.sconn_addr);

#ifdef STORMWEBRTC_USE_THREADS
    std::unique_lock<std::recursive_mutex> connection_lock(connection.m_Mutex);
#endif

    if (flags & MSG_NOTIFICATION)
    {
      auto notification = (sctp_notification *)data;
      switch (notification->sn_header.sn_type)
      {
      case SCTP_ASSOC_CHANGE:
        //connection.m_ServerImpl->HandleSctpAssociationChange(connection, notification->sn_assoc_change);
        break;
      case SCTP_SENDER_DRY_EVENT:
        //SetReadyToSendData();
        break;
      case SCTP_STREAM_RESET_EVENT:
        //OnStreamResetEvent(&notification.sn_strreset_event);
        break;
      }
    }
    else
    {
      //connection.m_ServerImpl->HandleSctpPacket(connection, data, datalen, rcv.rcv_sid, rcv.rcv_ppid);
    }


    free(data);
    return 1;
  };

  auto send_thresh_cb = [](struct socket* sock, uint32_t sb_free) -> int
  {
    return 0;
  };

  m_SctpSocket = usrsctp_socket(AF_CONN, SOCK_STREAM, IPPROTO_SCTP, sctp_receive_cb, send_thresh_cb, usrsctp_sysctl_get_sctp_sendspace() / 2, this);
  if (m_SctpSocket == nullptr)
  {
    throw std::runtime_error(std::string("Could not create sctp socket"));
  }

  if (usrsctp_set_non_blocking(m_SctpSocket, 1) < 0)
  {
    throw std::runtime_error(std::string("Could not set sctp socket non blocking"));
  }

  linger linger_opt;
  linger_opt.l_onoff = 1;
  linger_opt.l_linger = 0;
  if (usrsctp_setsockopt(m_SctpSocket, SOL_SOCKET, SO_LINGER, &linger_opt, sizeof(linger_opt)))
  {
    throw std::runtime_error(std::string("Could not set sctp socket linger"));
  }

  struct sctp_assoc_value stream_rst;
  stream_rst.assoc_id = SCTP_ALL_ASSOC;
  stream_rst.assoc_value = 1;
  if (usrsctp_setsockopt(m_SctpSocket, IPPROTO_SCTP, SCTP_ENABLE_STREAM_RESET, &stream_rst, sizeof(stream_rst)))
  {
    throw std::runtime_error(std::string("Could not set sctp socket stream reset"));
  }

  uint32_t nodelay = 1;
  if (usrsctp_setsockopt(m_SctpSocket, IPPROTO_SCTP, SCTP_NODELAY, &nodelay, sizeof(nodelay)))
  {
    throw std::runtime_error(std::string("Could not set sctp socket nodelay"));
  }

  int event_types[] =
  {
    SCTP_ASSOC_CHANGE,
    SCTP_PEER_ADDR_CHANGE,
    SCTP_SEND_FAILED_EVENT,
    SCTP_SENDER_DRY_EVENT,
    SCTP_STREAM_RESET_EVENT
  };

  struct sctp_event event = { 0 };
  event.se_assoc_id = SCTP_ALL_ASSOC;
  event.se_on = 1;
  for (size_t index = 0; index < 5; index++)
  {
    event.se_type = event_types[index];
    if (usrsctp_setsockopt(m_SctpSocket, IPPROTO_SCTP, SCTP_EVENT, &event, sizeof(event)) < 0)
    {
      throw std::runtime_error(std::string("Could not set sctp socket event sub"));
    }
  }

  sockaddr_in sctp_listen_addr;
  memset((void *)&sctp_listen_addr, 0, sizeof(sctp_listen_addr));
  sctp_listen_addr.sin_family = AF_INET;
  sctp_listen_addr.sin_port = htons(5000);
  sctp_listen_addr.sin_addr.s_addr = INADDR_ANY;

  if (usrsctp_bind(m_SctpSocket, (struct sockaddr *)&sctp_listen_addr, sizeof(struct sockaddr_in)) < 0)
  {
    throw std::runtime_error(std::string("sctp bind error"));
  }

  //sockaddr_conn target_addr;
  //if (usrsctp_connect(m_SctpListenSocket, 1) < 0)
  //{
  //  throw std::runtime_error(std::string("sctp listen error"));
  //}
}

