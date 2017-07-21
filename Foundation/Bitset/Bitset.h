#pragma once

#include "Foundation/Common.h"

class Bitset
{
public:
  Bitset();
  Bitset(std::size_t num_bits);
  Bitset(const Bitset & rhs);
  Bitset(Bitset && rhs);

  Bitset & operator =(const Bitset & rhs);
  Bitset & operator =(Bitset && rhs);

  void Set(std::size_t bit_index);
  void Set(std::size_t bit_index, bool val);
  void Unset(std::size_t bit_index);
  void Toggle(std::size_t bit_index);

  bool Get(std::size_t bit_index) const;

  void Clear();

private:

  std::unique_ptr<uint32_t[]> m_Buffer;
  std::size_t m_NumBits;
};

