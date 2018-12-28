#pragma once

class FileMapping
{
public:
  FileMapping();
  FileMapping(czstr file_path);

  FileMapping(const FileMapping & rhs) = delete;
  FileMapping(FileMapping && rhs);

  ~FileMapping();

  FileMapping & operator = (const FileMapping & rhs) = delete;
  FileMapping & operator = (FileMapping && rhs);

  const void * GetData() const;
  std::size_t GetLength() const;

  void Clear();

private:

  void * m_Data = nullptr;
  std::size_t m_Length = 0;
};
