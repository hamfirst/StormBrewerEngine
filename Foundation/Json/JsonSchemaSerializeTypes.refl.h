#pragma once

#include <vector>
#include <string>

#include <StormRefl/StormRefl.h>

struct JsonSchemaSerializeInfo
{
  STORM_REFL;
  int m_Type;
  std::size_t m_SubSchemaIndex;
  uint32_t m_TypeId;
};

struct JsonSchemaSerializeChildList
{
  STORM_REFL;
  std::vector<std::pair<std::string, std::size_t>> m_ChildSchemas;
};

struct JsonSchemaSerializeMessage
{
  STORM_REFL;
  std::vector<JsonSchemaSerializeInfo> m_Schemas;
  std::vector<JsonSchemaSerializeChildList> m_ChildSchemas;
  std::size_t m_PrimarySchema;
};
