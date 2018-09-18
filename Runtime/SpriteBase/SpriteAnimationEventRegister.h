#pragma once

#include "StormData/StormDataTypeDatabaseRegister.h"

#include "Foundation/CallList/CallList.h"
#include "Foundation/PropertyMeta/PropertyFieldMetaFuncs.h"

#include "Runtime/SpriteBase/SpriteAnimationEventTypeDatabase.h"

template <typename DataType, typename ... BaseTypes>
void SpriteAnimationEventTypeDatabase::RegisterType()
{
  static_assert(std::is_base_of<SpriteAnimationEventDataBase, DataType>::value, "Registering type that is not of the right base class");
  static_assert(std::is_same<SpriteAnimationEventDataBase, DataType>::value || sizeof...(BaseTypes) > 0, "Registering type that does not have a base class specified");

  SpriteAnimationEventDataTypeInfo type_info;
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


extern RUNTIME_EXPORT PreMainCallList g_SpriteAnimationEventRegisterCallList;

#define REGISTER_SPRITE_ANIM_EVENT_DATA(SpriteAnimationEventDataType) \
  ADD_PREMAIN_CALL(g_SpriteAnimationEventRegisterCallList, SpriteAnimationEventDataType, ([]() { SpriteAnimationEventTypeDatabase::RegisterType<SpriteAnimationEventDataType, SpriteAnimationEventDataBase>(); }));   

#define REGISTER_DERIVED_SPRITE_ANIM_EVENT_DATA(SpriteAnimationEventDataType, BaseType) \
  ADD_PREMAIN_CALL(g_SpriteAnimationEventRegisterCallList, SpriteAnimationEventDataType, ([]() { SpriteAnimationEventTypeDatabase::RegisterType<SpriteAnimationEventDataType, BaseType>(); }));   
