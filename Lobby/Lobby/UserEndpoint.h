#pragma once

#include <HurricaneDDS/DDSEndpointInterface.h>

#include "UserConnectionMessages.refl.h"
#include "LobbyConfig.h"

class UserEndpoint
{
public:
  UserEndpoint(const DDSEndpointInterface & endpoint_interface);

  void HandleData(const char * data);
  void HandleDisconnect();

private:

  void ConnectionError(const char * err_msg);
  void HandleReverseLookup(const DDSResolverRequest & resolver_data);
  void HandleTorBlacklistLookup(const DDSResolverRequest & resolver_data);

#ifdef ENABLE_AUTH_STEAM
  void HandleTokenValidation(bool success, const std::string & steam_id);
  void HandleSteamAuthenticationRequest(bool success, const char * data, const char * headers);
  void HandleSteamOwnershipRequest(bool success, const char * data, const char * headers);
  void HandleSteamUserInfoRequest(bool success, const char * data, const char * headers);
  void SetSteamUserId(uint64_t steam_id);
  void FinalizeSteamValidation(uint64_t steam_id);
#endif

  void FinalizeConnect();


private:

  enum EndpointState
  {
    kVersionRequest,
    kLookup,
    kGeolocate,
    kTorBlacklist,
    kIdentify,
    kExternalTokenValidation,
    kSteamTokenValidation,
    kSteamOwnershipValidation,
    kSteamUserInfo,
    kCreateConnectionObject,
    kConnectedToObj,
    kDisconnecting,
  };

  EndpointState m_State;
  DDSEndpointInterface m_EndpointInterface;

  int m_ProofVal = 0;
  bool m_Error = false;

  uint64_t m_PlatformId = 0;
  uint64_t m_UserId = 0;
  DDSKey m_ConnectionKey = 0;

  DDSDeferredCallback m_Callback;

  std::string m_RemoteHostName;
  std::string m_CountryCode;
  std::string m_CurrencyCode;
};
