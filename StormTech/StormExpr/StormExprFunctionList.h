#pragma once

#include <unordered_map>

#include "StormExprStack.h"
#include "StormExprValueBlockList.h"

using StormExprFunctionCallback = bool(*)(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t user_data);

class StormExprFunctionList
{
public:
  void RegisterFunction(const char * name, StormExprFunctionCallback callback, ptrdiff_t user_data);
  bool LookupFunction(uint32_t name_hash, StormExprFunctionCallback & out_callback, ptrdiff_t & out_user_data) const;

private:
  std::unordered_map<uint32_t, std::pair<StormExprFunctionCallback, ptrdiff_t>> m_Funcs;
};

