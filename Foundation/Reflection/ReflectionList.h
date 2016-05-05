#pragma once

#include "Foundation\Common.h"
#include "Foundation\Reflection\Reflection.h" 

template <class T>
class RArrayList
{
public:
  REFLECTION_PARENT_INFO;

  void Clear()
  {
    m_Values.clear();
  }

  void Reserve(std::size_t size)
  {
    m_Values.reserve(size);
  }

  void PushBack(const T & val)
  {
    m_Values.push_back(val);
  }

  void InsertAt(const T & val, std::size_t logical_index)
  {
    if (logical_index == m_Values.size())
    {
      m_Values.push_back(ContainerData());
      return;
    }

    m_Values.insert(m_Values.begin() + logical_index);
  }

  void RemoveAt(std::size_t logical_index)
  {
    m_Values.erase(m_Values.begin() + logical_index);
  }

  std::size_t HighestIndex()
  {
    return m_Values.size();
  }

  void Compress()
  {
  }

  auto begin()
  {
    return m_Values.begin();
  }

  auto end()
  {
    return m_Values.end();
  }

  auto begin() const
  {
    return m_Values.begin();
  }

  auto end() const
  {
    return m_Values.end();
  }

private:

  std::vector<T> m_Values;
};


template <class T>
class RSparseList
{
public:
  REFLECTION_PARENT_INFO;

  struct RSparseListIterator
  {
    RSparseListIterator(const RSparseListIterator & rhs) : m_List(rhs.m_List), m_PhysicalIndex(rhs.m_PhysicalIndex) { }

    bool operator != (const RSparseListIterator & rhs) const
    {
      if (m_List != rhs.m_List)
      {
        return true;
      }

      return m_PhysicalIndex != rhs.m_PhysicalIndex;
    }

    const std::pair<std::size_t, T &> operator *() const
    {
      std::pair<std::size_t, T &> val(m_PhysicalIndex, m_List->m_Values[m_PhysicalIndex].m_T);
      return val;
    }

    void operator++()
    {
      do
      {
        m_PhysicalIndex++;
      } while (m_PhysicalIndex < m_List->m_Values.size() && m_List->m_Values[m_PhysicalIndex].m_Valid == false);
    }

  private:

    RSparseListIterator(RSparseList<T> * list, std::size_t physical_index) : m_List(list), m_PhysicalIndex(physical_index) { }

    std::size_t m_PhysicalIndex = 0;
    RSparseList<T> * m_List;

    friend class RSparseList<T>;
  };

  struct RSparseListIteratorConst
  {
    RSparseListIteratorConst(const RSparseListIteratorConst & rhs) : m_List(rhs.m_List), m_PhysicalIndex(rhs.m_PhysicalIndex) { }

    bool operator != (const RSparseListIteratorConst & rhs) const
    {
      if (m_List != rhs.m_List)
      {
        return true;
      }

      return m_PhysicalIndex != rhs.m_PhysicalIndex;
    }

    const std::pair<std::size_t, const T &> operator *() const
    {
      std::pair<std::size_t, const T &> val(m_PhysicalIndex, m_List->m_Values[m_PhysicalIndex].m_T);
      return val;
    }

    void operator++()
    {
      do
      {
        m_PhysicalIndex++;
      } while (m_PhysicalIndex < m_List->m_Values.size() && m_List->m_Values[m_PhysicalIndex].m_Valid == false);
    }

  private:

    RSparseListIteratorConst(const RSparseList<T> * list, std::size_t physical_index) : m_List(list), m_PhysicalIndex(physical_index) { }

    std::size_t m_PhysicalIndex = 0;
    const RSparseList<T> * m_List;

    friend class RSparseList<T>;
  };

  void Clear()
  {
    m_Values.clear();
    m_HighestIndex = 0;
  }

  void Reserve(std::size_t size)
  {
    m_Values.reserve(size);
  }

  void PushBack(const T & val)
  {
    m_Values.push_back(ContainerData(val));
    m_HighestIndex = m_Values.size();
  }

  void InsertAt(const T & val, std::size_t logical_index)
  {
    m_Values.reserve(logical_index + 1);

    for (int index = m_Values.size(); index < logical_index; index++)
    {
      m_Values.push_back(ContainerData());
    }

    m_Values[logical_index] = ContainerData(val);
    m_HighestIndex = std::max(m_HighestIndex, logical_index);
  }


  void RemoveAt(std::size_t logical_index)
  {
    m_Values[logical_index].m_Valid = false;

    if (m_HighestIndex == logical_index)
    {
      for (std::size_t index = m_Values.size() - 1; index >= 0 && m_Values[index].m_Valid == false; index--)
      {
        m_HighestIndex--;
      }
    }
  }

  std::size_t HighestIndex()
  {
    return m_HighestIndex;
  }

  void Compress()
  {
    std::vector<ContainerData> new_vals;
    new_vals.reserve(m_Values.size());

    for (int index = 0; index < m_Values.size(); index++)
    {
      if (m_Values[index].m_Valid)
      {
        new_vals.push_back(ContainerData(m_Values[index].m_T));
      }
    }

    m_Values = new_vals;
  }

  RSparseListIterator begin()
  {
    int start_index = 0;
    while (start_index < m_HighestIndex && m_Values[start_index].m_Valid == false)
    {
      start_index++;
    }

    RSparseListIterator itr(this, start_index);
    return itr;
  }

