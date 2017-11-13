#pragma once

#include <Foundation/Buffer/Buffer.h>

#include <cstdio>

#if defined(_ANDROID)
#include "SDL2/SDL_rwops.h"
#endif


struct FileData final
{
#if !defined(_ANDROID)
  FILE * m_File;
#else
  SDL_RWops * m_File;
#endif

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

  void Read(const gsl::span<uint8_t> & buffer);
  void Read(const gsl::span<uint8_t> & buffer, std::size_t read_amount);
  void Write(const gsl::span<const uint8_t> & buffer, std::size_t write_amount);
  void Write(const std::string & str);

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
bool FileDelete(czstr path);

std::string FileReadFullAsString(czstr path);


