#pragma once

#include <vector>
#include <string>

class DocumentPath
{
public:
  DocumentPath(const std::string & path);

  enum class IndexType : int
  {
    kNone,
    kStringIndex,
    kIntIndex
  };

  struct PathElement
  {
    std::string m_FieldName;
    IndexType m_IndexType;
    std::string m_StringIndex;
    int m_IntIndex;
  };

  int GetSize() const;
  const PathElement & operator[](int i) const;

private:
  std::vector<PathElement> m_Path;
};
