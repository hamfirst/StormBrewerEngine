#pragma once

#include <vector>
#include <cstdint>

#include <sb/vector.h>

#include "Foundation/Handle/Handle.h"
#include "Foundation/Optional/NullOpt.h"

template <class T>
class HandleList
{
public:
  explicit HandleList(int reserve_size = 2048)
  {
    m_List.reserve(reserve_size);
  }

  HandleList(const HandleList<T> & rhs) = delete;
  HandleList(HandleList<T> && rhs) = delete;

  HandleList & operator =(const HandleList<T> & rhs) = delete;
  HandleList & operator =(HandleList<T> && rhs) = delete;

  ~HandleList()
  {
    for (int index = (int)m_List.size() - 1; index >= 0; index--)
    {
      auto & elem = m_List[index];
      if (elem.m_Handle.m_Valid)
      {
        FreeHandleInternal(index);
      }
    }
  }

  template <typename ... InitArgs>
  Handle AllocateElem(InitArgs && ... args)
  {
    auto itr = m_List.begin() + m_LastInsert;
    auto size = m_List.size();

    if (m_FreeCount > 0)
    {
      while (size)
      {
        if (itr == m_List.end())
        {
          itr = m_List.begin();
          m_LastInsert = 0;
        }

        m_LastInsert++;
        if (itr->m_Handle.m_Valid == 0)
        {
          itr->m_Handle.m_Valid = 1;
          m_FreeCount--;
          new (itr->m_Buffer) T(std::forward<InitArgs>(args)...);
          return itr->m_Handle;
        }

        itr++;
        size--;
      }
    }

    m_List.emplace_back();
    auto & elem = m_List.back();

    elem.m_Handle.m_Valid = 1;
    elem.m_Handle.m_Index = m_List.size() - 1;
    elem.m_Handle.m_Gen = 0;
    new (elem.m_Buffer) T(std::forward<InitArgs>(args)...);
    return elem.m_Handle;
  }

  void FreeElem(Handle handle)
  {
    if (handle.m_Valid == 0)
    {
      return;
    }

    int index = handle.m_Index;
    if (m_List[index].m_Handle.m_Valid == false || m_List[index].m_Handle.m_Gen != handle.m_Gen)
    {
      return;
    }

    FreeHandleInternal(index);
  }

  NullOptPtr<T> Resolve(Handle handle)
  {
    if (handle.m_Valid == 0)
    {
      return nullptr;
    }

    int index = handle.m_Index;
    if (index >= (int)m_List.size())
    {
      return nullptr;
    }

    if (m_List[index].m_Handle.m_Valid == false || m_List[index].m_Handle.m_Gen != handle.m_Gen)
    {
      return nullptr;
    }

    T * t = reinterpret_cast<T *>(m_List[index].m_Buffer);
    return t;
  }

  std::size_t GetNumHandles() const
  {
    std::size_t handle_count = 0;
    for (auto & elem : m_List)
    {
      if (elem.m_Handle.m_Valid)
      {
        handle_count++;
      }
    }

    return handle_count;
  }

  template <typename Callable>
  void VisitEach(Callable && callable)
  {
    for (auto & elem : m_List)
    {
      if (elem.m_Handle.m_Valid)
      {
        callable(elem.m_Handle, *reinterpret_cast<T *>(elem.m_Buffer));
      }
    }
  }

  template <typename Callable>
  void Filter(Callable && callable)
  {
    for(int index = (int)m_List.size() - 1; index >= 0; index--)
    {
      auto & elem = m_List[index];
      if (elem.m_Handle.m_Valid)
      {
        if (callable(elem.m_Handle, *reinterpret_cast<T *>(m_List[index].m_Buffer)) == false)
        {
          FreeHandleInternal(index);
        }
      }
    }
  }

  void ReleaseAll()
  {
    for (int index = (int)m_List.size() - 1; index >= 0; index--)
    {
      auto & elem = m_List[index];
      if (elem.m_Handle.m_Valid)
      {
        FreeHandleInternal(index);
      }
    }
  }

private:

  void FreeHandleInternal(int index)
  {
    m_List[index].m_Handle.m_Valid = 0;
    int gen = m_List[index].m_Handle.m_Gen + 1;
    if (gen == 128)
    {
      gen = 0;
    }

    m_List[index].m_Handle.m_Gen = gen;

    T * t = reinterpret_cast<T *>(m_List[index].m_Buffer);
    t->~T();

    m_LastInsert = index;
    m_FreeCount++;
  }

private:

  struct ContainerData
  {
    Handle m_Handle;
    uint8_t m_Buffer[sizeof(T)];
  };

  std::vector<ContainerData> m_List;
  int m_LastInsert = 0;
  int m_FreeCount = 0;
};

