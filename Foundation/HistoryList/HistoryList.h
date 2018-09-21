#pragma once

#include "Foundation/Optional/NullOpt.h"

#include <vector>
#include <cstdlib>
#include <cstdio>
#include <algorithm>

template <typename T, typename TimeValue>
struct HistoryListValueContainer
{
  HistoryListValueContainer(TimeValue t, T && val) :
    m_Frame(t),
    m_Value(std::move(val))
  {

  }

  TimeValue m_Frame;
  T m_Value;
};

template <typename T, typename TimeValue>
class HistoryListIterator
{
public:

  template <typename Visitor>
  void VisitElementsForCurrentTime(Visitor && visitor)
  {
    while (m_Current != m_Last && m_Current->m_Frame < m_CurrentFrame)
    {
      m_Current++;
    }

    while (m_Current != m_Last && m_Current->m_Frame == m_CurrentFrame)
    {
      visitor(m_Current->m_Frame, m_Current->m_Value);
      m_Current++;
    }
  }

  void Advance()
  {
    m_CurrentFrame++;
  }

  bool IsComplete() const
  {
    return m_Current == m_Last;
  }

  TimeValue GetCurrentFrame() const
  {
    return m_CurrentFrame;
  }

protected:

  template <typename ListT, typename ListTimeValue>
  friend class HistoryList;

  HistoryListIterator()
  {

  }

private:

  using ValueContainer = HistoryListValueContainer<T, TimeValue>;

  ValueContainer * m_Current;
  ValueContainer * m_Last;

  TimeValue m_CurrentFrame;
};

template <typename T, typename TimeValue = int>
class HistoryList
{
public:
  HistoryList() :
    m_Values(nullptr),
    m_Capacity(0),
    m_Size(0)
  {

  }

  ~HistoryList()
  {
    if (m_Values)
    {
      while (m_Size > 0)
      {
        m_Size--;
        m_Values[m_Size].~ValueContainer();
      }

      free(m_Values);
    }
  }

  HistoryList(HistoryList && rhs)
  {
    m_Values = rhs.m_Values;
    m_Size = rhs.m_Size;
    m_Capacity = rhs.m_Capacity;

    rhs.m_Values = nullptr;
    rhs.m_Size = 0;
    rhs.m_Capacity = 0;
  }

  HistoryList & operator = (HistoryList && rhs)
  {
    if (m_Values)
    {
      free(m_Values);
    }

    m_Values = rhs.m_Values;
    m_Size = rhs.m_Size;
    m_Capacity = rhs.m_Capacity;

    rhs.m_Values = nullptr;
    rhs.m_Size = 0;
    rhs.m_Capacity = 0;
    return *this;
  }

  void Push(TimeValue frame, T && value)
  {
    if (m_Size == m_Capacity)
    {
      Grow();
    }

    if (m_Size == 0 || frame >= m_Values[m_Size - 1].m_Frame)
    {
      ValidateElement(&m_Values[m_Size]);
      new(&m_Values[m_Size]) ValueContainer{ frame, std::move(value) };
      m_Size++;
      return;
    }

    new(&m_Values[m_Size]) ValueContainer(std::move(m_Values[m_Size - 1]));

    int dst_index = 0;
    for (int index = m_Size - 1; index >= 0; --index)
    {
      if (m_Values[index].m_Frame <= frame)
      {
        dst_index = index + 1;
        break;
      }
    }

    for (int index = m_Size - 1; index > dst_index; --index)
    {
      ValidateElement(&m_Values[index]);
      m_Values[index] = std::move(m_Values[index - 1]);
    }

    ValidateElement(&m_Values[dst_index]);
    m_Values[dst_index] = ValueContainer{ frame, std::move(value) };
  }

