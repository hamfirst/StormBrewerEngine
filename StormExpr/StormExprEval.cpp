
#include "StormExprEval.h"
#include "StormExprEvalBuilder.h"

#include <cstring>

StormExprEval::StormExprEval(StormExprEvalBuilder && eval_builder) :
  m_BlockList(std::move(eval_builder.m_LiteralBlockBuilder), *eval_builder.m_InitBlockList)
{
  int num_ops = 0;
  for (auto & expr : eval_builder.m_Expressions)
  {
    num_ops += (int)expr.size();
  }

  m_OpList = std::make_unique<StormExprOp[]>(num_ops);
  m_Funcs = std::make_unique<std::pair<std::size_t, std::size_t>[]>(eval_builder.m_Expressions.size());

  int func_index = 0;
  int func_start = 0;
  for (auto & expr : eval_builder.m_Expressions)
  {
    memcpy(&m_OpList[func_start], expr.data(), sizeof(StormExprOp) * expr.size());
    m_Funcs[func_index] = std::make_pair(func_start, func_start + expr.size());

    func_index++;
    func_start += (int)expr.size();
  }

  m_NumFuncs = eval_builder.m_Expressions.size();
}

bool StormExprEval::EvalFloat(std::size_t function_index, float & outp_val)
{
  StormExprStack stack;
  return EvalFloat(function_index, outp_val, stack);
}

bool StormExprEval::EvalFloat(std::size_t function_index, float & outp_val, StormExprStack & stack)
{
  stack.Clear();
  if (Eval(function_index, stack) == false)
  {
    return false;
  }

  StormExprValue final_val;
  if (stack.Pop(final_val) == false)
  {
    return false;
  }

  if (final_val.GetType() != StormExprValueType::kFloat)
  {
    return false;
  }

  outp_val = final_val.GetFloatVal();
  return true;
}

bool StormExprEval::EvalString(std::size_t function_index, std::string & outp_val)
{
  StormExprStack stack;
  return EvalString(function_index, outp_val, stack);
}

bool StormExprEval::EvalString(std::size_t function_index, std::string & outp_val, StormExprStack & stack)
{
  stack.Clear();
  if (Eval(function_index, stack) == false)
  {
    return false;
  }

  StormExprValue final_val;
  if (stack.Pop(final_val) == false)
  {
    return false;
  }

  if (final_val.GetType() != StormExprValueType::kString)
  {
    return false;
  }

  outp_val = final_val.GetStringVal();
  return true;
}

void StormExprEval::SetBlockBasePtr(std::size_t block_index, void * base_ptr)
{
  m_BlockList.SetBlockBasePtr(block_index + 1, base_ptr);
}

std::size_t StormExprEval::GetNumFuncs() const
{
  return m_NumFuncs;
}

bool StormExprEval::Eval(std::size_t function_index, StormExprStack & stack)
{
  if (function_index >= m_NumFuncs)
  {
    return false;
  }

  auto & func_info = m_Funcs[function_index];

  StormExprOp * start_op = &m_OpList[func_info.first];
  StormExprOp * end_op = &m_OpList[func_info.second];

  while (start_op != end_op)
  {
    if (start_op->Func(stack, m_BlockList, start_op->m_Index))
    {
      break;
    }

    start_op++;
  }

  return true;
}
