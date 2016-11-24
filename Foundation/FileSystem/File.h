#pragma once

#include <Foundation/Buffer/Buffer.h>

#include <cstdio>

struct FileData final
{
  FILE * m_File;
  int m_FileOpenError;
  size_t m_FileLength;
};

enum class FileOpenMode
{
  kWrite,
  kRead,
};

class File final
{
public:
  File();
  File(const File & rhs) = delete;
  File(File && rhs) noexcept;
  ~File();

  File & operator = (const File & rhs) = delete;
  File & operator = (File && rhs) noexcept;

  operator bool() const;
  int GetFileOpenError() const;
  size_t GetFileLength() const;

  void Read(gsl::span<uint8_t> & buffer);
  void Read(gsl::span<uint8_t> & buffer, std::size_t read_amount);
  void Write(const gsl::span<uint8_t> & buffer, std::size_t write_amount);

  Buffer ReadFileFull();

protected:
  File(czstr path, FileOpenMode mode);

  friend File FileOpen(czstr path, FileOpenMode mode);
  friend void FileClose(File & file);

private:
  FileData m_FileData;
};

File FileOpen(czstr path, FileOpenMode mode);
void FileClose(File & file);
bool FileExists(czstr path);

std::string FileReadFullAsString(czstr path);


