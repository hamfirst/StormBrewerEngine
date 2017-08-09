
#include "Engine/EngineCommon.h"
#include "Engine/UI/UIElementExprBinding.h"

UIElementExprBinding::UIElementExprBinding(float * f)
{
  m_Type = UIVariableType::kFloat;
  m_Float = f;
}

UIElementExprBinding::UIElementExprBinding(std::string * s)
{
  m_Type = UIVariableType::kString;
  m_String = s;
}

void UIElementExprBinding::Update(int function_index, StormExprEval & eval)
{
  switch (m_Type)
  {
  case UIVariableType::kFloat:
    {
      float val;
      if (eval.EvalFloat(function_index, val))
      {
        *m_Float = val;
      }
      break;
    }
  case UIVariableType::kString:
    {
      std::string val;
      if (eval.EvalString(function_index, val))
      {
        *m_String = std::move(val);
      }
      break;
    }
  }
}
