#pragma once

#include "StormNet/NetServerBackend.h"
#include "StormNet/NetServerInterface.h"
#include "StormWebrtc/StormWebrtcServer.h"

#include <sb/static_sized_array_alloc.h>

#include <unordered_map>
#include <memory>

struct NetTransmitterServerWebrtc;

struct NetServerBackendWebrtcSettings
{
  uint16_t m_Port;
  uint16_t m_MaxConnections;
  const char * m_KeyFile;
  const char * m_CertFile;

  std::vector<NetPipeMode> m_InStreams;
  std::vector<NetPipeMode> m_OutStreams;
};

class NetServerBackendWebrtc : public NetServerBackend
{
public:
  NetServerBackendWebrtc(NetServerInterface * iface, const NetServerBackendWebrtcSettings & settings);
  ~NetServerBackendWebrtc();

  NetServerBackendWebrtc(const NetServerBackendWebrtc & rhs) = delete;
  NetServerBackendWebrtc(NetServerBackendWebrtc && rhs) = delete;

  NetServerBackendWebrtc & operator = (const NetServerBackendWebrtc & rhs) = delete;
  NetServerBackendWebrtc & operator = (NetServerBackendWebrtc && rhs) = delete;

  void Update() override;
  void ForceDisconnect(uint32_t connection_id) override;

private:
  std::unique_ptr<StormWebrtcServer> m_Host;
  NetServerInterface * m_Interface;

  std::vector<NetPipeMode> m_IncStreams;
  std::vector<NetPipeMode> m_OutStreams;

  StaticSizedArrayAlloc<NetTransmitterServerWebrtc> m_Transmitters;
};
