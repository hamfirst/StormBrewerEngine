#pragma once

#include "StormNet/NetServerBackend.h"
#include "StormNet/NetServerInterface.h"

#include <sb/static_sized_array_alloc.h>

#include <unordered_map>
#include <memory>

namespace StormSockets
{
  class StormSocketBackend;
  class StormSocketServerFrontendWebsocket;
}

struct NetTransmitterServerWebsocket;

struct NetServerBackendWebsocketSettings
{
  uint16_t m_Port;
  uint16_t m_MaxConnections;
};

class NetServerBackendWebsocket : public NetServerBackend
{
public:
  NetServerBackendWebsocket(NetServerInterface * iface, const NetServerBackendWebsocketSettings & settings);
  ~NetServerBackendWebsocket();

  NetServerBackendWebsocket(const NetServerBackendWebsocket & rhs) = delete;
  NetServerBackendWebsocket(NetServerBackendWebsocket && rhs) = delete;

  NetServerBackendWebsocket & operator = (const NetServerBackendWebsocket & rhs) = delete;
  NetServerBackendWebsocket & operator = (NetServerBackendWebsocket && rhs) = delete;

  void Update() override;
  void ForceDisconnect(uint32_t connection_id) override;

private:
  friend struct NetTransmitterServerWebsocket;

  std::unique_ptr<StormSockets::StormSocketBackend> m_Backend;
  std::unique_ptr<StormSockets::StormSocketServerFrontendWebsocket> m_WebsocketFrontend;

  NetServerInterface * m_Interface;

  std::vector<NetPipeMode> m_IncStreams;
  std::vector<NetPipeMode> m_OutStreams;

  StaticSizedArrayAlloc<NetTransmitterServerWebsocket> m_Transmitters;
};
