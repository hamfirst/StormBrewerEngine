#pragma once

#include "Foundation/Update/UpdateRegistrationTemplates.h"

#define DECLARE_SERVER_OBJECT                                                                                                   \
  static czstr TypeName;                                                                                                        \
  static uint32_t TypeNameHash;                                                                                                 \
  static std::size_t TypeIndex;                                                                                                 \
  static const uint32_t * BaseTypes;                                                                                            \
  static uint32_t NumBaseTypes;                                                                                                 \
                                                                                                                                \
  virtual uint32_t GetTypeNameHash() const override;                                                                            \
  static void RegisterServerObject();                                                                                           \
                                                                                                                                \
  static bool CanCastToType(uint32_t type_name_hash);                                                                           \
  virtual bool CastToInternal(uint32_t type_name_hash) const override;                                                          \

#define DECLARE_BASE_SERVER_OBJECT                                                                                              \
  static czstr TypeName;                                                                                                        \
  static uint32_t TypeNameHash;                                                                                                 \
  static std::size_t TypeIndex;                                                                                                 \
  static const uint32_t * BaseTypes;                                                                                            \
  static uint32_t NumBaseTypes;                                                                                                 \
                                                                                                                                \
  virtual uint32_t GetTypeNameHash() const;                                                                                     \
  static void RegisterServerObject();                                                                                           \
                                                                                                                                \
  static bool CanCastToType(uint32_t type_name_hash);                                                                           \
  virtual bool CastToInternal(uint32_t type_name_hash) const;                                                                   \


#define REGISTER_SERVER_OBJECT_CODE(ServerObjectName, InitData, InitFunc, BaseClassHash)                                        \
czstr ServerObjectName::TypeName = #ServerObjectName;                                                                           \
uint32_t ServerObjectName::TypeNameHash = COMPILE_TIME_CRC32_STR(#ServerObjectName);                                            \
std::size_t ServerObjectName::TypeIndex = 0;                                                                                    \
const uint32_t * ServerObjectName::BaseTypes = nullptr;                                                                         \
uint32_t ServerObjectName::NumBaseTypes = 0;                                                                                    \
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
  type_info.m_BaseClassTypeNameHash = BaseClassHash;                                                                            \
  type_info.m_InitDataTypeNameHash = COMPILE_TIME_CRC32_STR(#InitData);                                                         \
  type_info.m_BaseListClassesPtr = &ServerObjectName::BaseTypes;                                                                \
  type_info.m_NumBaseClassesPtr = &ServerObjectName::NumBaseTypes;                                                              \
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
    StormReflCopy(*ptr, *static_cast<const ServerObjectName *>(rhs));                                                           \
    return ptr;                                                                                                                 \
  };                                                                                                                            \
                                                                                                                                \
  type_info.m_ObjectInit = [](NotNullPtr<ServerObject> object, NullOptPtr<ServerObjectInitData> init_data)                      \
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
  type_info.m_AddToUpdateList = [](NotNullPtr<ServerObject> object, ServerObjectUpdateList & l)                                 \
  {                                                                                                                             \
    RegisterUpdate(*static_cast<ServerObjectName *>(object), l);                                                                \
  };                                                                                                                            \
                                                                                                                                \
  g_ServerObjectSystem.RegisterType(type_info);                                                                                 \
}                                                                                                                               \
                                                                                                                                \
ADD_PREMAIN_CALL(g_ServerObjectRegisterCallList, ServerObjectName, []() { ServerObjectName::RegisterServerObject(); });         \
                                                                                                                                \
bool ServerObjectName::CanCastToType(uint32_t type_index)                                                                       \
{                                                                                                                               \
  for (uint32_t base_type = 0; base_type < ServerObjectName::NumBaseTypes; ++base_type)                                         \
  {                                                                                                                             \
    if (ServerObjectName::BaseTypes[base_type] == type_index)                                                                   \
    {                                                                                                                           \
      return true;                                                                                                              \
    }                                                                                                                           \
  }                                                                                                                             \
                                                                                                                                \
  return false;                                                                                                                 \
}                                                                                                                               \
                                                                                                                                \
bool ServerObjectName::CastToInternal(uint32_t type_index) const                                                                \
{                                                                                                                               \
  return ServerObjectName::CanCastToType(type_index);                                                                           \
}                                                                                                                               \


#define SERVER_OBJECT_CONSTRUCT_NOBASE          0
#define SERVER_OBJECT_CONSTRUCT_BASE(BaseClass) COMPILE_TIME_CRC32_STR(#BaseClass)

#define SERVER_OBJECT_INIT_DATA(InitData)       obj->Init(*static_cast<InitData *>(init_data));
#define SERVER_OBJECT_NOINIT_DATA   

#define REGISTER_BASE_SERVER_OBJECT(ServerObjectName) \
  REGISTER_SERVER_OBJECT_CODE(ServerObjectName, ServerObjectInitData, SERVER_OBJECT_NOINIT_DATA, SERVER_OBJECT_CONSTRUCT_NOBASE)

#define REGISTER_SERVER_OBJECT(ServerObjectName, BaseClass) \
  REGISTER_SERVER_OBJECT_CODE(ServerObjectName, ServerObjectInitData, SERVER_OBJECT_NOINIT_DATA, SERVER_OBJECT_CONSTRUCT_BASE(BaseClass))

#define REGISTER_SERVER_OBJECT_WITH_INIT_DATA(ServerObjectName, InitData, BaseClass) \
  REGISTER_SERVER_OBJECT_CODE(ServerObjectName, InitData, SERVER_OBJECT_INIT_DATA(InitData), SERVER_OBJECT_CONSTRUCT_BASE(BaseClass))
