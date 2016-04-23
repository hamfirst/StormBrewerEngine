
#pragma once

#include "Foundation\Common.h"
#include "Foundation\Hash\Hash.h"
#include "Foundation\Reflection\Reflection.h"
#include "Foundation\Reflection\ReflectionJson.h"

#define REGISTER_TYPE(ClassName) \
static class s_Reg##ClassName \
{\
  public:\
  s_Reg##ClassName() \
  {\
    static TypeRegisterInfo s_RegInfo\
    {\
      []() { g_TypeDatabase->RegisterType<ClassName>(#ClassName); },\
      g_TypeRegistrationList\
    };\
    g_TypeRegistrationList = &s_RegInfo; \
  }\
} s_RegInst##ClassName;\

struct TypeRegisterInfo
{
  void(*m_RegisterClass)();
  TypeRegisterInfo * m_Next;
};

struct TypeInfo
{
  std::string m_ClassName;

  void * (*m_HeapCreateDefault)();

  Json (*m_EncodeJson)(void *);
  void * (*m_DecodeJson)(const Json & json_data);

  std::vector<std::string> (*m_GetFields)();
};


class TypeDatabase
{
public:
  void FinalizeTypes();

  template<class T>
  void RegisterType(const char * class_name)
  {
    TypeInfo type_info
    {
      std::string(class_name),
      []() -> void * { return new T(); },
      [](void * ptr) -> Json { return EncodeJson(*((T *)ptr)); },
      [](const Json & json_data) -> void * { T * t = new T(); DecodeJson(*t, json_data); return t; },
      []() { return GetFields<T>(); }
    };

    m_Types[crc32(class_name)] = type_info;
  }

private:
  std::unordered_map<uint32_t, TypeInfo> m_Types;
};

extern Singleton<TypeDatabase> g_TypeDatabase;
extern TypeRegisterInfo * g_TypeRegistrationList;
