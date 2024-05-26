#pragma once
#include "StormRefl/StormReflMetaFuncs.h"
#include "StormData/StormDataTypeDatabaseRegister.h"

#include "Foundation/Update/UpdateRegistrationTemplates.h"
#include "Foundation/PropertyMeta/PropertyFieldMetaFuncs.h"
#include "Foundation/CallList/CallList.h"

#include "Runtime/ServerObject/ServerObjectTypeInfo.h"
#include "Runtime/ServerObject/ServerObjectInitDataTypeDatabase.h"
#include "Runtime/ServerObject/ServerObjectComponent.h"

template <typename ParentType, typename FieldInfo, typename FieldType>
struct ServerObjectRegisterComponent
{
  static void Process(std::vector<ServerObjectComponentInfo> & comp_info)
  {

  }
};

template <typename ParentType, typename FieldInfo, typename BaseClass, typename BaseConfig>
struct ServerObjectRegisterComponent<ParentType, FieldInfo, ServerObjectComponent<BaseClass, BaseConfig>>
{
  static void Process(std::vector<ServerObjectComponentInfo> & comp_info)
  {
    ServerObjectComponentInfo field_info;
    field_info.m_TypeIdHash = typeid(BaseClass).hash_code();
    field_info.m_TypeNameHash = StormReflTypeInfo<BaseClass>::GetNameHash();
    field_info.m_Get = &FieldInfo::GetFromParent;
    field_info.m_ConstGet = &FieldInfo::GetFromParentConst;
    field_info.m_Cast = static_cast<void * (*)(std::size_t, void *)>(&StormReflTypeInfo<BaseClass>::CastFromTypeIdHash);
    field_info.m_ConstCast = static_cast<const void * (*)(std::size_t, const void *)>(&StormReflTypeInfo<BaseClass>::CastFromTypeIdHash);
    comp_info.push_back(field_info);
  }
};

template <typename Comp>
struct ServerObjectSerializeComponent
{
  static void Serialize(const Comp & comp, ServerObjectNetBitWriter & writer)
  {

  }

  static void Deserialize(Comp & comp, ServerObjectNetBitReader & reader)
  {

  }
};

template <typename BaseClass, typename BaseConfig>
struct ServerObjectSerializeComponent<ServerObjectComponent<BaseClass, BaseConfig>>
{
  static void Serialize(const ServerObjectComponent<BaseClass, BaseConfig> & comp, ServerObjectNetBitWriter & writer)
  {
    comp.Serialize(writer);
  }

  static void Deserialize(ServerObjectComponent<BaseClass, BaseConfig> & comp, ServerObjectNetBitReader & reader)
  {
    comp.Deserialize(reader);
  }
};

template <typename Comp>
void ServerObjectComponentSerialize(const Comp & comp, ServerObjectNetBitWriter & writer)
{
  ServerObjectSerializeComponent<Comp>::Serialize(comp, writer);
}

template <typename Comp>
void ServerObjectComponentDeserialize(Comp & comp, ServerObjectNetBitReader & reader)
{
  ServerObjectSerializeComponent<Comp>::Deserialize(comp, reader);
}

#define DECLARE_SERVER_OBJECT                                                                                                   \
  STORM_REFL;                                                                                                                   \
  STORM_REFL_FUNCS;                                                                                                             \
  static czstr TypeName;                                                                                                        \
  static uint32_t TypeNameHash;                                                                                                 \
  static std::size_t TypeIndex;                                                                                                 \
  static ServerObjectEventDispatch EventDispatch;                                                                               \
                                                                                                                                \
  virtual uint32_t GetTypeNameHash() const override;                                                                            \
  static void RegisterServerObject();                                                                                           \
                                                                                                                                \
  static bool CanCastToType(uint32_t type_name_hash);                                                                           \
  virtual bool CastToInternal(uint32_t type_name_hash) const override;                                                          \
  virtual NotNullPtr<ServerObjectEventDispatch> GetEventDispatch() override;                                                    \


#define DECLARE_BASE_SERVER_OBJECT                                                                                              \
  STORM_REFL;                                                                                                                   \
  STORM_REFL_FUNCS;                                                                                                             \
  static czstr TypeName;                                                                                                        \
  static uint32_t TypeNameHash;                                                                                                 \
  static std::size_t TypeIndex;                                                                                                 \
  static ServerObjectEventDispatch EventDispatch;                                                                               \
                                                                                                                                \
  virtual uint32_t GetTypeNameHash() const;                                                                                     \
  static void RegisterServerObject();                                                                                           \
                                                                                                                                \
  static bool CanCastToType(uint32_t type_name_hash);                                                                           \
  virtual bool CastToInternal(uint32_t type_name_hash) const;                                                                   \
  virtual NotNullPtr<ServerObjectEventDispatch> GetEventDispatch();                                                             \


