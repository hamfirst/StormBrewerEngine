
#include "StormRefl/StormRefl.h"

#include "ProjectSettings/ProjectPorts.h"

#include <string>

struct UploadSettings
{
  STORM_REFL;

  std::string m_DistServerAddress = "https://www.stormbrewers.com";
  int m_DistServerPort = DIST_SERVER_PORT;
  std::string m_DistServerIdent = "dist";
};

struct ServerSettings
{
  STORM_REFL;

  int m_DistServerPort = DIST_SERVER_PORT;
  std::string m_DistServerIdent = "dist";
};

