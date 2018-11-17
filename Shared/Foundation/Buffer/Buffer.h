#pragma once

#include <memory>

#include "Foundation/Common.h"

class Buffer
{
public:
  Buffer();
  explicit Buffer(std::size_t size);
  Buffer(const void * data_to_copy, std::size_t size);

  Buffer(const Buffer & rhs) = delete;
  Buffer(Buffer && rhs) noexcept;

  Buffer & operator = (const Buffer & rhs) = delete;
  Buffer & operator = (Buffer && rhs) noexcept;

  NullOptPtr<uint8_t> Get();
  const NullOptPtr<uint8_t> Get() const;

  std::size_t GetSize() const;

private:
  std::unique_ptr<uint8_t[]> m_Data;
  std::size_t m_DataSize;
};
