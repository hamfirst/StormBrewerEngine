
#pragma once

#include "StormRefl/StormRefl.h"
#include "StormData/StormDataTypes.h"


enum class MapHandleType
{
  kEntity,
  kEffectLayer,
  kServerObject,
  kAnchor,
  kPath,
  kVolume,
  kNone,
};

MapHandleType GetMapHandleForTypeNameHash(uint32_t type_name_hash);

struct MapHandleBase
{
  STORM_DATA_DEFAULT_CONSTRUCTION(MapHandleBase);
  RUInt STORM_REFL_ATTR(noui) m_GUID;
};

struct MapEntityHandle : public MapHandleBase
{
  STORM_DATA_DEFAULT_CONSTRUCTION_DERIVED(MapEntityHandle);
};

struct MapEffectLayerHandle : public MapHandleBase
{
  STORM_DATA_DEFAULT_CONSTRUCTION_DERIVED(MapEffectLayerHandle);
};

struct MapServerObjectHandle : public MapHandleBase
{
  STORM_DATA_DEFAULT_CONSTRUCTION_DERIVED(MapServerObjectHandle);
};

struct MapAnchorHandle : public MapHandleBase
{
  STORM_DATA_DEFAULT_CONSTRUCTION_DERIVED(MapAnchorHandle);
};

struct MapPathHandle : public MapHandleBase
{
  STORM_DATA_DEFAULT_CONSTRUCTION_DERIVED(MapPathHandle);
};

struct MapVolumeHandle : public MapHandleBase
{
  STORM_DATA_DEFAULT_CONSTRUCTION_DERIVED(MapVolumeHandle);
};


