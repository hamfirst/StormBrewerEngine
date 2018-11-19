
#include "StormExprValueBlockList.h"
#include "StormExprValueBlock.h"
#include "StormExprValueInitBlockList.h"


StormExprValueBlockList::StormExprValueBlockList(StormExprLiteralBlockBuilder && literal_builder, StormExprValueInitBlockList & block_list) :
  m_NumBlocks(block_list.m_ValueBlocks.size() + 1),
  m_LiteralBlock(std::move(literal_builder)),
  m_Blocks(std::make_unique<StormExprValueBlock[]>(block_list.m_ValueBlocks.size() + 1)),
  m_BaseBlocks(std::make_unique<void *[]>(block_list.m_ValueBlocks.size() + 1))
{
  m_Blocks[0] = StormExprValueBlock(m_LiteralBlock);
  m_BaseBlocks[0] = m_LiteralBlock.m_Values.get();

  for (std::size_t index = 0, end = block_list.m_ValueBlocks.size(); index < end; ++index)
  {
    m_Blocks[index + 1] = StormExprValueBlock(*block_list.m_ValueBlocks[index]);
    m_BaseBlocks[index + 1] = nullptr;
  }
}

void StormExprValueBlockList::SetBlockBasePtr(std::size_t block_index, void * base_ptr)
{
  m_BaseBlocks[block_index] = base_ptr;
}

bool StormExprValueBlockList::GetValue(int value_id, StormExprValue & outp_value) const
{
  uint32_t value_block_index = (value_id >> 24) & 0xFF;
  uint32_t value_index = value_id & 0x00FFFFFF;

  if (value_block_index >= m_NumBlocks)
  {
    return false;
  }

  if (value_index >= m_Blocks[value_block_index].GetNumValues())
  {
    return false;
  }

  outp_value = m_Blocks[value_block_index].GetValue(m_BaseBlocks[value_block_index], value_index);
  return true;
}


void StormExprValueBlockList::GetValueQuick(int value_id, StormExprValue & outp_value) const
{
  uint32_t value_block_index = (value_id >> 24) & 0xFF;
  uint32_t value_index = value_id & 0x00FFFFFF;
  outp_value = m_Blocks[value_block_index].GetValue(m_BaseBlocks[value_block_index], value_index);
}