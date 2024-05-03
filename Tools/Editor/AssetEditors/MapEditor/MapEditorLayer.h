#pragma once

#include "Foundation/Common.h"

enum class MapEditorLayerItemType
{
  kMapProperties,
  kPathfinding,
  kManualTileLayerParent,
  kManualTileLayer,
  kEntityLayerParent,
  kEntityLayer,
  kEntity,
  kServerObjectLayerParent,
  kServerObjectLayer,
  kServerObject,
  kParallaxLayerParent,
  kParallaxLayer,
  kCreateParallaxObject,
  kParallaxObject,
  kEffectLayerParent,
  kEffectLayer,
  kVolumeParent,
  kCreateVolume,
  kAllVolumes,
  kVolume,
  kPathParent,
  kCreatePath,
  kAllPaths,
  kPath,
  kAnchorParent,
  kCreateAnchor,
  kAllAnchors,
  kAnchor,
};

class MapEditorLayerSelection
{
public:
  MapEditorLayerItemType m_Type;
  std::size_t m_Index;
  std::size_t m_SubIndex;
};

