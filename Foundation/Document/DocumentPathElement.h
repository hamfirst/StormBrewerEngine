
#pragma once

#include <string>

enum class DocumentPathIndexType : int
{
  kNone,
  kStringIndex,
  kIntIndex
};

struct DocumentPathElement
{
  DocumentPathElement() { }
  DocumentPathElement(std::string field_name);
  DocumentPathElement(std::string field_name, int index);
  DocumentPathElement(std::string field_name, std::string index);

  std::string m_FieldName;
  std::string m_StringIndex;
  DocumentPathIndexType m_IndexType;
  int m_IntIndex;
};
