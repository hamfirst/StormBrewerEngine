#pragma once


enum class StormExprOperatorType
{
  kNeg,
  kCat,
  kAdd,
  kSub,
  kMul,
  kDiv,
  kMod,
  kEq,
  kNeq,
  kGt,
  kGte,
  kLt,
  kLte,
  kTernary,
  kTernaryEnd,
  kRiv,
};

bool IsUniaryOperator(StormExprOperatorType op);
bool IsBinaryOperator(StormExprOperatorType op);
bool IsTrinaryOperator(StormExprOperatorType op);

int StormExprGetOperatorPrecedence(StormExprOperatorType op);
