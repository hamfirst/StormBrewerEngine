
#include "StormRefl/StormRefl.h"

#include <string>

struct UploadSettings
{
  STORM_REFL;

  std::string m_DistServerAddress = "https://www.stormbrewers.com";
  int m_DistServerPort = 45480;
  std::string m_DistServerIdent = "dist";
};

struct ServerSettings
{
  STORM_REFL;

  int m_DistServerPort = 45480;
  std::string m_DistServerIdent = "dist";
};

