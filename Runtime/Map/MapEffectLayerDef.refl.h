#pragma once

#include "Runtime/RuntimeCommon.h"

#include <StormData/StormData.h>
#include <StormData/StormDataTypes.h>

class MapEffectLayerRenderer;

struct MapEffectLayerLogicInfo
{
  std::unique_ptr<MapEffectLayerRenderer> (*m_CreateCodeObj)(void *);
};

struct MapEffectLayerLogicBase
{
  using TypeInfo = MapEffectLayerLogicInfo;
};

class RUNTIME_EXPORT MapEffectLayerInitData
{
public:
  STORM_DATA_DEFAULT_CONSTRUCTION(MapEffectLayerInitData);
};
