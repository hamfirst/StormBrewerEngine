
#include "StormExprValueBlockList.h"
#include "StormExprValueBlock.h"

StormExprValueBlockList::StormExprValueBlockList(std::vector<StormExprValueBlock *> && block_list) :
  m_Blocks(std::move(block_list))
{

}

bool StormExprValueBlockList::GetValue(int value_id, StormExprValue & outp_value) const
{
  uint32_t value_type = (value_id >> 24) & 0xFF;
  uint32_t value_index = value_id & 0x00FFFFFF;

  if (value_type >= m_Blocks.size())
  {
    return false;
  }

  if (value_index >= m_Blocks[value_type]->GetNumValues())
  {
    return false;
  }

  outp_value = m_Blocks[value_type]->GetValue(value_index);
  return true;
}
