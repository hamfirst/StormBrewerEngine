
#pragma once

#include "Foundation/Common.h"
#include "Foundation/Variant/Variant.h"
#include "Foundation/Json/JsonType.h"


#include <StormRefl/StormReflMetaFuncs.h>
#include <StormData/StormDataChangeNotifier.h>

enum class JsonParseResult
{
  kNone,
  kSyntaxError,
  kNull,
};

enum class JsonState
{

};

class Json
{
public:
  Json();
  Json(const Json & rhs);
  Json(Json && rhs);

  ~Json();

  Json & operator = (const Json & rhs);
  Json & operator = (Json && rhs);

  JsonType GetType() const
  {
    return (JsonType)m_JsonData->GetCurrentTypeIndex();
  }

  void Encode(std::string & sb);
  void EncodePretty(std::string & sb, int base_indent = 0, int advance = 2, bool do_indent = true);

  JsonParseResult Parse(czstr data);
  void ApplyChange(const ReflectionChangeNotification & change, NullOptPtr<ReflectionChangeNotification> reverse_change);

  void ApplyJson(const Json & rhs);

  NullOptPtr<Json> GetJsonAtPath(czstr path, bool create_nodes);

  static Json CreateEmptyObject();

protected:

  using ObjectType = std::unordered_map<uint32_t, std::pair<std::string, Json>>;
  using ArrayType = std::vector<Json>;

  JsonParseResult Parse(czstr data, czstr & result, bool allow_null);

  std::tuple<NullOptPtr<Json>, NullOptPtr<Json>, Optional<ObjectType::iterator>>  GetJsonAndParentAtPath(
    czstr path, NullOptPtr<Json> parent, czstr & created_node_path_end);

  void ApplyChangeDirect(const ReflectionChangeNotification & change, NullOptPtr<ReflectionChangeNotification> reverse_change, 
    Json * parent_node, ObjectType::iterator * itr, const std::string & created_node_path);

private:

  using JsonDataType = Variant<void *, bool, uint64_t, int64_t, float, std::string, ArrayType, ObjectType>;

  std::unique_ptr<JsonDataType> m_JsonData;
};
