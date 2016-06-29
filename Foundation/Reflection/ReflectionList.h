#pragma once

#include "Foundation\Common.h"
#include "Foundation\Reflection\Reflection.h" 
#include "Foundation\Reflection\ReflectionChangeNotifier.h" 

template <class T>
class RArrayList
{
public:
  REFLECTION_CHANGE_NOTIFIER_INFO;

  void Clear()
  {
    m_Values.clear();
    Cleared();
  }

  void Reserve(std::size_t size)
  {
    m_Values.reserve(size);
  }

  void PushBack(const T & val)
  {
    m_Values.push_back(val);
    Appended();
  }

  void InsertAt(const T & val, std::size_t logical_index)
  {
    if (logical_index == m_Values.size())
    {
      m_Values.push_back(ContainerData());
      return;
    }

    m_Values.insert(m_Values.begin() + logical_index);
    Inserted(logical_index);
  }

  void RemoveAt(std::size_t logical_index)
  {
    m_Values.erase(m_Values.begin() + logical_index);
    Removed(logical_index);
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

  bool operator == (const RArrayList<T> & rhs) const
  {
    if (m_Values.size() != rhs.m_Values.size())
    {
      return false;
    }

    auto itr1 = begin();
    auto itr2 = rhs.begin();

    auto last = end();

    while (itr1 != last)
    {
      if (*itr1 == *itr2)
      {
        ++itr1;
        ++itr2;
        continue;
      }

      return false;
    }

    return true;
  }

private:

  void Cleared()
  {
#ifdef REFLECTION_CHANGE_NOTIFIER
    ReflectionNotifyClearArray(m_ReflectionInfo);
#endif
  }

  void Appended()
  {
#ifdef REFLECTION_CHANGE_NOTIFIER
    ReflectionParentInfo new_info;
    new_info.m_ParentInfo = &m_ReflectionInfo;
    new_info.m_ParentIndex = static_cast<uint32_t>((m_Values.size() - 1));
    new_info.m_ParentType = 0;

    SetParentInfo(m_Values[m_Values.size() - 1], new_info);

    ReflectionNotifyAppendArray(m_ReflectionInfo, ReflectValue(m_Values[m_Values.size() - 1]));
#endif
  }

  void Inserted(std::size_t logical_index)
  {
#ifdef REFLECTION_CHANGE_NOTIFIER
    ReflectionParentInfo new_info;
    new_info.m_ParentInfo = &m_ReflectionInfo;
    for (int index = logical_index; index < m_Values.size(); index++)
    {
      new_info.m_ParentIndex = index;
      SetParentInfo(m_Values[index], new_info);
    }

    ReflectionNotifyInsertArray(m_ReflectionInfo, logical_index, ReflectValue(m_Values[m_Values.size() - 1]));
#endif
  }

  void Removed(std::size_t logical_index)
  {
#ifdef REFLECTION_CHANGE_NOTIFIER
    ReflectionParentInfo new_info;
    new_info.m_ParentInfo = &m_ReflectionInfo;
    for (int index = logical_index; index < m_Values.size(); index++)
    {
      new_info.m_ParentIndex = index;
      SetParentInfo(m_Values[index], new_info);
    }

    ReflectionNotifyRemoveArray(m_ReflectionInfo, logical_index);
#endif
  }

  std::vector<T> m_Values;
};


template <class T>
class RSparseList
{
public:
  REFLECTION_CHANGE_NOTIFIER_INFO;

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

    const std::pair<std::size_t, T &> operator ->() const
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

    const std::pair<std::size_t, T &> operator ->() const
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

    Inserted(m_Values.size() - 1);
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

    Inserted(logical_index);
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

    Removed(logical_index);
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
    Compressed();
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

