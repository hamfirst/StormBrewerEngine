#pragma once

#include <atomic>
#include <memory>

#include "Foundation/Optional/Optional.h"

template <typename T>
class MessageQueue
{
public:
  MessageQueue(int size)
  {
    m_Tail = 0;
    m_Head = 0;

    m_Queue = std::make_unique<int[]>(size);
    m_Array = std::make_unique<QueueData[]>(size);
    m_Length = size;

    for (int index = 0; index < m_Length; index++)
    {
      m_Queue[index] = -1;
    }
  }

  ~MessageQueue()
  {
    for (int index = 0; index < m_Length; index++)
    {
      if (m_Array[index].m_HasData)
      {
        T * t = reinterpret_cast<T *>(m_Array[index].m_Data);
        t->~T();
      }
    }
  }

  bool Enqueue(const T & message)
  {
    int message_index = AllocateArraySlot();
    if (message_index == -1)
    {
      return false;
    }

    new (m_Array[message_index].m_Data) T(message);
    if (InsertMessageIndex(message_index) == false)
    {
      ReleaseArraySlot(message_index);
      return false;
    }

    return true;
  }

  bool Enqueue(T && message)
  {
    int message_index = AllocateArraySlot();
    if (message_index == -1)
    {
      return false;
    }

    new (m_Array[message_index].m_Data) T(std::move(message));
    if (InsertMessageIndex(message_index) == false)
    {
      message = std::move(*reinterpret_cast<T *>(m_Array[message_index].m_Data));
      ReleaseArraySlot(message_index);
      return false;
    }

    return true;
  }

  bool HasData()
  {
    return m_Tail != m_Head;
  }

  Optional<T> TryDequeue()
  {
    while (true)
    {
      int idx = m_Tail;
      if (idx == m_Head)
      {
        return Optional<T>{};
      }

      int val = m_Queue[idx];
      int new_tail = (idx + 1) % m_Length;

      if (std::atomic_compare_exchange_weak((std::atomic_int *)&m_Tail, &idx, new_tail))
      {
        m_Queue[idx] = -1;

        T * t = reinterpret_cast<T *>(m_Array[val].m_Data);

        Optional<T> output = std::move(*t);
        t->~T();

        m_Array[val].m_HasData = 0;
        return output;
      }
    }
  }

private:

  int AllocateArraySlot()
  {
    int message_index = -1;
    for (int index = 0; index < m_Length; index++)
    {
      int new_val = 1;
      int old_val = 0;
      if (std::atomic_compare_exchange_weak((std::atomic_int *)&m_Array[index].m_HasData, &old_val, new_val))
      {
        message_index = index;
        break;
      }
    }

    return message_index;
  }

  void ReleaseArraySlot(int message_index)
  {
    T * t = reinterpret_cast<T *>(m_Array[message_index].m_Data);
    t->~T();
    m_Array[message_index].m_HasData = 0;
  }

  bool InsertMessageIndex(int message_index)
  {
    while (true)
    {
      int idx = m_Head;
      int new_head = (idx + 1) % m_Length;
      if (new_head == m_Tail)
      {
        return false;
      }

      int old_val = -1;
      if (std::atomic_compare_exchange_weak((std::atomic_int *)&m_Queue[idx], &old_val, message_index))
      {
        while (true)
        {
          idx = m_Head;
          new_head = (idx + 1) % m_Length;

          if (std::atomic_compare_exchange_weak((std::atomic_int *)&m_Head, &idx, new_head))
          {
            return true;
          }
        }
      }
    }
  }

private:
  struct QueueData
  {
    std::atomic_bool m_HasData;
    char m_Data[sizeof(T)];
  };

  volatile int m_Tail;
  volatile int m_Head;
  std::unique_ptr<int[]> m_Queue;
  std::unique_ptr<QueueData[]> m_Array;
  int m_Length;
};
