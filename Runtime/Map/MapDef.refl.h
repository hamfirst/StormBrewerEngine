#pragma once

#include <StormRefl/StormRefl.h>
#include <StormData/StormDataTypes.h>

#include "Foundation/BasicTypes/BasicTypes.refl.h"

#include "Runtime/RuntimeCommon.h"
#include "Runtime/Entity/EntityDef.refl.h"
#include "Runtime/ServerObject/ServerObjectDef.refl.h"
#include "Runtime/Anchor/AnchorDef.refl.h"
#include "Runtime/Anchor/AnchorTypeDatabase.h"
#include "Runtime/Path/PathDef.refl.h"
#include "Runtime/Path/PathTypeDatabase.h"
#include "Runtime/Volume/VolumeDef.refl.h"
#include "Runtime/Volume/VolumeTypeDatabase.h"
#include "Runtime/Map/MapEffectLayerDef.refl.h"
#include "Runtime/Map/MapPropertiesDef.refl.h"
#include "Runtime/Map/MapEffectLayerTypeDatabase.h"
#include "Runtime/Map/MapPropertiesTypeDatabase.h"
#include "Runtime/Map/MapTile.h"
#include "Runtime/Volume/VolumeTypeDatabase.h"

//#define MAP_PLATFORMER_PATHFINDING

struct RUNTIME_EXPORT MapPropertiesInfo
{
  STORM_DATA_DEFAULT_CONSTRUCTION(MapPropertiesInfo);
  RPolymorphic<MapPropertiesDef, MapPropertiesTypeDatabase, MapPropertiesDataTypeInfo, true> m_MapProperties;
};

struct RUNTIME_EXPORT MapManualTileLayer
{
  STORM_DATA_DEFAULT_CONSTRUCTION(MapManualTileLayer);

  RString STORM_REFL_ATTR_VAL(file, tilesheet) m_TileSheet;
  RString m_Name;
  RInt m_LayerOrder;
  RBool m_CollisionLayer = true;

  RSparseList<ROpaque<MapTile>> STORM_REFL_ATTR(noui) m_Tiles;
  RSparseList<ROpaque<MapAnimatedTile>> STORM_REFL_ATTR(noui) m_Animations;
};

struct RUNTIME_EXPORT MapEntity
{
  STORM_DATA_DEFAULT_CONSTRUCTION(MapEntity);
  RString m_Name;
  RInt m_XPosition;
  RInt m_YPosition;
  EntityDef m_EntityDef;
};

struct RUNTIME_EXPORT MapEntityLayer
{
  STORM_DATA_DEFAULT_CONSTRUCTION(MapEntityLayer);

  RString m_Name;
  RInt m_LayerOrder;
  RMergeList<MapEntity> STORM_REFL_ATTR(noui) m_Entities;
};

struct RUNTIME_EXPORT MapServerObject
{
  STORM_DATA_DEFAULT_CONSTRUCTION(MapServerObject);
  RString m_Name;
  RInt m_XPosition;
  RInt m_YPosition;

  ServerObjectDef m_ServerObject;
};

struct RUNTIME_EXPORT MapServerObjectLayer
{
  STORM_DATA_DEFAULT_CONSTRUCTION(MapServerObjectLayer);

  RString m_Name;
  RMergeList<MapServerObject> STORM_REFL_ATTR(noui) m_Objects;
};

enum STORM_REFL_ENUM class MapParalaxLayerObjectType
{
  kTexture,
  kSprite,
  kVfx,
};

struct RUNTIME_EXPORT MapParalaxLayerObject
{
  STORM_DATA_DEFAULT_CONSTRUCTION(MapParalaxLayerObject);
  RString m_Name;
  REnum<MapParalaxLayerObjectType> m_Type;
  RString STORM_REFL_ATTR_VAL(file, paralax) m_File;
  RString m_Animation;
  RFloat m_PresimTime;

  RInt m_XPosition;
  RInt m_YPosition;
};

struct RUNTIME_EXPORT MapParalaxLayer
{
  STORM_DATA_DEFAULT_CONSTRUCTION(MapParalaxLayer);

  RString m_Name;
  RInt m_LayerOrder;

  RString STORM_REFL_ATTR_VAL(file, image) m_Image;
  RBool m_RepeatX = true;
  RBool m_RepeatY = true;

  RFloat m_OffsetX;
  RFloat m_OffsetY;

  RFloat m_ParalaxX;
  RFloat m_ParalaxY;

  RFloat m_VelocityX;
  RFloat m_VelocityY;

  RMergeList<MapParalaxLayerObject> STORM_REFL_ATTR(noui) m_Objects;
};

struct RUNTIME_EXPORT MapEffectLayer
{
  STORM_DATA_DEFAULT_CONSTRUCTION(MapEffectLayer);

  RString m_Name;
  RInt m_LayerOrder;

  RPolymorphic<MapEffectLayerInitData, MapEffectLayerTypeDatabase, MapEffectLayerDataTypeInfo> m_EffectLayerData;
};

