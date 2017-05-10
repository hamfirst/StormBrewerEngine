#pragma once

#include <memory>

#include "Delegate.h"
#include "DelegateLink.h"

#include "Foundation/Optional/Optional.h"

template <typename ReturnType, typename ... Args>
class DelegateLink;

template <typename ReturnType, typename ... Args>
class DelegateList
{
public:
  DelegateList() :
    m_DelegateList(nullptr)
  {

  }

  ~DelegateList()
  {
    if (m_DelegateList)
    {
      for (int index = 0; index < m_ListSize; index++)
      {
        m_DelegateList[index].~Optional<Delegate<ReturnType, Args...>>();
      }

      free(m_DelegateList);
    }
  }

  DelegateList(const DelegateList & rhs) = delete;
  DelegateList(DelegateList && rhs) = delete;

  DelegateList & operator = (const DelegateList & rhs) = delete;
  DelegateList & operator = (DelegateList && rhs) = delete;

  template <typename ... DelegateParams>
  DelegateLink<ReturnType, Args...> AddDelegate(DelegateParams && ... params)
  {
    int delegate_index = AddDelegateInternal(Delegate<ReturnType, Args...>(std::forward<DelegateParams>(params)...));
    return DelegateLink<ReturnType, Args...>(delegate_index, this);
  }

  void Call(Args ... args)
  {
    for (int index = 0; index < m_ListSize; index++)
    {
      if (m_DelegateList[index])
      {
        m_DelegateList[index]->Call(args...);
      }
    }
  }

private:

  template <typename, typename ...>
  friend class DelegateLink;

  int AddDelegateInternal(Delegate<ReturnType, Args...> && del)
  {
    if (m_FreeSize == 0)
    {
      int new_list_size = m_ListSize * 2;
      if (new_list_size == 0)
      {
        new_list_size = 1;
      }

      if (new_list_size == 2)
      {
        new_list_size = 8;
      }

      auto new_mem = (Optional<Delegate<ReturnType, Args...>> *)malloc(sizeof(Optional<Delegate<ReturnType, Args...>>) * new_list_size);
      for (int index = 0; index < m_ListSize; index++)
      {
        new (&new_mem[index]) Optional<Delegate<ReturnType, Args...>>(std::move(m_DelegateList[index]));
        m_DelegateList[index].~Optional<Delegate<ReturnType, Args...>>();
      }

      for (int index = m_ListSize + 1; index < new_list_size; index++)
      {
        new (&new_mem[index]) Optional<Delegate<ReturnType, Args...>>();
      }

      int insert_index = m_ListSize;
      new(&new_mem[insert_index]) Optional<Delegate<ReturnType, Args...>>(std::move(del));

      m_FreeSize = new_list_size - m_ListSize - 1;
      m_ListSize = new_list_size;

      if (m_DelegateList)
      {
        free(m_DelegateList);
      }

      m_DelegateList = new_mem;
      return insert_index;
    }

    m_FreeSize--;
    for (int index = m_ListSize - 1; index >= 0; index--)
    {
      if (m_DelegateList[index])
      {
        continue;
      }

      m_DelegateList[index] = del;
      return index;
    }

    // We should never get here
    throw false;
  }

  void RemoveDelegateInternal(int index)
  {
    if (m_DelegateList[index])
    {
      m_DelegateList[index] = {};
      m_FreeSize++;
      return;
    }

    // We should never get here
    throw false;
  }

private:
  Optional<Delegate<ReturnType, Args...>> * m_DelegateList;
  int m_ListSize = 0;
  int m_FreeSize = 0;
};
