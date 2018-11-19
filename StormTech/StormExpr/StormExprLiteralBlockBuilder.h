#pragma once

#include <vector>

#include "StormExprValue.h"


class StormExprLiteralBlockBuilder
{
public:

  std::size_t AddLiteral(StormExprValue && val);

private:

  friend class StormExprLiteralBlock;

  std::vector<StormExprValue> m_Values;
};
