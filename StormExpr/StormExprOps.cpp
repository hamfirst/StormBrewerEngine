
#include "StormExprOps.h"
#include "StormExprValueBlockList.h"

StormExprOp StormExprGetOpForOperator(StormExprOperatorType op)
{
  switch (op)
  {
  case StormExprOperatorType::kNeg:
    return StormExprOp{ StormExprOpNeg };
  case StormExprOperatorType::kAdd:
    return StormExprOp{ StormExprOpAdd };
  case StormExprOperatorType::kSub:
    return StormExprOp{ StormExprOpSub };
  case StormExprOperatorType::kMul:
    return StormExprOp{ StormExprOpMul };
  case StormExprOperatorType::kDiv:
    return StormExprOp{ StormExprOpDiv };
  case StormExprOperatorType::kMod:
    return StormExprOp{ StormExprOpMod };
  case StormExprOperatorType::kEq:
    return StormExprOp{ StormExprOpEq };
  case StormExprOperatorType::kNeq:
    return StormExprOp{ StormExprOpNeq };
  case StormExprOperatorType::kGt:
    return StormExprOp{ StormExprOpGt };
  case StormExprOperatorType::kGte:
    return StormExprOp{ StormExprOpGte };
  case StormExprOperatorType::kLt:
    return StormExprOp{ StormExprOpLt };
  case StormExprOperatorType::kLte:
    return StormExprOp{ StormExprOpLte };
  case StormExprOperatorType::kTernary:
    return StormExprOp{ StormExprOpNop };
  case StormExprOperatorType::kTernaryEnd:
    return StormExprOp{ StormExprOpTern };
  case StormExprOperatorType::kRiv:
    return StormExprOp{ StormExprOpRiv };
  default:
    return StormExprOp{ StormExprOpNop };
  }
}


bool StormExprLoad(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t index)
{
  StormExprValue val;
  if (vals.GetValue((int)index, val))
  {
    stack.Push(std::move(val));
  }
  else
  {
    stack.Push({});
  }

  return false;
}

bool StormExprLoadLit(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t index)
{
  stack.Push(StormExprValue((float)index));
  return false;
}

bool StormExprOpNop(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t index)
{
  return false;
}

bool StormExprOpNeg(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t index)
{
  StormExprValue v1;
  if (!stack.Pop(v1))
  {
    stack.Push({});
    return false;
  }

  if (v1.GetType() != StormExprValueType::kFloat)
  {
    stack.Push({});
    return false;
  }

  stack.Push(v1.GetFloatVal() != 0 ? 1.0f : 0.0f);
  return false;
}

bool StormExprOpAdd(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t index)
{
  StormExprValue v1;
  StormExprValue v2;

  if (!stack.Pop(v1))
  {
    stack.Push({});
    return false;
  }

  if (!stack.Pop(v2))
  {
    stack.Push({});
    return false;
  }

  if (v1.GetType() != v2.GetType())
  {
    stack.Push({});
    return false;
  }

  if (v1.GetType() == StormExprValueType::kFloat)
  {
    stack.Push(v2.GetFloatVal() + v1.GetFloatVal());
  }
  else if (v1.GetType() == StormExprValueType::kString)
  {
    stack.Push(StormExprValue(v1.GetStringVal(), v2.GetStringVal()));
  }
  else
  {
    stack.Push({});
  }
  return false;
}

bool StormExprOpSub(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t index)
{
  StormExprValue v1;
  StormExprValue v2;

  if (!stack.Pop(v1))
  {
    stack.Push({});
    return false;
  }

  if (!stack.Pop(v2))
  {
    stack.Push({});
    return false;
  }

  if (v1.GetType() != v2.GetType())
  {
    stack.Push({});
    return false;
  }

  if (v1.GetType() != StormExprValueType::kFloat)
  {
    stack.Push({});
    return false;
  }

  stack.Push(v2.GetFloatVal() - v1.GetFloatVal());
  return false;
}

bool StormExprOpMul(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t index)
{
  StormExprValue v1;
  StormExprValue v2;

  if (!stack.Pop(v1))
  {
    stack.Push({});
    return false;
  }

  if (!stack.Pop(v2))
  {
    stack.Push({});
    return false;
  }

  if (v1.GetType() != v2.GetType())
  {
    stack.Push({});
    return false;
  }

  if (v1.GetType() != StormExprValueType::kFloat)
  {
    stack.Push({});
    return false;
  }

  stack.Push(v2.GetFloatVal() * v1.GetFloatVal());
  return false;
}

bool StormExprOpDiv(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t index)
{
  StormExprValue v1;
  StormExprValue v2;

  if (!stack.Pop(v1))
  {
    stack.Push({});
    return false;
  }

  if (!stack.Pop(v2))
  {
    stack.Push({});
    return false;
  }

  if (v1.GetType() != v2.GetType())
  {
    stack.Push({});
    return false;
  }

  if (v1.GetType() != StormExprValueType::kFloat)
  {
    stack.Push({});
    return false;
  }

  stack.Push(v2.GetFloatVal() / v1.GetFloatVal());
  return false;
}

