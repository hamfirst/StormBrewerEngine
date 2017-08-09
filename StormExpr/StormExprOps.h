#pragma once

#include "StormExprStack.h"
#include "StormExprValueBlock.h"
#include "StormExprOperator.h"

class StormExprValueBlockList;


struct StormExprOp
{
  bool(*Func)(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t user_data);
  ptrdiff_t m_Index;
};

StormExprOp StormExprGetOpForOperator(StormExprOperatorType op);

bool StormExprLoad(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t index);
bool StormExprLoadLit(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t index);
bool StormExprOpNop(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t index);
bool StormExprOpNeg(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t index);
bool StormExprOpAdd(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t index);
bool StormExprOpSub(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t index);
bool StormExprOpMul(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t index);
bool StormExprOpDiv(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t index);
bool StormExprOpMod(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t index);
bool StormExprOpEq(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t index);
bool StormExprOpNeq(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t index);
bool StormExprOpGt(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t index);
bool StormExprOpGte(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t index);
bool StormExprOpLt(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t index);
bool StormExprOpLte(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t index);
bool StormExprOpTern(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t index);
bool StormExprOpRiv(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t index);
