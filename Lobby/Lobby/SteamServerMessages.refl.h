#pragma once

#include <string>
#include <vector>

#include <StormRefl/StormRefl.h>

#include "LobbyConfig.h"

#ifdef ENABLE_AUTH_STEAM

struct SteamValidationResponseParams
{
  STORM_REFL;
  std::string result;
  std::string steamid;
  std::string ownersteamid;
  bool vacbanned;
  bool publisherbanned;
};

struct SteamValidationResponse
{
  STORM_REFL;
  SteamValidationResponseParams params;
};

struct SteamValidation
{
  STORM_REFL;
  SteamValidationResponse response;
};

struct SteamOwnershipResponseParams
{
  STORM_REFL;
  std::string appid;
  bool ownsapp;
  bool permanent;
  std::string timestamp;
  std::string ownersteamid;
};

struct SteamOwnershipResponse
{
  STORM_REFL;
  std::vector<SteamOwnershipResponseParams> apps;
};

struct SteamOwnership
{
  STORM_REFL;
  SteamOwnershipResponse appownership;
};

struct SteamTxnUserInfoResponseParams
{
  STORM_REFL;
  std::string state;
  std::string country;
  std::string currency;
  std::string status;
};

struct SteamTxnUserInfoResponse
{
  STORM_REFL;
  std::string result;
  SteamTxnUserInfoResponseParams params;
};


struct SteamTxnUserInfo
{
  STORM_REFL;
  SteamTxnUserInfoResponse response;
};

#endif