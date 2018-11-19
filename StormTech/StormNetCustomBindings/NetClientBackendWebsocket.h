#pragma once

#include "StormNet/NetClientBackend.h"
#include "StormNet/NetClientInterface.h"

#include "Foundation/Common.h"
#include "Foundation/Network/WebSocket.h"

#include "NetTransmitterClientWebsocket.h"

class NetClientBackendWebsocket : public NetClientBackend
{
public:
  NetClientBackendWebsocket(NetClientInterface * iface, const char * host, int port, const char * uri, const char * origin);
  ~NetClientBackendWebsocket();

  NetClientBackendWebsocket(const NetClientBackendWebsocket & rhs) = delete;
  NetClientBackendWebsocket(NetClientBackendWebsocket && rhs) = delete;

  NetClientBackendWebsocket & operator = (const NetClientBackendWebsocket & rhs) = delete;
  NetClientBackendWebsocket & operator = (NetClientBackendWebsocket && rhs) = delete;

  virtual void Update() override;
  virtual void Disconnect() override;

private:
  friend struct NetTransmitterClientWebsocket;

  NetTransmitterClientWebsocket m_Transmitter;
  std::unique_ptr<WebSocket> m_Host;

  NetClientInterface * m_Interface;
  bool m_Connected;
};



