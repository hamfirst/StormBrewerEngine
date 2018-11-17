
#include "Runtime/RuntimeCommon.h"
#include "Runtime/Map/MapHandles.refl.meta.h"

#include "StormData/StormDataJson.h"


MapHandleType GetMapHandleForTypeNameHash(uint32_t type_name_hash)
{
  switch(type_name_hash)
  {
    case StormReflTypeInfo<MapEntityHandle>::GetNameHash():
      return MapHandleType::kEntity;
    case StormReflTypeInfo<MapEffectLayerHandle>::GetNameHash():
      return MapHandleType::kEffectLayer;
    case StormReflTypeInfo<MapServerObjectHandle>::GetNameHash():
      return MapHandleType::kServerObject;
    case StormReflTypeInfo<MapAnchorHandle>::GetNameHash():
      return MapHandleType::kAnchor;
    case StormReflTypeInfo<MapPathHandle>::GetNameHash():
      return MapHandleType::kPath;
    case StormReflTypeInfo<MapVolumeHandle>::GetNameHash():
      return MapHandleType::kVolume;
  }

  return MapHandleType::kNone;
}

STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(MapHandleBase);
STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(MapEntityHandle);
STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(MapEffectLayerHandle);
STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(MapServerObjectHandle);
STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(MapAnchorHandle);
STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(MapPathHandle);
STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(MapVolumeHandle);

