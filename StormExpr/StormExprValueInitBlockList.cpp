
#include "StormExprValueInitBlockList.h"


StormExprValueInitBlockList::StormExprValueInitBlockList(std::vector<StormExprValueInitBlock *> && value_blocks) :
  m_ValueBlocks(std::move(value_blocks))
{
  
}


int StormExprValueInitBlockList::LookupValueIndexByNameHash(uint32_t name_hash) const
{
  for(int block = 0, end = (int)m_ValueBlocks.size(); block < end; ++block)
  {
    auto & init_block = m_ValueBlocks[block];

    auto index = init_block->LookupValueIndexByNameHash(name_hash);
    if (index < 0)
    {
      continue;
    }

    uint32_t value_id = (block + 1);
    value_id <<= 24;
    value_id += index;
    return value_id;
  }

  return -1;
}
