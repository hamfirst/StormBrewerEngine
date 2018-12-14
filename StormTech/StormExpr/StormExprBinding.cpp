
#include "StormExprBinding.h"

StormExprBinding::StormExprBinding(void * base_ptr, float * f)
{
  m_BaseOffset = (char *)f - (char *)base_ptr;
  m_Type = StormExprValueType::kFloat;
}

StormExprBinding::StormExprBinding(void * base_ptr, std::string * s)
{
  m_BaseOffset = (char *)s - (char *)base_ptr;
  m_Type = StormExprValueType::kString;
}

void StormExprBinding::Update(int function_index, StormExprEval & eval, void * base_ptr)
{
  switch (m_Type)
  {
  case StormExprValueType::kNothing:
    break;
  case StormExprValueType::kFloat:
    {
      float val;
      if (eval.EvalFloat(function_index, val))
      {
        auto ptr = (float *)((char *)base_ptr + m_BaseOffset);
        *ptr = val;
      }
      break;
    }
  case StormExprValueType::kString:
    {
      std::string val;
      if (eval.EvalString(function_index, val))
      {
        auto ptr = (std::string *)((char *)base_ptr + m_BaseOffset);
        *ptr = val;
      }
      break;
    }
  }
}

void StormExprBinding::Update(int function_index, StormExprEval & eval, void * base_ptr, StormExprStack & stack)
{
  switch (m_Type)
  {
  case StormExprValueType::kNothing:
    break;
  case StormExprValueType::kFloat:
    {
      float val;
      if (eval.EvalFloat(function_index, val, stack))
      {
        auto ptr = (float *)((char *)base_ptr + m_BaseOffset);
        *ptr = val;
      }
      break;
    }
  case StormExprValueType::kString:
    {
      std::string val;
      if (eval.EvalString(function_index, val, stack))
      {
        auto ptr = (std::string *)((char *)base_ptr + m_BaseOffset);
        *ptr = val;
      }
      break;
    }
  }
}
