
#include "Foundation/FileSystem/FileMapping.h"
#include "Foundation/FileSystem/File.h"

#ifdef _LINUX
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#endif

FileMapping::FileMapping()
{

}

FileMapping::FileMapping(czstr file_path)
{
#ifdef _LINUX
  auto fd = open(file_path, O_RDONLY);
  struct stat s = {};
  fstat(fd, &s);

  if(s.st_size == 0)
  {
    m_Data = nullptr;
    m_Length = 0;
    return;
  }

  m_Length = static_cast<std::size_t>(s.st_size);
  m_Data = mmap(nullptr, m_Length, PROT_READ, 0, fd, 0);
#else

  auto file = FileOpen(file_path, FileOpenMode::kRead);

  if(file.GetFileOpenError())
  {
    m_Data = nullptr;
    m_Length = 0;
    return;
  }

  m_Data = malloc(file.GetFileLength());
  m_Length = file.GetFileLength();

  file.Read(gsl::make_span(static_cast<uint8_t *>(m_Data), m_Length));

#endif
}

FileMapping::FileMapping(FileMapping && rhs)
{
  m_Data = rhs.m_Data;
  m_Length = rhs.m_Length;

  rhs.m_Data = nullptr;
  rhs.m_Length = 0;
}

FileMapping::~FileMapping()
{
  Clear();
}

FileMapping & FileMapping::operator = (FileMapping && rhs)
{
  m_Data = rhs.m_Data;
  m_Length = rhs.m_Length;

  rhs.m_Data = nullptr;
  rhs.m_Length = 0;
  return *this;
}

const void * FileMapping::GetData() const
{
  return m_Data;
}

std::size_t FileMapping::GetLength() const
{
  return m_Length;
}

void FileMapping::Clear()
{
#ifdef _LINUX
  if(m_Data)
  {
    munmap(m_Data, m_Length);
    m_Data = nullptr;
    m_Length = 0;
  }
#else

  if(m_Data)
  {
    free(m_Data);
    m_Data = nullptr;
    m_Length = 0;
  }
#endif
}
