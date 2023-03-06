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

struct RUNTIME_EXPORT FrameDataMultiBox
{
public:
  STORM_DATA_DEFAULT_CONSTRUCTION(FrameDataMultiBox);

  RString m_FrameDataName;
  ROpaque<std::vector<Box>> m_Data;
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

struct RUNTIME_EXPORT FrameDataLowerEdgeInfo
{
  STORM_REFL;
  int m_OffsetPixels;

  bool operator == (const FrameDataLowerEdgeInfo & rhs) const
  {
    return m_OffsetPixels == rhs.m_OffsetPixels;
  }
};

struct RUNTIME_EXPORT FrameDataLowerEdge
{
public:
  STORM_DATA_DEFAULT_CONSTRUCTION(FrameDataLowerEdge);

  RString m_FrameDataName;
  ROpaque<FrameDataLowerEdgeInfo> m_Data;
};

struct RUNTIME_EXPORT FrameDataAnchorElement
{
  STORM_DATA_DEFAULT_CONSTRUCTION(FrameDataAnchorElement);
  RString m_AnchorName;
  ROpaque<Vector2> m_Position;
};

struct RUNTIME_EXPORT FrameData
{
public:
  STORM_DATA_DEFAULT_CONSTRUCTION(FrameData);

  RMergeList<FrameDataSingleBox> m_SingleBoxData;
  RMergeList<FrameDataMultiBox> m_MultiBoxData;
  RMergeList<FrameDataSingleLine> m_SingleLineData;
  RMergeList<FrameDataLowerEdge> m_LowerEdgeData;
  RMergeList<FrameDataAnchorElement> m_Anchors;
};

enum class STORM_REFL_ENUM FrameDataDefType
{
  kSingleBox,
  kMultiBox,
  kSingleLine,
  kLowerEdge,
  kAnchor
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
