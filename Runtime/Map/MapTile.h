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

  uint64_t GetTileId() const
  {
    uint64_t h = m_TextureHash;
    return (h << 32) | (uint64_t)m_FrameId;
  }
};

struct MapAnimatedTile
{
  RInt x;
  RInt y;

  RUInt m_Animation;
  RUInt m_FrameOffset;

  bool operator == (const MapAnimatedTile & rhs) const
  {
    return x == rhs.x && y == rhs.y && m_Animation == rhs.m_Animation;
  }
};