#define REGISTER_SERVER_OBJECT_CODE(ServerObjectName, InitData, InitFunc, BaseClassHash)                                        \
czstr ServerObjectName::TypeName = #ServerObjectName;                                                                           \
uint32_t ServerObjectName::TypeNameHash = COMPILE_TIME_CRC32_STR(#ServerObjectName);                                            \
std::size_t ServerObjectName::TypeIndex = 0;                                                                                    \
ServerObjectEventDispatch ServerObjectName::EventDispatch;                                                                      \
SkipField<ServerObjectName> s_##ServerObjectName##Allocator;                                                                    \
                                                                                                                                \
uint32_t ServerObjectName::GetTypeNameHash() const                                                                              \
{                                                                                                                               \
  return ServerObjectName::TypeNameHash;                                                                                        \
}                                                                                                                               \
                                                                                                                                \
void ServerObjectName::RegisterServerObject()                                                                                   \
{                                                                                                                               \
  ServerObjectTypeInfo type_info;                                                                                               \
  type_info.m_TypeNameHash = ServerObjectName::TypeNameHash;                                                                    \
  type_info.m_InitDataTypeNameHash = COMPILE_TIME_CRC32_STR(#InitData);                                                         \
  type_info.m_TypeIndexPtr = &ServerObjectName::TypeIndex;                                                                      \
                                                                                                                                \
  type_info.m_ObjectCreate = []() -> ServerObject *                                                                             \
  {                                                                                                                             \
    auto ptr = s_##ServerObjectName##Allocator.Allocate();                                                                      \
    return ptr;                                                                                                                 \
  };                                                                                                                            \
                                                                                                                                \
  type_info.m_ObjectDuplicate = [](NotNullPtr<const ServerObject> rhs) -> ServerObject *                                        \
  {                                                                                                                             \
    auto ptr = s_##ServerObjectName##Allocator.Allocate(*static_cast<const ServerObjectName *>(rhs));                           \
    return ptr;                                                                                                                 \
  };                                                                                                                            \
                                                                                                                                \
  type_info.m_ObjectInit = [](NotNullPtr<ServerObject> object, NullOptPtr<const ServerObjectInitData> init_data,                \
          GameWorld & world)                                                                                                    \
  {                                                                                                                             \
    auto obj = static_cast<ServerObjectName *>(object);                                                                         \
    InitFunc                                                                                                                    \
  };                                                                                                                            \
                                                                                                                                \
  type_info.m_ObjectCopy = [](NotNullPtr<ServerObject> object, NullOptPtr<const ServerObject> rhs)                              \
  {                                                                                                                             \
    StormReflCopy(*static_cast<ServerObjectName *>(object), *static_cast<const ServerObjectName *>(rhs));                       \
  };                                                                                                                            \
                                                                                                                                \
  type_info.m_ObjectResetHandles = [](NotNullPtr<ServerObject> object, const ServerObjectManager & obj_manager)                 \
  {                                                                                                                             \
    ServerObjectResetHandle<ServerObjectName>::Process(*static_cast<ServerObjectName *>(object), obj_manager);                  \
  };                                                                                                                            \
                                                                                                                                \
  type_info.m_ObjectDestroy = [](NotNullPtr<ServerObject> object)                                                               \
  {                                                                                                                             \
    s_##ServerObjectName##Allocator.Release(static_cast<ServerObjectName *>(object));                                           \
  };                                                                                                                            \
                                                                                                                                \
  type_info.m_ObjectSerialize = [](NotNullPtr<ServerObject> object, ServerObjectNetBitWriter & writer)                          \
  {                                                                                                                             \
    SerializeServerObject(*static_cast<ServerObjectName *>(object), writer);                                                    \
  };                                                                                                                            \
                                                                                                                                \
  type_info.m_ObjectDeserialize = [](NotNullPtr<ServerObject> object, ServerObjectNetBitReader & reader)                        \
  {                                                                                                                             \
    DeserializeServerObject(*static_cast<ServerObjectName *>(object), reader);                                                  \
  };                                                                                                                            \
                                                                                                                                \
  type_info.m_ComponentSerialize = [](NotNullPtr<ServerObject> object, ServerObjectNetBitWriter & writer)                       \
  {                                                                                                                             \
    StormReflVisitEach(*static_cast<ServerObjectName *>(object),                                                                \
            [&](auto & field){ ServerObjectComponentSerialize(field.Get(), writer); });                                         \
  };                                                                                                                            \
                                                                                                                                \
  type_info.m_ComponentDeserialize = [](NotNullPtr<ServerObject> object, ServerObjectNetBitReader & reader)                     \
  {                                                                                                                             \
    StormReflVisitEach(*static_cast<ServerObjectName *>(object),                                                                \
            [&](auto & field){ ServerObjectComponentDeserialize(field.Get(), reader); });                                       \
  };                                                                                                                            \
                                                                                                                                \
  type_info.m_AddToUpdateList = [](NotNullPtr<ServerObject> object, ServerObjectUpdateList & l)                                 \
  {                                                                                                                             \
    RegisterUpdate(*static_cast<ServerObjectName *>(object), l);                                                                \
  };                                                                                                                            \
                                                                                                                                \
  StormReflVisitStatic<ServerObjectName>::VisitEach([&](auto field)                                                             \
  {                                                                                                                             \
    using FieldInfoType = decltype(field);                                                                                      \
    using MemberType = typename decltype(field)::member_type;                                                                   \
    ServerObjectRegisterComponent<ServerObjectName, FieldInfoType, MemberType>::Process(type_info.m_ComponentInfo);             \
  });                                                                                                                           \
                                                                                                                                \
  g_ServerObjectSystem.RegisterType(type_info);                                                                                 \
  RegisterServerObjectEvents<ServerObjectName>();                                                                               \
}                                                                                                                               \
                                                                                                                                \
ADD_PREMAIN_CALL(g_ServerObjectRegisterCallList, ServerObjectName, []() { ServerObjectName::RegisterServerObject(); });         \
                                                                                                                                \
bool ServerObjectName::CanCastToType(uint32_t type_name_hash)                                                                   \
{                                                                                                                               \
  char crap;                                                                                                                    \
  return StormReflTypeInfo<ServerObjectName>::CastFromTypeNameHash(type_name_hash, &crap) != nullptr;                           \
}                                                                                                                               \
                                                                                                                                \
bool ServerObjectName::CastToInternal(uint32_t type_name_hash) const                                                            \
{                                                                                                                               \
  return ServerObjectName::CanCastToType(type_name_hash);                                                                       \
}                                                                                                                               \
                                                                                                                                \
NotNullPtr<ServerObjectEventDispatch> ServerObjectName::GetEventDispatch()                                                      \
{                                                                                                                               \
  return &EventDispatch;                                                                                                        \
}                                                                                                                               \

#define SERVER_OBJECT_CONSTRUCT_NOBASE          0
#define SERVER_OBJECT_CONSTRUCT_BASE(BaseClass) COMPILE_TIME_CRC32_STR(#BaseClass)

#define SERVER_OBJECT_INIT_DATA(InitData)       obj->Init(*static_cast<const InitData *>(init_data), world);
#define SERVER_OBJECT_NOINIT_DATA   

#define REGISTER_BASE_SERVER_OBJECT(ServerObjectName) \
  REGISTER_SERVER_OBJECT_CODE(ServerObjectName, ServerObjectInitData, SERVER_OBJECT_NOINIT_DATA, SERVER_OBJECT_CONSTRUCT_NOBASE)

#define REGISTER_SERVER_OBJECT(ServerObjectName, BaseClass) \
  REGISTER_SERVER_OBJECT_CODE(ServerObjectName, ServerObjectInitData, SERVER_OBJECT_NOINIT_DATA, SERVER_OBJECT_CONSTRUCT_BASE(BaseClass))

#define REGISTER_SERVER_OBJECT_WITH_INIT_DATA(ServerObjectName, InitData, BaseClass) \
  REGISTER_SERVER_OBJECT_CODE(ServerObjectName, InitData, SERVER_OBJECT_INIT_DATA(InitData), SERVER_OBJECT_CONSTRUCT_BASE(BaseClass)) \
  REGISTER_TYPE(InitData, ServerObjectInitData)

#define SERVER_OBJECT_EVENT_HANDLER STORM_REFL_FUNC
