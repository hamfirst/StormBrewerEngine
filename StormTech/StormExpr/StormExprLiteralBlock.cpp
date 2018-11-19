
#include "StormExprLiteralBlock.h"
#include "StormExprLiteralBlockBuilder.h"

StormExprLiteralBlock::StormExprLiteralBlock(StormExprLiteralBlockBuilder && block_builder)
{
  m_Values = std::make_unique<StormExprValue[]>(block_builder.m_Values.size());
  m_NumValues = block_builder.m_Values.size();
  
  for(std::size_t index = 0, end = block_builder.m_Values.size(); index < end; ++index)
  {
    m_Values[index] = std::move(block_builder.m_Values[index]);
  }
}

