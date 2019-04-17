
#include "Foundation/Common.h"
#include "Foundation/Json/Json.h"

#include "StormRefl/StormReflJsonStd.h"

Json::Json()
  : m_JsonData(std::make_unique<JsonDataType>())
{

}

Json::Json(const Json & rhs)
{
  m_JsonData = std::make_unique<JsonDataType>(*rhs.m_JsonData.get());
}

Json::Json(Json && rhs)
{
  m_JsonData = std::move(rhs.m_JsonData);
}

Json::~Json()
{

}

Json & Json::operator = (const Json & rhs)
{
  m_JsonData = std::make_unique<JsonDataType>(*rhs.m_JsonData.get());
  return *this;
}

Json & Json::operator = (Json && rhs)
{
  m_JsonData = std::move(rhs.m_JsonData);
  return *this;
}

void Json::Encode(std::string & sb)
{
  switch (GetType())
  {
  case JsonType::kNull:
    sb += "null";
    return;
  case JsonType::kBool:
    if (m_JsonData->GetAs<bool>())
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
      uint64_t val = m_JsonData->GetAs<uint64_t>();
      sb += std::to_string(val);
    }
    break;
  case JsonType::kSignedIntegerNumber:
    {
      int64_t val = m_JsonData->GetAs<int64_t>();
      sb += std::to_string(val);
    }
    break;
  case JsonType::kFloatingNumber:
    {
      float val = m_JsonData->GetAs<float>();
      sb += std::to_string(val);
    }
    break;
  case JsonType::kString:
    {
      StormReflEncodeJson(m_JsonData->GetAs<std::string>(), sb);
    }
    break;
  case JsonType::kArray:
    {
      auto & vec = m_JsonData->GetAs<ArrayType>();

      sb += '[';
      for (std::size_t index = 0, end = vec.size(); index < end; ++index)
      {
        vec[index]->Encode(sb);
        if (index < end - 1)
        {
          sb += ',';
        }
      }
      sb += ']';
    }
    break;

  case JsonType::kObject:
    {
      auto & dict = m_JsonData->GetAs<ObjectType>();
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
        sb += itr->second.m_Name;
        sb += "\":";
        itr->second.m_Object->Encode(sb);
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
  case JsonType::kObject:
    {
      auto & dict = m_JsonData->GetAs<ObjectType>();
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
        sb += '\"';
        sb += itr->second.m_Name;
        sb += "\": ";
        itr->second.m_Object->EncodePretty(sb, base_indent + advance, advance, false);
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

JsonParseResult Json::Parse(czstr data)
{
  return Parse(data, data, false);
}

JsonParseResult Json::Parse(czstr data, czstr & result, bool allow_null)
{
  auto & json_data = *m_JsonData.get();
  StormReflJsonAdvanceWhiteSpace(data);
  if (*data == '{')
  {
    ObjectType dict;

    data++;
    StormReflJsonAdvanceWhiteSpace(data);
    if (*data == '}')
    {
      data++;
      result = data;

      json_data = std::move(dict);
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

      Json new_json;

      auto parse_result = new_json.Parse(data, data, true);
      if (parse_result == JsonParseResult::kNone)
      {
        dict.emplace(std::make_pair(crc32(id), JsonNameAndObject{ id, std::make_unique<Json>(std::move(new_json)) }));
        StormReflJsonAdvanceWhiteSpace(data);
      }
      else
      {
        return parse_result;
      }

      if (*data == ',')
      {
        data++;
      }
      else if (*data == '}')
      {
        data++;
        result = data;

        json_data = std::move(dict);
        return JsonParseResult::kNone;
      }
      else
      {
        return JsonParseResult::kSyntaxError;
      }
    }
  }
  else if (*data == '[')
  {
    ArrayType arr;

    data++;
    StormReflJsonAdvanceWhiteSpace(data);
    if (*data == ']')
    {
      data++;
      result = data;

      json_data = std::move(arr);
      return JsonParseResult::kNone;
    }

    while (true)
    {
      Json new_json;

      auto parse_result = new_json.Parse(data, data, true);
      if (parse_result == JsonParseResult::kNone)
      {
        arr.emplace_back(std::make_unique<Json>(std::move(new_json)));
        StormReflJsonAdvanceWhiteSpace(data);
      }
      else
      {
        return parse_result;
      }

      if (*data == ',')
      {
        data++;
        StormReflJsonAdvanceWhiteSpace(data);
      }
      else if (*data == ']')
      {
        data++;
        result = data;

        json_data = std::move(arr);
        return JsonParseResult::kNone;
      }
      else
      {
        return JsonParseResult::kSyntaxError;
      }
    }
  }
  else if (*data == '\"')
  {
    std::string str;
    if (StormReflJson<std::string>::Parse(str, data, result, false) == false)
    {
      return JsonParseResult::kSyntaxError;
    }

    json_data = str;
    return JsonParseResult::kNone;
  }
  else if ((*data <= '9' && *data >= '0') || *data == '-' || *data == '+' || *data == '.')
  {
    auto str = data;
    bool is_negative = false;

    if (*str == '-')
    {
      is_negative = true;
      str++;
    }

    bool is_floating_point = false;
    while (true)
    {
      if (*str == '.' || *str == 'e' || *str == 'E')
      {
        is_floating_point = true;
        break;
      }

      if (*str < '0' || *str > '9')
      {
        break;
      }

      str++;
    }

    uint64_t unsigned_val;
    int64_t signed_val;

    float float_val;

    if (is_floating_point)
    {
      if (StormReflParseJson(float_val, data, result))
      {
        json_data = float_val;
        return JsonParseResult::kNone;
      }
    }
    else if (is_negative)
    {
      if (StormReflParseJson(signed_val, data, result))
      {
        json_data = signed_val;
        return JsonParseResult::kNone;
      }
    }
    else
    {
      if (StormReflParseJson(unsigned_val, data, result))
      {
        json_data = unsigned_val;
        return JsonParseResult::kNone;
      }
    }

    return JsonParseResult::kSyntaxError;
  }
  else if (*data == 't')
  {
    if (StormReflJsonParseOverTrue(data, result) == false)
    {
      return JsonParseResult::kSyntaxError;
    }

    json_data = true;
    return JsonParseResult::kNone;
  }
  else if (*data == 'f')
  {
    if (StormReflJsonParseOverFalse(data, result) == false)
    {
      return JsonParseResult::kSyntaxError;
    }

    json_data = false;
    return JsonParseResult::kNone;
  }
  else if (*data == 'n')
  {
    if (StormReflJsonParseOverNull(data, result) == false)
    {
      return JsonParseResult::kSyntaxError;
    }

    json_data = (void *)nullptr;
    return JsonParseResult::kNull;
  }

  return JsonParseResult::kSyntaxError;
}

void Json::ApplyChange(const ReflectionChangeNotification & change, NullOptPtr<ReflectionChangeNotification> reverse_change)
{
  czstr created_node_end = nullptr;
  auto result = GetJsonAndParentAtPath(change.m_Path.data(), nullptr, created_node_end);

  std::string created_node_path;
  if (created_node_end)
  {
    created_node_path = std::string(change.m_Path.data(), created_node_end);
  }

  if (result.m_Json == nullptr)
  {
    throw false;
  }

  result.m_Json->ApplyChangeDirect(change, reverse_change, result.m_Parent, result.m_Iterator.GetPtr(), created_node_path);
}

void Json::ApplyJson(const Json & rhs)
{
  if(rhs.m_JsonData->GetCurrentTypeIndex() == (int)JsonType::kObject && m_JsonData->GetCurrentTypeIndex() == (int)JsonType::kObject)
  {
    auto & rhs_dict = rhs.m_JsonData->GetAs<ObjectType>();
    auto & this_dict = m_JsonData->GetAs<ObjectType>();

    for (auto & elem : rhs_dict)
    {
      auto itr = this_dict.find(elem.first);
      if (itr == this_dict.end())
      {
        if (elem.second.m_Object->GetType() != JsonType::kNull)
        {
          auto json_copy = std::make_unique<Json>(*elem.second.m_Object.get());
          this_dict.emplace(std::make_pair(elem.first, JsonNameAndObject{ elem.second.m_Name, std::move(json_copy) }));
        }
      }
      else
      {
        if (elem.second.m_Object->GetType() == JsonType::kNull)
        {
          this_dict.erase(itr);
        }
        else
        {
          auto & json = itr->second.m_Object;
          json->ApplyJson(*elem.second.m_Object.get());
        }
      }
    }
  }
  else
  {
    m_JsonData = std::make_unique<JsonDataType>(*rhs.m_JsonData.get());
  }
}

NullOptPtr<Json> Json::GetJsonAtPath(czstr path, bool create_nodes)
{
  if (*path == 0)
  {
    return this;
  }

  if (m_JsonData->GetCurrentTypeIndex() != (int)JsonType::kObject)
  {
    if (create_nodes)
    {
      m_JsonData = std::make_unique<JsonDataType>(ObjectType{});
    }
    else
    {
      return nullptr;
    }
  }

  std::string index;
  uint32_t hash = crc32begin();

  if (*path == '.')
  {
    path++;

    while (*path != 0 && *path != '.' && *path != '[')
    {
      hash = crc32additive(hash, *path);
      index += *path;
      path++;
    }
  }
  else if (*path == '[')
  {
    path++;

    while (*path != 0 && *path != ']')
    {
      hash = crc32additive(hash, *path);
      index += *path;
      path++;
    }

    if(*path == ']')
    { 
      path++;
    }
  }

  hash = crc32end(hash);

  auto & obj = m_JsonData->GetAs<ObjectType>();
  auto itr = obj.find(hash);

  if (itr == obj.end())
  {
    if (create_nodes == false)
    {
      return nullptr;
    }

    Json new_json;
    new_json.m_JsonData = std::make_unique<JsonDataType>();

    auto result = obj.emplace(std::make_pair(hash, JsonNameAndObject{ index, std::make_unique<Json>(std::move(new_json)) }));
    auto & json = result.first->second.m_Object;

    return json->GetJsonAtPath(path, create_nodes);
  }

  return itr->second.m_Object->GetJsonAtPath(path, create_nodes);
}

Json::ParentAndPath Json::GetJsonAndParentAtPath(czstr path, NullOptPtr<Json> parent, czstr & created_node_path_end)
{
  if (*path == 0)
  {
    return ParentAndPath{ this, parent, Optional<Json::ObjectType::iterator>{} };
  }

  if (m_JsonData->GetCurrentTypeIndex() != (int)JsonType::kObject)
  {
    m_JsonData = std::make_unique<JsonDataType>(ObjectType{});
  }

  std::string index;
  uint32_t hash = crc32begin();

  if (*path == '.')
  {
    path++;
    while (*path != 0 && *path != '.' && *path != '[')
    {
      hash = crc32additive(hash, *path);
      index += *path;
      path++;
    }
  }
  else if (*path == '[')
  {
    path++;
    while (*path != 0 && *path != ']')
    {
      hash = crc32additive(hash, *path);
      index += *path;
      path++;
    }

    if (*path == ']')
    {
      path++;
    }
  }

  hash = crc32end(hash);

  auto & obj = m_JsonData->GetAs<ObjectType>();
  auto itr = obj.find(hash);

  if (itr == obj.end())
  {
    if (created_node_path_end == nullptr)
    {
      created_node_path_end = path;
    }

    if (*path == 0)
    {
      auto result = obj.emplace(std::make_pair(hash, JsonNameAndObject{ index, std::make_unique<Json>() }));
      auto & json = result.first->second.m_Object;

      return ParentAndPath{ json.get(), this, Optional<Json::ObjectType::iterator>(result.first) };
    }
    else
    {
      Json new_json;
      new_json.m_JsonData = std::make_unique<JsonDataType>(ObjectType{});

      auto result = obj.emplace(std::make_pair(hash, JsonNameAndObject{ index, std::make_unique<Json>(std::move(new_json)) }));
      auto & json = result.first->second.m_Object;

      return json->GetJsonAndParentAtPath(path, this, created_node_path_end);
    }
  }

  if (*path == 0)
  {
    return ParentAndPath{ itr->second.m_Object.get(), this, Optional<Json::ObjectType::iterator>(itr) };
  }
  else
  {
    return itr->second.m_Object->GetJsonAndParentAtPath(path, this, created_node_path_end);
  }

  return ParentAndPath{ this, parent, Optional<Json::ObjectType::iterator>{} };
}


void Json::ApplyChangeDirect(const ReflectionChangeNotification & change, NullOptPtr<ReflectionChangeNotification> reverse_change,
  Json * parent_node, ObjectType::iterator * itr, const std::string & created_node_path)
{
  if (created_node_path.size() > 0 && reverse_change)
  {
    reverse_change->m_Type = ReflectionNotifyChangeType::kRevert;
    reverse_change->m_Path = created_node_path;
    reverse_change = nullptr;
  }

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

      if (Parse(change.m_Data.data()) == JsonParseResult::kSyntaxError)
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
      if (type == JsonType::kObject)
      {
        auto & obj = m_JsonData->GetAs<ObjectType>();
        obj.clear();
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
      if (type == JsonType::kObject)
      {
        auto & obj = m_JsonData->GetAs<ObjectType>();
        std::map<uint64_t, Json> sorted;

        for (auto & val : obj)
        {
          if (val.second.m_Object->GetType() != JsonType::kNull)
          {
            sorted.emplace(std::make_pair(std::strtoull(val.second.m_Name.data(), nullptr, 10), std::move(*val.second.m_Object.get())));
          }
        }

        obj.clear();
        uint64_t index = 0;
        for (auto & val : sorted)
        {
          obj.emplace(std::make_pair(crc32integer(index), JsonNameAndObject{ std::to_string(index), std::make_unique<Json>(std::move(val.second)) }));
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
      if (type != JsonType::kObject)
      {
        m_JsonData = std::make_unique<JsonDataType>(ObjectType{});
      }

      auto & obj = m_JsonData->GetAs<ObjectType>();
      auto num_str = std::to_string(change.m_SubIndex);

      Hash hash = crc32(num_str);

      Json json;
      if (json.Parse(change.m_Data.data()) == JsonParseResult::kSyntaxError)
      {
        throw false;
      }

      auto result = obj.emplace(std::make_pair(hash, JsonNameAndObject{ std::move(num_str), std::make_unique<Json>(json) }));
      if (result.second == false)
      {
        result.first->second.m_Object = std::make_unique<Json>(std::move(json));
      }
    }
    break;
  case ReflectionNotifyChangeType::kRemove:
    {
      auto type = GetType();
      if (type == JsonType::kObject)
      {
        auto & obj = m_JsonData->GetAs<ObjectType>();
        auto num_str = std::to_string(change.m_SubIndex);

        Hash hash = crc32(num_str);
        auto itr = obj.find(hash);
        if (itr != obj.end())
        {
          if (reverse_change)
          {
            reverse_change->m_Type = ReflectionNotifyChangeType::kInsert;
            reverse_change->m_Path = change.m_Path;
            reverse_change->m_SubIndex = change.m_SubIndex;
            itr->second.m_Object->Encode(reverse_change->m_Data);
          }

          obj.erase(itr);
        }
      }
    }
    break;
  case ReflectionNotifyChangeType::kRevert:
    {
      if (reverse_change)
      {
        reverse_change->m_Type = ReflectionNotifyChangeType::kSet;
        reverse_change->m_Path = change.m_Path;
        Encode(reverse_change->m_Data);
      }

      if (parent_node)
      {
        ObjectType & obj = parent_node->m_JsonData->GetAs<ObjectType>();
        obj.erase(*itr);
      }
    }
    break;
  }
}

Json Json::CreateEmptyObject()
{
  Json json;
  json.m_JsonData = std::make_unique<JsonDataType>(ObjectType{});
  return json;
}
