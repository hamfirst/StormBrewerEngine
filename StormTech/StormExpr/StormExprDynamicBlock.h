#pragma once

#include "StormExprBinding.h"
#include "StormExprValue.h"
#include "StormExprValueInitBlock.h"

#include <vector>
#include <string>

struct StormExprDynamicBlockVariable
{
  uint16_t m_Index;
  StormExprValueType m_Type;
};

class StormExprDynamicBlock
{
public:

  StormExprDynamicBlockVariable AddVariable(StormExprValueType type);
  void Link(const StormExprDynamicBlockVariable & var, const char * variable_name, StormExprValueInitBlock & float_init_block, StormExprValueInitBlock & string_init_block);

  void SetVariable(const StormExprDynamicBlockVariable & var, float val);
  void SetVariable(const StormExprDynamicBlockVariable & var, const std::string & val);
  void SetVariable(const StormExprDynamicBlockVariable & var, const char * val);

  void * GetBasePtr(const StormExprDynamicBlockVariable & var);
  void * GetBaseFloatPtr();
  void * GetBaseStringPtr();

  StormExprBinding GetBinding(StormExprDynamicBlockVariable var);

private:

  std::vector<float> m_Floats;
  std::vector<std::string> m_Strings;
};
