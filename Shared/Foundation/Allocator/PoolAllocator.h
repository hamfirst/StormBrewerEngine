#pragma once

#include "Foundation/Common.h"
#include "Foundation/Assert/Assert.h"

template <typename T, int BlockSize=4096>
class PoolAllocator
{
public:
  PoolAllocator()
  {
    m_FirstBlock = nullptr;
    m_Current = nullptr;
    m_Allocated = 0;
  }

  PoolAllocator(const PoolAllocator<T, BlockSize> & rhs) = delete;
  PoolAllocator(PoolAllocator<T, BlockSize> && rhs) noexcept
  {
    m_FirstBlock = rhs.m_FirstBlock;
    m_Current = rhs.m_Current;
    m_Allocated = rhs.m_Allocated;

    rhs.m_FirstBlock = nullptr;
    rhs.m_Current = nullptr;
  }

  ~PoolAllocator()
  {
    DestroyAllBlocks();
  }

  PoolAllocator<T, BlockSize> & operator = (const PoolAllocator<T, BlockSize> & rhs) = delete;
  PoolAllocator<T, BlockSize> & operator = (PoolAllocator<T, BlockSize> && rhs) noexcept
  {
    DestroyAllBlocks();

    m_FirstBlock = rhs.m_FirstBlock;
    m_Current = rhs.m_Current;
    m_Allocated = rhs.m_Allocated;

    rhs.m_FirstBlock = nullptr;
    rhs.m_Current = nullptr;
    return *this;
  }

  template <typename ... Args>
  NotNullPtr<T> Allocate(Args && argx)
  {
    if(m_Current == nullptr)
    {
      Grow();
    }

    auto ptr = m_Current;
    m_Current = m_Current->m_Next;
    ++m_Allocated;

    return new(ptr) T(std::forward<Args>(args)...);
  }

  void Deallocate(NotNullPtr<T> t)
  {
    t->~T();
    auto elem = reinterpret_cast<Elem *>(t);
    elem->m_Next = m_Current;

    --m_Allocated;
    ASSERT(m_Allocated >= 0, "Invalid deallocation");

    m_Current = elem;
  }

private:

  void Grow()
  {
    Block * block = reinterpret_cast<Block *>(malloc(sizeof(Block)));
    block->m_NextBlock = m_FirstBlock;
    m_FirstBlock = block;

    int offset = 0;
    for(int index = 0; index < kElemsPerBlock; ++index)
    {
      auto elem = reinterpret_cast<Elem *>(&block->m_BlockMem[offset]);
      elem->m_Next = m_Current;
      m_Current = elem;

      offset += kElemSize;
    }
  }

  void DestroyAllBlocks()
  {
    ASSERT(m_Allocated == 0, "Allocator being destroyed with outstanding allocations");

    while(m_FirstBlock)
    {
      auto prev = m_FirstBlock;
      m_FirstBlock = m_FirstBlock->m_NextBlock;

      free(prev);
    }

    m_Current = nullptr;
  }

private:

  struct Block
  {
    Block * m_NextBlock;
    char m_BlockMem[BlockSize - sizeof(Block *)];
  };

  struct Elem
  {
    Elem * m_Next;
  };

  static const int kElemSize = sizeof(T) < sizeof(Elem) ? sizeof(Elem) : sizeof(T);
  static const int kElemsPerBlock = sizeof(Block::m_BlockMem) / kElemSize;

  static_assert(kElemsPerBlock > 0, "Allocator element is too big to fit in block");

  Block * m_FirstBlock;
  Elem * m_Current;
  int m_Allocated;
};
