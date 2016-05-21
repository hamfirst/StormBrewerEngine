
#include "Foundation\Common.h"
#include "Foundation\Document\DocumentPathElement.h"

DocumentPathElement::DocumentPathElement(std::string index)
{
  m_StringIndex = index;
  m_IntIndex = 0;
  m_Type = kStringIndex;
}

DocumentPathElement::DocumentPathElement(int index)
{
  m_IntIndex = index;
  m_Type = kIntIndex;
}
