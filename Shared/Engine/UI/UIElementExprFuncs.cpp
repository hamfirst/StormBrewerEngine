
#include "Engine/EngineCommon.h"
#include "Engine/UI/UIElementExprFuncs.h"

#include "StormNet/NetMetaUtil.h"
#include "StormExpr/StormExprFunctionReg.h"

#include "Foundation/Lerp/LerpFuncs.h"

static float s_LastLerp = 0;
static float s_LastLerpTimeAlive = 0;
static float s_LastLerpDestination = 0;

void UIResetLerpVals(float time_alive)
{
  s_LastLerp = 0;
  s_LastLerpTimeAlive = time_alive;
  s_LastLerpDestination = 0;
}

bool UILerp(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t func)
{
  int arg_count = (int)stack.PopFloat();
  if (arg_count != 3 && arg_count != 2)
  {
    while (arg_count != 0)
    {
      stack.Pop();
      arg_count--;
    }

    stack.Push(StormExprValue());
    return false;
  }

  if (arg_count == 3)
  {
    auto to = stack.PopFloat();
    auto from = stack.PopFloat();
    auto time = stack.PopFloat();

    if (time < s_LastLerpTimeAlive)
    {
      s_LastLerp = time;
      s_LastLerpDestination = to;

      stack.Push(StormExprValue());
      return false;
    }

    auto time_since = s_LastLerpTimeAlive - s_LastLerp;
    auto lerp_time = time - s_LastLerp;

    auto t = time_since / lerp_time;
    auto v = Easing::EaseInOut(t, EasingType::kQuadratic);
    stack.Push((to - from) * v + from);
    return false;
  }
  else
  {
    auto to = stack.PopFloat();
    auto time = stack.PopFloat();

    if (time < s_LastLerpTimeAlive)
    {
      s_LastLerp = time;
      s_LastLerpDestination = to;

      stack.Push(StormExprValue());
      return false;
    }

    auto time_since = s_LastLerpTimeAlive - s_LastLerp;
    auto lerp_time = time - s_LastLerp;

    auto t = time_since / lerp_time;
    auto v = Easing::EaseInOut(t, EasingType::kQuadratic);
    stack.Push((to - s_LastLerpDestination) * v + s_LastLerpDestination);
    return false;
  }
}

bool UILerpPause(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t func)
{
  int arg_count = (int)stack.PopFloat();
  if (arg_count != 2 && arg_count != 1)
  {
    while (arg_count != 0)
    {
      stack.Pop();
      arg_count--;
    }

    stack.Push(StormExprValue());
    return false;
  }

  if (arg_count == 2)
  {
    auto val = stack.PopFloat();
    auto time = stack.PopFloat();

    if (time < s_LastLerpTimeAlive)
    {
      s_LastLerp = time;
      s_LastLerpDestination = val;

      stack.Push(StormExprValue());
      return false;
    }

    stack.Push(val);
    return false;
  }
  else
  {
    auto time = stack.PopFloat();

    if (time < s_LastLerpTimeAlive)
    {
      s_LastLerp = time;

      stack.Push(StormExprValue());
      return false;
    }

    stack.Push(s_LastLerpDestination);
    return false;
  }
}

bool UILerpEnd(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t func)
{
  int arg_count = (int)stack.PopFloat();
  if (arg_count != 0)
  {
    while (arg_count != 0)
    {
      stack.Pop();
      arg_count--;
    }

    stack.Push(StormExprValue());
    return false;
  }

  stack.Push(s_LastLerpDestination);
  return false;
}

bool Fmt(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t func)
{
  int arg_count = (int)stack.PopFloat();

  std::string outp;

  for (int index = 0; index < arg_count; ++index)
  {
    StormExprValue val;
    if (stack.Pop(val) == false)
    {
      stack.Push(StormExprValue());
      return false;
    }

    switch (val.GetType())
    {
    case StormExprValueType::kFloat:
      outp = std::to_string(val.GetFloatVal()) + outp;
      break;

    case StormExprValueType::kString:
      outp = val.GetStringVal() + outp;
      break;
    }
  }

  stack.Push(StormExprValue(outp.data()));
  return false;
}

std::string IntStr(float val)
{
  return std::to_string((int)val);
}


StormExprFunctionList UICreateFunctionList()
{
  StormExprFunctionList function_list;

  function_list.RegisterFunction("ql", UILerp, 0);
  function_list.RegisterFunction("qp", UILerpPause, 0);
  function_list.RegisterFunction("qe", UILerpEnd, 0);
  function_list.RegisterFunction("fmt", Fmt, 0);

  StormExprRegisterFunction("sqrt", function_list, sqrtf);
  StormExprRegisterFunction("sin", function_list, sinf);
  StormExprRegisterFunction("cos", function_list, cosf);
  StormExprRegisterFunction("tan", function_list, tanf);
  StormExprRegisterFunction("intstr", function_list, IntStr);
  return function_list;
}

