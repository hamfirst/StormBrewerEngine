
#include "Runtime/RuntimeCommon.h"
#include "Runtime/Map/MapDef.refl.meta.h"
#include "Runtime/Map/MapTileJson.h"

#include "StormData/StormDataJson.h"

STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(MapManualTileLayer);
STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(MapEntity);
STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(MapEntityLayer);
STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(MapServerObject);
STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(MapServerObjectLayer);
STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(MapParallaxLayerObject);
STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(MapParallaxLayer);
STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(MapEffectLayer);
STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(MapPathPoint);
STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(MapAnchor);
STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(MapPath);
STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(MapVolume);
STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(MapPathfindingInfo);
STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(MapPropertiesInfo);
STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(MapDef);
STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(MapDefPropertiesOnly);



Vector2 MapAnchor::GetPoint() const
{
  return Vector2(m_X, m_Y);
}

MapAnchor::operator Vector2() const
{
  return GetPoint();
}

Vector2 MapPathPoint::GetPoint() const
{
  return Vector2(m_X, m_Y);
}

MapPathPoint::operator Vector2() const
{
  return GetPoint();
}

Box MapVolume::GetBox() const
{
  return Box::FromPoints(Vector2(m_XStart, m_YStart), Vector2(m_XEnd, m_YEnd));
}

bool MapPathfindingCalculatedInfo::operator == (const MapPathfindingCalculatedInfo & rhs) const
{
  return m_Id == rhs.m_Id;
}
