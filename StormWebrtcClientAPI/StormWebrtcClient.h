#pragma once

#include <memory>
#include <queue>
#include <vector>
#include <cstdlib>

enum class StormWebrtcClientStreamType : uint8_t
{
  kReliable,
  kUnreliable,
};

using StormWebrtcClientChannelList = std::vector<StormWebrtcClientStreamType>;

struct StormWebrtcPacketDeleter
{
  void operator()(uint8_t *p) { free(p); }
};

struct StormWebrtcClientPacket
{
  std::unique_ptr<uint8_t[], StormWebrtcPacketDeleter> m_Buffer;
  int m_Length;
  int m_Stream;
  bool m_SenderChannel;
};

class StormWebrtcClient
{
public:
  StormWebrtcClient(const StormWebrtcClientChannelList & in_channels, const StormWebrtcClientChannelList & out_channels);
  StormWebrtcClient(const StormWebrtcClientChannelList & in_channels, const StormWebrtcClientChannelList & out_channels, const char * ipaddr, int port, const char * fingerprint);
  StormWebrtcClient(const StormWebrtcClient & rhs) = delete;
  StormWebrtcClient(StormWebrtcClient && rhs)  noexcept;
  ~StormWebrtcClient();

  StormWebrtcClient & operator = (const StormWebrtcClient & rhs) = delete;
  StormWebrtcClient & operator = (StormWebrtcClient && rhs) noexcept;

  void StartConnect(const char * ipaddr, int port, const char * fingerprint);

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


