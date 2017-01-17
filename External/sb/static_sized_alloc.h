#pragma once

#include <cstdlib>
#include <cstdint>
#include <cstring>

#include <bitset>

template <typename Type>
class StaticSizedAlloc
{
public:
  StaticSizedAlloc(std::size_t max_allocs) :
    m_MaxAllocs(max_allocs)
  {
    if (max_allocs == 0)
    {
      throw false;
    }

    m_Memory = static_cast<uint8_t *>(malloc(sizeof(Type) * m_MaxAllocs));

    std::size_t alloc_mask_size = (m_MaxAllocs + 7) / 8;
    m_AllocMask = static_cast<uint8_t *>(malloc(alloc_mask_size));

    memset(m_AllocMask, 0, alloc_mask_size);

    for (std::size_t index = 0; index < m_MaxAllocs - 1; index++)
    {
      *GetPtrAt(index) = GetAllocAt(index + 1);
    }

    *GetPtrAt(m_MaxAllocs - 1) = nullptr;
    m_Head = GetPtrAt(0);
  }

  ~StaticSizedAlloc()
  {
    for (std::size_t index = 0; index < m_MaxAllocs; index++)
    {
      if (GetAllocMask(index))
      {
        GetAllocAt(index)->~Type();
      }
    }

    free(m_Memory);
    free(m_AllocMask);
  }

  StaticSizedAlloc(const StaticSizedAlloc & rhs) = delete;
  StaticSizedAlloc(StaticSizedAlloc && rhs) = delete;

  StaticSizedAlloc & operator = (const StaticSizedAlloc & rhs) = delete;
  StaticSizedAlloc & operator = (StaticSizedAlloc && rhs) = delete;

  template <typename ... InitArgs>
  Type * Allocate(InitArgs && ... args)
  {
    void * ptr = AllocateRaw();

    try
    {
      Type * t = new (ptr) Type(std::forward<InitArgs>(args)...);
      return t;
    }
    catch (...)
    {
      FreeRaw(ptr);
      throw;
    }
  }

  void * AllocateRaw()
  {
    static_assert(sizeof(Type) >= sizeof(void *), "Allocation type is too small to alias with a pointer");

    if (m_Head == nullptr)
    {
      throw false;
    }

    std::size_t index = GetIndexAt(m_Head);

    if (GetAllocMask(index))
    {
      throw false;
    }

    void * t = m_Head;

    void ** head_ptr = reinterpret_cast<void **>(m_Head);
    void * new_head = *head_ptr;

    SetAllocMask(index);
    m_Head = new_head;

    return t;
  }

  void Free(Type * type)
  {
    type->~Type();
    FreeRaw(type);
  }

  void FreeRaw(void * ptr)
  {
    std::size_t index = GetIndexAt(ptr);
    if (GetAllocMask(index) == false)
    {
      throw false;
    }

    UnsetAllocMask(index);

    void ** head_ptr = reinterpret_cast<void **>(ptr);
    *head_ptr = m_Head;

    m_Head = ptr;
  }

  std::size_t GetAllocationId(Type * ptr)
  {
    return GetIndexAt(ptr);
  }

  Type * GetElementForId(std::size_t id)
  {
    if (id >= m_MaxAllocs)
    {
      return nullptr;
    }

    if (GetAllocMask(id) == false)
    {
      return nullptr;
    }

    return GetAllocAt(id);
  }

private:
  Type * GetAllocAt(std::size_t index)
  {
    if (index >= m_MaxAllocs)
    {
      throw false;
    }

    return reinterpret_cast<Type *>(&m_Memory[sizeof(Type) * index]);
  }

  void ** GetPtrAt(std::size_t index)
  {
    if (index >= m_MaxAllocs)
    {
      throw false;
    }

    return reinterpret_cast<void **>(&m_Memory[sizeof(Type) * index]);
  }

  std::size_t GetIndexAt(void * ptr)
  {
    Type * t = reinterpret_cast<Type *>(ptr);

    std::size_t index = static_cast<std::size_t>(t - GetAllocAt(0));
    if (index >= m_MaxAllocs)
    {
      throw false;
    }

    return index;
  }

  bool GetAllocMask(std::size_t index)
  {
    std::size_t bit = index & 0x7;
    std::size_t byte = index >> 3;

    return (m_AllocMask[byte] & static_cast<uint8_t>(1 << bit)) != 0;
  }

  void SetAllocMask(std::size_t index)
  {
    std::size_t bit = index & 0x7;
    std::size_t byte = index >> 3;

    m_AllocMask[byte] |= static_cast<uint8_t>(1 << bit);
  }

  void UnsetAllocMask(std::size_t index)
  {
    std::size_t bit = index & 0x7;
    std::size_t byte = index >> 3;

    m_AllocMask[byte] &= ~static_cast<uint8_t>(1 << bit);
  }

private:
  std::size_t m_MaxAllocs;
  void * m_Head;
  uint8_t * m_Memory;
  uint8_t * m_AllocMask;
};
