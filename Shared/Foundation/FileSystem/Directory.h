#pragma once

#include "Foundation/Common.h"

class DirectoryIterator
{
public:
  DirectoryIterator();
  DirectoryIterator(const char * dir);

  DirectoryIterator(const DirectoryIterator & rhs) = default;
  DirectoryIterator(DirectoryIterator && rhs) = default;

  DirectoryIterator & operator = (const DirectoryIterator & rhs) = default;
  DirectoryIterator & operator = (DirectoryIterator && rhs) = default;

  ~DirectoryIterator() = default;

  bool operator == (const DirectoryIterator & iterator) const;
  bool operator != (const DirectoryIterator & iterator) const;
  DirectoryIterator & operator ++ ();

  const std::string & operator *() const;

private:
  std::string m_CurFile;
  std::vector<std::pair<void *, std::string>> m_DirectoryHandle;
};

class DirectoryIteratorRequest
{
public:
  DirectoryIteratorRequest(const char * dir);

  DirectoryIterator & begin();
  DirectoryIterator & end();

private:
  DirectoryIterator m_Begin;
  DirectoryIterator m_End;
};


std::vector<std::string> GetFilesInDirectory(czstr path);
std::vector<std::string> GetFilesInDirectory(czstr path, czstr extension);

