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
    kStringIndex,
    kIntIndex
  };

  struct PathElement
  {
    IndexType m_Type;
    std::string m_Data;
  };

  int GetSize() const;
  const PathElement & operator[](int i) const;

private:
  std::vector<PathElement> m_Path;
};
