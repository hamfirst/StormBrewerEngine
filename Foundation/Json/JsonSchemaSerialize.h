#pragma once

#include "Foundation/Common.h"
#include "Foundation/Json/JsonType.h"
#include "Foundation/Json/JsonSchema.h"
#include "Foundation/Json/JsonSchemaSerializeTypes.refl.h"

#include <StormRefl/StormReflMetaFuncs.h>
#include <StormData/StormDataTypes.h>


std::size_t JsonSerializeGetSchemaIndex(NotNullPtr<JsonSchema> schema,
  std::vector<JsonSchemaSerializeInfo> & schema_list,
  std::vector<JsonSchemaSerializeChildList> & child_schemas,
  std::unordered_map<JsonSchema *, std::size_t> & schema_map);

std::size_t JsonSchemaSerializeProcess(NotNullPtr<JsonSchema>, std::vector<JsonSchemaSerializeInfo> & schema_list,
  std::vector<JsonSchemaSerializeChildList> & child_schemas, std::unordered_map<JsonSchema *, std::size_t> & schema_map);

std::string SerializeJsonSchema(NotNullPtr<JsonSchema> schema);

template <typename T>
std::string SerializeJsonSchema()
{
  return SerializeJsonSchema(GetJsonSchema<T>());
}

NotNullPtr<JsonSchema> DeserializeJsonSchema(const std::string & data, std::unique_ptr<JsonSchema[]> & schema_list, std::unique_ptr<JsonChildSchemaList[]> & child_list);