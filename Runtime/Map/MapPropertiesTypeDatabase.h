#pragma once

#include <StormData/StormDataTypeDatabase.h>

#include "Runtime/Map/MapPropertiesDef.refl.h"

class MapPropertiesInitData;
class MapPropertiesRenderer;

struct PropertyField;
class PropertyFieldDatabase;

struct MapPropertiesDataTypeInfo : public StormDataTypeInfo
{
  PropertyField * (*RegisterPropertyFields)(PropertyFieldDatabase & property_db);
  std::unique_ptr<MapPropertiesRenderer> (*m_CreateCodeObj)(const void * init_data);
};

extern template
std::unordered_map<uint32_t, MapPropertiesDataTypeInfo> StormDataTypeDatabase<MapPropertiesInitData, MapPropertiesDataTypeInfo>::m_TypeList;
extern template class StormDataTypeDatabase<MapPropertiesInitData, MapPropertiesDataTypeInfo>;

class MapPropertiesTypeDatabase : public StormDataTypeDatabase<MapPropertiesInitData, MapPropertiesDataTypeInfo>
{
public:
  template <typename CodeType, typename DataType, typename ... BaseTypes>
  static void RegisterType();
};

