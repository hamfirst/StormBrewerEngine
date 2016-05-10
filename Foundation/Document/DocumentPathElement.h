
#pragma once

#include <string>

struct DocumentPathElement
{
  DocumentPathElement() { }
  DocumentPathElement(std::string field_name);
  DocumentPathElement(std::string field_name, int index);

  std::string m_FieldName;
  int m_Index;
};
