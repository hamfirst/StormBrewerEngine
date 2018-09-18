#pragma once

#include "Engine/EngineCommon.h"

#include "Runtime/UI/UIDef.refl.h"

#include "StormExpr/StormExprEval.h"

class UIElementExprBinding
{
public:

  UIElementExprBinding(float * f);
  UIElementExprBinding(std::string * s);

  UIElementExprBinding(const UIElementExprBinding & rhs) = default;
  UIElementExprBinding(UIElementExprBinding && rhs) = default;

  UIElementExprBinding & operator = (const UIElementExprBinding & rhs) = default;
  UIElementExprBinding & operator = (UIElementExprBinding && rhs) = default;

  void Update(int function_index, StormExprEval & eval);

private:
  UIVariableType m_Type;

  union
  {
    float * m_Float;
    std::string * m_String;
  };
};

struct UIElementExprBindingInfo
{
  std::string m_Name;
  UIElementExprBinding m_Value;
};

using UIElementExprBindingList = std::vector<UIElementExprBindingInfo>;
