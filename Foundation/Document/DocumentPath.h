#pragma once

#include <vector>
#include <string>

#include "Foundation\Document\DocumentPathElement.h"

class DocumentPath
{
public:
  DocumentPath(const std::string & path);

  int GetSize() const;
  const DocumentPathElement & operator[](int i) const;

private:
  std::vector<DocumentPathElement> m_Path;
};
