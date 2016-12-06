
#include "Foundation/Common.h"
#include "Foundation/Json/Json.h"
#include "Foundation/Json/JsonSchema.h"

#include <StormRefl/StormReflJsonStd.h>

Json::Json(NotNullPtr<const JsonSchema> schema)
  : m_Schema(schema), m_State(0)
{
  Clear();
}

Json::Json(const Json & rhs)
{
  m_Schema = rhs.m_Schema;
  m_JsonData = rhs.m_JsonData;
}

Json::Json(Json && rhs)
{
  m_Schema = rhs.m_Schema;
  m_JsonData = std::move(rhs.m_JsonData);
}

Json::~Json()
{

}

Json & Json::operator = (const Json & rhs)
{
  m_Schema = rhs.m_Schema;
  m_JsonData = rhs.m_JsonData;
  return *this;
}

Json & Json::operator = (Json && rhs)
{
  m_Schema = rhs.m_Schema;
  m_JsonData = std::move(rhs.m_JsonData);
  return *this;
}

void Json::Clear()
{
  switch (m_Schema->m_Type)
  {
  case JsonType::kNull:
    m_JsonData = (void *)nullptr;
    return;
  case JsonType::kBool:
    m_JsonData = false;
    break;
  case JsonType::kUnsignedIntegerNumber:
    {
      uint64_t val = 0;
      m_JsonData = val;
    }
    break;
  case JsonType::kSignedIntegerNumber:
    {
      int64_t val = 0;
      m_JsonData = val;
    }
    break;
  case JsonType::kFloatingNumber:
    {
      float val = 0;
      m_JsonData = val;
    }
    break;
  case JsonType::kString:
    m_JsonData = std::string("");
    break;
  case JsonType::kHomogenousArray:
    m_JsonData = HomogeneousType();
    break;
  case JsonType::kHeterogenousArray:
    m_JsonData = HeterogeneousType();
    break;
  case JsonType::kHashMap:
    m_JsonData = HashMapType();
    break;
  case JsonType::kObject:
    m_JsonData = ObjectType();
    break;
  }
}

void Json::SetState(int state)
{
  m_State = state;
  if (GetType() == JsonType::kHashMap)
  {
    auto & arr = m_JsonData.GetAs<HashMapType>();
    for (auto & elem : arr)
    {
      auto & json = std::get<Json>(elem.second);
      json.SetState(state);
    }
  }
  else if (GetType() == JsonType::kObject)
  {
    auto & dict = m_JsonData.GetAs<ObjectType>();
    for (auto & elem : dict)
    {
      auto & json = std::get<Json>(elem.second);
      json.SetState(state);
    }
  }
}

void Json::Encode(std::string & sb)
{
  switch (GetType())
  {
  case JsonType::kNull:
    sb += "null";
    return;
  case JsonType::kBool:
    if (m_JsonData.GetAs<bool>())
    {
      sb += "true";
    }
    else
    {
      sb += "false";
    }
    break;
  case JsonType::kUnsignedIntegerNumber:
    {
      uint64_t val = m_JsonData.GetAs<uint64_t>();
      sb += std::to_string(val);
    }
    break;
  case JsonType::kSignedIntegerNumber:
    {
      int64_t val = m_JsonData.GetAs<int64_t>();
      sb += std::to_string(val);
    }
    break;
  case JsonType::kFloatingNumber:
    {
      float val = m_JsonData.GetAs<float>();
      sb += std::to_string(val);
    }
    break;
  case JsonType::kString:
    {
      StormReflEncodeJson(m_JsonData.GetAs<std::string>(), sb);
    }
    break;
  case JsonType::kHomogenousArray:
    {
      auto & vec = m_JsonData.GetAs<std::vector<Json>>();
      auto itr = vec.begin();

      if (itr == vec.end())
      {
        sb += "[]";
        break;
      }

      sb += '[';
      while(true)
      {
        itr->Encode(sb);
        ++itr;

        if (itr == vec.end())
        {
          break;
        }

        sb += ',';
      }

      sb += ']';
    }
    break;
  case JsonType::kHeterogenousArray:
    {
      auto & vec = m_JsonData.GetAs<HeterogeneousType>();
      auto itr = vec.begin();

      if (itr == vec.end())
      {
        sb += "[]";
        break;
      }

      sb += '[';
      while(true)
      {
        itr->Encode(sb);
        ++itr;

        if (itr == vec.end())
        {
          break;
        }

        sb += ',';
      }

      sb += ']';
    }
    break;
  case JsonType::kHashMap:
    {
      auto & dict = m_JsonData.GetAs<HashMapType>();
      auto itr = dict.begin();

      if (itr == dict.end())
      {
        sb += "{}";
        break;
      }

      sb += '{';
      while (true)
      {
        uint64_t id = std::get<uint64_t>(itr->second);
        bool additive = std::get<bool>(itr->second);

        if (!additive)
        {
          sb += "\"+";
        }
        else
        {
          sb += '\"';
        }

        sb += std::to_string(id);
        sb += "\":";
        std::get<Json>(itr->second).Encode(sb);
        ++itr;

        if (itr == dict.end())
        {
          break;
        }

        sb += ',';
      }

      sb += '}';
    }
    break;


  case JsonType::kObject:
    {
      auto & dict = m_JsonData.GetAs<ObjectType>();
      auto itr = dict.begin();

      if (itr == dict.end())
      {
        sb += "{}";
        break;
      }

      sb += '{';
      while (true)
      {
        sb += '\"';
        sb += itr->second.first;
        sb += "\":";
        itr->second.second.Encode(sb);
        ++itr;

        if (itr == dict.end())
        {
          break;
        }

        sb += ',';
      }

      sb += '}';
    }
    break;
  }
}

