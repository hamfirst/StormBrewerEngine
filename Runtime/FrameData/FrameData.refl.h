#pragma once

#include "Runtime/RuntimeCommon.h"

#include "Foundation/BasicTypes/BasicTypes.refl.h"

#include <StormRefl/StormRefl.h>
#include <StormData/StormDataTypes.h>

struct RUNTIME_EXPORT FrameDataSingleBox
{
public:
  STORM_DATA_DEFAULT_CONSTRUCTION(FrameDataSingleBox);

  RString m_FrameDataName;
  ROpaque<Box> m_Data;
};

struct RUNTIME_EXPORT FrameDataSingleLineInfo
{
  STORM_REFL;
  Vector2 m_Start;
  Vector2 m_End;

  bool operator == (const FrameDataSingleLineInfo & rhs) const
  {
    return m_Start == rhs.m_Start && m_End == rhs.m_End;
  }
};

struct RUNTIME_EXPORT FrameDataSingleLine
{
public:
  STORM_DATA_DEFAULT_CONSTRUCTION(FrameDataSingleLine);

  RString m_FrameDataName;
  ROpaque<FrameDataSingleLineInfo> m_Data;
};

struct RUNTIME_EXPORT FrameData
{
public:
  STORM_DATA_DEFAULT_CONSTRUCTION(FrameData);

  RMergeList<FrameDataSingleBox> m_SingleBoxData;
  RMergeList<FrameDataSingleLine> m_SingleLineData;
};

enum STORM_REFL_ENUM class FrameDataDefType
{
  kSingleBox,
  kSingleLine,
};

struct RUNTIME_EXPORT FrameDataDefElem
{
  STORM_REFL;
  FrameDataDefType m_Type;
  std::string m_Name;
};

struct RUNTIME_EXPORT FrameDataDef
{
  STORM_REFL;
  std::vector<FrameDataDefElem> m_SpriteGlobalData;
  std::vector<FrameDataDefElem> m_SpriteFrameData;

  std::vector<FrameDataDefElem> m_TileGlobalData;
  std::vector<FrameDataDefElem> m_TileFrameData;
};
