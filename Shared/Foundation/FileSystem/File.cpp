
#include "Foundation/Common.h"
#include "Foundation/FileSystem/File.h"

#include <errno.h>

#ifdef _MSC_VER
#define PEDANTIC_BULLSHIT
#include "Windows.h"
#endif

#ifdef _LINUX
#include "sys/stat.h"
#endif


File::File()
{
  m_FileData = {};
}

File::File(File && rhs) noexcept
{
  m_FileData = rhs.m_FileData;
  rhs.m_FileData = {};
}

File & File::operator = (File && rhs) noexcept
{
  FileClose(*this);

  m_FileData = rhs.m_FileData;
  rhs.m_FileData = {};
  return *this;
}

File::File(czstr path, FileOpenMode mode)
{
  czstr mode_str;
  switch (mode)
  {
  default:
  case FileOpenMode::kRead:
    mode_str = "rb";
    break;
  case FileOpenMode::kWrite:
    mode_str = "wb";
    break;
  }

#if !defined(_ANDROID) && !defined(_IOS)

#ifdef PEDANTIC_BULLSHIT
  m_FileData.m_File = nullptr;
  m_FileData.m_FileOpenError = fopen_s(&m_FileData.m_File, path, mode_str);
#else
  m_FileData.m_File = fopen(path, mode_str);
  m_FileData.m_FileOpenError = errno;
#endif

  if (m_FileData.m_File != nullptr)
  {
    m_FileData.m_FileOpenError = 0;

    fseek(m_FileData.m_File, 0, SEEK_END);
    m_FileData.m_FileLength = ftell(m_FileData.m_File);
    fseek(m_FileData.m_File, 0, SEEK_SET);
  }
  else
  {
    m_FileData.m_FileLength = 0;
  }
#else

  if(path[0] != '.' || path[1] != '/')
  {
    m_FileData.m_File = {};
    printf("Failed to open file %s: error - %s\n", path, SDL_GetError());
    m_FileData.m_FileOpenError = 1;
  }

#ifdef _IOS

  auto ptr = &path[2];
  auto start_filename = ptr;
  while(*ptr != 0)
  {
    if(*ptr == '/')
    {
      start_filename = ptr + 1;
    }

    ptr++;
  }

  m_FileData.m_File = SDL_RWFromFile(start_filename, mode_str);
#else
  m_FileData.m_File = SDL_RWFromFile(path + 2, mode_str);
#endif

  if(m_FileData.m_File != nullptr)
  {
    m_FileData.m_FileOpenError = 0;
    m_FileData.m_FileLength = SDL_RWsize(m_FileData.m_File);
  }
  else
  {
    printf("Failed to open file %s: error - %s\n", path + 2, SDL_GetError());
    m_FileData.m_FileOpenError = 1;
  }
#endif
}

File::~File()
{
  FileClose(*this);
}

File::operator bool() const
{
  return m_FileData.m_File != nullptr;
}

int File::GetFileOpenError() const
{
  return m_FileData.m_FileOpenError;
}

size_t File::GetFileLength() const
{
  return m_FileData.m_FileLength;
}

void File::Read(const gsl::span<uint8_t> & buffer)
{
  Read(buffer, buffer.size());
}

void File::Read(const gsl::span<uint8_t> & buffer, std::size_t read_amount)
{
  if (m_FileData.m_File == nullptr)
  {
    return;
  }

#if !defined(_ANDROID) && !defined(_IOS)
#ifdef PEDANTIC_BULLSHIT
  fread_s(buffer.data(), buffer.size(), 1, read_amount, m_FileData.m_File);
#else
  fread(buffer.data(), 1, read_amount, m_FileData.m_File);
#endif
#else
  SDL_RWread(m_FileData.m_File, buffer.data(), 1, read_amount);
#endif
}

void File::Write(const gsl::span<const uint8_t> & buffer, std::size_t write_amount)
{
  if (m_FileData.m_File == nullptr)
  {
    return;
  }

#if !defined(_ANDROID) && !defined(_IOS)
  fwrite(buffer.data(), 1, write_amount, m_FileData.m_File);
#else
  SDL_RWwrite(m_FileData.m_File, buffer.data(), 1, write_amount);
#endif
}

void File::Write(const std::string & str)
{
  if (m_FileData.m_File == nullptr)
  {
    return;
  }

#if !defined(_ANDROID) && !defined(_IOS)
  fwrite(str.data(), 1, str.length(), m_FileData.m_File);
#else
  SDL_RWwrite(m_FileData.m_File, str.data(), 1, str.length());
#endif
}

Buffer File::ReadFileFull()
{
  if (m_FileData.m_File == nullptr)
  {
    return{};
  }

  Buffer buffer(m_FileData.m_FileLength);
  Read(gsl::make_span(buffer.Get(), buffer.GetSize()));
  return buffer;
}

File FileOpen(czstr path, FileOpenMode mode)
{
  return File(path, mode);
}

void FileClose(File & file)
{
  if (file.m_FileData.m_File != nullptr)
  {
#if !defined(_ANDROID) && !defined(_IOS)
    fclose(file.m_FileData.m_File);
#else
    SDL_RWclose(file.m_FileData.m_File);
#endif

    file.m_FileData = {};
  }
}

bool FileExists(czstr path)
{
#if !defined(_ANDROID) && !defined(_IOS)
#ifdef PEDANTIC_BULLSHIT
  FILE * fp = nullptr;
  if (fopen_s(&fp, path, "rb"))
  {
    return false;
  }

  fclose(fp);
  return true;
#else
  FILE * fp = fopen(path, "rb");
  if (fp == nullptr)
  {
    return false;
  }

  fclose(fp);
  return true;
#endif
#else
  if(path[0] != '.' || path[1] != '/')
  {
    return false;
  }

  auto fp = SDL_RWFromFile(path + 2, "rb");
  if(fp == nullptr)
  {
    return false;
  }

  SDL_RWclose(fp);
  return true;
#endif
}

bool FileDelete(czstr path)
{
  return remove(path) == 0;
}

std::string FileReadFullAsString(czstr path)
{
  auto file = FileOpen(path, FileOpenMode::kRead);
  if (file.GetFileOpenError())
  {
    return{};
  }

  std::string str;
  str.resize(file.GetFileLength(), 0);

  file.Read(gsl::make_span((uint8_t *)str.data(), file.GetFileLength()));
  return str;
}


Optional<Buffer> FileReadFull(czstr path)
{
  auto file = FileOpen(path, FileOpenMode::kRead);
  if (file.GetFileOpenError())
  {
    return{};
  }

  Buffer buffer(file.GetFileLength());
  file.Read(gsl::make_span(buffer.Get(), file.GetFileLength()));
  return buffer;
}

std::time_t GetLastWriteTime(czstr path)
{
#ifdef _MSC_VER
#error implement this
#else
  struct stat attrib;
  stat(path, &attrib);

  return attrib.st_mtime;
#endif
}
