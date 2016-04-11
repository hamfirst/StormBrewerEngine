
#include "Foundation\Common.h"
#include "Foundation\Document\DocumentPath.h"
#include "Foundation\Json\Json.h"


DocumentPath::DocumentPath(const std::string & path)
{
  Json parsed_value = path;
  for (auto json_value : parsed_value)
  {
    DocumentPathElement elem;

    elem.m_FieldName = json_value["Field"].get<std::string>();
    
    auto index = json_value.find("Index");
    if (index == json_value.end())
    {
      elem.m_IndexType = DocumentPathIndexType::kNone;
    }
    else if(index->is_number())
    {
      elem.m_IndexType = DocumentPathIndexType::kIntIndex;
      elem.m_IntIndex = index->get<int>();
    }
    else
    {
      elem.m_IndexType = DocumentPathIndexType::kStringIndex;
      elem.m_StringIndex = index->get<std::string>();
    }

    m_Path.push_back(elem);
  }
}

int DocumentPath::GetSize() const
{
  return (int)m_Path.size();
}

const DocumentPathElement & DocumentPath::operator[](int i) const
{
  return m_Path[i];
}