  RSparseListIterator end()
  {
    RSparseListIterator itr(this, m_HighestIndex);
    return itr;
  }

  RSparseListIteratorConst begin() const
  {
    std::size_t start_index = 0;
    while (start_index < m_HighestIndex && m_Values[start_index].m_Valid == false)
    {
      start_index++;
    }

    RSparseListIteratorConst itr(this, start_index);
    return itr;
  }

  RSparseListIteratorConst end() const
  {
    RSparseListIteratorConst itr(this, m_HighestIndex);
    return itr;
  }

private:
  struct ContainerData
  {
    ContainerData()
      : m_Valid(false)
    {

    }

    ContainerData(const T & t)
      : m_T(t), m_Valid(true)
    {
      
    }

    bool m_Valid = false;
    T m_T;
  };

  std::size_t m_HighestIndex = 0;
  std::vector<ContainerData> m_Values;
};

template <class T>
class RMergeList
{
public:
  REFLECTION_PARENT_INFO;

  struct RMergeListIterator
  {
    RMergeListIterator(const RMergeListIterator & rhs) : m_List(rhs.m_List), m_PhysicalIndex(rhs.m_PhysicalIndex) { }

    bool operator != (const RMergeListIterator & rhs) const
    {
      if (m_List != rhs.m_List)
      {
        return true;
      }

      return m_PhysicalIndex != rhs.m_PhysicalIndex;
    }

    const std::pair<int, T &> operator *() const
    {
      std::pair<int, T &> val(m_List->m_Indices[m_PhysicalIndex], m_List->m_Values[m_PhysicalIndex]);
      return val;
    }

    void operator++()
    {
      m_PhysicalIndex++;
    }

  private:

    RMergeListIterator(RMergeList<T> * list, std::size_t physical_index) : m_List(list), m_PhysicalIndex(physical_index) { }

    int m_PhysicalIndex = 0;
    RMergeList<T> * m_List;

    friend class RMergeList<T>;
  };

  struct RMergeListIteratorConst
  {
    RMergeListIteratorConst(const RMergeListIteratorConst & rhs) : m_List(rhs.m_List), m_PhysicalIndex(rhs.m_PhysicalIndex) { }

    bool operator != (const RMergeListIteratorConst & rhs) const
    {
      if (m_List != rhs.m_List)
      {
        return true;
      }

      return m_PhysicalIndex != rhs.m_PhysicalIndex;
    }

    const std::pair<int, const T &> operator *() const
    {
      std::pair<int, const T &> val(m_List->m_Indices[m_PhysicalIndex], m_List->m_Values[m_PhysicalIndex]);
      return val;
    }

    void operator++()
    {
      m_PhysicalIndex++;
    }

  private:

    RMergeListIteratorConst(const RMergeList<T> * list, std::size_t physical_index) : m_List(list), m_PhysicalIndex(physical_index) { }

    int m_PhysicalIndex = 0;
    const RMergeList<T> * m_List;

    friend class RMergeList<T>;
  };

  void Clear()
  {
    m_Indices.clear();
    m_Values.clear();

    m_HighestIndex = 0;
  }

  void Reserve(std::size_t size)
  {
    m_Indices.reserve(size);
    m_Values.reserve(size);
  }

  void PushBack(const T & val)
  {
    m_Indices.push_back(m_HighestIndex);
    m_Values.push_back(val);

    m_HighestIndex++;
  }

  void InsertAt(const T & val, std::size_t logical_index)
  {
    if (logical_index == m_HighestIndex)
    {
      PushBack(val);
      return;
    }

    if (logical_index > m_HighestIndex)
    {
      m_Indices.push_back(logical_index);
      m_Values.push_back(val);
      m_HighestIndex = logical_index + 1;
      return;
    }

    size_t array_size = m_Indices.size();
    for (int test = 0; test < array_size; test++)
    {
      if (m_Indices[test] == logical_index)
      {
        m_Values[test] = val;
        return;
      }

      if (m_Indices[test] > logical_index)
      {
        m_Indices.insert(m_Indices.begin() + test, logical_index);
        m_Values.insert(m_Values.begin() + test, val);
        return;
      }
    }
  }

  // Removes the elemnt that has its index = logical_index
  void RemoveAt(std::size_t logical_index)
  {
    size_t array_size = m_Indices.size();
    for (size_t test = 0; test < array_size; test++)
    {
      if (m_Indices[test] == logical_index)
      {
        m_Indices.erase(m_Indices.begin() + test);
        m_Values.erase(m_Values.begin() + test);
        return;
      }
    }
  }

  std::size_t HighestIndex()
  {
    return m_HighestIndex;
  }

  void Compress()
  {
    for (int index = 0; index < m_Indices.size(); index++)
    {
      m_Indices[index] = index;
    }
  }

  RMergeListIterator begin()
  {
    RMergeListIterator itr(this, 0);
    return itr;
  }

  RMergeListIterator end()
  {
    RMergeListIterator itr(this, m_Values.size());
    return itr;
  }

  RMergeListIteratorConst begin() const
  {
    RMergeListIteratorConst itr(this, 0);
    return itr;
  }

  RMergeListIteratorConst end() const
  {
    RMergeListIteratorConst itr(this, m_Values.size());
    return itr;
  }

private:

  std::size_t m_HighestIndex = 0;

  std::vector<uint32_t> m_Indices;
  std::vector<T> m_Values;
};