struct RUNTIME_EXPORT MapAnchor
{
  STORM_DATA_DEFAULT_CONSTRUCTION(MapAnchor);
  RString m_Name;
  RPolymorphic<AnchorDataBase, AnchorTypeDatabase, AnchorDataTypeInfo> m_AnchorData;

  RString STORM_REFL_ATTR_VAL(file, sprite) m_Sprite;

  RInt m_X;
  RInt m_Y;

  Vector2 GetPoint() const;
  operator Vector2() const;
};

struct RUNTIME_EXPORT MapPathPoint
{
  STORM_DATA_DEFAULT_CONSTRUCTION(MapPathPoint);

  RInt m_X;
  RInt m_Y;

  Vector2 GetPoint() const;
  operator Vector2() const;
};

struct RUNTIME_EXPORT MapPath
{
  STORM_DATA_DEFAULT_CONSTRUCTION(MapPath);
  RString m_Name;
  RPolymorphic<PathDataBase, PathTypeDatabase, PathDataTypeInfo> m_PathData;
  RMergeList<MapPathPoint> m_Points;

  template <typename Visitor>
  void VisitLines(Visitor && visitor, bool connect_to_start = false) const
  {
    auto start = m_Points.begin();
    if (start == m_Points.end())
    {
      return;
    }

    auto next = m_Points.begin();
    ++next;

    while (next != m_Points.end())
    {
      auto p1 = start->second.GetPoint();
      auto p2 = next->second.GetPoint();

      visitor(p1, p2);

      ++next;
      ++start;
    }

    if (connect_to_start)
    {
      next = m_Points.begin();

      auto p1 = start->second.GetPoint();
      auto p2 = next->second.GetPoint();

      visitor(p1, p2);
    }
  }
};

struct RUNTIME_EXPORT MapVolume
{
  STORM_DATA_DEFAULT_CONSTRUCTION(MapVolume);
  RString m_Name;
  RPolymorphic<VolumeDataBase, VolumeTypeDatabase, VolumeDataTypeInfo> m_VolumeData;
  RInt m_XStart;
  RInt m_YStart;
  RInt m_XEnd;
  RInt m_YEnd;

  Box GetBox() const;
};

struct RUNTIME_EXPORT MapPathfindingSurface
{
  STORM_REFL;
  Vector2 m_P1;
  Vector2 m_P2;

  int m_Clearance;

  int m_StartConnections1;
  int m_EndConnections1;
  int m_StartConnections2;
  int m_EndConnections2;
};

struct RUNTIME_EXPORT MapPathfindingSurfaceConnection
{
  STORM_REFL;
  uint32_t m_SurfaceIndex;
  bool m_P1;
};

struct RUNTIME_EXPORT MapPathfindingCalculatedInfo
{
  STORM_REFL;

  uint32_t m_Id = 0;

#ifndef MAP_PLATFORMER_PATHFINDING

  int m_GridWidth;
  int m_GridHeight;
  int m_StartX;
  int m_StartY;
  int m_SizeX;
  int m_SizeY;
  std::vector<std::tuple<uint8_t, uint8_t, uint8_t>> m_GridInfo;

#else

  std::vector<MapPathfindingSurface> m_Surfaces;
  std::vector<MapPathfindingSurfaceConnection> m_Connections;

#endif

  bool operator == (const MapPathfindingCalculatedInfo & rhs) const;
};

struct RUNTIME_EXPORT MapPathfindingInfo
{
  STORM_DATA_DEFAULT_CONSTRUCTION(MapPathfindingInfo);

#ifndef MAP_PLATFORMER_PATHFINDING
  RInt m_GridWidth = 8;
  RInt m_GridHeight = 8;

  RInt m_MaximumClearanceX = 32;
  RInt m_MaximumClearanceY = 32;
#else
  RInt m_MinimumClearance = 24;
  RInt m_MaximumClearance = 200;
#endif

  RMergeList<RString> m_CollisionMask = { "Collision" };
  RBool STORM_REFL_ATTR(noui) m_Valid = false;
  ROpaque<MapPathfindingCalculatedInfo> STORM_REFL_ATTR(noui) m_CalculatedInfo;
};

struct RUNTIME_EXPORT MapDef
{
  STORM_DATA_DEFAULT_CONSTRUCTION(MapDef);

  MapPropertiesInfo m_PropertiesInfo;
  MapPathfindingInfo m_PathfingindInfo;
  RMergeList<MapManualTileLayer> m_ManualTileLayers;
  RMergeList<MapServerObjectLayer> m_ServerObjectLayers;
  RMergeList<MapEntityLayer> m_EntityLayers;
  RMergeList<MapParalaxLayer> m_ParalaxLayers;
  RMergeList<MapEffectLayer> m_EffectLayers;
  RMergeList<MapAnchor> m_Anchors;
  RMergeList<MapPath> m_Paths;
  RMergeList<MapVolume> m_Volumes;
};


