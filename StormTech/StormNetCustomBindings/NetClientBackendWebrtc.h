#pragma once

#include "StormNet/NetClientBackend.h"
#include "StormNet/NetClientInterface.h"
#include "StormWebrtcClientAPI/StormWebrtcClient.h"

#include "NetTransmitterClientWebrtc.h"

class NetClientBackendWebrtc : public NetClientBackend
{
public:
  NetClientBackendWebrtc(NetClientInterface * iface, const char * host_addr, uint16_t port, const char * fingerprint, 
                         const std::vector<NetPipeMode> & inc_channels, const std::vector<NetPipeMode> & out_channels);
  ~NetClientBackendWebrtc();

  NetClientBackendWebrtc(const NetClientBackendWebrtc & rhs) = delete;
  NetClientBackendWebrtc(NetClientBackendWebrtc && rhs) = delete;

  NetClientBackendWebrtc & operator = (const NetClientBackendWebrtc & rhs) = delete;
  NetClientBackendWebrtc & operator = (NetClientBackendWebrtc && rhs) = delete;

  virtual void Update() override;
  virtual void Disconnect() override;

private:
  friend struct NetTransmitterClientWebrtc;

  NetTransmitterClientWebrtc m_Transmitter;
  std::unique_ptr<StormWebrtcClient> m_Host;

  std::vector<std::pair<uint8_t, bool>> m_IncSeqs;
  std::vector<std::pair<uint8_t, bool>> m_OutSeqs;

  NetClientInterface * m_Interface;
  bool m_Connected;
};



