#pragma once

#include <memory>
#include <queue>
#include <vector>
#include <cstdlib>

#include "StormWebrtcClientTypes.h"

class StormWebrtcClientWeb
{
public:
  StormWebrtcClientWeb(const StormWebrtcClientChannelList & in_channels, const StormWebrtcClientChannelList & out_channels);
  StormWebrtcClientWeb(const StormWebrtcClientChannelList & in_channels, const StormWebrtcClientChannelList & out_channels, const char * ipaddr, int port, const char * fingerprint);
  StormWebrtcClientWeb(const StormWebrtcClientWeb & rhs) = delete;
  StormWebrtcClientWeb(StormWebrtcClientWeb && rhs)  noexcept;
  ~StormWebrtcClientWeb();

  StormWebrtcClientWeb & operator = (const StormWebrtcClientWeb & rhs) = delete;
  StormWebrtcClientWeb & operator = (StormWebrtcClientWeb && rhs) noexcept;

  void StartConnect(const char * ipaddr, int port, const char * fingerprint);
  void Update();

  bool IsConnected();
  bool IsConnecting();
  void Close();

  void SendPacket(int stream, bool sender_channel, const void * data, std::size_t data_len);
  bool PollPacket(StormWebrtcClientPacket & out_packet);

private:
  int m_Socket;
  bool m_Connected;
  bool m_Connecting;

  StormWebrtcClientChannelList m_InChannels;
  StormWebrtcClientChannelList m_OutChannels;

  std::queue<StormWebrtcClientPacket> m_PendingPackets;

public:

  void SetConnected(bool connected);
  void GotMessage(int stream, bool sender, void * data, int length);
};


