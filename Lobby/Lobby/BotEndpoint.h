#pragma once

#include <HurricaneDDS/DDSEndpointInterface.h>

#include "UserConnectionMessages.refl.h"
#include "LobbyConfig.h"

#if defined(ENABLE_BOTS) && defined(ENABLE_CHANNELS)

class BotEndpoint
{
public:
  BotEndpoint(const DDSEndpointInterface & endpoint_interface);

  void HandleData(const char * data);
  void HandleDisconnect();

private:

  void ConnectToObject();

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

  bool m_Error;

  DDSKey m_BotKey;
  std::string m_UserName;
  std::string m_Password;

  DDSDeferredCallback m_Callback;

};

#endif