void Json::EncodePretty(std::string & sb, int base_indent, int advance, bool do_indent)
{
  if (do_indent)
  {
    StormReflJsonHelpers::StormReflEncodeIndent(base_indent, sb);
  }

  switch (GetType())
  {
  case JsonType::kHashMap:
    {
      auto & dict = m_JsonData.GetAs<HashMapType>();
      auto itr = dict.begin();

      if (itr == dict.end())
      {
        sb += "{ }";
        break;
      }

      sb += "{\n";
      while (true)
      {
        StormReflJsonHelpers::StormReflEncodeIndent(base_indent + advance, sb);
        uint64_t id = std::get<uint64_t>(itr->second);
        bool additive = std::get<bool>(itr->second);

        if (!additive)
        {
          sb += "\"+";
        }
        else
        {
          sb += '\"';
        }

        sb += std::to_string(id);
        sb += "\": ";
        std::get<Json>(itr->second).EncodePretty(sb, base_indent + advance, advance, false);
        ++itr;

        if (itr == dict.end())
        {
          break;
        }

        sb += ",\n";
      }

      sb += '\n';
      StormReflJsonHelpers::StormReflEncodeIndent(base_indent, sb);
      sb += "}";
    }
    break;

  case JsonType::kObject:
    {
      auto & dict = m_JsonData.GetAs<ObjectType>();
      auto itr = dict.begin();

      if (itr == dict.end())
      {
        sb += "{ }";
        break;
      }

      bool is_pod = true;
      JsonChildSchemaList * child_list = (JsonChildSchemaList *)m_Schema->m_ExtData;

      for (int index = 0; index < child_list->m_NumChildren; index++)
      {
        auto child_type = child_list->m_Children[index]->m_Type;
        if (child_type == JsonType::kObject || child_type == JsonType::kHashMap)
        {
          is_pod = false;
          break;
        }
      }

      if (is_pod)
      {
        Encode(sb);
        break;
      }

      sb += "{\n";
      while (true)
      {
        StormReflJsonHelpers::StormReflEncodeIndent(base_indent + advance, sb);
        sb += '\"';
        sb += itr->second.first;
        sb += "\": ";
        itr->second.second.EncodePretty(sb, base_indent + advance, advance, false);
        ++itr;

        if (itr == dict.end())
        {
          break;
        }

        sb += ",\n";
      }

      sb += '\n';
      StormReflJsonHelpers::StormReflEncodeIndent(base_indent, sb);
      sb += "}";
    }
    break;
  default:
    Encode(sb);
    break;
  }

}

JsonParseResult Json::Parse(czstr data, std::vector<std::pair<std::string, std::string>> & schema_errors)
{
  return Parse(data, data, false, "", schema_errors);
}

