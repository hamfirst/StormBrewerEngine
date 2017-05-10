#pragma once

#include "Runtime/RuntimeCommon.h"


struct MapTile
{
  int x;
  int y;

  uint32_t m_TextureHash;
  uint32_t m_FrameId;

  bool operator == (const MapTile & rhs) const
  {
    return x == rhs.x && y == rhs.y && m_TextureHash == rhs.m_TextureHash && m_FrameId == rhs.m_FrameId;
  }
};

