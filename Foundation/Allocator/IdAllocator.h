#pragma once

#include "Foundation/Common.h"

class IdAllocator
{
public:
  IdAllocator(bool grow = true);
  explicit IdAllocator(std::size_t initial_size, bool grow = true);
  explicit IdAllocator(std::size_t initial_size, std::vector<std::size_t> & used_ids, bool grow = true);

  IdAllocator(const IdAllocator & rhs) = delete;
  IdAllocator(IdAllocator && rhs) = delete;

  IdAllocator & operator =(const IdAllocator & rhs) = delete;
  IdAllocator & operator =(IdAllocator && rhs) = delete;

  ~IdAllocator();

  std::size_t Allocate();
  void Release(std::size_t id);

  static const std::size_t kInvalidId = (std::size_t) - 1;
private:


  std::size_t * m_Ids;
  std::size_t m_Head;
  std::size_t m_Capacity;
  bool m_Grow;
};
