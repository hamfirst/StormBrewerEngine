
#include "Engine/EngineCommon.h"
#include "Engine/UI/UIElementExprBlock.h"

UIElementExprDynamicBlockVariable UIElementExprDynamicBlock::AddVariable(const UIDefInputVariable & var, StormExprValueInitBlock & init_block)
{
  UIElementExprDynamicBlockVariable out_var;
  out_var.m_Type = var.m_Type;
  switch ((UIVariableType)var.m_Type)
  {
  case UIVariableType::kFloat:
    out_var.m_Index = (uint16_t)m_Floats.size();
    m_Floats.push_back(0);

    init_block.AddValue(var.m_VariableName.data(), StormExprValueProvider(&m_Floats.back()));
    break;
  case UIVariableType::kString:
    out_var.m_Index = (uint16_t)m_Strings.size();
    m_Strings.emplace_back("");

    init_block.AddValue(var.m_VariableName.data(), StormExprValueProvider(&m_Strings.back()));
  }

  return out_var;
}

void UIElementExprDynamicBlock::SetVariable(const UIElementExprDynamicBlockVariable & var, float val)
{
  if (var.m_Type == UIVariableType::kFloat)
  {
    m_Floats[var.m_Index] = val;
  }
}

void UIElementExprDynamicBlock::SetVariable(const UIElementExprDynamicBlockVariable & var, const std::string & val)
{
  if (var.m_Type == UIVariableType::kString)
  {
    m_Strings[var.m_Index] = val;
  }
}

void UIElementExprDynamicBlock::SetVariable(const UIElementExprDynamicBlockVariable & var, czstr val)
{
  if (var.m_Type == UIVariableType::kString)
  {
    m_Strings[var.m_Index] = val;
  }
}

UIElementExprBinding UIElementExprDynamicBlock::GetBinding(UIElementExprDynamicBlockVariable var)
{
  switch (var.m_Type)
  {
  case UIVariableType::kFloat:
  default:
    return UIElementExprBinding(&m_Floats[var.m_Index]);
    break;
  case UIVariableType::kString:
    return UIElementExprBinding(&m_Strings[var.m_Index]);
    break;
  }
}
