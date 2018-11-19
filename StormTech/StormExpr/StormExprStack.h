#pragma once

#include <memory>

#include "StormExprValue.h"

class StormExprStack
{
public:
  StormExprStack();
  ~StormExprStack();

  void Push(StormExprValue && value);
  void PushQuick(StormExprValue && value);
  bool Pop(StormExprValue & outp_value);
  void PopQuick(StormExprValue & outp_value1);
  void PopDoubleQuick(StormExprValue & outp_value1, StormExprValue & outp_value2);
  void PopTripleQuick(StormExprValue & outp_value1, StormExprValue & outp_value2, StormExprValue & outp_value3);
  bool Pop();

  float PopFloat(float default_val = 0.0f);

  void Clear();

private:
  void Grow();

private:

  StormExprValue * m_Stack;
  std::size_t m_Size;
  std::size_t m_Capacity;
};

