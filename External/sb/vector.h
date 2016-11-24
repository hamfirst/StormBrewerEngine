#pragma once

#include <vector>
#include <algorithm>

template <class T>
bool vremove_ordered(std::vector<T> & vec, const T & elem)
{
  auto itr = std::find(vec.begin(), vec.end(), elem);
  if (itr != vec.end())
  {
    vec.erase(itr);
    return true;
  }

  return false;
}

template <class T>
bool vremove_quick(std::vector<T> & vec, const T & elem)
{
  auto itr = std::find(vec.begin(), vec.end(), elem);
  if (itr != vec.end()) 
  {
    std::iter_swap(itr, vec.end() - 1);
    vec.erase(vec.end() - 1);
    return true;
  }

  return false;
}

template <class T>
bool vremove_index_quick(std::vector<T> & vec, std::size_t index)
{
  auto itr = vec.begin() + index;
  if (itr != vec.end())
  {
    std::iter_swap(itr, vec.end() - 1);
    vec.erase(vec.end() - 1);
    return true;
  }

  return false;
}

template <class T>
bool vfind(const std::vector<T> & vec, const T & elem)
{
  auto itr = std::find(vec.begin(), vec.end(), elem);
  return (itr != vec.end());
}



