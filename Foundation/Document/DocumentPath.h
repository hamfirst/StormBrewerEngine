#pragma once

#include <vector>
#include <string>

class DocumentPath
{
public:
  DocumentPath(const std::string & path);

  enum IndexType : int
  {
    kFieldName,
    kIndex,
  };

  struct PathElement
  {
    IndexType m_Type;
    std::string m_Data;
  };

  int GetSize();
  PathElement & operator[](int i);

private:
  std::vector<PathElement> m_Path;
};