  template <typename IterType, typename TimePred, typename ValuePred>
  void MergeList(IterType begin, IterType end, TimePred && time_pred, ValuePred && value_pred)
  {
    auto list_size = end - begin;
    if (list_size == 0)
    {
      return;
    }

    while (m_Size + list_size >= m_Capacity)
    {
      Grow();
    }

    if(m_Size == 0)
    {
      for(auto itr = begin; itr != end; ++itr)
      {
        auto & elem = (*itr);
        ValidateElement(&m_Values[m_Size]);
        new(&m_Values[m_Size]) ValueContainer( time_pred(elem), std::move(value_pred(elem)) );
        m_Size++;
      }

      return;
    }

    auto earliest = time_pred(*begin);

    // Find the index of the first spot to place the merged list
    int dst_index = 0;
    for (int index = m_Size - 1; index >= 0; --index)
    {
      if (m_Values[index].m_Frame <= earliest)
      {
        dst_index = index + 1;
        break;
      }
    }

    std::vector<ValueContainer> list_values;
    list_values.reserve(list_size);
    for(auto itr = begin; itr != end; ++itr)
    {
      auto & elem = (*itr);
      list_values.emplace_back(ValueContainer(time_pred(elem), std::move(value_pred(elem))));
    }

    auto list_begin = list_values.begin();
    auto list_end = list_values.end();

    while(true)
    {
      if (dst_index == m_Size)
      {
        // Put the rest of the elements in the list
        for(auto itr = list_begin; itr != list_end; ++itr)
        {
          auto & elem = (*itr);
          ValidateElement(&m_Values[m_Size]);
          new(&m_Values[m_Size]) ValueContainer(std::move(elem));
          m_Size++;
        }

        return;
      }

      if(begin == end)
      {
        return;
      }

      auto insert_time = list_begin->m_Frame;
      auto list_time = m_Values[dst_index].m_Frame;

      if(insert_time < list_time)
      {
        std::swap(*list_begin, m_Values[dst_index]);

        for(auto swap_itr = list_begin + 1; swap_itr != list_end; ++swap_itr)
        {
          if(swap_itr->m_Frame < list_time)
          {
            std::swap(*swap_itr, *(swap_itr - 1));
          }
          else
          {
            break;
          }
        }

        ++dst_index;
      }
      else
      {
        ++dst_index;
      }
    }
  }

  template <typename Visitor>
  void VisitElementsSince(TimeValue frame, Visitor && visitor)
  {
    if (m_Size == 0)
    {
      return;
    }

    auto elem = &m_Values[m_Size - 1];
    while (true)
    {
      if (elem->m_Frame >= frame)
      {
        if(elem == m_Values)
        {
          break;
        }
        elem--;
      }
      else
      {
        elem++;
        break;
      }
    }

    auto end = &m_Values[m_Size];
    if(elem == end && m_Size > 1)
    {
      return;
    }

    while (elem != end)
    {
      visitor(elem->m_Frame, elem->m_Value);
      elem++;
    }
  }

  HistoryListIterator<T, TimeValue> IterateElementsSince(TimeValue frame)
  {
    HistoryListIterator<T, TimeValue> iterator;
    iterator.m_Last = &m_Values[m_Size];
    iterator.m_Current = m_Values;
    iterator.m_CurrentFrame = frame;

    if (m_Size == 0)
    {
      return iterator;
    }

    auto elem = &m_Values[m_Size - 1];
    while (elem != m_Values)
    {
      if (elem->m_Frame < frame)
      {
        iterator.m_Current = elem + 1;
        break;
      }

      elem--;
    }

    return iterator;
  }

  void PurgeElementsSince(TimeValue frame)  
  {
    if (m_Size == 0)
    {
      return;
    }

    auto elem = &m_Values[m_Size - 1];
    auto end = &m_Values[-1];
    while (elem != end)
    {
      if (elem->m_Frame < frame)
      {
        break;
      }

      ValidateElement(elem);
      elem->~ValueContainer();
      elem--;
      m_Size--;
    }

  }

  void Clear()
  {
    while (m_Size)
    {
      m_Size--;
      m_Values[m_Size].~ValueContainer();
    }
  }

  T * GetTailElement()
  {
    if (m_Size == 0)
    {
      return nullptr;
    }

    return &m_Values[m_Size - 1].m_Value;
  }

protected:

  void Grow()
  {
    auto new_capacity = m_Capacity == 0 ? 128 : m_Capacity * 2;
    auto new_values = (ValueContainer *)malloc(new_capacity * sizeof(ValueContainer));

    for (auto ptr = m_Values, dst = new_values, end = m_Values + m_Size; ptr != end; ++ptr, ++dst)
    {
      new(dst) ValueContainer(std::move(*ptr));
    }

    free(m_Values);
    m_Values = new_values;
    m_Capacity = new_capacity;
  }

  void ValidateElement(NotNullPtr<HistoryListValueContainer<T, TimeValue>> ptr)
  {
#ifdef _DEBUG
    ASSERT(ptr >= m_Values && ptr < m_Values + m_Capacity, "Writing to invalid location");
#endif
  }

private:

  using ValueContainer = HistoryListValueContainer<T, TimeValue>;

  NotNullPtr<ValueContainer> m_Values;
  int m_Size;
  int m_Capacity;
};

