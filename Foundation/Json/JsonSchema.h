#pragma once

#include "Foundation/Common.h"
#include "Foundation/Json/JsonType.h"

#include <StormRefl/StormReflMetaFuncs.h>
#include <StormData/StormDataTypes.h>

struct JsonSchema
{
  JsonType m_Type;
  void * m_ExtData;
  uint32_t m_TypeId;
};

struct JsonChildSchemaList
{
  int m_NumChildren;
  std::vector<JsonSchema *> m_Children;
  std::vector<std::string> m_Names;
  std::unordered_map<Hash, int> m_NameLookup;
};

template <typename T, typename Enable = void>
struct JsonSchemaBuilder
{
  static NotNullPtr<JsonSchema> GetSchema()
  {
    static_assert(StormReflCheckReflectable<T>::value, "Not a reflectable type");
    static JsonChildSchemaList child_list{ StormReflTypeInfo<T>::fields_n };

    static JsonSchema obj_schema{ JsonType::kObject, &child_list, (uint32_t)StormReflTypeInfo<T>::GetNameHash() };

    static bool initialzed = false;
    if (initialzed == false)
    {
      auto visitor = [&](auto f)
      {
        using member_type = typename std::remove_reference_t<decltype(f)>::member_type;
        child_list.m_Children.emplace_back(JsonSchemaBuilder<member_type>::GetSchema());
        child_list.m_Names.emplace_back(f.GetName());
        child_list.m_NameLookup.emplace(std::make_pair(f.GetFieldNameHash(), f.GetFieldIndex()));
      };

      T * t = nullptr;
      StormReflVisitEach(*t, visitor);

      initialzed = true;
    }

    return &obj_schema;
  }
};

template <> 
struct JsonSchemaBuilder<RBool, void> 
{ 
  static NotNullPtr<JsonSchema> GetSchema() 
  { 
    static JsonSchema schema{ JsonType::kBool }; 
    return &schema; 
  } 
};

template <typename T> 
struct JsonSchemaBuilder<RNumber<T>, std::enable_if_t<std::is_integral<T>::value && std::is_signed<T>::value>> 
{ 
  static NotNullPtr<JsonSchema> GetSchema() 
  { 
    static JsonSchema schema{ JsonType::kSignedIntegerNumber }; 
    return &schema; 
  } 
};

template <typename T> 
struct JsonSchemaBuilder<RNumber<T>, std::enable_if_t<std::is_integral<T>::value && std::is_unsigned<T>::value>> 
{ 
  static NotNullPtr<JsonSchema> GetSchema() 
  { 
    static JsonSchema schema{ JsonType::kUnsignedIntegerNumber }; 
    return &schema; 
  } 
};

template <typename T> 
struct JsonSchemaBuilder<RNumber<T>, std::enable_if_t<std::is_floating_point<T>::value>> 
{ 
  static NotNullPtr<JsonSchema> GetSchema() 
  { 
    static JsonSchema schema{ JsonType::kFloatingNumber }; 
    return &schema; 
  } 
};

template <>
struct JsonSchemaBuilder<RString, void>
{
  static NotNullPtr<JsonSchema> GetSchema()
  {
    static JsonSchema schema{ JsonType::kString };
    return &schema;
  }
};

template <typename T>
struct JsonSchemaBuilder<REnum<T>, void>
{
  static NotNullPtr<JsonSchema> GetSchema()
  {
    static JsonSchema schema{ JsonType::kString };
    return &schema;
  }
};

template <typename T>
struct JsonSchemaBuilder<RSparseList<T>, void>
{
  static NotNullPtr<JsonSchema> GetSchema()
  {
    static JsonSchema schema{ JsonType::kHashMap, JsonSchemaBuilder<T>::GetSchema() };
    return &schema;
  }
};

template <typename T>
struct JsonSchemaBuilder<RMergeList<T>, void>
{
  static NotNullPtr<JsonSchema> GetSchema()
  {
    static JsonSchema schema{ JsonType::kHashMap, JsonSchemaBuilder<T>::GetSchema() };
    return &schema;
  }
};

template <typename K, typename T>
struct JsonSchemaBuilder<RMap<K, T>, void>
{
  static NotNullPtr<JsonSchema> GetSchema()
  {
    static JsonSchema schema{ JsonType::kHashMap, JsonSchemaBuilder<T>::GetSchema() };
    return &schema;
  }
};

template <typename T>
JsonSchema * GetJsonSchema()
{
  return JsonSchemaBuilder<T>::GetSchema();
}
