
#pragma once

#include "Foundation\Common.h"
#include "Foundation\Hash\Hash.h"
#include "Foundation\Reflection\Reflection.h"

#include "Foundation\CallList\CallList.h"

struct ReflectionParentInfo;

struct TypeInfo
{
  std::string m_ClassName;
  uint32_t m_TypeNameHash;

  void * (*m_HeapCreateDefault)();

  void (*m_EncodeJson)(const void * ptr, void * json_data);
  void (*m_DecodeJson)(void * ptr, const void * json_data);

  void (*m_SetParentInfo)(void * ptr, const ReflectionParentInfo & parent_info);
  bool (*m_Compare)(const void * ptr1, const void * ptr2);

  const char * (*m_GetFieldName)(int index);
};


class TypeDatabase
{
public:
  void Init();

  void RegisterType(const TypeInfo & type_info);
  Optional<TypeInfo> GetTypeInfo(uint32_t type_name_hash);

private:
  std::unordered_map<uint32_t, TypeInfo> m_Types;
};

extern Singleton<TypeDatabase> g_TypeDatabase;
extern PreMainCallList g_TypeDatabaseRegistrationCallList;
