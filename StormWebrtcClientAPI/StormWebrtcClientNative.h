#pragma once

#include <memory>
#include <queue>
#include <vector>
#include <cstdlib>

#include "mbedtls/entropy.h"
#include "mbedtls/ctr_drbg.h"
#include "mbedtls/certs.h"
#include "mbedtls/x509.h"
#include "mbedtls/ssl.h"
#include "mbedtls/ssl_cookie.h"
#include "mbedtls/net.h"
#include "mbedtls/error.h"
#include "mbedtls/debug.h"
#include "mbedtls/timing.h"

#include "usrsctplib/usrsctp.h"

#include "StormWebrtcClientTypes.h"

enum class StormWebrtcClientNativeState
{
  kDisconnected,
  kInitialHello,
  kSecondHello,
  kSCTPConnect,
  kChannelInit,
};

class StormWebrtcClientNative
{
public:
  StormWebrtcClientNative(const StormWebrtcClientChannelList & in_channels, const StormWebrtcClientChannelList & out_channels);
  StormWebrtcClientNative(const StormWebrtcClientChannelList & in_channels, const StormWebrtcClientChannelList & out_channels, const char * ipaddr, int port, const char * fingerprint);
  StormWebrtcClientNative(const StormWebrtcClientNative & rhs) = delete;
  StormWebrtcClientNative(StormWebrtcClientNative && rhs) = delete;
  ~StormWebrtcClientNative();

  StormWebrtcClientNative & operator = (const StormWebrtcClientNative & rhs) = delete;
  StormWebrtcClientNative & operator = (StormWebrtcClientNative && rhs) = delete;

  void StartConnect(const char * ipaddr, int port, const char * fingerprint);
  void Update();

  bool IsConnected();
  bool IsConnecting();
  void Close();

  void SendPacket(int stream, bool sender_channel, const void * data, std::size_t data_len);
  bool PollPacket(StormWebrtcClientPacket & out_packet);

private:

  void StartSctpConnect();

private:
  int m_Socket;
  bool m_Connected;
  bool m_Connecting;

  StormWebrtcClientNativeState m_State;

  StormWebrtcClientChannelList m_InChannels;
  StormWebrtcClientChannelList m_OutChannels;

  std::queue<StormWebrtcClientPacket> m_PendingPackets;

private:

  mbedtls_x509_crt m_CA;
  mbedtls_entropy_context m_Entropy;
  mbedtls_ctr_drbg_context m_CtrDrbg;
  mbedtls_timing_delay_context m_Timer;

  mbedtls_ssl_config m_SSLConfig;
  mbedtls_ssl_context m_SSLContext;

  struct socket * m_SctpSocket;
};


