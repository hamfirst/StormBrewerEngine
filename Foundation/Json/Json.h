
#pragma once

#include "Foundation/Common.h"
#include "Foundation/Variant/Variant.h"
#include "Foundation/Json/JsonType.h"


#include <StormRefl/StormReflMetaFuncs.h>
#include <StormData/StormDataChangeNotifier.h>

struct JsonSchema;

enum class JsonParseResult
{
  kNone,
  kSchemaError,
  kSyntaxError,
  kNull,
};

enum class JsonState
{

};

class Json
{
public:
  Json(NotNullPtr<const JsonSchema> schema);
  Json(const Json & rhs);
  Json(Json && rhs);

  ~Json();

  Json & operator = (const Json & rhs);
  Json & operator = (Json && rhs);

  void Clear();

  JsonType GetType() const
  {
    return (JsonType)m_JsonData.GetCurrentTypeIndex();
  }

  NotNullPtr<const JsonSchema> GetSchema() const
  {
    return m_Schema;
  }

  void SetState(int state);

  void Encode(std::string & sb);
  void EncodePretty(std::string & sb, int base_indent = 0, int advance = 2, bool do_indent = true);

  JsonParseResult Parse(czstr data, std::vector<std::pair<std::string, std::string>> & schema_errors);
  void ApplyChange(const ReflectionChangeNotification & change, NullOptPtr<ReflectionChangeNotification> reverse_change);

  void ApplyJson(const Json & rhs);

  NullOptPtr<Json> GetJsonAtPath(czstr path, bool create_nodes);
  bool RevertDataAtPath(czstr path);

protected:

  JsonParseResult Parse(czstr data, czstr & result, bool allow_null, const std::string & path, std::vector<std::pair<std::string, std::string>> & schema_errors);

  void ApplyChangeDirect(const ReflectionChangeNotification & change, NullOptPtr<ReflectionChangeNotification> reverse_change);

private:

  class vector_alias : public std::vector<Json>
  {

  };

  using ObjectType = std::unordered_map<uint32_t, std::pair<std::string, Json>>;
  using HashMapType = std::unordered_map<uint32_t, std::tuple<uint64_t, bool, Json>>;
  using HomogeneousType = std::vector<Json>;
  using HeterogeneousType = vector_alias;

  using JsonDataType = Variant<void *, bool, uint64_t, int64_t, float, std::string, HomogeneousType, HeterogeneousType, HashMapType, ObjectType>;

  NotNullPtr<const JsonSchema> m_Schema;
  int m_State;
  JsonDataType m_JsonData;
};
