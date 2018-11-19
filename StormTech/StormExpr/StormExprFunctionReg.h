#pragma once

#include "StormExprFunctionList.h"

template <typename ... Args>
void StormExprRegisterFunction(czstr name, StormExprFunctionList & func_list, float(*Func)(Args...))
{
  auto func_marshal = [](StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t func)
  {
    int arg_count = (int)stack.PopFloat();
    if (arg_count != sizeof...(Args))
    {
      while (arg_count != 0)
      {
        stack.Pop();
        arg_count--;
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
void StormExprRegisterFunction(czstr name, StormExprFunctionList & func_list, std::string(*Func)(Args...))
{
  auto func_marshal = [](StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t func)
  {
    int arg_count = (int)stack.PopFloat();
    if (arg_count != sizeof...(Args))
    {
      while (arg_count != 0)
      {
        stack.Pop();
        arg_count--;
      }

      stack.Push(StormExprValue());
      return false;
    }

    std::array<StormExprValue, sizeof...(Args)> stack_vals;
    for (int index = sizeof...(Args)-1; index >= 0; --index)
    {
      stack.Pop(stack_vals[index]);
    }

    std::string(*func_ptr)(Args...) = (std::string(*)(Args...))func;
    auto val = NetMetaUtil::Apply(func_ptr, stack_vals);

    stack.Push(val.data());
    return false;
  };

  func_list.RegisterFunction(name, func_marshal, (ptrdiff_t)Func);
}
