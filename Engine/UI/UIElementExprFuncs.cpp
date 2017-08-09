
#include "Engine/EngineCommon.h"
#include "Engine/UI/UIElementExprFuncs.h"

#include "StormNet/NetMetaUtil.h"


template <typename ... Args>
void RegisterUIFunction(czstr name, StormExprFunctionList & func_list, float(*Func)(Args...))
{
  auto func_marshal = [](StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t func)
  {
    int arg_count = (int)stack.PopFloat();
    if (arg_count != sizeof...(Args))
    {
      while (arg_count != 0)
      {
        stack.Pop();
      }

      stack.Push(StormExprValue());
      return false;
    }

    std::array<StormExprValue, sizeof...(Args)> stack_vals;
    for (int index = sizeof...(Args)-1; index >= 0; --index)
    {
      stack.Pop(stack_vals[index]);
    }

    float(*func_ptr)(Args...) = (float(*)(Args...))func;
    auto val = NetMetaUtil::Apply(func_ptr, stack_vals);
    
    stack.Push(val);
    return false;
  };

  func_list.RegisterFunction(name, func_marshal, (ptrdiff_t)Func);
}

template <typename ... Args>
void RegisterUIFunction(czstr name, StormExprFunctionList & func_list, std::string(*Func)(Args...))
{

}

StormExprFunctionList UICreateFunctionList()
{
  StormExprFunctionList function_list;

  RegisterUIFunction("sqrt", function_list, sqrtf);
  RegisterUIFunction("sin", function_list, sinf);
  RegisterUIFunction("cos", function_list, cosf);
  RegisterUIFunction("tan", function_list, tanf);
  return function_list;
}

