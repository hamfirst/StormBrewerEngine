#pragma once

#include "StormData/StormDataTypeDatabaseRegister.h"

#include "Foundation/CallList/CallList.h"
#include "Foundation/PropertyMeta/PropertyFieldMetaFuncs.h"

#include "Runtime/Anchor/AnchorTypeDatabase.h"

template <typename DataType, typename ... BaseTypes>
void AnchorTypeDatabase::RegisterType()
{
  static_assert(std::is_base_of<AnchorDataBase, DataType>::value, "Registering type that is not of the right base class");
  static_assert(std::is_same<AnchorDataBase, DataType>::value || sizeof...(BaseTypes) > 0, "Registering type that does not have a base class specified");

  AnchorDataTypeInfo type_info;
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


extern RUNTIME_EXPORT PreMainCallList g_AnchorRegisterCallList;

#define REGISTER_ANCHOR_DATA(AnchorDataType) \
  ADD_PREMAIN_CALL(g_AnchorRegisterCallList, AnchorDataType, ([]() { AnchorTypeDatabase::RegisterType<AnchorDataType, AnchorDataBase>(); }));   

#define REGISTER_DERIVED_ANCHOR_DATA(AnchorDataType, BaseType) \
  ADD_PREMAIN_CALL(g_AnchorRegisterCallList, AnchorDataType, ([]() { AnchorTypeDatabase::RegisterType<AnchorDataType, BaseType>(); }));   