JsonParseResult Json::Parse(czstr data, czstr & result, bool allow_null, const std::string & path, std::vector<std::pair<std::string, std::string>> & schema_errors)
{
  StormReflJsonAdvanceWhiteSpace(data);
  if (*data == '{')
  {
    if (m_Schema->m_Type == JsonType::kHashMap)
    {
      HashMapType dict;

      data++;
      StormReflJsonAdvanceWhiteSpace(data);
      if (*data == '}')
      {
        data++;
        result = data;

        m_JsonData = dict;
        return JsonParseResult::kNone;
      }

      while (true)
      {
        if (*data != '\"')
        {
          return JsonParseResult::kSyntaxError;
        }

        data++;

        bool additive = true;
        if (*data == '+')
        {
          additive = false;
          data++;
        }

        uint64_t id;
        if (StormReflJson<uint64_t>::Parse(id, data, data) == false)
        {
          return JsonParseResult::kSyntaxError;
        }

        if (*data != '\"')
        {
          return JsonParseResult::kSyntaxError;
        }

        data++;
        StormReflJsonAdvanceWhiteSpace(data);

        if (*data != ':')
        {
          return JsonParseResult::kSyntaxError;
        }

        data++;

        std::string sub_path = path;
        if (!additive)
        {
          sub_path += "[+";
        }
        else
        {
          sub_path += '[';
        }

        sub_path += std::to_string(id);
        sub_path += ']';

        Json json((JsonSchema *)m_Schema->m_ExtData);

        const char * elem_start = data;
        auto parse_result = json.Parse(data, data, additive == false, sub_path, schema_errors);

        if (parse_result == JsonParseResult::kSyntaxError)
        {
          return JsonParseResult::kSyntaxError;
        }

        if (parse_result == JsonParseResult::kSchemaError)
        {
          if (StormReflJsonParseOverValue(elem_start, data) == false)
          {
            return JsonParseResult::kSyntaxError;
          }

          schema_errors.emplace_back(std::make_pair(sub_path, std::string(elem_start, data)));
          StormReflJsonAdvanceWhiteSpace(data);
        }
        else
        {
          dict.emplace(std::make_pair(crc32integer(id), std::make_tuple(id, additive, std::move(json))));
          StormReflJsonAdvanceWhiteSpace(data);
        }

        if (*data == ',')
        {
          data++;
        }
        else if (*data == '}')
        {
          data++;
          result = data;

          m_JsonData = std::move(dict);
          return JsonParseResult::kNone;
        }
        else
        {
          return JsonParseResult::kSyntaxError;
        }
      }
    }
    else if (m_Schema->m_Type == JsonType::kObject)
    {
      ObjectType dict;

      data++;
      StormReflJsonAdvanceWhiteSpace(data);
      if (*data == '}')
      {
        data++;
        result = data;

        m_JsonData = dict;
        return JsonParseResult::kNone;
      }

      while (true)
      {
        std::string id;
        if (StormReflParseJson(id, data, data) == false)
        {
          return JsonParseResult::kSyntaxError;
        }

        StormReflJsonAdvanceWhiteSpace(data);

        if (*data != ':')
        {
          return JsonParseResult::kSyntaxError;
        }

        data++;

        std::string sub_path = path;
        sub_path += '.';
        sub_path += id;

        JsonChildSchemaList * child_list = (JsonChildSchemaList *)m_Schema->m_ExtData;
        auto itr = child_list->m_NameLookup.find(crc32(id));

        auto parse_result = JsonParseResult::kSchemaError;
        const char * elem_start = data;
        if (itr != child_list->m_NameLookup.end())
        {
          Json json(child_list->m_Children[itr->second]);

          parse_result = json.Parse(data, data, false, sub_path, schema_errors);
          if (parse_result == JsonParseResult::kNone)
          {
            dict.emplace(std::make_pair(itr->first, std::make_pair(id, std::move(json))));
            StormReflJsonAdvanceWhiteSpace(data);
          }

          if (parse_result == JsonParseResult::kSyntaxError)
          {
            return JsonParseResult::kSyntaxError;
          }
        }

        if (parse_result == JsonParseResult::kSchemaError)
        {
          if (StormReflJsonParseOverValue(elem_start, data) == false)
          {
            return JsonParseResult::kSyntaxError;
          }

          schema_errors.emplace_back(std::make_pair(sub_path, std::string(elem_start, data)));
          StormReflJsonAdvanceWhiteSpace(data);
        }

        if (*data == ',')
        {
          data++;
        }
        else if (*data == '}')
        {
          data++;
          result = data;

          m_JsonData = std::move(dict);
          return JsonParseResult::kNone;
        }
        else
        {
          return JsonParseResult::kSyntaxError;
        }
      }
    }
    else
    {
      return JsonParseResult::kSchemaError;
    }
  }
  else if (*data == '[')
  {
    if (m_Schema->m_Type == JsonType::kHomogenousArray)
    {
      HomogeneousType arr;

      data++;
      StormReflJsonAdvanceWhiteSpace(data);
      if (*data == ']')
      {
        data++;
        result = data;

        m_JsonData = arr;
        return JsonParseResult::kNone;
      }
    }
    else if (m_Schema->m_Type == JsonType::kHeterogenousArray)
    {
      return JsonParseResult::kSyntaxError;
    }
    else
    {
      return JsonParseResult::kSchemaError;
    }
  }
  else if (*data == '\"')
  {
    if (m_Schema->m_Type != JsonType::kString)
    {
      return JsonParseResult::kSchemaError;
    }

    std::string str;
    if (StormReflJson<std::string>::Parse(str, data, result) == false)
    {
      return JsonParseResult::kSyntaxError;
    }

    m_JsonData = str;
    return JsonParseResult::kNone;
  }
  else if ((*data <= '9' && *data >= '0') || *data == '-' || *data == '+' || *data == '.')
  {
    if (m_Schema->m_Type == JsonType::kUnsignedIntegerNumber)
    {
      uint64_t val;
      if (StormReflJson<uint64_t>::Parse(val, data, result) == false)
      {
        return JsonParseResult::kSyntaxError;
      }

      m_JsonData = val;
      return JsonParseResult::kNone;
    }
    else if (m_Schema->m_Type == JsonType::kSignedIntegerNumber)
    {
      int64_t val;
      if (StormReflJson<int64_t>::Parse(val, data, result) == false)
      {
        return JsonParseResult::kSyntaxError;
      }

      m_JsonData = val;
      return JsonParseResult::kNone;
    }
    else if (m_Schema->m_Type == JsonType::kFloatingNumber)
    {
      float val;
      if (StormReflJson<float>::Parse(val, data, result) == false)
      {
        return JsonParseResult::kSyntaxError;
      }

      m_JsonData = val;
      return JsonParseResult::kNone;
    }
    else
    {
      return JsonParseResult::kSchemaError;
    }
  }
  else if (*data == 't')
  {
    if (m_Schema->m_Type != JsonType::kBool)
    {
      return JsonParseResult::kSchemaError;
    }

    if (StormReflJsonParseOverTrue(data, result) == false)
    {
      return JsonParseResult::kSyntaxError;

    }

    m_JsonData = true;
    return JsonParseResult::kNone;
  }
  else if (*data == 'f')
  {
    if (m_Schema->m_Type != JsonType::kBool)
    {
      return JsonParseResult::kSchemaError;
    }

    if (StormReflJsonParseOverFalse(data, result) == false)
    {
      return JsonParseResult::kSyntaxError;
    }

    m_JsonData = false;
    return JsonParseResult::kNone;
  }
  else if (*data == 'n')
  {
    if (!allow_null)
    {
      return JsonParseResult::kSchemaError;
    }

    if (StormReflJsonParseOverNull(data, result) == false)
    {
      return JsonParseResult::kSyntaxError;
    }

    m_JsonData = (void *)nullptr;
    return JsonParseResult::kNull;
  }

  return JsonParseResult::kSyntaxError;
}

