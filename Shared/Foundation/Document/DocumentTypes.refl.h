#pragma once

#include "Foundation/Common.h"

#include "StormRefl/StormRefl.h"

struct DocumentLink
{
  STORM_REFL;
  std::string m_SourceAsset;
  std::string m_RemotePath;
  std::string m_LocalPath;
};
