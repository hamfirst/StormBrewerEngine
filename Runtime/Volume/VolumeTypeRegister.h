#pragma once

#include "StormData/StormDataTypeDatabaseRegister.h"

#include "Foundation/CallList/CallList.h"
#include "Foundation/PropertyMeta/PropertyFieldMetaFuncs.h"

#include "Runtime/Volume/VolumeTypeDatabase.h"

template <typename DataType, typename ... BaseTypes>
void VolumeTypeDatabase::RegisterType()
{
  static_assert(std::is_base_of<VolumeDataBase, DataType>::value, "Registering type that is not of the right base class");
  static_assert(std::is_same<VolumeDataBase, DataType>::value || sizeof...(BaseTypes) > 0, "Registering type that does not have a base class specified");

  VolumeDataTypeInfo type_info;
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


extern RUNTIME_EXPORT PreMainCallList g_VolumeRegisterCallList;

#define REGISTER_VOLUME_DATA(VolumeDataType) \
  ADD_PREMAIN_CALL(g_VolumeRegisterCallList, VolumeDataType, ([]() { VolumeTypeDatabase::RegisterType<VolumeDataType, VolumeDataBase>(); }));   

#define REGISTER_DERIVED_VOLUME_DATA(VolumeDataType, BaseType) \
  ADD_PREMAIN_CALL(g_VolumeRegisterCallList, VolumeDataType, ([]() { VolumeTypeDatabase::RegisterType<VolumeDataType, BaseType>(); }));   
