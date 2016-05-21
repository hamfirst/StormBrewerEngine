#pragma once

#include "Foundation\Common.h"
#include "Foundation\Reflection\Reflection.h"

template <class K, class T>
class ReflectionMap
{
public:
  REFLECTION_CHANGE_NOTIFIER_INFO;

  bool operator == (const ReflectionMap<K, T> & rhs) const
  {
    if (rhs.Size() != this->Size())
    {
      return false;
    }

    auto it1 = rhs.begin();
    auto it2 = this->begin();

    auto last = this->end();
    while (it2 != last)
    {
      if (it1->first == it2->first && it1->second == it2->second)
      {
        ++it1;
        ++it2;
        continue;
      }

      return false;
    }

    return true;
  }

  void Clear()
  {
    m_Values.clear();
  }

  void Reserve(size_t size)
  {
    m_Values.reserve(size);
  }

  void Set(const K & k, T && t)
  {
    m_Values.insert_or_assign(k, t);
  }

  void Remove(const K & k)
  {
    auto itr = m_Values.find(k);
    if (itr == m_Values.end())
    {
      return;
    }

    m_Values.erase(itr);
  }

  Optional<T> Get(const K & k)
  {
    auto itr = m_Values.find(k);
    if (itr == m_Values.end())
    {
      return Optional<T>();
    }

    return itr->second;
  }

  T & operator [] (const K & k)
  {
    return m_Values[k];
  }

  std::size_t Size() const
  {
    return m_Values.size();
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

public:
  std::unordered_map<K, T> m_Values;
};
