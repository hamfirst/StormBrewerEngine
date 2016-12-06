#pragma once

#include "Foundation/Common.h"

#include <StormRefl/StormRefl.h>

struct DocumentSchemaError
{
  STORM_REFL;
  std::size_t m_Time;
  std::string m_Path;
  std::string m_Data;
};

struct DocumentLink
{
  STORM_REFL;
  std::string m_SourceAsset;
  std::string m_RemotePath;
  std::string m_LocalPath;
};
