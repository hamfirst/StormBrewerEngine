#pragma once

#include "Foundation/Optional/NullOpt.h"

template <typename T, int MaxSize>
class CircularQueue
{
public:

  template <typename ... Args>
  CircularQueue(Args && ... args) :
    m_Count(0),
    m_Head(0),
    m_Tail(0),
    m_Array(reinterpret_cast<T *>(&m_Buffer[0]))
  {
    for (int index = 0; index < MaxSize; ++index)
    {
      auto * elem = (&m_Buffer[sizeof(T) * index]);
      new(&m_Array[index]) T(std::forward<Args>(args)...);
    }
  }

  CircularQueue(const CircularQueue & rhs) = delete;
  CircularQueue(CircularQueue && rhs) = delete;

  CircularQueue & operator = (const CircularQueue & rhs) = delete;
  CircularQueue & operator = (CircularQueue && rhs) = delete;

  ~CircularQueue()
  {

  }

  template <typename InputType>
  void BlockWrite(NullOptPtr<const InputType> src, int length)
  {
    while (true)
    {
      auto space_avail = MaxSize - m_Head;
      auto to_write = std::min(space_avail, length);

      auto start = src;
      auto end = src + to_write;
      auto * dst = &m_Array[m_Head];

      while (start != end)
      {
        *dst = (T)*start;
        dst++;
        start++;
      }

      m_Head += to_write;
      length -= to_write;
      src += to_write;

      m_Count += to_write;

      if (m_Head >= MaxSize)
      {
        m_Head = 0;
      }

      if (length == 0)
      {
        break;
      }
    }
  }

  int BlockRead(NotNullPtr<T> dest, int requested_length)
  {
    requested_length = std::min(requested_length, m_Count);
    requested_length = std::min(requested_length, MaxSize);

    auto top_avail = MaxSize - m_Tail;

    if (requested_length <= top_avail)
    {
      std::copy(&m_Array[m_Tail], &m_Array[m_Tail + requested_length], &dest[0]);
      m_Tail += requested_length;
    }
    else
    {
      auto initial_copy_size = (MaxSize - m_Tail);
      std::copy(&m_Array[m_Tail], &m_Array[MaxSize], &dest[0]);

      auto remainder = requested_length - initial_copy_size;
      std::copy(&m_Array[0], &m_Array[remainder], &dest[initial_copy_size]);

      m_Tail = remainder;
    }

    m_Count -= requested_length;
    return requested_length;
  }

  int BlockReadStride(NotNullPtr<T> dest, int requested_length, int stride)
  {
    requested_length = std::min(requested_length, m_Count);
    requested_length = std::min(requested_length, MaxSize);

    auto top_avail = MaxSize - m_Tail;

    if (requested_length <= top_avail)
    {
      CopyStride(&m_Array[m_Tail], dest, requested_length, stride);
      m_Tail += requested_length;
    }
    else
    {
      auto initial_copy_size = (MaxSize - m_Tail);
      CopyStride(&m_Array[m_Tail], dest, initial_copy_size, stride);

      auto remainder = requested_length - initial_copy_size;
      CopyStride(&m_Array[0], dest, remainder, stride);

      m_Tail = remainder;
    }

    m_Count -= requested_length;
    return requested_length;
  }

protected:
  void CopyStride(T * src, T * & dst, int length, int stride)
  {
    while (length)
    {
      *dst = *src;
      src++;
      dst += stride;
      length--;
    }
  }

private:

  int m_Count;
  int m_Head;
  int m_Tail;

  alignas(alignof(T)) unsigned char m_Buffer[sizeof(T[MaxSize])];
  T * m_Array;
};
