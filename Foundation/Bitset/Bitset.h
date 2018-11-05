#pragma once

#include "Foundation/Common.h"


template <int N, typename BufferType = uint64_t>
class StaticBitset
{
public:
  StaticBitset()
  {
    Clear();
  }

  StaticBitset(const StaticBitset<N, BufferType> & rhs)
  {
    memcpy(m_Buffer, rhs.m_Buffer, sizeof(m_Buffer));
  }

  StaticBitset<N, BufferType> & operator = (const StaticBitset<N, BufferType> & rhs)
  {
    memcpy(m_Buffer, rhs.m_Buffer, sizeof(m_Buffer));
  }


  void Set(std::size_t bit_index)
  {
    ASSERT(bit_index < N, "Accessing out of bounds bit");
    auto byte = bit_index / kBitsPerBufferObj;
    auto bit = bit_index & (kBitsPerBufferObj - 1);

    m_Buffer[byte] |= (BufferType(1) << bit);
  }

  void Set(std::size_t bit_index, bool val)
  {
    if(val)
    {
      Set(bit_index);
    }
    else
    {
      Unset(bit_index);
    }
  }

  void Unset(std::size_t bit_index)
  {
    ASSERT(bit_index < N, "Accessing out of bounds bit");
    auto byte = bit_index / kBitsPerBufferObj;
    auto bit = bit_index & (kBitsPerBufferObj - 1);

    m_Buffer[byte] &= ~(BufferType(1) << bit);
  }

  void Toggle(std::size_t bit_index)
  {
    ASSERT(bit_index < N, "Accessing out of bounds bit");
    auto byte = bit_index / kBitsPerBufferObj;
    auto bit = bit_index & (kBitsPerBufferObj - 1);

    auto bit_mask = (BufferType(1) << bit);
    if(m_Buffer[byte] & bit_mask)
    {
      m_Buffer[byte] &= ~bit_mask;
    }
    else
    {
      m_Buffer[byte] |= bit_mask;
    }
  }

  bool Get(std::size_t bit_index) const
  {
    ASSERT(bit_index < N, "Accessing out of bounds bit");
    auto byte = bit_index / kBitsPerBufferObj;
    auto bit = bit_index & (kBitsPerBufferObj - 1);

    return (m_Buffer[byte] & (BufferType(1) << bit));
  }

  void Clear()
  {
    memset(m_Buffer, 0, sizeof(kBufferSize));
  }

private:
  static const int kBitsPerBufferObj = sizeof(BufferType) * 8;
  static const int kBufferSize = (N + kBitsPerBufferObj - 1) / kBitsPerBufferObj;

  BufferType m_Buffer[kBufferSize];
};

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

  std::size_t m_NumWords;
  std::unique_ptr<uint32_t[]> m_Buffer;
  std::size_t m_NumBits;
};

