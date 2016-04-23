#pragma once

#include "Foundation\Common.h"

template <class K, class T>
class ReflectionMap
{
public:
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
