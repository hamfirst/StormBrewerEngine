#pragma once

//template <> struct JsonSchemaBuilder<bool, void> { static NotNullPtr<JsonSchema> GetSchema() { static JsonSchema schema{ JsonType::kBool }; return &schema; } };
//template <> struct JsonSchemaBuilder<int8_t, void> { static NotNullPtr<JsonSchema> GetSchema() { static JsonSchema schema{ JsonType::kSignedIntegerNumber }; return &schema; } };
//template <> struct JsonSchemaBuilder<int16_t, void> { static NotNullPtr<JsonSchema> GetSchema() { static JsonSchema schema{ JsonType::kSignedIntegerNumber }; return &schema; } };
//template <> struct JsonSchemaBuilder<int32_t, void> { static NotNullPtr<JsonSchema> GetSchema() { static JsonSchema schema{ JsonType::kSignedIntegerNumber }; return &schema; } };
//template <> struct JsonSchemaBuilder<int64_t, void> { static NotNullPtr<JsonSchema> GetSchema() { static JsonSchema schema{ JsonType::kSignedIntegerNumber }; return &schema; } };
//template <> struct JsonSchemaBuilder<uint8_t, void> { static NotNullPtr<JsonSchema> GetSchema() { static JsonSchema schema{ JsonType::kUnsignedIntegerNumber }; return &schema; } };
//template <> struct JsonSchemaBuilder<uint16_t, void> { static NotNullPtr<JsonSchema> GetSchema() { static JsonSchema schema{ JsonType::kUnsignedIntegerNumber }; return &schema; } };
//template <> struct JsonSchemaBuilder<uint32_t, void> { static NotNullPtr<JsonSchema> GetSchema() { static JsonSchema schema{ JsonType::kUnsignedIntegerNumber }; return &schema; } };
//template <> struct JsonSchemaBuilder<uint64_t, void> { static NotNullPtr<JsonSchema> GetSchema() { static JsonSchema schema{ JsonType::kUnsignedIntegerNumber }; return &schema; } };
//template <> struct JsonSchemaBuilder<float> { static NotNullPtr<JsonSchema> GetSchema() { static JsonSchema schema{ JsonType::kFloatingNumber }; return &schema; } };
//template <> struct JsonSchemaBuilder<double> { static NotNullPtr<JsonSchema> GetSchema() { static JsonSchema schema{ JsonType::kFloatingNumber }; return &schema; } };
//template <> struct JsonSchemaBuilder<std::string> { static NotNullPtr<JsonSchema> GetSchema() { static JsonSchema schema{ JsonType::kString }; return &schema; } };
//
//template <typename T> 
//struct JsonSchemaBuilder<std::vector<T>> 
//{ 
//  static NotNullPtr<JsonSchema> GetSchema()
//  { 
//    static JsonSchema schema{ JsonType::kArray, JsonSchemaBuilder<T>::GetSchema() };
//    return &schema;
//  } 
//};
//
//template <typename T1, typename T2>
//struct JsonSchemaBuilder<std::pair<T1, T2>>
//{
//  static NotNullPtr<JsonSchema> GetSchema()
//  {
//    static JsonSchema schema[3] = {};
//    schema[0] = JsonSchema{ JsonType::kArray, &schema[1], nullptr };
//    schema[1] = *JsonSchemaBuilder<T1>::GetSchema();
//    schema[1].m_NextSchema = &schema[2];
//    schema[2] = *JsonSchemaBuilder<T2>::GetSchema();
//
//    return &schema[0];
//  }
//};
