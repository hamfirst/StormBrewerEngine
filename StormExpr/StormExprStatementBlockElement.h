#pragma once

#include <vector>
#include <cstdint>

#include "StormExprOperator.h"

class StormExprStatementBlock;

enum class StormExprStatementBlockElementType
{
  kNone,
  kValue,
  kOperator,
  kSubBlock,
  kFunctionCall,
};

struct StormExprFunctionStatementInfo
{
  uint32_t m_FunctionNameHash;
  StormExprStatementBlock ** m_SubBlocks;
  int m_SubBlockCount;
};

class StormExprStatementBlockElement
{
public:

  StormExprStatementBlockElement();
  explicit StormExprStatementBlockElement(const char * start, int value_id);
  explicit StormExprStatementBlockElement(const char * start, StormExprOperatorType operator_type);
  explicit StormExprStatementBlockElement(const char * start, StormExprStatementBlock * sub_block);
  explicit StormExprStatementBlockElement(const char * start, uint32_t function_name_hash, const std::vector<StormExprStatementBlock *> & blocks);

  StormExprStatementBlockElement(const StormExprStatementBlockElement & rhs) = delete;
  StormExprStatementBlockElement(StormExprStatementBlockElement && rhs);

  ~StormExprStatementBlockElement();

  StormExprStatementBlockElement & operator = (const StormExprStatementBlockElement & rhs) = delete;
  StormExprStatementBlockElement & operator = (StormExprStatementBlockElement && rhs);

  StormExprStatementBlockElementType GetType() const;
  const char * GetStart() const;
  int GetValueId() const;
  StormExprOperatorType GetOperatorType() const;
  StormExprStatementBlock * GetSubBlock();
  StormExprFunctionStatementInfo & GetFunctionInfo();

private:
  StormExprStatementBlockElementType m_Type;
  const char * m_Start;

  union
  {
    int m_ValueId;
    StormExprOperatorType m_Operator;
    StormExprStatementBlock * m_SubBlock;

    StormExprFunctionStatementInfo m_FuncInfo;
  };
};

