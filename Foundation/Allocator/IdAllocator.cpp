
#include "Foundation/Common.h"
#include "Foundation/Allocator/IdAllocator.h"


IdAllocator::IdAllocator(bool grow) :
  IdAllocator(16, grow)
{

}

IdAllocator::IdAllocator(std::size_t initial_size, bool grow) :
  m_Grow(grow)
{
  m_Ids = new std::size_t[initial_size];
  m_Head = 0;
  m_Capacity = initial_size;

  for (std::size_t index = 0, end = initial_size - 1; index < end; ++index)
  {
    m_Ids[index] = index + 1;
  }

  m_Ids[initial_size - 1] = kInvalidId;
}

IdAllocator::IdAllocator(std::size_t initial_size, std::vector<std::size_t> & used_ids, bool grow) :
  m_Grow(grow)
{
  if (initial_size < 16)
  {
    initial_size = 16;
  }

  m_Ids = new std::size_t[initial_size];
  m_Head = 0;
  m_Capacity = initial_size;

  std::size_t used_index = 0;
  std::size_t * prev_index = &m_Head;

  for (std::size_t index = 0, end = initial_size; index < end; ++index)
  {
    if (used_index < used_ids.size() && used_ids[used_index] == index)
    {
      m_Ids[index] = kInvalidId;
      used_index++;
    }
    else
    {
      *prev_index = index;
      prev_index = &m_Ids[index];
    }
  }

  *prev_index = kInvalidId;
}

IdAllocator::~IdAllocator()
{
  delete[] m_Ids;
}

std::size_t IdAllocator::Allocate()
{
  if (m_Head == kInvalidId)
  {
    if (m_Grow == false)
    {
      return kInvalidId;
    }

    auto new_ids = new std::size_t[m_Capacity * 2];

    memcpy(new_ids, m_Ids, sizeof(std::size_t) * m_Capacity);
    for (std::size_t index = m_Capacity, end = m_Capacity * 2 - 1; index < end; ++index)
    {
      new_ids[index] = index + 1;
    }

    delete[] m_Ids;
    m_Ids = new_ids;

    m_Ids[m_Capacity * 2 - 1] = kInvalidId;
    m_Head = m_Capacity;
    m_Capacity *= 2;
  }

  auto val = m_Head;
  m_Head = m_Ids[m_Head];
  m_Ids[val] = kInvalidId;
  return val;
}

void IdAllocator::Release(std::size_t id)
{
  m_Ids[id] = m_Head;
  m_Head = id;
}
