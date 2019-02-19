#pragma once

#include <HurricaneDDS/DDSEndpointInterface.h>

#include "UserConnectionMessages.refl.h"

class UserEndpoint
{
public:
  UserEndpoint(const DDSEndpointInterface & endpoint_interface);

  void HandleData(const char * data);
  void HandleDisconnect();

private:

  void ConnectionError(const char * err_msg);
  void HandleTokenValidation(bool success, const std::string & steam_id);
  void HandleReverseLookup(const DDSResolverRequest & resolver_data);
  void HandleTorBlacklistLookup(const DDSResolverRequest & resolver_data);
  void HandleSteamAuthenticationRequest(bool success, const char * data, const char * headers);
  void HandleSteamOwnershipRequest(bool success, const char * data, const char * headers);
  void HandleSteamUserInfoRequest(bool success, const char * data, const char * headers);

  void FinalizeSteamValidation(uint64_t steam_id);
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
  DDSKey m_ConnectionKey = 0;

  DDSDeferredCallback m_Callback;

  std::string m_RemoteHostName;
  std::string m_CountryCode;
  std::string m_CurrencyCode;
};
