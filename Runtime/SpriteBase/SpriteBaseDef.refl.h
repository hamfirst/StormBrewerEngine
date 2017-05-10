#pragma once

#include "Runtime/RuntimeCommon.h"
#include "Runtime/FrameData/FrameData.refl.h"

#include <StormRefl/StormRefl.h>
#include <StormData/StormDataTypes.h>

struct RUNTIME_EXPORT SpriteBaseDefTexture
{
public:
  STORM_DATA_DEFAULT_CONSTRUCTION(SpriteBaseDefTexture);

  RString STORM_REFL_ATTR_VAL(file, image) m_Filename;

  RInt m_FrameWidth;
  RInt m_FrameHeight;
};

struct RUNTIME_EXPORT SpriteBaseDefAnimFrame
{
public:
  STORM_DATA_DEFAULT_CONSTRUCTION(SpriteBaseDefAnimFrame);

  RNumber<uint64_t> m_FrameId;
  RInt m_FrameDuration = 5;
};

struct RUNTIME_EXPORT SpriteBaseDefAnimation
{
public:
  STORM_DATA_DEFAULT_CONSTRUCTION(SpriteBaseDefAnimation);

  RString m_Name;
  RMergeList<SpriteBaseDefAnimFrame> m_Frames;
};

struct RUNTIME_EXPORT SpriteBaseDef
{
public:
  STORM_DATA_DEFAULT_CONSTRUCTION(SpriteBaseDef);

  RMergeList<SpriteBaseDefTexture> m_Textures;
  RMergeList<SpriteBaseDefAnimation> m_Animations;

  FrameData m_GlobalData;
  RMap<uint64_t, FrameData> m_FrameData;
};
