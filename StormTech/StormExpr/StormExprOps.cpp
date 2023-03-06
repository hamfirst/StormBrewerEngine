
#include "StormExprOps.h"
#include "StormExprValueBlockList.h"

#include <cmath>
#include <stdexcept>

StormExprOp StormExprGetOpForOperator(StormExprOperatorType op, bool quick_version)
{
  if (!quick_version)
  {
    switch (op)
    {
    case StormExprOperatorType::kCat:
      return StormExprOp{ StormExprOpCat };
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
  else
  {
    switch (op)
    {
    case StormExprOperatorType::kCat:
      return StormExprOp{ StormExprOpCatQuick };
    case StormExprOperatorType::kNeg:
      return StormExprOp{ StormExprOpNegQuick };
    case StormExprOperatorType::kAdd:
      return StormExprOp{ StormExprOpAddQuick };
    case StormExprOperatorType::kSub:
      return StormExprOp{ StormExprOpSubQuick };
    case StormExprOperatorType::kMul:
      return StormExprOp{ StormExprOpMulQuick };
    case StormExprOperatorType::kDiv:
      return StormExprOp{ StormExprOpDivQuick };
    case StormExprOperatorType::kMod:
      return StormExprOp{ StormExprOpModQuick };
    case StormExprOperatorType::kEq:
      return StormExprOp{ StormExprOpEqQuick };
    case StormExprOperatorType::kNeq:
      return StormExprOp{ StormExprOpNeqQuick };
    case StormExprOperatorType::kGt:
      return StormExprOp{ StormExprOpGtQuick };
    case StormExprOperatorType::kGte:
      return StormExprOp{ StormExprOpGteQuick };
    case StormExprOperatorType::kLt:
      return StormExprOp{ StormExprOpLtQuick };
    case StormExprOperatorType::kLte:
      return StormExprOp{ StormExprOpLteQuick };
    case StormExprOperatorType::kTernary:
      return StormExprOp{ StormExprOpNopQuick };
    case StormExprOperatorType::kTernaryEnd:
      return StormExprOp{ StormExprOpTernQuick };
    case StormExprOperatorType::kRiv:
      return StormExprOp{ StormExprOpRivQuick };
    default:
      return StormExprOp{ StormExprOpNop };
    }
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

bool StormExprOpCat(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t index)
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

  if (v1.GetType() != StormExprValueType::kString)
  {
    stack.Push({});
    return false;
  }

  stack.Push(StormExprValue(v2.GetStringVal(), v1.GetStringVal()));
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

  if (v1.GetType() != StormExprValueType::kFloat)
  {
    stack.Push({});
    return false;
  }

  stack.Push(v2.GetFloatVal() + v1.GetFloatVal());
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



bool StormExprLoadQuick(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t index)
{
  StormExprValue val;
  vals.GetValueQuick((int)index, val);
  stack.PushQuick(std::move(val));
  return false;
}

bool StormExprLoadLitQuick(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t index)
{
  stack.PushQuick(StormExprValue((float)index));
  return false;
}

bool StormExprOpCatQuick(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t index)
{
  throw std::runtime_error("Strings are not allowed when running in number only mode");
}

bool StormExprOpNopQuick(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t index)
{
  return false;
}

bool StormExprOpNegQuick(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t index)
{
  StormExprValue v1;
  stack.PopQuick(v1);
  stack.PushQuick(v1.GetFloatVal() != 0 ? 1.0f : 0.0f);
  return false;
}

bool StormExprOpAddQuick(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t index)
{
  StormExprValue v1;
  StormExprValue v2;
  stack.PopDoubleQuick(v1, v2);
  stack.PushQuick(v2.GetFloatVal() + v1.GetFloatVal());
  return false;
}

bool StormExprOpSubQuick(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t index)
{
  StormExprValue v1;
  StormExprValue v2;
  stack.PopDoubleQuick(v1, v2);
  stack.PushQuick(v2.GetFloatVal() + v1.GetFloatVal());
  return false;
}

bool StormExprOpMulQuick(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t index)
{
  StormExprValue v1;
  StormExprValue v2;
  stack.PopDoubleQuick(v1, v2);
  stack.PushQuick(v2.GetFloatVal() * v1.GetFloatVal());
  return false;
}

bool StormExprOpDivQuick(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t index)
{
  StormExprValue v1;
  StormExprValue v2;
  stack.PopDoubleQuick(v1, v2);
  stack.PushQuick(v2.GetFloatVal() / v1.GetFloatVal());
  return false;
}

bool StormExprOpModQuick(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t index)
{
  StormExprValue v1;
  StormExprValue v2;
  stack.PopDoubleQuick(v1, v2);
  stack.Push(fmod(v2.GetFloatVal(), v1.GetFloatVal()));
  return false;
}

bool StormExprOpEqQuick(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t index)
{
  StormExprValue v1;
  StormExprValue v2;
  stack.PopDoubleQuick(v1, v2);
  stack.Push(v2.GetFloatVal() == v1.GetFloatVal() ? 1.0f : 0.0f);
  return false;
}

bool StormExprOpNeqQuick(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t index)
{
  StormExprValue v1;
  StormExprValue v2;
  stack.PopDoubleQuick(v1, v2);
  stack.Push(v2.GetFloatVal() != v1.GetFloatVal() ? 1.0f : 0.0f);
  return false;
}

bool StormExprOpGtQuick(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t index)
{
  StormExprValue v1;
  StormExprValue v2;
  stack.PopDoubleQuick(v1, v2);
  stack.Push(v2.GetFloatVal() > v1.GetFloatVal() ? 1.0f : 0.0f);
  return false;
}

bool StormExprOpGteQuick(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t index)
{
  StormExprValue v1;
  StormExprValue v2;
  stack.PopDoubleQuick(v1, v2);
  stack.Push(v2.GetFloatVal() >= v1.GetFloatVal() ? 1.0f : 0.0f);
  return false;
}

bool StormExprOpLtQuick(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t index)
{
  StormExprValue v1;
  StormExprValue v2;
  stack.PopDoubleQuick(v1, v2);
  stack.Push(v2.GetFloatVal() < v1.GetFloatVal() ? 1.0f : 0.0f);
  return false;
}

bool StormExprOpLteQuick(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t index)
{
  StormExprValue v1;
  StormExprValue v2;
  stack.PopDoubleQuick(v1, v2);
  stack.Push(v2.GetFloatVal() <= v1.GetFloatVal() ? 1.0f : 0.0f);
  return false;
}

bool StormExprOpTernQuick(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t index)
{
  StormExprValue v1;
  StormExprValue v2;
  StormExprValue v3;
  stack.PopTripleQuick(v1, v2, v3);

  if ((v3.GetType() == StormExprValueType::kFloat && v3.GetFloatVal() != 0))
  {
    stack.PushQuick(std::move(v2));
  }
  else
  {
    stack.PushQuick(std::move(v1));
  }

  return false;
}

bool StormExprOpRivQuick(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t index)
{
  StormExprValue v1;
  StormExprValue v2;
  stack.PopDoubleQuick(v1, v2);

  if (v2.GetType() != StormExprValueType::kNothing)
  {
    stack.Push(std::move(v2));
    return true;
  }

  stack.Push(std::move(v1));
  return false;
}

