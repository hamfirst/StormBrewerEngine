#pragma once

#include "StormRefl/StormRefl.h"
#include "StormData/StormData.h"
#include "StormData/StormDataTypes.h"

#include "Runtime/RuntimeCommon.h"


enum STORM_REFL_ENUM class AtlasDefType
{
  kImage,
  kRepeat,
  k3SliceVertical,
  k3SliceHorizontal,
  k9Slice
};

struct RUNTIME_EXPORT AtlasDefTexture
{
public:
  STORM_DATA_DEFAULT_CONSTRUCTION(AtlasDefTexture);

  RString STORM_REFL_ATTR_VAL(file, image) m_Filename;
};

struct RUNTIME_EXPORT AtlasDefElementPosition
{
  STORM_DATA_DEFAULT_CONSTRUCTION(AtlasDefElementPosition);
  REnum<AtlasDefType> m_Type;

  RInt m_StartX = 0;
  RInt m_StartY = 0;
  RInt m_EndX = 32;
  RInt m_EndY = 32;

  RInt m_StartOffsetX = 4;
  RInt m_StartOffsetY = 4;
  RInt m_EndOffsetX = 4;
  RInt m_EndOffsetY = 4;

  RBool m_RepeatHorizontal = true;
  RBool m_RepeatVertical = true;
};

struct RUNTIME_EXPORT AtlasDefElement
{
  STORM_DATA_DEFAULT_CONSTRUCTION(AtlasDefElement);

  RUInt STORM_REFL_ATTR(noui) m_TextureHash;
  RString m_Name;

  AtlasDefElementPosition m_Data;
};

struct RUNTIME_EXPORT AtlasDef
{
  STORM_DATA_DEFAULT_CONSTRUCTION(AtlasDef);

  RMergeList<AtlasDefTexture> m_Textures;
  RMergeList<AtlasDefElement> m_Elements;
};
