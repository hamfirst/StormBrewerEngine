#pragma once

#include "StormData/StormDataTypeDatabaseRegister.h"

#include "Foundation/CallList/CallList.h"

#include "Runtime/Map/MapEffectLayerTypeDatabase.h"

template <typename CodeType, typename DataType, typename ... BaseTypes>
void MapEffectLayerTypeDatabase::RegisterType()
{
  static_assert(std::is_base_of<MapEffectLayerInitData, DataType>::value, "Registering type that is not of the right base class");
  static_assert(std::is_same<MapEffectLayerInitData, DataType>::value || sizeof...(BaseTypes) > 0, "Registering type that does not have a base class specified");

  MapEffectLayerDataTypeInfo type_info;
  InitTypeInfo<DataType>(type_info);

  auto type_name_hash = StormReflTypeInfo<DataType>::GetNameHash();

  type_info.m_BaseTypes.emplace_back(std::make_pair(type_name_hash, [](void * ptr) {return ptr; }));
  type_info.m_CreateCodeObj = [](const void * init_data) -> std::unique_ptr<MapEffectLayerRenderer> { return std::make_unique<CodeType>(*(const DataType *)init_data); };

  type_info.RegisterPropertyFields = [](PropertyFieldDatabase & property_db)
  {
    auto prop = GetProperyMetaData<DataType>(property_db);
    property_db.RegisterStructWithAlternateName(StormReflTypeInfo<DataType>::GetNameHash(), prop);
    return prop;
  };

  m_TypeList.emplace(std::make_pair(type_name_hash, type_info));
}


extern RUNTIME_EXPORT PreMainCallList g_MapEffectLayerRegisterCallList;

#define REGISTER_EFFECT_LAYER_DATA(MapEffectRendererType, MapEffectLayerDataType) \
  ADD_PREMAIN_CALL(g_MapEffectLayerRegisterCallList, MapEffectLayerDataType, ([]() { MapEffectLayerTypeDatabase::RegisterType<MapEffectRendererType, MapEffectLayerDataType, MapEffectLayerInitData>(); }));   

#define REGISTER_DERIVED_EFFECT_LAYER_DATA(MapEffectRendererType, MapEffectLayerDataType, BaseType) \
  ADD_PREMAIN_CALL(g_MapEffectLayerRegisterCallList, MapEffectLayerDataType, ([]() { MapEffectLayerTypeDatabase::RegisterType<MapEffectRendererType, MapEffectLayerDataType, BaseType>(); }));   
