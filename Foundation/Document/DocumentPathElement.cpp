
#include "Foundation\Common.h"
#include "Foundation\Document\DocumentPathElement.h"


DocumentPathElement::DocumentPathElement(std::string field_name)
{
  m_FieldName = field_name;
  m_Index = 0;
}

DocumentPathElement::DocumentPathElement(std::string field_name, int index)
{
  m_FieldName = field_name;
  m_Index = 0;
}
