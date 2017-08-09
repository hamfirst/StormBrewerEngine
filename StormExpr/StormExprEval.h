#pragma once

#include <cstddef>

#include <memory>

#include "StormExprOps.h"
#include "StormExprLiteralBlock.h"
#include "StormExprValueBlock.h"
#include "StormExprValueBlockList.h"

class StormExprEvalBuilder;

class StormExprEval
{
public:

  StormExprEval(StormExprEvalBuilder && eval_builder);

  bool EvalFloat(std::size_t function_index, float & outp_val);
  bool EvalString(std::size_t function_index, std::string & outp_val);
  void SetBlockList(const StormExprValueBlockList & block_list);

private:

  bool Eval(std::size_t function_index, StormExprStack & stack);


  std::unique_ptr<StormExprOp[]> m_OpList;
  std::unique_ptr<std::pair<std::size_t, std::size_t>[]> m_Funcs;

  std::size_t m_NumFuncs;

  StormExprLiteralBlock m_LiteralBlock;
  StormExprValueBlock m_LiteralValues;
  StormExprValueBlockList m_BlockList;
};


