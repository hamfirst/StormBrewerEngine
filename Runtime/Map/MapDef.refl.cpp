
#include "Runtime/RuntimeCommon.h"
#include "Runtime/Map/MapDef.refl.meta.h"
#include "Runtime/Map/MapTileJson.h"

#include "StormData/StormDataJson.h"

STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(MapManualTileLayer);
STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(MapEntity);
STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(MapEntityLayer);
STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(MapParalaxLayer);
STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(MapEffectLayer);
STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(MapPathPoint);
STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(MapPath);
STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(MapVolume);
STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(MapDef);


Vector2 MapPathPoint::GetPoint() const
{
  return Vector2(m_X, m_Y);
}

Box MapVolume::GetBox() const
{
  return Box::FromPoints(Vector2(m_XStart, m_YStart), Vector2(m_XEnd, m_YEnd));
}
