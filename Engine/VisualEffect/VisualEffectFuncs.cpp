
#include "Engine/EngineCommon.h"
#include "Engine/VisualEffect/VisualEffectFuncs.h"

#include "StormNet/NetMetaUtil.h"
#include "StormExpr/StormExprFunctionReg.h"

float Normalize(float a, float b, float r)
{
  return b * r + a * (1.0f - r);
}

float CircleX(float radius, float ra, float rb)
{
  if (rb < ra)
  {
    std::swap(ra, rb);
  }

  return rb * radius * cosf(2.0f * kPi * ra / rb);
}

float CircleY(float radius, float ra, float rb)
{
  if (rb < ra)
  {
    std::swap(ra, rb);
  }

  return rb * radius * sinf(2.0f * kPi * ra / rb);
}

StormExprFunctionList VisualEffectCreateFunctionList()
{
  StormExprFunctionList function_list;

  StormExprRegisterFunction("sqrt", function_list, sqrtf);
  StormExprRegisterFunction("sin", function_list, sinf);
  StormExprRegisterFunction("cos", function_list, cosf);
  StormExprRegisterFunction("tan", function_list, tanf);
  StormExprRegisterFunction("n", function_list, Normalize);
  StormExprRegisterFunction("cx", function_list, CircleX);
  StormExprRegisterFunction("cy", function_list, CircleY);
  return function_list;
}

