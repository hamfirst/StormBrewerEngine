#pragma once

#include <cstddef>
#include <string>

#include "StormExprValue.h"
#include "StormExprValueInitBlock.h"
#include "StormExprLiteralBlockBuilder.h"
#include "StormExprValueInitBlockList.h"
#include "StormExprOps.h"
#include "StormExprOperator.h"
#include "StormExprStatementBlock.h"
#include "StormExprStatementBlockElement.h"
#include "StormExprFunctionList.h"

using StormExprOpList = std::vector<StormExprOp>;

class StormExprEvalBuilder
{
public:

  StormExprEvalBuilder(StormExprFunctionList & funcs, bool quick_version = false);

  int ParseExpression(const char * str, const char *&error, const char *& error_desc);
  void SetBlockList(StormExprValueInitBlockList & init_block_list);

  static bool IsLiteralFloatValue(const char * str, float & outp_float);
  static bool IsLiteralStringValue(const char * str, std::string & outp_str);

protected:

  static void SkipWhiteSpace(const char *& str);
  static bool IsIdentifierStartCharacter(char c);
  static bool IsIdentifierCharacter(char c);

  static bool ParseIdentifier(const char * str, const char * & result, const char *&error, const char *& error_desc, uint32_t & identifier_hash);
  static bool ParseNumber(const char * str, const char * & result, const char *&error, const char *& error_desc, StormExprValue & value);
  static bool ParseString(const char * str, const char * & result, const char *&error, const char *& error_desc, StormExprValue & value);
  static bool ParseNothing(const char * str, const char * & result, const char *&error, const char *& error_desc);
  static bool ParseBasicOperation(const char * str, const char * & result, const char *&error, const char *& error_desc, StormExprOperatorType & op);

  bool ParseFunctionCall(const char * str, const char * & result, const char *&error, const char *& error_desc, StormExprStatementBlockElement & elem, int paren_level);
  bool ParseStatementElement(const char * str, const char * & result, const char *&error, const char *& error_desc, 
    StormExprStatementBlockElement & elem, int paren_level, int function_call_level);
  bool ParseStatement(const char * str, const char * & result, const char *&error, const char *& error_desc, StormExprStatementBlock & block, int paren_level, int function_call_level);

  bool CompileOperand(StormExprStatementBlock & statement_block, std::size_t & index, StormExprOpList & op_list, const char * start, const char *&error, const char *& error_desc);
  void CompileOperator(const StormExprStatementBlockElement & op, StormExprOpList & op_list);
  void CompileOperatorFlush(std::vector<StormExprStatementBlockElement> & operator_stack, StormExprOpList & op_list);
  void CompileLoad(const StormExprStatementBlockElement & op, StormExprOpList & op_list);
  bool CompileStatement(StormExprStatementBlock & statement_block, StormExprOpList & op_list, std::size_t & index,
    const char * start, const char *&error, const char *& error_desc, int ternary_stack_size);

private:

  friend class StormExprEval;

  StormExprFunctionList & m_Functions;
  std::vector<StormExprOpList> m_Expressions;
  bool m_QuickVersion;

  StormExprLiteralBlockBuilder m_LiteralBlockBuilder;
  StormExprValueInitBlockList * m_InitBlockList;
};


