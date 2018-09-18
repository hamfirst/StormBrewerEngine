#pragma once

#include "Runtime/RuntimeCommon.h"
#include "Runtime/FrameData/FrameData.refl.h"
#include "Runtime/SpriteBase/SpriteAnimationEventDef.refl.h"
#include "Runtime/SpriteBase/SpriteAnimationEventTypeDatabase.h"

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

struct RUNTIME_EXPORT SpriteBaseAnimationEvent
{
  STORM_DATA_DEFAULT_CONSTRUCTION(SpriteBaseAnimationEvent);
  RInt m_Frame;
  RInt m_FrameDelay;

  RPolymorphic<SpriteAnimationEventDataBase, SpriteAnimationEventTypeDatabase, SpriteAnimationEventDataTypeInfo> m_EventData;
  ROpaque<std::vector<Box>> m_EventArea;
};

struct RUNTIME_EXPORT SpriteBaseDefAnimation
{
public:
  STORM_DATA_DEFAULT_CONSTRUCTION(SpriteBaseDefAnimation);

  RString m_Name;
  RMergeList<SpriteBaseDefAnimFrame> m_Frames;
  RMergeList<SpriteBaseAnimationEvent> m_Events;
};

struct RUNTIME_EXPORT SpriteBaseDefSkinElement
{
public:
  STORM_DATA_DEFAULT_CONSTRUCTION(SpriteBaseDefSkinElement);

  RString m_Texture;
  RString m_Replacement;
};

struct RUNTIME_EXPORT SpriteBaseDefSkin
{
public:
  STORM_DATA_DEFAULT_CONSTRUCTION(SpriteBaseDefSkin);

  RString m_Name;
  RMergeList<SpriteBaseDefSkinElement> m_TextureReplacements;
};

struct RUNTIME_EXPORT SpriteBaseDefAnchor
{
public:
  STORM_DATA_DEFAULT_CONSTRUCTION(SpriteBaseDefAnchor);

  RString m_AnchorName;
  ROpaque<Vector2> m_DefaultPosition;
};

struct RUNTIME_EXPORT SpriteBaseDef
{
public:
  STORM_DATA_DEFAULT_CONSTRUCTION(SpriteBaseDef);

  RMergeList<SpriteBaseDefTexture> m_Textures;
  RMergeList<SpriteBaseDefAnimation> m_Animations;
  RMergeList<SpriteBaseDefSkin> m_Skins;
  RMergeList<SpriteBaseDefAnchor> m_Anchors;

  FrameData m_InstanceData;
  RMap<uint64_t, FrameData> m_FrameData;
};
