#pragma once

#include <StormRefl/StormRefl.h>
#include <StormData/StormDataTypes.h>

#include "Foundation/BasicTypes/BasicTypes.refl.h"

#include "Runtime/RuntimeCommon.h"
#include "Runtime/Entity/EntityDef.refl.h"
#include "Runtime/Path/PathDef.refl.h"
#include "Runtime/Path/PathTypeDatabase.h"
#include "Runtime/Volume/VolumeDef.refl.h"
#include "Runtime/Volume/VolumeTypeDatabase.h"
#include "Runtime/Map/MapTile.h"



struct RUNTIME_EXPORT MapManualTileLayer
{
  STORM_DATA_DEFAULT_CONSTRUCTION(MapManualTileLayer);

  RString STORM_REFL_ATTR_VAL(file, tilesheet) m_TileSheet;
  RString m_Name;
  RInt m_LayerOrder;
  RBool m_CollisionLayer = true;

  RSparseList<ROpaque<MapTile>> STORM_REFL_ATTR(noui) m_Tiles;
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

struct RUNTIME_EXPORT MapParalaxLayer
{
  STORM_DATA_DEFAULT_CONSTRUCTION(MapParalaxLayer);

  RString m_Name;
  RInt m_LayerOrder;

  RString STORM_REFL_ATTR_VAL(file, image) m_Image;
  RBool m_RepeatX = true;
  RBool m_RepeatY = true;

  RFloat m_ParalaxX;
  RFloat m_ParalaxY;
};

struct RUNTIME_EXPORT MapPathPoint
{
  STORM_DATA_DEFAULT_CONSTRUCTION(MapPathPoint);

  RInt m_X;
  RInt m_Y;
};

struct RUNTIME_EXPORT MapPath
{
  STORM_DATA_DEFAULT_CONSTRUCTION(MapPath);
  RString m_Name;
  RPolymorphic<PathDataBase, PathTypeDatabase, PathDataTypeInfo> m_PathData;
  RMergeList<MapPathPoint> m_Points;
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
};

struct RUNTIME_EXPORT MapDef
{
  STORM_DATA_DEFAULT_CONSTRUCTION(MapDef);

  RMergeList<MapManualTileLayer> m_ManualTileLayers;
  RMergeList<MapEntityLayer> m_EntityLayers;
  RMergeList<MapParalaxLayer> m_ParalaxLayers;
  RMergeList<MapPath> m_Paths;
  RMergeList<MapVolume> m_Volumes;
};


