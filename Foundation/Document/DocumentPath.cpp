
#include "Foundation\Common.h"
#include "Foundation\Document\DocumentPath.h"
#include "Foundation\Json\Json.h"

static bool ValidIdentifierCharacter(std::string::value_type c)
{
  return isalnum(c) > 0 || c == '_';
}

static bool ValidPathCharacter(std::string::value_type c)
{
  return ValidIdentifierCharacter(c) || c == '[' || c == ']' || c == '.' || c == '-';
}

DocumentPath::DocumentPath(const std::string & path)
{
  Json parsed_value = path;
  for (auto json_value : parsed_value)
  {
    PathElement elem;

    elem.m_FieldName = json_value["field"].get<std::string>();
    
    auto index = json_value.find("index");
    if (index == json_value.end())
    {
      elem.m_IndexType = IndexType::kNone;
    }
    else if(index->is_number())
    {
      elem.m_IndexType = IndexType::kIntIndex;
      elem.m_IntIndex = index->get<int>();
    }
    else
    {
      elem.m_IndexType = IndexType::kStringIndex;
      elem.m_StringIndex = index->get<std::string>();
    }

    m_Path.push_back(elem);
  }
}

int DocumentPath::GetSize() const
{
  return (int)m_Path.size();
}

const DocumentPath::PathElement & DocumentPath::operator[](int i) const
{
  return m_Path[i];
}
