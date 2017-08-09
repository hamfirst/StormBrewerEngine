#pragma once

#include <vector>

#include "StormExprLiteralBlockBuilder.h"
#include "StormExprValueInitBlock.h"

class StormExprValueInitBlockList
{
public:
  StormExprValueInitBlockList(std::vector<StormExprValueInitBlock *> && value_blocks);

  int LookupValueIndexByNameHash(uint32_t name_hash) const;

private:

  std::vector<StormExprValueInitBlock *> m_ValueBlocks;
};

