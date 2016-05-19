
#pragma once

#include <string>

struct DocumentPathElement
{
  DocumentPathElement(std::string index);
  DocumentPathElement(int index);

  enum DocumentPathElementType
  {
    kStringIndex,
    kIntIndex,
  };

  DocumentPathElementType m_Type;
  std::string m_StringIndex;
  uint32_t m_IntIndex;
};
