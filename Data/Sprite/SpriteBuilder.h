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
    (Boxes, r_list<SpriteFrameDataBox>)
  )
};

struct SpriteFrameMetaData
{
  REFL_MEMBERS
  (
    (BoxLists, r_list<SpriteFrameDataBoxList>),
    (AnchorList, r_list<SpriteFrameDataAnchor>),
    (FrameHash, r_hash),
    (FrameFlags, int)
  )
};

struct SpriteBuilderSchemaTexture
{
  REFL_MEMBERS
  (
    (TextureFile, r_string),
    (TileWidth, int),
    (TileHeight, int)
  )
};

struct SpriteAnchor
{
  REFL_MEMBERS
  (
    (Name, r_string),
    (DefaultX, int),
    (DefaultY, int)
  )
};

struct SpriteAnimEvent
{
  REFL_MEMBERS
  (
    (EventType, r_string),
    (EventData, r_string),
    (MetaDataType, SpriteFrameDataType),
    (Mode, SpriteAnimEventMode)
  )
};

struct SpriteAnimationFrame
{
  REFL_MEMBERS
  (
    (FrameHash, r_hash),
    (FrameDelay, int),
    (LoopFrame, bool),
    (HoldFrame, bool),
    (MarkFrame, bool),
    (Events, r_list<SpriteAnimEvent>)
  )
};

struct SpriteAnimation
{
  REFL_MEMBERS
  (
    (Name, r_string),
    (Expanded, bool),
    (Events, r_list<SpriteAnimEvent>),
    (Frames, r_list<SpriteAnimationFrame>)
  )
};

struct SpriteBuilderSchema
{
  REFL_MEMBERS
  (
    (PreviewAnimate, bool),
    (ShowMetaData, bool),
    (ShowFrameGrid, bool),
    (Textures, r_list<SpriteBuilderSchemaTexture>),
    (Anchors, r_list<SpriteAnchor>),
    (FrameMetaData, r_dictionary<SpriteFrameMetaData>),
    (MoveBox, SpriteFrameDataBox)
  )
};

class SpriteBuilder
{
public:

private:
  SpriteBuilderSchema m_Data;
};
