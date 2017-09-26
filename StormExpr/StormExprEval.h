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
  bool EvalFloat(std::size_t function_index, float & outp_val, StormExprStack & stack);
  bool EvalString(std::size_t function_index, std::string & outp_val);
  bool EvalString(std::size_t function_index, std::string & outp_val, StormExprStack & stack);
  void SetBlockBasePtr(std::size_t block_index, void * base_ptr);

  std::size_t GetNumFuncs() const;

private:

  bool Eval(std::size_t function_index, StormExprStack & stack);


  std::unique_ptr<StormExprOp[]> m_OpList;
  std::unique_ptr<std::pair<std::size_t, std::size_t>[]> m_Funcs;

  std::size_t m_NumFuncs;

  StormExprValueBlockList m_BlockList;
};


