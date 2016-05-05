#pragma once

#include "DataCommon.h"
#include "BasicTypes\BasicTypes.h"

REFL_ENUM(SpriteFrameDataType, int,
  HitBox,
  Collision,
  GroundCollision,
  Damage1,
  Damage2,
  Hazard,
  Invalid);

REFL_ENUM(SpriteAnimEventMode, int,
  ApplyOnAllFrames,
  ApplyOnInitialFrame,
  ApplyOnStartOfFrame);


struct SpriteFrameDataBox
{
  REFL_MEMBERS
  (
    (Start, Vector2),
    (End, Vector2)
  )
};

struct SpriteFrameDataAnchor
{
  REFL_MEMBERS
  (
    (AnchorIndex, int),
    (Pos, Vector2)
  )
};

struct SpriteFrameDataBoxList
{
  REFL_MEMBERS
  (
    (Type, SpriteFrameDataType),
    (Boxes, RList<SpriteFrameDataBox>)
  )
};

struct SpriteFrameMetaData
{
  REFL_MEMBERS
  (
    (BoxLists, RList<SpriteFrameDataBoxList>),
    (AnchorList, RList<SpriteFrameDataAnchor>),
    (FrameHash, RHash),
    (FrameFlags, int)
  )
};

struct SpriteBuilderSchemaTexture
{
  REFL_MEMBERS
  (
    (TextureFile, RString),
    (TileWidth, int),
    (TileHeight, int)
  )
};

struct SpriteAnchor
{
  REFL_MEMBERS
  (
    (Name, RString),
    (DefaultX, int),
    (DefaultY, int)
  )
};

struct SpriteAnimEvent
{
  REFL_MEMBERS
  (
    (EventType, RString),
    (EventData, RString),
    (MetaDataType, SpriteFrameDataType),
    (Mode, SpriteAnimEventMode)
  )
};

struct SpriteAnimationFrame
{
  REFL_MEMBERS
  (
    (FrameHash, RHash),
    (FrameDelay, int),
    (LoopFrame, bool),
    (HoldFrame, bool),
    (MarkFrame, bool),
    (Events, RList<SpriteAnimEvent>)
  )
};

struct SpriteAnimation
{
  REFL_MEMBERS
  (
    (Name, RString),
    (Expanded, bool),
    (Events, RList<SpriteAnimEvent>),
    (Frames, RList<SpriteAnimationFrame>)
  )
};

struct SpriteBuilderSchema
{
  REFL_MEMBERS
  (
    (PreviewAnimate, bool),
    (ShowMetaData, bool),
    (ShowFrameGrid, bool),
    (Textures, RList<SpriteBuilderSchemaTexture>),
    (Anchors, RList<SpriteAnchor>),
    (FrameMetaData, RHashMap<SpriteFrameMetaData>),
    (MoveBox, SpriteFrameDataBox)
  )
};

class SpriteBuilder
{
public:

private:
  SpriteBuilderSchema m_Data;
};
