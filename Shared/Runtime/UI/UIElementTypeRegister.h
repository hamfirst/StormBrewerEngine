#pragma once

#include "StormData/StormDataTypeDatabaseRegister.h"
#include "StormRefl/StormReflMetaFuncs.h"

#include "Foundation/CallList/CallList.h"
#include "Foundation/PropertyMeta/PropertyFieldMetaFuncs.h"

#include "Runtime/UI/UIDef.refl.h"
#include "Runtime/UI/UIElementTypeDatabase.h"

template <typename FieldType>
static void UICreateRuntimeDesc(czstr name, std::vector<UIRuntimeFieldDesc> & desc_list)
{

}

template <>
void UICreateRuntimeDesc<float>(czstr name, std::vector<UIRuntimeFieldDesc> & desc_list)
{
  desc_list.push_back(UIRuntimeFieldDesc{ UIVariableType::kFloat, name });
}

template <>
void UICreateRuntimeDesc<std::string>(czstr name, std::vector<UIRuntimeFieldDesc> & desc_list)
{
  desc_list.push_back(UIRuntimeFieldDesc{ UIVariableType::kString, name });
}

template <typename RuntimeDataType>
void UICreateRuntimeInfo(std::vector<UIRuntimeFieldDesc> & desc_list)
{
  auto visitor = [&](auto f)
  {
    using MemberType = typename decltype(f)::member_type;
    UICreateRuntimeDesc<MemberType>(f.GetName(), desc_list);
  };

  StormReflVisitStatic<RuntimeDataType>::VisitEach(visitor);
}

template <typename RuntimeClass, typename InitDataType, typename RuntimeDataType>
void UIElementTypeDatabase::RegisterType()
{
  static_assert(std::is_base_of<UIElementInitDataBase, InitDataType>::value, "Registering type that is not of the right base class");

  UIElementDataTypeInfo type_info;
  StormDataInitTypeInfo<InitDataType>(type_info);

  UICreateRuntimeInfo<RuntimeDataType>(type_info.m_RuntimeDesc);

  auto type_name_hash = StormReflTypeInfo<InitDataType>::GetNameHash();

  type_info.RegisterPropertyFields = [](PropertyFieldDatabase & property_db)
  {
    auto prop = GetProperyMetaData<InitDataType>(property_db);
    property_db.RegisterStructWithAlternateName(StormReflTypeInfo<InitDataType>::GetNameHash(), prop);
    return prop;
  };

  m_TypeList.emplace(std::make_pair(type_name_hash, type_info));
}


extern RUNTIME_EXPORT PreMainCallList g_UIElementRegisterCallList;

#define REGISTER_UIELEMENT_DATA(RuntimeClass, InitDataType, RuntimeDataType) \
  ADD_PREMAIN_CALL(g_UIElementRegisterCallList, RuntimeClass, ([]() { UIElementTypeDatabase::Get().RegisterType<RuntimeClass, InitDataType, RuntimeDataType>(); }));
