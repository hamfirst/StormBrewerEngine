
#include "Foundation/Common.h"
#include "Foundation/Bitset/Bitset.h"

Bitset::Bitset() :
  m_NumWords(0),
  m_NumBits(0)
{

}

Bitset::Bitset(std::size_t num_bits) :
  m_NumWords((num_bits + 31) / 32),
  m_Buffer(std::make_unique<uint32_t[]>(m_NumWords)),
  m_NumBits(num_bits)
{
  
}

Bitset::Bitset(const Bitset & rhs) :
  m_NumWords(rhs.m_NumWords),
  m_Buffer(std::make_unique<uint32_t[]>(m_NumWords)),
  m_NumBits(rhs.m_NumBits)
{
  memcpy(m_Buffer.get(), rhs.m_Buffer.get(), sizeof(uint32_t) * m_NumWords);
}

Bitset::Bitset(Bitset && rhs) :
  m_NumWords(rhs.m_NumWords),
  m_Buffer(std::move(rhs.m_Buffer)),
  m_NumBits(rhs.m_NumBits)
{
  rhs.m_NumBits = 0;
}

Bitset & Bitset::operator =(const Bitset & rhs)
{
  m_NumWords = rhs.m_NumWords;
  m_Buffer = std::make_unique<uint32_t[]>(rhs.m_NumWords);
  m_NumBits = rhs.m_NumBits;
  memcpy(m_Buffer.get(), rhs.m_Buffer.get(), sizeof(uint32_t) * rhs.m_NumWords);

  return *this;
}

Bitset & Bitset::operator =(Bitset && rhs)
{
  m_NumWords = rhs.m_NumWords;
  m_Buffer = std::move(rhs.m_Buffer);
  m_NumBits = rhs.m_NumBits;
  rhs.m_NumBits = 0;

  return *this;
}

void Bitset::Set(std::size_t bit_index)
{
  if (bit_index >= m_NumBits)
  {
    return;
  }

  auto word_index = bit_index >> 5;
  auto bit = bit_index & 31;

  assert(word_index < m_NumWords);

  uint32_t mask = 1 << bit_index;
  m_Buffer[word_index] |= mask;
}

void Bitset::Set(std::size_t bit_index, bool val)
{
  if (val)
  {
    Set(bit_index);
  }
  else
  {
    Unset(bit_index);
  }
}

void Bitset::Unset(std::size_t bit_index)
{
  if (bit_index >= m_NumBits)
  {
    return;
  }

  auto word_index = bit_index >> 5;
  auto bit = bit_index & 31;

  assert(word_index < m_NumWords);

  uint32_t mask = 1 << bit_index;
  m_Buffer[word_index] &= ~mask;
}

void Bitset::Toggle(std::size_t bit_index)
{
  if (bit_index >= m_NumBits)
  {
    return;
  }

  auto word_index = bit_index >> 5;
  auto bit = bit_index & 31;

  assert(word_index < m_NumWords);

  uint32_t mask = 1 << bit_index;
  m_Buffer[word_index] ^= mask;
}

bool Bitset::Get(std::size_t bit_index) const
{
  if (bit_index >= m_NumBits)
  {
    return false;
  }

  auto word_index = bit_index >> 5;
  auto bit = bit_index & 31;

  assert(word_index < m_NumWords);

  uint32_t mask = 1 << bit_index;
  return (m_Buffer[word_index] & mask) != 0;
}

void Bitset::Clear()
{
  memset(m_Buffer.get(), 0, 4 * m_NumWords);
}
