#pragma once

#include <HurricaneDDS/DDSEndpointInterface.h>

#include "UserConnectionMessages.refl.h"

class GameServerEndpoint
{
public:
  GameServerEndpoint(const DDSEndpointInterface & endpoint_interface);

  void HandleData(const char * data);
  void HandleDisconnect();

private:

  void ConnectToObject();


private:

  template <typename T>
  void SendPacket(const T & t);

private:

  enum EndpointState
  {
    kIdentify,
    kCreatingObject,
    kConnected,
    kDisconnecting,
  };

  EndpointState m_State;
  DDSEndpointInterface m_EndpointInterface;

  DDSKey m_ServerKey;
  DDSDeferredCallback m_Callback;

  int m_Version;
};
