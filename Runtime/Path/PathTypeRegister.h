#pragma once

#include "StormData/StormDataTypeDatabaseRegister.h"

#include "Foundation/CallList/CallList.h"
#include "Foundation/PropertyMeta/PropertyFieldMetaFuncs.h"

#include "Runtime/Path/PathTypeDatabase.h"

template <typename DataType, typename ... BaseTypes>
void PathTypeDatabase::RegisterType()
{
  static_assert(std::is_base_of<PathDataBase, DataType>::value, "Registering type that is not of the right base class");
  static_assert(std::is_same<PathDataBase, DataType>::value || sizeof...(BaseTypes) > 0, "Registering type that does not have a base class specified");

  PathDataTypeInfo type_info;
  InitTypeInfo<DataType>(type_info);

  auto type_name_hash = StormReflTypeInfo<DataType>::GetNameHash();

  type_info.m_BaseTypes.emplace_back(std::make_pair(type_name_hash, [](void * ptr) {return ptr; }));

  type_info.RegisterPropertyFields = [](PropertyFieldDatabase & property_db)
  {
    auto prop = GetProperyMetaData<DataType>(property_db);
    property_db.RegisterStructWithAlternateName(StormReflTypeInfo<DataType>::GetNameHash(), prop);
    return prop;
  };

  m_TypeList.emplace(std::make_pair(type_name_hash, type_info));
}


extern RUNTIME_EXPORT PreMainCallList g_PathRegisterCallList;

#define REGISTER_PATH_DATA(PathDataType) \
  ADD_PREMAIN_CALL(g_PathRegisterCallList, PathDataType, ([]() { PathTypeDatabase::RegisterType<PathDataType, PathDataBase>(); }));   

#define REGISTER_DERIVED_PATH_DATA(PathDataType, BaseType) \
  ADD_PREMAIN_CALL(g_PathRegisterCallList, PathDataType, ([]() { PathTypeDatabase::RegisterType<PathDataType, BaseType>(); }));   
