#pragma once

#include "Foundation\Reflection\Reflection.h"
#include "Foundation\Reflection\TypeDatabase.h"
#include "Foundation\Reflection\ReflectionJson.h"

#define REGISTER_TYPE(ClassName) \
static class s_Reg##ClassName \
{\
  public:\
  s_Reg##ClassName() \
  {\
    g_TypeDatabaseRegistrationCallList.AddCall([]() { RegisterType<ClassName>(#ClassName); });\
  }\
} s_RegInst##ClassName;\



template<class T>
void RegisterType(const char * class_name)
{
  TypeInfo type_info
  {
    std::string(class_name),
    crc32(typeid(T).name()),
    []() -> void * { return new T(); },
    [](const void * ptr, void * json_data) { Json * json = static_cast<Json *>(json_data); *json = EncodeJson(*(static_cast<const T *>(ptr))); },
    [](void * ptr, const void * json_data) { const Json * json = static_cast<const Json *>(json_data); DecodeJson(*(static_cast<T *>(ptr)), *json); },

#ifdef REFLECTION_PARENT
    [](void * ptr, const ReflectionParentInfo & parent_info) { T * t = static_cast<T *>(ptr); t->m_ReflectionInfo = parent_info; },
#else
    [](void * ptr, const ReflectionParentInfo & parent_info) {},
#endif

    []() { return GetFields<T>(); }
  };

  g_TypeDatabase->RegisterType(type_info);
}