void Json::ApplyChange(const ReflectionChangeNotification & change, NullOptPtr<ReflectionChangeNotification> reverse_change)
{
  Json * json = GetJsonAtPath(change.m_Path.data(), true);
  if (json == nullptr)
  {
    throw false;
  }

  json->ApplyChangeDirect(change, reverse_change);
}

void Json::ApplyJson(const Json & rhs)
{
  if (m_Schema->m_Type != rhs.m_Schema->m_Type)
  {
    return;
  }

  if (m_Schema->m_Type == JsonType::kObject)
  {
    auto & rhs_dict = rhs.m_JsonData.GetAs<ObjectType>();
    auto & this_dict = m_JsonData.GetAs<ObjectType>();

    JsonChildSchemaList * child_list = (JsonChildSchemaList *)m_Schema->m_ExtData;

    for (auto & elem : rhs_dict)
    {
      auto itr = this_dict.find(elem.first);
      if (itr == this_dict.end())
      {
        auto name_itr = child_list->m_NameLookup.find(elem.first);
        if (name_itr == child_list->m_NameLookup.end())
        {
          continue;
        }

        this_dict.emplace(elem);
      }
      else
      {
        auto & json = std::get<Json>(itr->second);
        json.ApplyJson(std::get<Json>(elem.second));
      }
    }
  }
  else if(m_Schema->m_Type == JsonType::kHashMap)
  {
    auto & rhs_arr = rhs.m_JsonData.GetAs<HashMapType>();
    auto & this_arr = m_JsonData.GetAs<HashMapType>();

    for (auto & elem : rhs_arr)
    {
      bool additive = std::get<bool>(elem.second);
      auto & elem_json = std::get<Json>(elem.second);

      auto itr = this_arr.find(elem.first);

      if (elem_json.GetType() == JsonType::kNull)
      {
        if (itr != this_arr.end())
        {
          this_arr.erase(itr);
        }
      }
      else if (additive)
      {
        if (itr == this_arr.end())
        {
          this_arr.emplace(elem);
        }
      }
      else
      {
        if (itr != this_arr.end())
        {
          auto & json = std::get<Json>(itr->second);
          json.ApplyJson(elem_json);
        }
      }
    }
  }
  else
  {
    m_JsonData = rhs.m_JsonData;
  }
}

