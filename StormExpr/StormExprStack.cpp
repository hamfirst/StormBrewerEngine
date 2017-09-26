
#include "StormExprStack.h"  

#include <cstdlib>
#include <cstring>

StormExprStack::StormExprStack()
{
  m_Capacity = 8;
  m_Size = 0;
  m_Stack = (StormExprValue *)malloc(sizeof(StormExprValue) * m_Capacity);
}

StormExprStack::~StormExprStack()
{
  Clear();
  free(m_Stack);
}

void StormExprStack::Push(StormExprValue && value)
{
  if (m_Size == m_Capacity)
  {
    Grow();
  }

  new (&m_Stack[m_Size]) StormExprValue(std::forward<StormExprValue>(value));
  m_Size++;
}

void StormExprStack::PushQuick(StormExprValue && value)
{
  if (m_Size == m_Capacity)
  {
    Grow();
  }

  m_Stack[m_Size].CopyQuick(value);
  m_Size++;
}

bool StormExprStack::Pop(StormExprValue & outp_value)
{
  if (m_Size == 0)
  {
    return false;
  }

  m_Size--;
  outp_value = std::move(m_Stack[m_Size]);
  return true;
}

void StormExprStack::PopQuick(StormExprValue & outp_value1)
{
  m_Size--;
  outp_value1.CopyQuick(m_Stack[m_Size]);
}

void StormExprStack::PopDoubleQuick(StormExprValue & outp_value1, StormExprValue & outp_value2)
{
  m_Size--;
  outp_value1.CopyQuick(m_Stack[m_Size]);
  m_Size--;
  outp_value2.CopyQuick(m_Stack[m_Size]);
}

void StormExprStack::PopTripleQuick(StormExprValue & outp_value1, StormExprValue & outp_value2, StormExprValue & outp_value3)
{
  m_Size--;
  outp_value1.CopyQuick(m_Stack[m_Size]);
  m_Size--;
  outp_value2.CopyQuick(m_Stack[m_Size]);
  m_Size--;
  outp_value3.CopyQuick(m_Stack[m_Size]);
}

bool StormExprStack::Pop()
{
  if (m_Size == 0)
  {
    return false;
  }

  m_Size--;
  m_Stack[m_Size].~StormExprValue();
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
  while (m_Size != 0)
  {
    m_Size--;
    m_Stack[m_Size].~StormExprValue();
  }
}

void StormExprStack::Grow()
{
  m_Capacity *= 2;

  auto new_stack = (StormExprValue *)malloc(sizeof(StormExprValue) * m_Capacity);
  memcpy(new_stack, m_Stack, sizeof(StormExprValue) * m_Size);

  free(m_Stack);
  m_Stack = new_stack;
}

