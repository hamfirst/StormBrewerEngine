#pragma once

#include <memory>
#include <unordered_map>

#include "StormExprValueProvider.h"
#include "StormExprLiteralBlock.h"
#include "StormExprValueInitBlock.h"
#include "StormExprValueInitBlockList.h"


class StormExprValueBlock
{
public:
  StormExprValueBlock();
  StormExprValueBlock(const StormExprValueInitBlock & init_block);
  StormExprValueBlock(const StormExprLiteralBlock & literal_block);

  StormExprValueBlock & operator = (StormExprValueBlock && rhs) = default;

  StormExprValue GetValue(void * base_ptr, std::size_t value_index) const;
  std::size_t GetNumValues() const;

private:

  std::unique_ptr<StormExprValueProvider[]> m_Values;
  int m_NumValues;
};