NullOptPtr<Json> Json::GetJsonAtPath(czstr path, bool create_nodes)
{
  if (*path == 0)
  {
    return this;
  }

  if (*path == '.')
  {
    if (m_Schema->m_Type != JsonType::kObject)
    {
      return nullptr;
    }

    ObjectType & dict = m_JsonData.GetAs<ObjectType>();

    Hash id_hash = crc32begin();
    path++;

    const char * start_path = path;

    while (*path != 0 && *path != '[' && *path != '.')
    {
      id_hash = crc32additive(id_hash, *path);
      path++;
    }

    id_hash = crc32end(id_hash);

    auto itr = dict.find(id_hash);
    if (itr == dict.end())
    {
      if (create_nodes == false)
      {
        return nullptr;
      }

      JsonChildSchemaList * child_list = (JsonChildSchemaList *)m_Schema->m_ExtData;
      auto name_itr = child_list->m_NameLookup.find(id_hash);

      if (name_itr == child_list->m_NameLookup.end())
      {
        return nullptr;
      }

      auto child_schema = child_list->m_Children[name_itr->second];

      auto result = dict.emplace(std::make_pair(id_hash, std::make_pair(std::string(start_path, path), Json(child_schema))));
      itr = result.first;
    }

    auto & child_json = itr->second.second;
    return child_json.GetJsonAtPath(path, create_nodes);
  }
  else if (*path == '[')
  {
    if (m_Schema->m_Type != JsonType::kHashMap)
    {
      return nullptr;
    }

    HashMapType & arr = m_JsonData.GetAs<HashMapType>();

    path++;
    if (*path < '0' || *path > '9')
    {
      return nullptr;
    }

    uint64_t index = *path - '0';

    while (*path != ']')
    {
      if (*path < '0' || *path > '9')
      {
        return nullptr;
      }

      index *= 10;
      index += *path - '0';
      path++;
    }

    uint32_t id = crc32integer(index);
    auto itr = arr.find(id);
    if (itr == arr.end())
    {
      if (create_nodes == false)
      {
        return nullptr;
      }

      auto result = arr.emplace(std::make_pair(id, std::make_tuple(index, false, Json((JsonSchema *)m_Schema->m_ExtData))));
      itr = result.first;
    }

    auto & child_json = std::get<Json>(itr->second);
    return child_json.GetJsonAtPath(path, create_nodes);
  }

  return nullptr;
}

bool Json::RevertDataAtPath(czstr path)
{
  if (*path == 0)
  {
    throw false;
  }

  std::size_t len = strlen(path);
  if (path[len - 1] == ']')
  {
    const char * path_end = &path[len - 2];
    while (true)
    {
      if (path_end == path - 1)
      {
        throw false;
      }

      if (*path_end == '[')
      {
        break;
      }

      path_end--;
    }

    std::string sub_path(path, path_end);
    auto json = GetJsonAtPath(sub_path.data(), false);

    if (json && json->GetType() == JsonType::kHashMap)
    {
      uint64_t index = strtoull(path_end + 1, nullptr, 10);

      auto & arr = json->m_JsonData.GetAs<HashMapType>();
      auto itr = arr.find(crc32integer(index));

      if (itr != arr.end())
      {
        arr.erase(itr);
        return true;
      }
    }
  }
  else
  {
    const char * path_end = &path[len - 2];
    while (true)
    {
      if (path_end == path - 1)
      {
        throw false;
      }

      if (*path_end == '.')
      {
        break;
      }

      path_end--;
    }

    std::string sub_path(path, path_end);
    auto json = GetJsonAtPath(sub_path.data(), false);

    if (json && json->GetType() == JsonType::kObject)
    {
      uint32_t field_hash = crc32(path_end + 1);

      auto & dict = json->m_JsonData.GetAs<ObjectType>();
      auto itr = dict.find(field_hash);

      if (itr != dict.end())
      {
        dict.erase(itr);
        return true;
      }
    }
  }


  return false;
}