bool StormExprOpMod(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t index)
{
  StormExprValue v1;
  StormExprValue v2;

  if (!stack.Pop(v1))
  {
    stack.Push({});
    return false;
  }

  if (!stack.Pop(v2))
  {
    stack.Push({});
    return false;
  }

  if (v1.GetType() != v2.GetType())
  {
    stack.Push({});
    return false;
  }

  if (v1.GetType() != StormExprValueType::kFloat)
  {
    stack.Push({});
    return false;
  }

  stack.Push(fmod(v2.GetFloatVal(), v1.GetFloatVal()));
  return false;
}

bool StormExprOpEq(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t index)
{
  StormExprValue v1;
  StormExprValue v2;

  if (!stack.Pop(v1))
  {
    stack.Push({});
    return false;
  }

  if (!stack.Pop(v2))
  {
    stack.Push({});
    return false;
  }

  if (v1.GetType() != v2.GetType())
  {
    stack.Push({});
    return false;
  }

  if (v1.GetType() != StormExprValueType::kFloat)
  {
    stack.Push({});
    return false;
  }

  stack.Push(v2.GetFloatVal() == v1.GetFloatVal() ? 1.0f : 0.0f);
  return false;
}

bool StormExprOpNeq(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t index)

{
  StormExprValue v1;
  StormExprValue v2;

  if (!stack.Pop(v1))
  {
    stack.Push({});
    return false;
  }

  if (!stack.Pop(v2))
  {
    stack.Push({});
    return false;
  }

  if (v1.GetType() != v2.GetType())
  {
    stack.Push({});
    return false;
  }

  if (v1.GetType() != StormExprValueType::kFloat)
  {
    stack.Push({});
    return false;
  }

  stack.Push(v2.GetFloatVal() != v1.GetFloatVal() ? 1.0f : 0.0f);
  return false;
}

bool StormExprOpGt(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t index)
{
  StormExprValue v1;
  StormExprValue v2;

  if (!stack.Pop(v1))
  {
    stack.Push({});
    return false;
  }

  if (!stack.Pop(v2))
  {
    stack.Push({});
    return false;
  }

  if (v1.GetType() != v2.GetType())
  {
    stack.Push({});
    return false;
  }

  if (v1.GetType() != StormExprValueType::kFloat)
  {
    stack.Push({});
    return false;
  }

  stack.Push(v2.GetFloatVal() > v1.GetFloatVal() ? 1.0f : 0.0f);
  return false;
}

bool StormExprOpGte(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t index)
{
  StormExprValue v1;
  StormExprValue v2;

  if (!stack.Pop(v1))
  {
    stack.Push({});
    return false;
  }

  if (!stack.Pop(v2))
  {
    stack.Push({});
    return false;
  }

  if (v1.GetType() != v2.GetType())
  {
    stack.Push({});
    return false;
  }

  if (v1.GetType() != StormExprValueType::kFloat)
  {
    stack.Push({});
    return false;
  }

  stack.Push(v2.GetFloatVal() >= v1.GetFloatVal() ? 1.0f : 0.0f);
  return false;
}

bool StormExprOpLt(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t index)
{
  StormExprValue v1;
  StormExprValue v2;

  if (!stack.Pop(v1))
  {
    stack.Push({});
    return false;
  }

  if (!stack.Pop(v2))
  {
    stack.Push({});
    return false;
  }

  if (v1.GetType() != v2.GetType())
  {
    stack.Push({});
    return false;
  }

  if (v1.GetType() != StormExprValueType::kFloat)
  {
    stack.Push({});
    return false;
  }

  stack.Push(v2.GetFloatVal() < v1.GetFloatVal() ? 1.0f : 0.0f);
  return false;
}

bool StormExprOpLte(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t index)
{
  StormExprValue v1;
  StormExprValue v2;

  if (!stack.Pop(v1))
  {
    stack.Push({});
    return false;
  }

  if (!stack.Pop(v2))
  {
    stack.Push({});
    return false;
  }

  if (v1.GetType() != v2.GetType())
  {
    stack.Push({});
    return false;
  }

  if (v1.GetType() != StormExprValueType::kFloat)
  {
    stack.Push({});
    return false;
  }

  stack.Push(v2.GetFloatVal() <= v1.GetFloatVal() ? 1.0f : 0.0f);
  return false;
}

bool StormExprOpTern(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t index)
{
  StormExprValue v1;
  StormExprValue v2;
  StormExprValue v3;

  if (!stack.Pop(v1))
  {
    stack.Push({});
    return false;
  }

  if (!stack.Pop(v2))
  {
    stack.Push({});
    return false;
  }

  if (!stack.Pop(v3))
  {
    stack.Push({});
    return false;
  }

  if((v3.GetType() == StormExprValueType::kFloat && v3.GetFloatVal() != 0) ||
     (v3.GetType() == StormExprValueType::kString))
  {
    stack.Push(std::move(v2));
  }
  else
  {
    stack.Push(std::move(v1));
  }

  return false;
}

bool StormExprOpRiv(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t index)
{
  StormExprValue v1;
  StormExprValue v2;

  if (!stack.Pop(v1))
  {
    stack.Push({});
    return false;
  }

  if (!stack.Pop(v2))
  {
    stack.Push({});
    return false;
  }

  if (v2.GetType() != StormExprValueType::kNothing)
  {
    stack.Push(std::move(v2));
    return true;
  }

  stack.Push(std::move(v1));
  return false;
}
