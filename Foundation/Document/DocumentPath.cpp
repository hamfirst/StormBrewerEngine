
#include "Foundation\Common.h"
#include "Foundation\Document\DocumentPath.h"
#include "Foundation\Json\Json.h"


DocumentPath::DocumentPath(const std::string & path)
{
  Json parsed_value = path;
  for (auto elem_value : parsed_value)
  {
    int type = elem_value["Type"].get<int>();

    if (type == DocumentPathElement::kIntIndex)
    {
      int index = elem_value["Index"].get<uint32_t>();
      m_Path.emplace_back(index);
    }
    else if (type == DocumentPathElement::kStringIndex)
    {
      std::string index = elem_value["Index"].get<std::string>();
      m_Path.emplace_back(index);
    }
    else
    {
      throw std::exception("inconsistent document path");
    }
  }
}

DocumentPath::DocumentPath(const std::vector<DocumentPathElement> & val)
{
  m_Path = val;
}

DocumentPath::DocumentPath(std::vector<DocumentPathElement> && val)
{
  m_Path = val;
}

int DocumentPath::GetSize() const
{
  return (int)m_Path.size();
}

const DocumentPathElement & DocumentPath::operator[](int i) const
{
  return m_Path[i];
}

std::string DocumentPath::Encode() const
{
  Json encoded_value;
  
  for (auto elem : m_Path)
  {
    Json elem_value;
    elem_value["Type"] = elem.m_Type;

    if (elem.m_Type == DocumentPathElement::kIntIndex)
    {
      elem_value["Index"] = (int)elem.m_Type;
    }
    else if (elem.m_Type == DocumentPathElement::kStringIndex)
    {
      elem_value["Index"] = elem.m_StringIndex;
    }
    else
    {
      throw std::exception("inconsistent document path");
    }

    encoded_value.push_back(elem_value);
  }

  return encoded_value.dump();
}