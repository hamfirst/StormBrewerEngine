#pragma once

#include <vector>

#include "StormExprStatementBlockElement.h"

class StormExprStatementBlock
{
public:

  void PushStatementElement(StormExprStatementBlockElement && element);

  const std::vector<StormExprStatementBlockElement> & GetStatementList() const;
  std::vector<StormExprStatementBlockElement> & GetStatementList();
  std::size_t GetNumElements() const;

private:
  
  std::vector<StormExprStatementBlockElement> m_Elements;
};
