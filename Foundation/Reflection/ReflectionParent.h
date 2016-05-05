#pragma once

#include "Foundation\Common.h"

#ifdef REFLECTION_PARENT

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
  value.m_ReflectionParentInfo = info;

  ReflectionParentInfo new_info;
  new_info.m_Parent = &value;
  new_info.m_ParentArrayIndex = 0;
  new_info.m_ParentFieldIndex = 0;
  new_info.m_ParentType = crc32(typeid(T).name());

  MemberParenInfoVisitor parent_setter(new_info);

  VisitEach(value, parent_setter);
}

template <typename T, typename std::enable_if<
  std::is_class<T>::value && T::is_reflectable
>::type * = nullptr>
void SetParentInfo(T & value)
{
  ReflectionParentInfo default_info;
  default_info.m_Parent = &value;
  default_info.m_ParentArrayIndex = 0;
  default_info.m_ParentFieldIndex = 0;
  default_info.m_ParentType = 0;

  SetParentInfo(value, default_info);
}

template <class EnumType>
void SetParentInfo(const REnum<EnumType> & value, ReflectionParentInfo info)
{
  return value.m_ReflectionInfo = info;
}

template <class T>
void SetParentInfo(const RArrayList<T> & value, ReflectionParentInfo info)
{
  for (auto t : value)
  {
    SetParentInfo(value, info);
    info.m_ParentArrayIndex++;
  }
}

template <class T>
void SetParentInfo(const RSparseList<T> & value, ReflectionParentInfo info)
{
  for (auto t : value)
  {
    info.m_ParentArrayIndex = t.first;
    SetParentInfo(value, info);
  }
}

template <class T>
void SetParentInfo(const RMergeList<T> & value, ReflectionParentInfo info)
{
  for (auto t : value)
  {
    info.m_ParentArrayIndex = t.first;
    SetParentInfo(value, info);
  }
}

template <class T>
void SetParentInfo(const RHashMap<T> & value, ReflectionParentInfo info)
{
  for (auto t : value)
  {
    info.m_ParentArrayIndex = t.first;
    SetParentInfo(value, info);
  }
}

struct MemberParentInfoVisitor
{
  MemberParentInfoVisitor(ReflectionParentInfo & value)
    : m_Value(value)
  {

  }

  template <class T, int FieldIndex>
  void operator()(T::field_data<FieldIndex, T> field_info)
  {
    m_Value.m_ParentFieldIndex = FieldIndex;
    SetParentInfo(field_info.Get(), m_Value);
  }

public:
  ReflectionParentInfo m_Value;
};

#endif
