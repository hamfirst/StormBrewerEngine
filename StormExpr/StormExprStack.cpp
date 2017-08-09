
#include "StormExprStack.h"

void StormExprStack::Push(StormExprValue && value)
{
  m_Stack.emplace_back(std::move(value));
}

bool StormExprStack::Pop(StormExprValue & outp_value)
{
  if (m_Stack.size() == 0)
  {
    return false;
  }

  outp_value = std::move(m_Stack.back());
  m_Stack.pop_back();
  return true;
}

bool StormExprStack::Pop()
{
  if (m_Stack.size() == 0)
  {
    return false;
  }

  m_Stack.pop_back();
  return true;
}

float StormExprStack::PopFloat(float default_val)
{
  StormExprValue out_val;
  if (Pop(out_val))
  {
    if (out_val.GetType() == StormExprValueType::kFloat)
    {
      return out_val.GetFloatVal();
    }
  }

  return default_val;
}

void StormExprStack::Clear()
{
  m_Stack.clear();
}