void Json::ApplyChangeDirect(const ReflectionChangeNotification & change, NullOptPtr<ReflectionChangeNotification> reverse_change)
{
  switch (change.m_Type)
  {
  case ReflectionNotifyChangeType::kSet:
    {
      if(reverse_change)
      {
        reverse_change->m_Type = ReflectionNotifyChangeType::kSet;
        reverse_change->m_Path = change.m_Path;
        Encode(reverse_change->m_Data);
      }

      std::vector<std::pair<std::string, std::string>> schema_errors;
      Parse(change.m_Data.data(), schema_errors);

      if (schema_errors.size())
      {
        throw false;
      }
    }
    break;
  case ReflectionNotifyChangeType::kClear:
    {
      if(reverse_change)
      {
        reverse_change->m_Type = ReflectionNotifyChangeType::kSet;
        reverse_change->m_Path = change.m_Path;
        Encode(reverse_change->m_Data);
      }

      auto type = GetType();
      if (type == JsonType::kHashMap)
      {
        auto & arr = m_JsonData.GetAs<HashMapType>();
        arr.clear();
      }
      else
      {
        throw false;
      }
    }
    break;
  case ReflectionNotifyChangeType::kCompress:
    {
      if(reverse_change)
      {
        reverse_change->m_Type = ReflectionNotifyChangeType::kSet;
        reverse_change->m_Path = change.m_Path;
        Encode(reverse_change->m_Data);
      }

      auto type = GetType();
      if (type == JsonType::kHashMap)
      {
        auto & arr = m_JsonData.GetAs<HashMapType>();
        std::map<uint64_t, Json> sorted;

        for (auto & val : arr)
        {
          sorted.emplace(std::make_pair(std::get<uint64_t>(val.second), std::move(std::get<Json>(val.second))));
        }

        arr.clear();
        uint64_t index = 0;
        for (auto & val : sorted)
        {
          arr.emplace(std::make_pair(crc32integer(index), std::make_tuple(index, true, std::move(val.second))));
          index++;
        }
      }
    }
    break;
  case ReflectionNotifyChangeType::kInsert:
    {
      if(reverse_change)
      {
        reverse_change->m_Type = ReflectionNotifyChangeType::kRemove;
        reverse_change->m_Path = change.m_Path;
        reverse_change->m_SubIndex = change.m_SubIndex;
      }

      auto type = GetType();
      if (type == JsonType::kHashMap)
      {
        auto & arr = m_JsonData.GetAs<HashMapType>();
        auto num_str = std::to_string(change.m_SubIndex);

        Hash hash = crc32(num_str);
        uint64_t index = std::strtoull(num_str.data(), nullptr, 10);

        Json json((JsonSchema *)m_Schema->m_ExtData);

        std::vector<std::pair<std::string, std::string>> schema_errors;
        json.Parse(change.m_Data.data(), schema_errors);

        if (schema_errors.size())
        {
          throw false;
        }

        arr.emplace(std::make_pair(hash, std::make_tuple(index, true, std::move(json))));
      }
    }
    break;
  case ReflectionNotifyChangeType::kRemove:
    {
      auto type = GetType();
      if (type == JsonType::kHashMap)
      {
        auto & arr = m_JsonData.GetAs<HashMapType>();
        auto num_str = std::to_string(change.m_SubIndex);

        Hash hash = crc32(num_str);
        auto itr = arr.find(hash);
        if (itr != arr.end())
        {
          if (reverse_change)
          {
            reverse_change->m_Type = ReflectionNotifyChangeType::kInsert;
            reverse_change->m_Path = change.m_Path;
            reverse_change->m_SubIndex = change.m_SubIndex;
            std::get<Json>(itr->second).Encode(reverse_change->m_Data);
          }

          arr.erase(itr);
        }
      }
    }
    break;
  }
}
