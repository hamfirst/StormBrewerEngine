
#include "Foundation\Common.h"
#include "Foundation\Document\DocumentPathElement.h"


DocumentPathElement::DocumentPathElement(std::string field_name)
{
  m_FieldName = field_name;
  m_IndexType = DocumentPathIndexType::kNone;
}

DocumentPathElement::DocumentPathElement(std::string field_name, int index)
{
  m_FieldName = field_name;
  m_IndexType = DocumentPathIndexType::kIntIndex;
  m_IntIndex = index;
}

DocumentPathElement::DocumentPathElement(std::string field_name, std::string index)
{
  m_FieldName = field_name;
  m_IndexType = DocumentPathIndexType::kStringIndex;
  m_StringIndex = index;
}
