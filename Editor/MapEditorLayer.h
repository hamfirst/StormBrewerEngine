#pragma once

#include "Foundation/Common.h"

enum class MapEditorLayerItemType
{
  kManualTileLayerParent,
  kManualTileLayer,
  kEntityLayerParent,
  kEntityLayer,
  kEntity,
  kParalaxLayerParent,
  kParalaxLayer,
  kEffectLayerParent,
  kEffectLayer,
  kVolumeParent,
  kCreateVolume,
  kVolume,
  kPathParent,
  kCreatePath,
  kPath,
};

class MapEditorLayerSelection
{
public:
  MapEditorLayerItemType m_Type;
  std::size_t m_Index;
  std::size_t m_SubIndex;
};

