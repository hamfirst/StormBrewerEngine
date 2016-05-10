
#include "Foundation\Common.h"
#include "Foundation\Json\Json.h"
#include "Foundation\Reflection\TypeDatabase.h"
#include "Foundation\Reflection\ReflectionJsonThin.h"


std::string ReflectValue(const RByte & value)
{
  return std::to_string((int8_t)value);
}

std::string ReflectValue(const RShort & value)
{
  return std::to_string((int16_t)value);
}

std::string ReflectValue(const RInt & value)
{
  return std::to_string((int32_t)value);
}

std::string ReflectValue(const RLong & value)
{
  return std::to_string((int64_t)value);
}

std::string ReflectValue(const RUByte & value)
{
  return std::to_string((uint8_t)value);
}

std::string ReflectValue(const RUShort & value)
{
  return std::to_string((uint16_t)value);
}

std::string ReflectValue(const RUInt & value)
{
  return std::to_string((uint32_t)value);
}

std::string ReflectValue(const RULong & value)
{
  return std::to_string((uint64_t)value);
}

std::string ReflectValue(const RFloat & value)
{
  return std::string("\"") + std::to_string((float)value) + std::string("\"");
}

std::string ReflectValue(const RString & value)
{
  return Json::escape_string(value);
}

std::string ReflectValue(const void * value, uint32_t type_name_hash)
{
  Optional<TypeInfo> type_info = g_TypeDatabase->GetTypeInfo(type_name_hash);
  if (type_info)
  {
    Json json;
    type_info->m_EncodeJson(value, &json);
    return json.dump();
  }
  else
  {
    return "{}";
  }
}

std::string ReflectValuePolymorphic(const void * value, uint32_t type_name_hash)
{
  Optional<TypeInfo> type_info = g_TypeDatabase->GetTypeInfo(type_name_hash);
  if (type_info)
  {
    Json json;
    type_info->m_EncodeJson(value, &json);

    return std::string("{TypeNameHash: ") + std::to_string(type_name_hash) + std::string(", Obj: ") + json.dump() + std::string("}");
  }
  else
  {
    return std::string("{TypeNameHash: ") + std::to_string(type_name_hash) + std::string(", Obj: {}}");
  }
}

