
#include "StormExprOperator.h"


bool IsUniaryOperator(StormExprOperatorType op)
{
  switch (op)
  {
  case StormExprOperatorType::kNeg:
    return true;
  default:
    return false;
  }
}

bool IsBinaryOperator(StormExprOperatorType op)
{
  if (IsUniaryOperator(op))
  {
    return false;
  }

  if (IsTrinaryOperator(op))
  {
    return false;
  }

  return true;
}

bool IsTrinaryOperator(StormExprOperatorType op)
{
  switch (op)
  {
  case StormExprOperatorType::kTernary:
    return true;
  default:
    return false;
  }
}

int StormExprGetOperatorPrecedence(StormExprOperatorType op)
{
  switch (op)
  {
  case StormExprOperatorType::kNeg:
    return 0;
  case StormExprOperatorType::kAdd:
    return 2;
  case StormExprOperatorType::kSub:
    return 2;
  case StormExprOperatorType::kMul:
    return 1;
  case StormExprOperatorType::kDiv:
    return 1;
  case StormExprOperatorType::kMod:
    return 1;
  case StormExprOperatorType::kEq:
    return 4;
  case StormExprOperatorType::kNeq:
    return 4;
  case StormExprOperatorType::kGt:
    return 3;
  case StormExprOperatorType::kGte:
    return 3;
  case StormExprOperatorType::kLt:
    return 3;
  case StormExprOperatorType::kLte:
    return 3;
  case StormExprOperatorType::kTernary:
    return 5;
  case StormExprOperatorType::kTernaryEnd:
    return 5;
  case StormExprOperatorType::kRiv:
    return 6;
  default:
    return 7;
  }
}
