
#include "StormExprValueBlock.h"

StormExprValueBlock::StormExprValueBlock(const StormExprValueInitBlock & init_block)
{
  auto num_vals = init_block.GetNumValues();

  m_Values = std::make_unique<StormExprValueProvider[]>(num_vals);
  for (std::size_t index = 0; index < num_vals; ++index)
  {
    m_Values[index] = init_block.GetValueProvider(index);
  }

  m_NumValues = (int)num_vals;
}

StormExprValueBlock::StormExprValueBlock(const StormExprLiteralBlock & literal_block)
{
  auto & vals = literal_block.m_Values;
  auto num_vals = literal_block.m_NumValues;

  m_Values = std::make_unique<StormExprValueProvider[]>(num_vals);
  for (std::size_t index = 0; index < num_vals; ++index)
  {
    vals[index].GetValueProvider(m_Values[index]);
  }

  m_NumValues = (int)num_vals;
}

StormExprValue StormExprValueBlock::GetValue(std::size_t value_index) const
{
  return m_Values[value_index].GetValue();
}

std::size_t StormExprValueBlock::GetNumValues() const
{
  return m_NumValues;
}
