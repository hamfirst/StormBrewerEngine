#pragma once

#include <vector>
#include <string>

#include "Foundation\Document\DocumentPathElement.h"

class DocumentPath
{
public:
  DocumentPath(const std::string & path);
  DocumentPath(const std::vector<DocumentPathElement> & val);
  DocumentPath(std::vector<DocumentPathElement> && val);

  int GetSize() const;
  const DocumentPathElement & operator[](int i) const;

  std::string Encode() const;

private:
  std::vector<DocumentPathElement> m_Path;
};
