#pragma once

#include <vector>

#include "StormExprValue.h"

class StormExprStack
{
public:

  void Push(StormExprValue && value);
  bool Pop(StormExprValue & outp_value);
  bool Pop();

  float PopFloat(float default_val = 0.0f);

  void Clear();
private:

  std::vector<StormExprValue> m_Stack;
};

