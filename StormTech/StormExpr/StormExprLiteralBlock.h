#pragma once

#include <memory>

#include "StormExprValue.h"

class StormExprLiteralBlockBuilder;

class StormExprLiteralBlock
{
public:

  StormExprLiteralBlock(StormExprLiteralBlockBuilder && block_builder);

private:

  friend class StormExprValueBlock;
  friend class StormExprValueBlockList;

  std::unique_ptr<StormExprValue[]> m_Values;
  std::size_t m_NumValues;
};

