#pragma once

#include "Foundation/Common.h"
#include "Foundation/CallList/CallList.h"
#include "Foundation/PropertyMeta/PropertyFieldMetaFuncs.h"

#include "StormData/StormDataTypeDatabase.h"
#include "StormData/StormDataTypeDatabaseRegister.h"
#include "StormData/StormDataPolymorphic.h"

struct PropertyField;
class PropertyFieldDatabase;

template <typename BaseType, typename LogicBaseType = void>
struct TypeDatabaseTypeInfo : public StormDataTypeInfo
{
  using LogicTypeInfo = typename LogicBaseType::TypeInfo;

  PropertyField * (*RegisterPropertyFields)(PropertyFieldDatabase & property_db);
  LogicTypeInfo m_LogicTypeInfo;
};

template <typename BaseType>
struct TypeDatabaseTypeInfo<BaseType, void> : public StormDataTypeInfo
{
  PropertyField * (*RegisterPropertyFields)(PropertyFieldDatabase & property_db);
};

template <typename DataType, typename LogicBaseType, typename LogicTypeInfo>
struct TypeDatabaseInitLogicInfo
{
  static void Process(LogicTypeInfo & logic_type_info)
  {
    ASSERT(false, "Init logic info not implemented for this logic base type");
  }
};

template <typename DataType, typename BaseType, typename LogicBaseType>
void TypeDatabaseInitDataInfo(TypeDatabaseTypeInfo<BaseType, LogicBaseType> & type_info)
{
  type_info.m_BaseTypes.emplace_back(std::make_pair(type_info.m_TypeNameHash, [](void * ptr) {return ptr; }));

  if constexpr (std::is_same_v<BaseType, DataType> == false)
  {
    using DataTypeBase = typename StormReflTypeInfo<DataType>::MyBase;
    type_info.m_BaseTypes.emplace_back(std::make_pair(StormReflTypeInfo<DataTypeBase>::GetNameHash(),
            [](void * c) -> void * { auto ptr = (DataType *)c; return (DataTypeBase *)ptr; }));
  }

  type_info.RegisterPropertyFields = [](PropertyFieldDatabase & property_db)
  {
    auto prop = GetProperyMetaData<DataType>(property_db);
    property_db.RegisterStructWithAlternateName(StormReflTypeInfo<DataType>::GetNameHash(), prop);
    return prop;
  };
}

template <typename BaseType, typename LogicBaseType = void>
class TypeDatabase : public StormDataTypeDatabase<BaseType, TypeDatabaseTypeInfo<BaseType, LogicBaseType>>,
        public StormDataTypeDatabaseSingleton<TypeDatabase<BaseType, LogicBaseType>>
{
public:
  using TypeInfo = TypeDatabaseTypeInfo<BaseType, LogicBaseType>;

  template <typename DataType, typename LogicType>
  void RegisterType()
  {
    static_assert(std::is_base_of<BaseType, DataType>::value, "Registering type that is not of the right base class");
    static_assert(std::is_base_of<LogicBaseType, LogicType>::value, "Registering type that is not of the right base class");

    using LogicTypeInfo = typename TypeDatabaseTypeInfo<BaseType, LogicBaseType>::LogicTypeInfo;

    TypeDatabaseTypeInfo<BaseType, LogicBaseType> type_info;
    StormDataInitTypeInfo<DataType>(type_info);
    TypeDatabaseInitDataInfo<DataType>(type_info);
    TypeDatabaseInitLogicInfo<DataType, LogicType, LogicTypeInfo>::Process(type_info.m_LogicTypeInfo);

    this->m_TypeList.emplace(std::make_pair(type_info.m_TypeNameHash, type_info));
  }
};

template <typename BaseType>
class TypeDatabase<BaseType, void> :
        public StormDataTypeDatabase<BaseType, TypeDatabaseTypeInfo<BaseType, void>>,
        public StormDataTypeDatabaseSingleton<TypeDatabase<BaseType, void>>
{
public:
  using TypeInfo = TypeDatabaseTypeInfo<BaseType, void>;

  template <typename DataType>
  void RegisterType()
  {
    static_assert(std::is_base_of<BaseType, DataType>::value, "Registering type that is not of the right base class");

    TypeDatabaseTypeInfo<BaseType, void> type_info;
    StormDataInitTypeInfo<DataType>(type_info);
    TypeDatabaseInitDataInfo<DataType>(type_info);

    this->m_TypeList.emplace(std::make_pair(type_info.m_TypeNameHash, type_info));
  }
};

template <typename BaseType, typename LogicBaseType = void, bool DefaultFirstNonBase = false>
using RPolymorphic = RPolymorphicBase<BaseType, TypeDatabase<BaseType, LogicBaseType>, TypeDatabaseTypeInfo<BaseType, LogicBaseType>, DefaultFirstNonBase>;

extern PreMainCallList g_TypeDatabaseRegisterCallList;

#define REGISTER_TYPE(Type, Base)  ADD_PREMAIN_CALL(g_TypeDatabaseRegisterCallList, Type##Base, \
  [] { TypeDatabase<Base>::Get().RegisterType<Type>(); })

#define REGISTER_LOGIC_TYPE(Type, Base, Logic, LogicBase)  ADD_PREMAIN_CALL(g_TypeDatabaseRegisterCallList, Type##Base, \
  [] { TypeDatabase<Base, LogicBase>::Get().RegisterType<Type, Logic>(); })

