#pragma once

#include <cstddef>
#include <vector>

class StormExprValueBlock;
class StormExprValue;

class StormExprValueBlockList
{
public:
  StormExprValueBlockList() = default;
  StormExprValueBlockList(std::vector<StormExprValueBlock *> && block_list);

  bool GetValue(int value_id, StormExprValue & outp_value) const;

private:

  friend class StormExprEval;

  std::vector<StormExprValueBlock *> m_Blocks;
};
