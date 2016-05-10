#pragma once

#include "Foundation\Common.h"
#include "Foundation\Json\Json.h"
#include "Foundation\Reflection\ReflectionCommon.h"
#include "Foundation\Reflection\TypeDatabase.h"


template <typename NumericType>
void DecodeJson(RNumber<NumericType> & value, const Json & j)
{
  value = j.get<NumericType>();
}

static void DecodeJson(RBool & value, const Json & j)
{
  value = j.get<bool>();
}

static void DecodeJson(RString & value, const Json & j)
{
  value = j.get<std::string>();
}

template <typename T, typename std::enable_if<
  std::is_class<T>::value && T::is_reflectable
>::type * = nullptr>
void DecodeJson(T & value, const Json & j)
{
  MemberJsonDecoderVisitor decoder(j);
  VisitEach(value, decoder);
}

template <class EnumType>
void DecodeJson(REnum<EnumType> & value, const Json & j)
{
  value = EnumType::_from_string(j.get<std::string>().data());
}

template <typename T>
void DecodeJson(RPolymorphic<T> & value, const Json & j)
{
  uint32_t type_name_hash = j["TypeNameHash"].get<uint32_t>();
  const Json & sub_obj_val = j["Obj"];

  Optional<TypeInfo> type_info = g_TypeDatabase->GetTypeInfo(type_name_hash);
  if (type_info)
  {
    value.SetType(type_name_hash);
    type_info->m_DecodeJson(value.GetValue());
  }
}

template <typename T>
void DecodeJson(RArrayList<T> & value, const Json & j)
{
  value.Clear();
  value.Reserve(j.size());
  for (auto t : j)
  {
    T new_val;
    DecodeJson(new_val, t);

    value.PushBack(new_val);
  }
}

template <class T>
void DecodeJson(RSparseList<T> & value, const Json & j)
{
  value.Clear();
  value.Reserve(j.size());
  for (auto t : j)
  {
    T new_val;
    DecodeJson(new_val, t);

    value.PushBack(new_val);
  }
}

template <class T>
void DecodeJson(RMergeList<T> & value, const Json & j)
{
  value.Clear();
  value.Reserve(j.size());
  for (Json::iterator it = j.begin(); it != j.end(); ++it)
  {
    T new_val;
    DecodeJson(new_val, it.value());

    int index = std::stoi(it.key());
    value.InsertAt(new_val, index);
  }
}

template <class T>
void DecodeJson(RHashMap<T> & value, const Json & j)
{
  value.Clear();
  value.Reserve(j.size());
  for (auto it : j)
  {
    T new_val;
    DecodeJson(new_val, it);

    RHash key = it.get<RHash>();
    value.Set(key, std::move(new_val));
  }
}

struct MemberJsonDecoderVisitor
{
  MemberJsonDecoderVisitor(const Json & value)
    : m_Value(value)
  {

  }

  template <class FieldData>
  void operator()(FieldData f)
  {
    DecodeJson(f.Get(), m_Value[f.GetName()]);
  }

public:
  const Json & m_Value;
};

template <typename NumericType>
Json EncodeJson(const RNumber<NumericType> & value)
{
  return (NumericType)value;
}

static Json EncodeJson(const RBool & value)
{
  return (bool)value;
}

static Json EncodeJson(const RString & value)
{
  return value.data();
}

template <typename T, typename std::enable_if<
  std::is_class<T>::value && T::is_reflectable
>::type * = nullptr>
Json EncodeJson(const T & value)
{
  Json j_value;
  MemberJsonEncoderVisitor encoder(j_value);

  VisitEach(value, encoder);
  return j_value;
}

template <class EnumType>
Json EncodeJson(const REnum<EnumType> & value)
{
  return value._to_string();
}

template <class T>
Json EncodeJson(const RPolymorphic<T> & value)
{
  Json j_value;
  Optional<TypeInfo> type_info = g_TypeDatabase->GetTypeInfo(value.GetTypeNameHash());
  if (!type_info)
  {
    return j_value;
  }

  j_value["TypeNameHash"] = value.GetTypeNameHash();
  j_value["Obj"] = type_info.m_EncodeJson(value.GetValue());
  return j_value;
}

template <class T>
Json EncodeJson(const RArrayList<T> & value)
{
  Json j_value;
  for (auto t : value)
  {
    j_value.push_back(EncodeJson(t));
  }

  return j_value;
}

template <class T>
Json EncodeJson(const RSparseList<T> & value)
{
  Json j_value;
  for (auto t : value)
  {
    j_value.push_back(EncodeJson(t.second));
  }

  return j_value;
}

template <class T>
Json EncodeJson(const RMergeList<T> & value)
{
  Json j_value;
  for (auto t : value)
  {
    j_value[std::to_string(t.first)] = EncodeJson(t.second);
  }

  return j_value;
}

template <class T>
Json EncodeJson(const RHashMap<T> & value)
{
  Json j_value;
  for (auto t : value)
  {
    j_value[t.first] = EncodeJson(t.second);
  }

  return j_value;
}

struct MemberJsonEncoderVisitor
{
  MemberJsonEncoderVisitor(Json & value)
    : m_Value(value)
  {
  
  }

  template <class FieldData>
  void operator()(FieldData f)
  {
    m_Value[f.GetName()] = EncodeJson(f.Get());
  }

public:
  Json & m_Value;
};

