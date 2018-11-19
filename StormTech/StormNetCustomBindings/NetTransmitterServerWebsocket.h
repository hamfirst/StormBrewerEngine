#pragma once

#include "StormNet/NetTransmitter.h"
#include "StormNet/NetPipeMode.h"
#include "StormNet/NetBitWriterVector.h"

#include "StormSockets/StormSocketConnectionId.h"

class NetServerBackendWebsocket;

struct NetTransmitterServerWebsocket : public NetTransmitter
{
  NetTransmitterServerWebsocket();

  NetBitWriter & CreateWriter(NetPipeMode mode, int channel_index, int channel_bits, bool ack) override;
  void SendWriter(NetBitWriter & writer) override;

public:
  NetBitWriterVector m_Writer = NetBitWriterVector(1400);

  NetServerBackendWebsocket * m_Server = nullptr;
  StormSockets::StormSocketConnectionId m_Handle = {};
  bool m_Disconnected = false;
};
