#pragma once

#include <cstddef>
#include <memory>

#include "StormExprLiteralBlock.h"

class StormExprValueBlock;
class StormExprValue;
class StormExprValueInitBlockList;
class StormExprLiteralBlockBuilder;

class StormExprValueBlockList
{
public:
  StormExprValueBlockList(StormExprLiteralBlockBuilder && literal_builder, StormExprValueInitBlockList & block_list);

  void SetBlockBasePtr(std::size_t block_index, void * base_ptr);
  bool GetValue(int value_id, StormExprValue & outp_value) const;
  void GetValueQuick(int value_id, StormExprValue & outp_value) const;

private:

  friend class StormExprEval;

  std::size_t m_NumBlocks;

  StormExprLiteralBlock m_LiteralBlock;

  std::unique_ptr<StormExprValueBlock[]> m_Blocks;
  std::unique_ptr<void *[]> m_BaseBlocks;
};
