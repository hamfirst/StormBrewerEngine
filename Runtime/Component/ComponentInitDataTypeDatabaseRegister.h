#pragma once

#include "StormData/StormDataTypeDatabase.h"
#include "StormData/StormDataTypeDatabaseRegister.h"

#include "Foundation/PropertyMeta/PropertyFieldDatabase.h"
#include "Foundation/PropertyMeta/PropertyFieldMetaData.h"
#include "Foundation/PropertyMeta/PropertyFieldMetaFuncs.h"

#include "Runtime/Component/ComponentInitDataTypeDatabase.h"

#include "Runtime/Component/ComponentInitData.refl.h"

class Component;

template <typename TypeInfo, typename Class, typename ... BaseTypes>
struct ComponentInitBaseClass
{
  static void Process(TypeInfo & type_info)
  {

  }
};

template <typename TypeInfo, typename Class, typename BaseType, typename ... BaseTypes>
struct ComponentInitBaseClass<TypeInfo, Class, BaseType, BaseTypes...>
{
  static void Process(TypeInfo & type_info)
  {
    static_assert(std::is_base_of<BaseType, Class>::value, "Registering type that is not of the right base class");
    type_info.m_BaseTypes.emplace_back(std::make_pair(BaseType::TypeNameHash, [](void * c) -> void * { auto ptr = (Class *)c; return (BaseType *)ptr; }));

    ComponentInitBaseClass<TypeInfo, Class, BaseTypes...>::Process(type_info);
  }
};

template <typename RegComponent, typename InitData, typename ... BaseTypes>
void ComponentInitDataTypeDatabase::RegisterType()
{
  static_assert(std::is_base_of<Component, RegComponent>::value, "Registering type that is not of the right base class");
  static_assert(std::is_same<Component, RegComponent>::value || sizeof...(BaseTypes) > 0, "Registering type that does not have a base class specified");

  ComponentInitDataTypeInfo type_info;
  InitTypeInfo<InitData>(type_info);

  type_info.m_Name = RegComponent::TypeName;
  type_info.m_BaseTypes.emplace_back(std::make_pair(RegComponent::TypeNameHash, [](void * ptr) {return ptr; }));

  type_info.RegisterPropertyFields = [](PropertyFieldDatabase & property_db) 
  { 
    auto prop = GetProperyMetaData<InitData>(property_db); 
    property_db.RegisterStructWithAlternateName(RegComponent::TypeNameHash, prop);
    return prop;
  };

  ComponentInitBaseClass<ComponentInitDataTypeInfo, RegComponent, BaseTypes...>::Process(type_info);

  m_TypeList.emplace(std::make_pair(RegComponent::TypeNameHash, type_info));
}
