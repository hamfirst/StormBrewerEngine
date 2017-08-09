
#include "StormExprLiteralBlockBuilder.h"

std::size_t StormExprLiteralBlockBuilder::AddLiteral(StormExprValue && val)
{
  for(std::size_t index = 0, end = m_Values.size(); index < end; ++index)
  {
    if (m_Values[index] == val)
    {
      return index;
    }
  }

  m_Values.emplace_back(std::move(val));
  return m_Values.size() - 1;
}


