#pragma once

#include <vector>
#include <unordered_map>

#include "StormExprValueProvider.h"

class StormExprValueInitBlock
{
public:
  std::size_t AddValue(const char * name, StormExprValueProvider && initial_val);
  int LookupValueIndexByName(const char * name) const;
  int LookupValueIndexByNameHash(uint32_t name_hash) const;

  std::size_t GetNumValues() const;
  const StormExprValueProvider & GetValueProvider(std::size_t index) const;

private:

  std::vector<StormExprValueProvider> m_Values;
  std::unordered_map<std::uint32_t, std::size_t> m_NameLookup;
};
