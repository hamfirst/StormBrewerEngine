
#include "Foundation/Common.h"
#include "Foundation/Json/JsonSchemaSerialize.h"
#include "Foundation/Json/JsonSchemaSerializeTypes.refl.meta.h"

#include <StormRefl/StormReflJsonStd.h>


std::size_t JsonSerializeGetSchemaIndex(NotNullPtr<JsonSchema> schema,
  std::vector<JsonSchemaSerializeInfo> & schema_list,
  std::vector<JsonSchemaSerializeChildList> & child_schemas,
  std::unordered_map<JsonSchema *, std::size_t> & schema_map)
{
  auto itr = schema_map.find(schema);
  if (itr != schema_map.end())
  {
    return itr->second;
  }

  return JsonSchemaSerializeProcess(schema, schema_list, child_schemas, schema_map);
}

std::size_t JsonSchemaSerializeProcess(NotNullPtr<JsonSchema> schema, std::vector<JsonSchemaSerializeInfo> & schema_list,
  std::vector<JsonSchemaSerializeChildList> & child_schemas, std::unordered_map<JsonSchema *, std::size_t> & schema_map)
{
  if (schema->m_Type == JsonType::kObject)
  {
    JsonSchemaSerializeChildList child_info;
    JsonChildSchemaList * child_list = (JsonChildSchemaList *)schema->m_ExtData;

    for (int index = 0; index < child_list->m_NumChildren; index++)
    {
      auto sub_schema_index = JsonSerializeGetSchemaIndex(child_list->m_Children[index], schema_list, child_schemas, schema_map);
      child_info.m_ChildSchemas.emplace_back(std::make_pair(child_list->m_Names[index], sub_schema_index));
    }

    auto child_list_index = child_schemas.size();
    child_schemas.emplace_back(std::move(child_info));

    JsonSchemaSerializeInfo info{ (int)JsonType::kObject, child_list_index, schema->m_TypeId };
    auto schema_index = schema_list.size();

    schema_list.emplace_back(info);
    return schema_index;
  }
  else if (schema->m_Type == JsonType::kHashMap)
  {
    JsonSchemaSerializeInfo info;
    info.m_Type = (int)schema->m_Type;
    info.m_SubSchemaIndex = JsonSerializeGetSchemaIndex((JsonSchema *)schema->m_ExtData, schema_list, child_schemas, schema_map);
    info.m_TypeId = 0;

    auto schema_index = schema_list.size();
    schema_list.emplace_back(info);
    return schema_index;
  }
  else
  {
    JsonSchemaSerializeInfo info;
    info.m_Type = (int)schema->m_Type;
    info.m_SubSchemaIndex = 0;
    info.m_TypeId = 0;

    auto schema_index = schema_list.size();
    schema_list.emplace_back(info);
    return schema_index;
  }
}

std::string SerializeJsonSchema(NotNullPtr<JsonSchema> schema)
{
  JsonSchemaSerializeMessage message;
  std::unordered_map<JsonSchema *, std::size_t> schema_map;
  message.m_PrimarySchema = JsonSerializeGetSchemaIndex(schema, message.m_Schemas, message.m_ChildSchemas, schema_map);

  return StormReflEncodeJson(message);
}

NotNullPtr<JsonSchema> DeserializeJsonSchema(const std::string & data, std::unique_ptr<JsonSchema[]> & schema_list, std::unique_ptr<JsonChildSchemaList[]> & child_list)
{
  JsonSchemaSerializeMessage message;
  if (StormReflParseJson(message, data.data()) == false)
  {
    throw false;
  }

  schema_list = std::make_unique<JsonSchema[]>(message.m_Schemas.size());
  child_list = std::make_unique<JsonChildSchemaList[]>(message.m_Schemas.size());

  for (std::size_t index = 0; index < message.m_Schemas.size(); index++)
  {
    schema_list[index].m_Type = (JsonType)message.m_Schemas[index].m_Type;
    if (schema_list[index].m_Type == JsonType::kObject)
    {
      schema_list[index].m_ExtData = &child_list[message.m_Schemas[index].m_SubSchemaIndex];
      schema_list[index].m_TypeId = message.m_Schemas[index].m_TypeId;
    }
    else if (schema_list[index].m_Type == JsonType::kHashMap)
    {
      schema_list[index].m_ExtData = &schema_list[message.m_Schemas[index].m_SubSchemaIndex];
      schema_list[index].m_TypeId = 0;
    }
    else
    {
      schema_list[index].m_ExtData = nullptr;
      schema_list[index].m_TypeId = 0;
    }
  }

  for (std::size_t index = 0; index < message.m_ChildSchemas.size(); index++)
  {
    child_list[index].m_NumChildren = (int)message.m_ChildSchemas[index].m_ChildSchemas.size();

    int child_index = 0;
    for (auto elem : message.m_ChildSchemas[index].m_ChildSchemas)
    {
      child_list[index].m_Children.emplace_back(&schema_list[elem.second]);
      child_list[index].m_Names.emplace_back(elem.first);
      child_list[index].m_NameLookup.emplace(std::make_pair(crc32(elem.first), child_index));
      child_index++;
    }
  }

  return &schema_list[message.m_PrimarySchema];
}
