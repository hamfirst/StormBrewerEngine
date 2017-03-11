
#include "Foundation/Common.h"
#include "Foundation/FileSystem/File.h"

#ifdef _MSC_VER
#define PEDANTIC_BULLSHIT
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
  Read(buffer, buffer.length());
}

void File::Read(const gsl::span<uint8_t> & buffer, std::size_t read_amount)
{
  if (m_FileData.m_File == nullptr)
  {
    return;
  }

#ifdef PEDANTIC_BULLSHIT
  fread_s(buffer.data(), buffer.size(), 1, read_amount, m_FileData.m_File);
#else
  fread(buffer.data(), 1, read_amount, m_FileData.m_File);
#endif
}

void File::Write(const gsl::span<const uint8_t> & buffer, std::size_t write_amount)
{
  if (m_FileData.m_File == nullptr)
  {
    return;
  }

  fwrite(buffer.data(), 1, write_amount, m_FileData.m_File);
}

void File::Write(const std::string & str)
{
  if (m_FileData.m_File == nullptr)
  {
    return;
  }

  fwrite(str.data(), 1, str.length(), m_FileData.m_File);
}

Buffer File::ReadFileFull()
{
  if (m_FileData.m_File == nullptr)
  {
    return{};
  }

  Buffer buffer(m_FileData.m_FileLength);
  Read(gsl::as_span(buffer.Get(), buffer.GetSize()));
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
    fclose(file.m_FileData.m_File);
    file.m_FileData = {};
  }
}

bool FileExists(czstr path)
{
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

  file.Read(gsl::as_span((uint8_t *)str.data(), file.GetFileLength()));
  return str;
}

