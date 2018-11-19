
#include "StormExprValueInitBlock.h"
#include "StormExprHash.h"

std::size_t StormExprValueInitBlock::AddValue(const char * name, StormExprValueProvider && initial_val)
{
  auto value_index = m_Values.size();
  auto name_hash = StormExprHashString(name);

  m_Values.emplace_back(std::move(initial_val));
  m_NameLookup.emplace(std::make_pair(name_hash, value_index));
  return value_index;
}

int StormExprValueInitBlock::LookupValueIndexByName(const char * name) const
{
  auto name_hash = StormExprHashString(name);
  return LookupValueIndexByNameHash((uint32_t)name_hash);
}

int StormExprValueInitBlock::LookupValueIndexByNameHash(uint32_t name_hash) const
{
  auto itr = m_NameLookup.find(name_hash);

  if (itr == m_NameLookup.end())
  {
    return -1;
  }

  return (int)itr->second;
}

std::size_t StormExprValueInitBlock::GetNumValues() const
{
  return m_Values.size();
}

const StormExprValueProvider & StormExprValueInitBlock::GetValueProvider(std::size_t index) const
{
  return m_Values[index];
}
