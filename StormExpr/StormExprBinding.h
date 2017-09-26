#pragma once

#include <vector>

#include "StormExprEval.h"

class StormExprBinding
{
public:

  StormExprBinding(void * base_ptr, float * f);
  StormExprBinding(void * base_ptr, std::string * s);

  StormExprBinding(const StormExprBinding & rhs) = default;
  StormExprBinding(StormExprBinding && rhs) = default;

  StormExprBinding & operator = (const StormExprBinding & rhs) = default;
  StormExprBinding & operator = (StormExprBinding && rhs) = default;

  void Update(int function_index, StormExprEval & eval, void * base_ptr);
  void Update(int function_index, StormExprEval & eval, void * base_ptr, StormExprStack & stack);

private:

  StormExprValueType m_Type;
  ptrdiff_t m_BaseOffset;
};

struct StormExprBindingInfo
{
  std::string m_Name;
  StormExprBinding m_Value;
};

using StormExprBindingList = std::vector<StormExprBindingInfo>;
