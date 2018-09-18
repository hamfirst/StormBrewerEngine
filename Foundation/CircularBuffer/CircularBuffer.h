#pragma once

#include "Foundation/Optional/NullOpt.h"

template <typename T, int MaxSize>
class CircularBuffer
{
public:
  
  CircularBuffer() :
    m_Count(0),
    m_Head(-1)
  {
    for (int index = 0; index < MaxSize; ++index)
    {
      m_Valid[index] = false;
    }
  }

  CircularBuffer(const CircularBuffer<T, MaxSize> & rhs) = delete;
  CircularBuffer(CircularBuffer<T, MaxSize> && rhs) = delete;

  CircularBuffer & operator = (const CircularBuffer<T, MaxSize> & rhs) = delete;
  CircularBuffer & operator = (CircularBuffer<T, MaxSize> && rhs) = delete;

  ~CircularBuffer()
  {
    Clear();
  }

  void Clear()
  {
    if (m_Count >= MaxSize)
    {
      for (int index = 0; index < MaxSize; ++index)
      {
        auto v = Val(index);
        v->~T();
      }
    }
    else
    {
      while (m_Count)
      {
        auto v = Val(m_Head);
        v->~T();

        m_Head--;
        m_Count--;

        if (m_Head < 0)
        {
          m_Head += MaxSize;
        }
      }
    }

    for (int index = 0; index < MaxSize; ++index)
    {
      m_Valid[index] = false;
    }

    m_Count = 0;
    m_Head = -1;
  }

  template <typename ... InitArgs>
  void Push(InitArgs && ... args)
  {
    m_Head++;
    if (m_Head >= MaxSize)
    {
      m_Head = 0;
    }

    auto v = Val(m_Head);

    m_Count++;
    if (m_Count > MaxSize)
    {
      ASSERT(m_Valid[m_Head], "Assigning element that wasn't allocated");
      *v = T(std::forward<InitArgs>(args)...);
    }
    else
    {
      ASSERT(!m_Valid[m_Head], "Constructing element that was allocated");
      new (v) T(std::forward<InitArgs>(args)...);
    }

    m_Valid[m_Head] = true;
  }

  template <typename ... InitArgs>
  void ReplaceTop(InitArgs && ... args)
  {
    ASSERT(m_Count > 0, "Can't replace top on empty list");
    auto v = Val(m_Head);

    *v = T(std::forward<InitArgs>(args)...);
  }

  void SetAt(const T & t, int history_index)
  {
    if (history_index < 0 || history_index >= m_Count || history_index >= MaxSize)
    {
      return;
    }

    history_index = m_Head - history_index;
    if (history_index < 0)
    {
      history_index += MaxSize;
    }

    *Val(history_index) = t;
  }

  void SetAt(T && t, int history_index)
  {
    if (history_index < 0 || history_index >= m_Count || history_index >= MaxSize)
    {
      return;
    }

    history_index = m_Head - history_index;
    if (history_index < 0)
    {
      history_index += MaxSize;
    }

    *Val(history_index) = std::move(t);
  }

  NullOptPtr<T> Get(int history_index = 0)
  {
    if (history_index < 0 || history_index >= m_Count || history_index >= MaxSize)
    {
      return nullptr;
    }

    history_index = m_Head - history_index;
    if (history_index < 0)
    {
      history_index += MaxSize;
    }

    return Val(history_index);
  }

  NullOptPtr<const T> Get(int history_index = 0) const
  {
    if (history_index < 0 || history_index >= m_Count || history_index >= MaxSize)
    {
      return nullptr;
    }

    history_index = m_Head - history_index;
    if (history_index < 0)
    {
      history_index += MaxSize;
    }

    return Val(history_index);
  }

  void Purge(int count)
  {
    if (count >= m_Count)
    {
      Clear();
      return;
    }

    ASSERT(m_Head != -1, "Invalid state");

    m_Count = std::min(m_Count, MaxSize);
    while (count)
    {
      ASSERT(m_Valid[m_Head], "Purging non allocated element");
      auto v = Val(m_Head);
      v->~T();

      m_Valid[m_Head] = false;

      m_Head--;
      m_Count--;
      count--;

      if (m_Head < 0)
      {
        m_Head += MaxSize;
      }
    }
  }

  std::size_t Count() const
  {
    return (std::size_t)std::min(MaxSize, m_Count);
  }

private:

  inline T * Val(int index)
  {
    auto arr = reinterpret_cast<T *>(&m_Buffer[0]);
    return &arr[index];
  }

  int m_Count;
  int m_Head;

  alignas(alignof(T)) unsigned char m_Buffer[sizeof(T[MaxSize])];
  bool m_Valid[MaxSize];
};
