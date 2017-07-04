#pragma once

#include "StormNet/NetTransmitter.h"
#include "StormNet/NetPipeMode.h"
#include "StormNet/NetBitWriterVector.h"

#include "StormWebrtc/StormWebrtcServer.h"

struct NetTransmitterServerWebrtc : public NetTransmitter
{
  NetTransmitterServerWebrtc();

  NetBitWriter & CreateWriter(NetPipeMode mode, int channel_index, int channel_bits, bool ack) override;
  void SendWriter(NetBitWriter & writer) override;

public:
  NetBitWriterVector m_Writer = NetBitWriterVector(1400);
  int m_StreamIndex = 0;
  bool m_SenderChannel = false;

  std::vector<std::pair<uint8_t, bool>> m_IncSeqs;
  std::vector<std::pair<uint8_t, bool>> m_OutSeqs;

  StormWebrtcServer * m_Server = nullptr;
  StormWebrtcConnectionHandle m_Handle = {};
  bool m_Disconnected = false;
};
