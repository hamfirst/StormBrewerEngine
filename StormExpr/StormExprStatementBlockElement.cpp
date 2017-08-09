
#include "StormExprStatementBlockElement.h"
#include "StormExprStatementBlock.h"

StormExprStatementBlockElement::StormExprStatementBlockElement() :
  m_Type(StormExprStatementBlockElementType::kNone),
  m_Start(nullptr)
{

}

StormExprStatementBlockElement::StormExprStatementBlockElement(const char * start, int value_id) :
  m_Type(StormExprStatementBlockElementType::kValue),
  m_Start(start),
  m_ValueId(value_id)
{
  
}

StormExprStatementBlockElement::StormExprStatementBlockElement(const char * start, StormExprOperatorType operator_type) :
  m_Type(StormExprStatementBlockElementType::kOperator),
  m_Start(start),
  m_Operator(operator_type)
{

}

StormExprStatementBlockElement::StormExprStatementBlockElement(const char * start, StormExprStatementBlock * sub_block) :
  m_Type(StormExprStatementBlockElementType::kSubBlock),
  m_Start(start),
  m_SubBlock(sub_block)
{

}

StormExprStatementBlockElement::StormExprStatementBlockElement(const char * start, uint32_t function_name_hash, const std::vector<StormExprStatementBlock *> & blocks) :
  m_Type(StormExprStatementBlockElementType::kFunctionCall),
  m_Start(start)
{
  m_FuncInfo.m_FunctionNameHash = function_name_hash;
  m_FuncInfo.m_SubBlocks = new StormExprStatementBlock *[blocks.size()];
  m_FuncInfo.m_SubBlockCount = (int)blocks.size();
  for (std::size_t index = 0, end = blocks.size(); index < end; ++index)
  {
    m_FuncInfo.m_SubBlocks[index] = blocks[index];
  }
}

StormExprStatementBlockElement::StormExprStatementBlockElement(StormExprStatementBlockElement && rhs) :
  m_Type(rhs.m_Type),
  m_Start(rhs.m_Start)
{
  m_FuncInfo = rhs.m_FuncInfo;
  rhs.m_Type = StormExprStatementBlockElementType::kNone;
  rhs.m_FuncInfo = {};
  rhs.m_Start = nullptr;
}

StormExprStatementBlockElement::~StormExprStatementBlockElement()
{
  if (m_Type == StormExprStatementBlockElementType::kSubBlock)
  {
    delete m_SubBlock;
  }

  if (m_Type == StormExprStatementBlockElementType::kFunctionCall)
  { 
    for (int index = 0; index < m_FuncInfo.m_SubBlockCount; index++)
    {
      delete m_FuncInfo.m_SubBlocks[index];
    }

    delete [] m_FuncInfo.m_SubBlocks;
  }
}

StormExprStatementBlockElement & StormExprStatementBlockElement::operator = (StormExprStatementBlockElement && rhs)
{
  if (m_Type == StormExprStatementBlockElementType::kSubBlock)
  {
    delete m_SubBlock;
  }

  if (m_Type == StormExprStatementBlockElementType::kFunctionCall)
  {
    for (int index = 0; index < m_FuncInfo.m_SubBlockCount; index++)
    {
      delete m_FuncInfo.m_SubBlocks[index];
    }

    delete[] m_FuncInfo.m_SubBlocks;
  }

  m_Type = rhs.m_Type;
  m_FuncInfo = rhs.m_FuncInfo;
  m_Start = rhs.m_Start;
  rhs.m_Type = StormExprStatementBlockElementType::kNone;
  rhs.m_FuncInfo = {};
  rhs.m_Start = nullptr;
  return *this;
}

StormExprStatementBlockElementType StormExprStatementBlockElement::GetType() const
{
  return m_Type;
}

const char * StormExprStatementBlockElement::GetStart() const
{
  return m_Start;
}

int StormExprStatementBlockElement::GetValueId() const
{
  return m_ValueId;
}

StormExprOperatorType StormExprStatementBlockElement::GetOperatorType() const
{
  return m_Operator;
}

StormExprStatementBlock * StormExprStatementBlockElement::GetSubBlock()
{
  return m_SubBlock;
}

StormExprFunctionStatementInfo & StormExprStatementBlockElement::GetFunctionInfo()
{
  return m_FuncInfo;
}
