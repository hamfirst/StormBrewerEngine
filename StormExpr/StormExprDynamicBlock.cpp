
#include "StormExprDynamicBlock.h"

StormExprDynamicBlockVariable StormExprDynamicBlock::AddVariable(StormExprValueType type)
{
  StormExprDynamicBlockVariable out_var;
  out_var.m_Type = type;
  switch (type)
  {
  case StormExprValueType::kFloat:
    out_var.m_Index = (uint16_t)m_Floats.size();
    m_Floats.push_back(0);
    break;
  case StormExprValueType::kString:
    out_var.m_Index = (uint16_t)m_Strings.size();
    m_Strings.emplace_back("");
    break;
  default:
    out_var.m_Index = 0;
    break;
  }

  return out_var;
}

void StormExprDynamicBlock::Link(const StormExprDynamicBlockVariable & var, const char * variable_name, StormExprValueInitBlock & float_init_block, StormExprValueInitBlock & string_init_block)
{
  switch (var.m_Type)
  {
  case StormExprValueType::kFloat:
    float_init_block.AddValue(variable_name, StormExprValueProvider(m_Floats.data(), &m_Floats[var.m_Index]));
    break;
  case StormExprValueType::kString:
    string_init_block.AddValue(variable_name, StormExprValueProvider(m_Strings.data(), &m_Strings[var.m_Index]));
    break;
  }
}

void StormExprDynamicBlock::SetVariable(const StormExprDynamicBlockVariable & var, float val)
{
  if (var.m_Type == StormExprValueType::kFloat)
  {
    m_Floats[var.m_Index] = val;
  }
}

void StormExprDynamicBlock::SetVariable(const StormExprDynamicBlockVariable & var, const std::string & val)
{
  if (var.m_Type == StormExprValueType::kString)
  {
    m_Strings[var.m_Index] = val;
  }
}

void StormExprDynamicBlock::SetVariable(const StormExprDynamicBlockVariable & var, const char * val)
{
  if (var.m_Type == StormExprValueType::kString)
  {
    m_Strings[var.m_Index] = val;
  }
}

void * StormExprDynamicBlock::GetBasePtr(const StormExprDynamicBlockVariable & var)
{
  switch (var.m_Type)
  {
  case StormExprValueType::kFloat:
  default:
    return GetBaseFloatPtr();
    break;
  case StormExprValueType::kString:
    return GetBaseStringPtr();
    break;
  }
}

void * StormExprDynamicBlock::GetBaseFloatPtr()
{
  return m_Floats.data();
}

void * StormExprDynamicBlock::GetBaseStringPtr()
{
  return m_Strings.data();
}

StormExprBinding StormExprDynamicBlock::GetBinding(StormExprDynamicBlockVariable var)
{
  switch (var.m_Type)
  {
  case StormExprValueType::kFloat:
  default:
    return StormExprBinding(m_Floats.data(), &m_Floats[var.m_Index]);
    break;
  case StormExprValueType::kString:
    return StormExprBinding(m_Strings.data(), &m_Strings[var.m_Index]);
    break;
  }
}