  bool operator == (const RSparseList<T> & rhs) const
  {
    if (m_Indices.size() != rhs.m_Indices.size())
    {
      return false;
    }

    auto itr1 = begin();
    auto itr2 = rhs.begin();

    auto last = end();

    while (itr1 != last)
    {
      if (itr1->first == itr2->first && itr1->second == itr2->second)
      {
        ++itr1;
        ++itr2;
        continue;
      }

      return false;
    }

    return true;
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

  void Cleared()
  {
#ifdef REFLECTION_CHANGE_NOTIFIER
    ReflectionNotifyClearObject(m_ReflectionInfo);
#endif
  }

  void Compressed()
  {
#ifdef REFLECTION_CHANGE_NOTIFIER
    ReflectionParentInfo new_info;
    new_info.m_ParentInfo = &m_ReflectionInfo;
    new_info.m_ParentType = 0;

    for (uint32_t index = 0; index < m_Values.size(); index++)
    {
      new_info.m_ParentIndex = index;
      SetParentInfo(m_Values[index].m_T, new_info);
    }


    ReflectionNotifyCompress(m_ReflectionInfo);
#endif
  }

  void Inserted(std::size_t logical_index)
  {
#ifdef REFLECTION_CHANGE_NOTIFIER
    ReflectionParentInfo new_info;
    new_info.m_ParentInfo = &m_ReflectionInfo;
    new_info.m_ParentType = 0;
    new_info.m_ParentIndex = logical_index;
    SetParentInfo(m_Values[logical_index].m_T, new_info);

    ReflectionNotifyInsertObject(m_ReflectionInfo, logical_index, ReflectValue(m_Values[logical_index].m_T));
#endif
  }

  void Removed(std::size_t logical_index)
  {
#ifdef REFLECTION_CHANGE_NOTIFIER
    ReflectionNotifyRemoveObject(m_ReflectionInfo, logical_index);
#endif
  }

  std::size_t m_HighestIndex = 0;
  std::vector<ContainerData> m_Values;
};

template <class T>
class RMergeList
{
public:
  REFLECTION_CHANGE_NOTIFIER_INFO;

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

    const std::pair<int, T &> operator ->() const
    {
      std::pair<int, T &> val(m_List->m_Indices[m_PhysicalIndex], m_List->m_Values[m_PhysicalIndex]);
      return val;
    }

    RMergeListIterator & operator++()
    {
      m_PhysicalIndex++;
      return *this;
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

    const std::pair<int, T &> operator ->() const
    {
      std::pair<int, T &> val(m_List->m_Indices[m_PhysicalIndex], m_List->m_Values[m_PhysicalIndex]);
      return val;
    }

    RMergeListIteratorConst & operator++()
    {
      m_PhysicalIndex++;
      return *this;
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
    Inserted(m_HighestIndex - 1, m_Indices.size() - 1);
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

      Inserted(logical_index, m_Indices.size() - 1);
      return;
    }

    size_t array_size = m_Indices.size();
    for (size_t test = 0; test < array_size; test++)
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

        Inserted(logical_index, test);
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

        Removed(logical_index);
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

    Compressed();
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

  bool operator == (const RMergeList<T> & rhs) const
  {
    if (m_Indices.size() != rhs.m_Indices.size())
    {
      return false;
    }

    auto itr1 = begin();
    auto itr2 = rhs.begin();

    auto last = end();

    while (itr1 != last)
    {
      if ((*itr1).first == (*itr2).first && (*itr1).second == (*itr2).second)
      {
        ++itr1;
        ++itr2;
        continue;
      }

      return false;
    }

    return true;
  }

private:

  void Cleared()
  {
#ifdef REFLECTION_CHANGE_NOTIFIER
    ReflectionNotifyClearObject(m_ReflectionInfo);
#endif
  }

  void Compressed()
  {
#ifdef REFLECTION_CHANGE_NOTIFIER
    ReflectionNotifyCompress(m_ReflectionInfo);
#endif
  }

  void Inserted(std::size_t logical_index, std::size_t physical_index)
  {
#ifdef REFLECTION_CHANGE_NOTIFIER
    ReflectionParentInfo new_info;
    new_info.m_ParentInfo = &m_ReflectionInfo;
    new_info.m_ParentIndex = logical_index;
    new_info.m_ParentType = 0;

    SetParentInfo(m_Values[logical_index], new_info);

    ReflectionNotifyInsertObject(m_ReflectionInfo, logical_index, ReflectValue(m_Values[physical_index]));
#endif
  }

  void Removed(std::size_t logical_index)
  {
#ifdef REFLECTION_CHANGE_NOTIFIER
    ReflectionNotifyRemoveObject(m_ReflectionInfo, logical_index);
#endif
  }

  std::size_t m_HighestIndex = 0;

  std::vector<uint32_t> m_Indices;
  std::vector<T> m_Values;
};
