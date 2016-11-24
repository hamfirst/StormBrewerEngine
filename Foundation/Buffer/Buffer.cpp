
#include "Foundation/Common.h"
#include "Foundation/Buffer/Buffer.h"


Buffer::Buffer() :
  m_DataSize(0)
{

}

Buffer::Buffer(std::size_t size)
{
  m_Data = std::make_unique<uint8_t[]>(size);
  m_DataSize = size;
}

Buffer::Buffer(void * data_to_copy, std::size_t size) :
  Buffer(size)
{
  memcpy(m_Data.get(), data_to_copy, size);
}

Buffer::Buffer(Buffer && rhs) noexcept
{
  m_Data = std::move(rhs.m_Data);
  m_DataSize = rhs.m_DataSize;

  rhs.m_DataSize = 0;
}

Buffer & Buffer::operator = (Buffer && rhs) noexcept
{
  m_Data = std::move(rhs.m_Data);
  m_DataSize = rhs.m_DataSize;

  rhs.m_DataSize = 0;
  return *this;
}

uint8_t * Buffer::Get()
{
  return m_Data.get();
}

const uint8_t * Buffer::Get() const
{
  return m_Data.get();
}

std::size_t Buffer::GetSize() const
{
  return m_DataSize;
}
