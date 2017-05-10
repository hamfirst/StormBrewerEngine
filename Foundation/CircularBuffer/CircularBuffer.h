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

  }

  CircularBuffer(const CircularBuffer & rhs) = default;
  CircularBuffer(CircularBuffer && rhs) = default;

  CircularBuffer & operator = (const CircularBuffer & rhs) = default;
  CircularBuffer & operator = (CircularBuffer && rhs) = default;

  void Push(const T & t)
  {
    m_Head++;
    if (m_Head >= MaxSize)
    {
      m_Head = 0;
    }

    m_Array[m_Head] = t;
    m_Count++;
  }

  void Push(T && t)
  {
    m_Head++;
    if (m_Head >= MaxSize)
    {
      m_Head = 0;
    }

    m_Array[m_Head] = std::move(t);
    m_Count++;
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

    m_Array[history_index] = t;
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

    m_Array[history_index] = std::move(t);
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

    return &m_Array[history_index];
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

    return &m_Array[history_index];
  }

private:

  int m_Count;
  int m_Head;

  T m_Array[MaxSize];
};
