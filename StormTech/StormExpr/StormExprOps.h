#pragma once

#include <cstddef>

#include "StormExprStack.h"
#include "StormExprValueBlock.h"
#include "StormExprOperator.h"

class StormExprValueBlockList;


struct StormExprOp
{
  bool(*Func)(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t user_data);
  ptrdiff_t m_Index;
};

StormExprOp StormExprGetOpForOperator(StormExprOperatorType op, bool quick_version);

bool StormExprLoad(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t index);
bool StormExprLoadLit(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t index);
bool StormExprOpCat(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t index);
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

bool StormExprLoadQuick(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t index);
bool StormExprLoadLitQuick(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t index);
bool StormExprOpCatQuick(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t index);
bool StormExprOpNopQuick(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t index);
bool StormExprOpNegQuick(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t index);
bool StormExprOpAddQuick(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t index);
bool StormExprOpSubQuick(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t index);
bool StormExprOpMulQuick(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t index);
bool StormExprOpDivQuick(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t index);
bool StormExprOpModQuick(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t index);
bool StormExprOpEqQuick(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t index);
bool StormExprOpNeqQuick(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t index);
bool StormExprOpGtQuick(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t index);
bool StormExprOpGteQuick(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t index);
bool StormExprOpLtQuick(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t index);
bool StormExprOpLteQuick(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t index);
bool StormExprOpTernQuick(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t index);
bool StormExprOpRivQuick(StormExprStack & stack, const StormExprValueBlockList & vals, ptrdiff_t index);
