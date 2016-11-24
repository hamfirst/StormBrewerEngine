#ifndef VECTORREARANGE_H
#define VECTORREARANGE_H

#include <vector>

template <class T>
void RearrangeVector(std::vector<T> & vec, int src_index, int target_index)
{
  T val = std::move(vec[src_index]);

  vec.erase(vec.begin() + src_index);
  vec.emplace(vec.begin() + target_index, std::move(val));
}


#endif // VECTORREARANGE_H
