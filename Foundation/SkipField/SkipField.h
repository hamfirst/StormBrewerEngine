#pragma once

#include <colony/colony.h>

#include "Foundation/Optional/NullOpt.h"
#include "Foundation/Handle/Handle.h"
#include "Foundation/SkipField/SkipFieldIterator.h"

template <typename Type>
struct SkipFieldHandleData
{
  union
  {
    Type * m_Type;
    SkipFieldHandleData<Type> * m_Next;
  };

  uint16_t m_Valid;
  uint16_t m_Generation;
};

struct SkipFieldHandleCreationData
{
  uint32_t m_Index;
  uint64_t m_Generation;
};

template <typename Type>
struct SkipFieldHandleList
{
public:

  explicit SkipFieldHandleList(int initial_size = 8) :
    m_CurrentSize(initial_size)
  {
    m_Handles = new SkipFieldHandleData<Type>[initial_size];
    for (int index = 0; index < initial_size - 1; ++index)
    {
      m_Handles[index].m_Generation = 0;
      m_Handles[index].m_Valid = 0;
      m_Handles[index].m_Next = &m_Handles[index + 1];
    }

    m_Handles[initial_size - 1].m_Generation = 0;
    m_Handles[initial_size - 1].m_Valid = 0;
    m_Handles[initial_size - 1].m_Next = nullptr;

    m_Head = &m_Handles[0];
  }

  ~SkipFieldHandleList()
  {
    delete [] m_Handles;
  }

  SkipFieldHandleCreationData AllocateHandle(NotNullPtr<Type> type)
  {
    if (m_Head == nullptr)
    {
      Grow();
    }

    auto next = m_Head->m_Next;

    SkipFieldHandleCreationData return_val;

    m_Head->m_Type = type;
    m_Head->m_Valid = 1;
    m_Head->m_Generation = (m_Head->m_Generation + 1) & 0x7F;

    return_val.m_Generation = m_Head->m_Generation;
    return_val.m_Index = (uint32_t)(m_Head - m_Handles);

    m_Head = next;
    return return_val;
  }

  bool ReleaseHandle(const Handle & handle)
  {
    auto & handle_data = m_Handles[handle.m_Index];
    if (handle_data.m_Valid == 0)
    {
      return false;
    }

    if (handle_data.m_Generation != handle.m_Gen)
    {
      return false;
    }

    handle_data.m_Valid = 0;
    handle_data.m_Next = m_Head;
    m_Head = &handle_data;
    return true;
  }

  NullOptPtr<Type> ResolveHandle(const Handle & handle)
  {
    auto & handle_data = m_Handles[handle.m_Index];
    if (handle_data.m_Valid == 0)
    {
      return nullptr;
    }

    if (handle_data.m_Generation != handle.m_Gen)
    {
      return nullptr;
    }

    return handle_data.m_Type;
  }

private:

  void Grow()
  {
    int new_size = m_CurrentSize * 2;
    SkipFieldHandleData<Type> * new_handles = new SkipFieldHandleData<Type>[new_size];

    memcpy(new_handles, m_Handles, sizeof(SkipFieldHandleData<Type>) * m_CurrentSize);
    memset(&new_handles[m_CurrentSize], 0, sizeof(SkipFieldHandleData<Type>) * m_CurrentSize);

    m_Head = nullptr;

    for (int index = m_CurrentSize * 2 - 1; index >= m_CurrentSize; --index)
    {
      if (new_handles[index].m_Valid == 0)
      {
        new_handles[index].m_Next = m_Head;
        m_Head = &new_handles[index];
      }
    }

    delete[] m_Handles;
    m_Handles = new_handles;
    m_CurrentSize = new_size;
  }

private:

  SkipFieldHandleData<Type> * m_Handles;
  SkipFieldHandleData<Type> * m_Head;

  int m_CurrentSize;
};

template <typename Type>
class SkipField
{
public:

  template <typename ... Args>
  NotNullPtr<Type> Allocate(Args && ... args)
  {
    auto result = m_Colony.emplace(std::forward<Args>(args)...);
    auto & val = (*result);

    auto handle_data = m_HandleList.AllocateHandle(&val);

    Handle handle;
    handle.m_Gen = handle_data.m_Generation;
    handle.m_Index = handle_data.m_Index;

    val.SetHandle(handle);
    val.SetIterator(*(reinterpret_cast<SkipFieldIterator *>(&result)));
    return &val;
  }

  void Release(NotNullPtr<Type> ptr)
  {
    auto itr = reinterpret_cast<const typename plf::colony<Type>::iterator *>(&ptr->GetIterator().m_Buffer);
    auto handle = ptr->GetHandle();

    if (m_HandleList.ReleaseHandle(handle))
    {
      if (m_Iterating)
      {
        m_DeadIterators.emplace_back(*itr);
      }
      else
      {
        m_Colony.erase(*itr);
      }
    }
  }

  NullOptPtr<Type> ResolveHandle(const Handle & handle)
  {
    return m_HandleList.ResolveHandle(handle);
  }

  template <typename Callable>
  void VisitAll(Callable && callable)
  {
    m_Iterating++;
    for (auto & elem : m_Colony)
    {
      callable(elem);
    }
    m_Iterating--;

    if (m_Iterating == 0)
    {
      for (auto & elem : m_DeadIterators)
      {
        m_Colony.erase(elem);
      }

      m_DeadIterators.clear();
    }
  }


private:

  plf::colony<Type> m_Colony;
  SkipFieldHandleList<Type> m_HandleList;

  int m_Iterating = 0;
  std::vector<typename plf::colony<Type>::iterator> m_DeadIterators;
};
