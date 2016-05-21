#pragma once

#include "Foundation\Common.h"
#include "Foundation\Reflection\TypeDatabaseThin.h"

#ifdef REFLECTION_CHANGE_NOTIFIER

template <typename NumericType>
void SetParentInfo(RNumber<NumericType> & value, const ReflectionParentInfo & info)
{
  value.m_ReflectionInfo = info;
}

static void SetParentInfo(RString & value, const ReflectionParentInfo & info)
{
  value.m_ReflectionInfo = info;
}

template <typename T, typename std::enable_if<
  std::is_class<T>::value && T::is_reflectable
>::type * = nullptr>
void SetParentInfo(T & value, const ReflectionParentInfo & info)
{
  value.m_ReflectionInfo = info;

  ReflectionParentInfo new_info;
  new_info.m_ParentInfo = &value.m_ReflectionInfo;
  new_info.m_ParentIndex = 0;
  new_info.m_ParentType = value.GetTypeNameHash();

  MemberParentInfoVisitor parent_setter(new_info);

  VisitEach(value, parent_setter);
}

template <class T>
void SetParentInfo(RPolymorphic<T> & value, const ReflectionParentInfo & info)
{
  value.m_ReflectionInfo = info;

  ReflectionParentInfo new_info;
  new_info.m_ParentInfo = &value.m_ReflectionInfo;
  new_info.m_ParentIndex = 0;
  new_info.m_ParentType = 0xFFFFFFFF;

  SetParentInfo(value.GetValue(), value.GetTypeNameHash(), new_info);
}

template <class EnumType>
void SetParentInfo(REnum<EnumType> & value, const ReflectionParentInfo & info)
{
  value.m_ReflectionInfo = info;
}

template <class T>
void SetParentInfo(RArrayList<T> & value, const ReflectionParentInfo & info)
{
  value.m_ReflectionInfo = info;

  ReflectionParentInfo new_info;
  new_info.m_ParentInfo = &value.m_ReflectionInfo;

  for (T & t : value)
  {
    SetParentInfo(t, new_info);
    new_info.m_ParentIndex++;
  }
}

template <class T>
void SetParentInfo(RSparseList<T> & value, const ReflectionParentInfo & info)
{
  value.m_ReflectionInfo = info;

  ReflectionParentInfo new_info;
  new_info.m_ParentInfo = &value.m_ReflectionInfo;

  for (auto t : value)
  {
    new_info.m_ParentIndex = t.first;
    SetParentInfo(t, new_info);
  }
}

template <class T>
void SetParentInfo(RMergeList<T> & value, const ReflectionParentInfo & info)
{
  value.m_ReflectionInfo = info;

  ReflectionParentInfo new_info;
  new_info.m_ParentInfo = &value.m_ReflectionInfo;

  for (auto t : value)
  {
    new_info.m_ParentIndex = t.first;
    SetParentInfo(value, new_info);
  }
}

template <class T>
void SetParentInfo(RHashMap<T> & value, const ReflectionParentInfo & info)
{
  value.m_ReflectionInfo = info;

  ReflectionParentInfo new_info;
  new_info.m_ParentInfo = &value.m_ReflectionInfo;

  for (auto t : value)
  {
    new_info.m_ParentIndex = t.first;
    SetParentInfo(value, new_info);
  }
}

struct MemberParentInfoVisitor
{
  MemberParentInfoVisitor(ReflectionParentInfo & value)
    : m_Value(value)
  {

  }

  template<typename FieldInfo>
  void operator()(FieldInfo field_info)
  {
    SetParentInfo(field_info.Get(), m_Value);
    m_Value.m_ParentIndex++;
  }

public:
  ReflectionParentInfo m_Value;
};


// For base level structs, this sets the default info
template <typename T, typename std::enable_if<
  std::is_class<T>::value && T::is_reflectable
>::type * = nullptr>
void InitializeParentInfo(T & value)
{
  ReflectionParentInfo default_info;
  SetParentInfo(value, default_info);
}


#endif
