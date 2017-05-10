#pragma once

#include "StormData/StormDataTypeDatabaseRegister.h"

#include "Foundation/CallList/CallList.h"

#include "Runtime/Path/PathTypeDatabase.h"

template <typename DataType, typename ... BaseTypes>
void PathTypeDatabase::RegisterType()
{
  static_assert(std::is_base_of<Component, RegComponent>::value, "Registering type that is not of the right base class");
  static_assert(std::is_same<Component, RegComponent>::value || sizeof...(BaseTypes) > 0, "Registering type that does not have a base class specified");

  ComponentInitDataTypeInfo type_info;
  InitTypeInfo<DataType>(type_info);

  type_info.m_BaseTypes.emplace_back(std::make_pair(RegComponent::TypeNameHash, [](void * ptr) {return ptr; }));

  type_info.RegisterPropertyFields = [](PropertyFieldDatabase & property_db)
  {
    auto prop = GetProperyMetaData<InitData>(property_db);
    property_db.RegisterStructWithAlternateName(RegComponent::TypeNameHash, prop);
    return prop;
  };

  m_TypeList.emplace(std::make_pair(RegComponent::TypeNameHash, type_info));
}


extern RUNTIME_EXPORT PreMainCallList g_PathtRegisterCallList;

#define REGISTER_PATH_DATA(PathDataType) \
  ADD_PREMAIN_CALL(g_PathtRegisterCallList, PathDataType, []() { PathTypeDatabase::RegisterType<PathDataType, PathDataBase>(); });   

#define REGISTER_DERIVED_PATH_DATA(PathDataType, BaseType) \
  ADD_PREMAIN_CALL(g_PathtRegisterCallList, PathDataType, []() { PathTypeDatabase::RegisterType<PathDataType, BaseType>(); });   
