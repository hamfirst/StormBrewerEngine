#pragma once

#include "Foundation\Reflection\Reflection.h"
#include "Foundation\Reflection\TypeDatabase.h"
#include "Foundation\Reflection\ReflectionJson.h"
#include "Foundation\Reflection\ReflectionParent.h"

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
void RegisterType(czstr class_name)
{
  TypeInfo type_info
  {
    std::string(class_name),
    crc32(typeid(T).name()),
    []() -> void * { return new T(); },
    [](const void * ptr, void * json_data) { Json * json = static_cast<Json *>(json_data); *json = EncodeJson(*(static_cast<const T *>(ptr))); },
    [](void * ptr, const void * json_data) { const Json * json = static_cast<const Json *>(json_data); DecodeJson(*(static_cast<T *>(ptr)), *json); },

#ifdef REFLECTION_CHANGE_NOTIFIER
    [](void * ptr, const ReflectionParentInfo & parent_info) { T * t = static_cast<T *>(ptr); SetParentInfo(*t, parent_info); },
#else
    [](void * ptr, const ReflectionParentInfo & parent_info) {},
#endif

    [](const void * ptr1, const void * ptr2) { const T * t1 = static_cast<const T *>(ptr1); const T * t2 = static_cast<const T *>(ptr2); return *t1 == *t2; },

    [](int index) { return GetFieldName<T>(index); }
  };

  g_TypeDatabase->RegisterType(type_info);
}
