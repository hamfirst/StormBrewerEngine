
#pragma once

#include <StormRefl/StormRefl.h>
#include <StormData/StormDataTypes.h>

struct GoogleCredentialsInfo
{
  STORM_REFL;

  std::string type;
  std::string project_id;
  std::string private_key_id;
  std::string private_key;
  std::string client_email;
  std::string client_id;
  std::string auth_uri;
  std::string token_uri;
  std::string auth_provider_x509_cert_url;
  std::string client_x509_cert_url;
};

struct GooglePlatformSettings
{
  STORM_REFL;

  std::string project_id;
  std::string instance_type;
};


struct GoogleAssertionHeader
{
  STORM_REFL;

  std::string alg;
  std::string kid;
  std::string typ;
};

struct GoogleAssertionPayload
{
  STORM_REFL;

  std::string iss;
  std::string scope;
  std::string aud;
  long iat;
  long exp;
};

struct GoogleTokenResponse
{
  STORM_REFL;

  std::string access_token;
  std::string token_type;
  int expires_in;
};

