#pragma once

#include "DataCommon.h"
 
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
    (int, StartX),
    (int, StartY),
    (int, EndX),
    (int, EndY)
  )
};

struct SpriteFrameDataAnchor
{
  REFL_MEMBERS
  (
    (int, AnchorIndex),
    (int, X),
    (int, Y)
  )
};

struct SpriteFrameDataBoxList
{
  REFL_MEMBERS
  (
    (SpriteFrameDataType, Type),
    (r_list<SpriteFrameDataBox>, Boxes)
  )
};

struct SpriteFrameMetaData
{
  REFL_MEMBERS
  (
    (r_list<SpriteFrameDataBoxList>, BoxLists),
    (r_list<SpriteFrameDataAnchor>, AnchorList),
    (r_hash, FrameHash),
    (int, FrameFlags)
  )
};

struct SpriteBuilderSchemaTexture
{
  REFL_MEMBERS
  (
    (r_string, TextureFile),
    (int, TileWidth),
    (int, TileHeight)
  )
};

struct SpriteAnchor
{
  REFL_MEMBERS
  (
    (r_string, Name),
    (int, DefaultX),
    (int, DefaultY)
  )
};

struct SpriteAnimEvent
{
  REFL_MEMBERS
  (
    (r_string, EventType),
    (r_string, EventData),
    (SpriteFrameDataType, MetaDataType),
    (SpriteAnimEventMode, Mode)
  )
};

struct SpriteAnimationFrame
{
  REFL_MEMBERS
  (
    (r_hash, FrameHash),
    (int, FrameDelay),
    (bool, LoopFrame),
    (bool, HoldFrame),
    (bool, MarkFrame),
    (r_list<SpriteAnimEvent>, Events)
  )
};

struct SpriteAnimation
{
  REFL_MEMBERS
  (
    (r_string, Name),
    (bool, Expanded),
    (r_list<SpriteAnimEvent>, Events),
    (r_list<SpriteAnimationFrame>, Frames)
  )
};

struct SpriteBuilderSchema
{
  REFL_MEMBERS
  (
    (bool, PreviewAnimate),
    (bool, ShowMetaData),
    (bool, ShowFrameGrid),
    (r_list<SpriteBuilderSchemaTexture>, Textures),
    (r_list<SpriteAnchor>, Anchors),
    (r_dictionary<SpriteFrameMetaData>, FrameMetaData),
    (SpriteFrameDataBox, MoveBox)
  )
};



class SpriteBuilder
{
public:

private:
  SpriteBuilderSchema m_Data;
};
