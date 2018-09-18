#pragma once

#include <StormData/StormDataTypeDatabase.h>

#include "Runtime/Map/MapEffectLayerDef.refl.h"

class MapEffectLayerInitData;
class MapEffectLayerRenderer;

struct PropertyField;
class PropertyFieldDatabase;

struct MapEffectLayerDataTypeInfo : public StormDataTypeInfo
{
  PropertyField * (*RegisterPropertyFields)(PropertyFieldDatabase & property_db);
  std::unique_ptr<MapEffectLayerRenderer> (*m_CreateCodeObj)(const void * init_data);
};

extern template
std::unordered_map<uint32_t, MapEffectLayerDataTypeInfo> StormDataTypeDatabase<MapEffectLayerInitData, MapEffectLayerDataTypeInfo>::m_TypeList;
extern template class StormDataTypeDatabase<MapEffectLayerInitData, MapEffectLayerDataTypeInfo>;

class MapEffectLayerTypeDatabase : public StormDataTypeDatabase<MapEffectLayerInitData, MapEffectLayerDataTypeInfo>
{
public:
  template <typename CodeType, typename DataType, typename ... BaseTypes>
  static void RegisterType();
};

