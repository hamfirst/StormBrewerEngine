#pragma once

#include "StormNet/NetTransmitter.h"
#include "StormNet/NetPipeMode.h"
#include "StormNet/NetBitWriterVector.h"

class NetClientBackendWebrtc;

struct NetTransmitterClientWebrtc : public NetTransmitter
{
  NetTransmitterClientWebrtc();

  NetBitWriter & CreateWriter(NetPipeMode mode, int channel_index, int channel_bits, bool ack) override;
  void SendWriter(NetBitWriter & writer) override;

public:
  NetBitWriterVector m_Writer = NetBitWriterVector(1400);
  int m_StreamIndex = 0;
  bool m_SenderChannel = false;

  NetClientBackendWebrtc * m_Client = nullptr;
  bool m_Disconnected = false;
};
