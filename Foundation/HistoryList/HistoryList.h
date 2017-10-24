#pragma once

#include "Foundation/Optional/NullOpt.h"

#include <cstdlib>
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
      new(&m_Values[m_Size]) ValueContainer{ frame, std::move(value) };
      m_Size++;
      return;
    }

    new(&m_Values[m_Size]) ValueContainer(std::move(m_Values[m_Size - 1]));

    int dst_index = 0;
    for (int index = m_Size - 1; m_Size >= 0; --index)
    {
      if (m_Values[index].m_Frame <= frame)
      {
        dst_index = index + 1;
        break;
      }
    }

    for (int index = m_Size - 1; index > dst_index; --index)
    {
      m_Values[index] = std::move(m_Values[index - 1]);
    }

    m_Values[dst_index] = ValueContainer{ frame, std::move(value) };
  }

  template <typename IterType, typename TimePred, typename ValuePred>
  void MergeList(IterType begin, IterType end, int list_size, TimePred && time_pred, ValuePred && value_pred)
  {
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
        new(&m_Values[m_Size]) ValueContainer( time_pred(elem), std::move(value_pred(elem)) );
        m_Size++;
      }

      return;
    }

    auto earliest = time_pred(*begin);

    int dst_index = 0;
    for (int index = m_Size - 1; m_Size >= 0; --index)
    {
      if (m_Values[index].m_Frame <= earliest)
      {
        dst_index = index + 1;
        break;
      }
    }

    if (dst_index == m_Size)
    {
      for(auto itr = begin; itr != end; ++itr)
      {
        auto & elem = (*itr);
        new(&m_Values[m_Size]) ValueContainer( time_pred(elem), std::move(value_pred(elem)) );
        m_Size++;
      }

      return;
    }

    auto merge_elems = m_Size - dst_index;
    auto buffer = (ValueContainer *)malloc(sizeof(ValueContainer) * merge_elems);

    for (int index = 0, src = dst_index; index < merge_elems; ++index, ++src)
    {
      new (&buffer[index]) ValueContainer(std::move(m_Values[src]));
    }

    int buffer_index = 0;
    int list_index = 0;

    int move_elems = merge_elems;
    ValueContainer * dst = &m_Values[dst_index];

    Optional<ValueContainer> place_holder;

    while (true)
    {
      ValueContainer * src;

      if (buffer_index == merge_elems)
      {
        if (list_index == list_size)
        {
          break;
        }

        place_holder.Emplace(ValueContainer( time_pred(*begin), std::move(value_pred(*begin)) ));
        src = &place_holder.Value();
        ++begin;

        list_index++;
      }
      else if (list_index == list_size)
      {
        src = &buffer[buffer_index];
        buffer_index++;
      }
      else
      {
        if (buffer[buffer_index].m_Frame < time_pred(*begin))
        {
          src = &buffer[buffer_index];
          buffer_index++;
        }
        else
        {
          place_holder.Emplace(ValueContainer( time_pred(*begin), std::move(value_pred(*begin)) ));
          src = &place_holder.Value();
          ++begin;

          list_index++;
        }
      }

      if (move_elems)
      {
        *dst = std::move(*src);
        move_elems--;
      }
      else
      {
        new(dst) ValueContainer(std::move(*src));
      }

      dst++;
    }

    m_Size += list_size;
  }

  template <typename Visitor>
  void VisitElementsSince(TimeValue frame, Visitor && visitor)
  {
    if (m_Size == 0)
    {
      return;
    }

    auto elem = &m_Values[m_Size - 1];
    auto end = &m_Values[m_Size];
    auto start = &m_Values[-1];
    while (true)
    {
      if (elem == start)
      {
        elem++;
        break;
      }

      if (elem->m_Frame >= frame)
      {
        elem--;
      }
      else
      {
        elem++;
        break;
      }
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

private:

  using ValueContainer = HistoryListValueContainer<T, TimeValue>;

  NotNullPtr<ValueContainer> m_Values;
  int m_Size;
  int m_Capacity;
};

