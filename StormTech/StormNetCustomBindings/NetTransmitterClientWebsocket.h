#pragma once

#include "StormNet/NetTransmitter.h"
#include "StormNet/NetPipeMode.h"
#include "StormNet/NetBitWriterVector.h"

class NetClientBackendWebsocket;

struct NetTransmitterClientWebsocket : public NetTransmitter
{
  NetTransmitterClientWebsocket();

  NetBitWriter & CreateWriter(NetPipeMode mode, int channel_index, int channel_bits, bool ack) override;
  void SendWriter(NetBitWriter & writer) override;

public:
  NetBitWriterVector m_Writer = NetBitWriterVector(1400);
  NetClientBackendWebsocket * m_Client = nullptr;
  bool m_Disconnected = false;
};
