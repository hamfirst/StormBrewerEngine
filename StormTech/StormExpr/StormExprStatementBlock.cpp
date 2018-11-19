
#include "StormExprStatementBlock.h"

void StormExprStatementBlock::PushStatementElement(StormExprStatementBlockElement && element)
{
  m_Elements.emplace_back(std::move(element));
}

const std::vector<StormExprStatementBlockElement> & StormExprStatementBlock::GetStatementList() const
{
  return m_Elements;
}

std::vector<StormExprStatementBlockElement> & StormExprStatementBlock::GetStatementList()
{
  return m_Elements;
}

std::size_t StormExprStatementBlock::GetNumElements() const
{
  return m_Elements.size();
}
