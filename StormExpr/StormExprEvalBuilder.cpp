
#include "StormExprEvalBuilder.h"
#include "StormExprOperator.h"
#include "StormExprHash.h"

StormExprEvalBuilder::StormExprEvalBuilder(StormExprFunctionList & funcs) :
  m_Functions(funcs),
  m_InitBlockList(nullptr)
{

}

int StormExprEvalBuilder::ParseExpression(const char * str, const char *&error, const char *& error_desc)
{
  auto start_str = str;

  StormExprStatementBlock statement_block;
  if (ParseStatement(str, str, error, error_desc, statement_block, 0, 0) == false)
  {
    return -1;
  }

  StormExprOpList op_list;

  std::size_t index = 0;
  if (CompileStatement(statement_block, op_list, index, start_str, error, error_desc, 0) == false)
  {
    return -1;
  }

  int expr_index = (int)m_Expressions.size();
  m_Expressions.emplace_back(std::move(op_list));

  return expr_index;
}

void StormExprEvalBuilder::SetBlockList(StormExprValueInitBlockList & init_block_list)
{
  m_InitBlockList = &init_block_list;
}

bool StormExprEvalBuilder::IsLiteralFloatValue(const char * str, float & outp_float)
{
  SkipWhiteSpace(str);

  StormExprValue val;

  const char * error;
  const char * error_desc;
  if (ParseNumber(str, str, error, error_desc, val) == false)
  {
    return false;
  }

  SkipWhiteSpace(str);
  if (*str == 0)
  {
    outp_float = val.GetFloatVal();
    return true;
  }

  return false;
}

bool StormExprEvalBuilder::IsLiteralStringValue(const char * str, std::string & outp_str)
{
  SkipWhiteSpace(str);

  StormExprValue val;

  const char * error;
  const char * error_desc;
  if (ParseString(str, str, error, error_desc, val) == false)
  {
    return false;
  }

  SkipWhiteSpace(str);
  if (*str == 0)
  {
    outp_str = val.GetStringVal();
    return true;
  }

  return false;
}

void StormExprEvalBuilder::SkipWhiteSpace(const char *& str)
{
  while (iswspace(*str))
  {
    str++;
  }
}

bool StormExprEvalBuilder::IsIdentifierStartCharacter(char c)
{
  if (c == '_')
  {
    return true;
  }

  if (c >= 'a' && c <= 'z')
  {
    return true;
  }

  if (c >= 'A' && c <= 'Z')
  {
    return true;
  }

  return false;
}

bool StormExprEvalBuilder::IsIdentifierCharacter(char c)
{
  if (c >= '0' && c <= '9')
  {
    return true;
  }

  if (c == '.')
  {
    return true;
  }

  return IsIdentifierStartCharacter(c);
}


bool StormExprEvalBuilder::ParseIdentifier(const char * str, const char * & result, const char *&error, const char *& error_desc, uint32_t & identifier_hash)
{
  if (!IsIdentifierStartCharacter(*str))
  {
    return false;
  }

  auto start_identifier = str;
  auto end_identifier = str;

  end_identifier++;

  while (true)
  {
    if (!IsIdentifierCharacter(*end_identifier))
    {
      break;
    }

    end_identifier++;
  }


  identifier_hash = (uint32_t)StormExprHashString(start_identifier, end_identifier);
  result = end_identifier;
  return true;
}

bool StormExprEvalBuilder::ParseNumber(const char * str, const char * & result, const char *&error, const char *& error_desc, StormExprValue & value)
{
  char * parse_end;
  float f = (float)strtod(str, &parse_end);

  if (parse_end != str)
  {
    value = f;
    result = parse_end;
    return true;
  }

  return false;
}

bool StormExprEvalBuilder::ParseString(const char * str, const char * & result, const char *&error, const char *& error_desc, StormExprValue & value)
{
  if (*str != '\"')
  {
    return false;
  }

  auto str_start = str;

  str++;
  std::string data;

  while (true)
  {
    if (*str == '0')
    {
      error = str_start;
      error_desc = "String literal has no end quote";
      return false;
    }

    if (*str == '\"')
    {
      value = data.c_str();
      
      str++;
      result = str;
      return true;
    }

    if (*str == '\\')
    {
      str++;
      if (*str == '0')
      {
        return false;
      }

      switch (*str)
      {
      case '\"':
        data += '\"';
        break;
      case '\\':
        data += '\\';
        break;
      case '/':
        data += '/';
        break;
      case 'b':
        data += '\b';
        break;
      case 'f':
        data += '\f';
        break;
      case 'r':
        data += '\r';
        break;
      case 'n':
        data += '\n';
        break;
      case 't':
        data += '\t';
        break;
      default:
        data += '\\';
        data += *str;
        break;
      }
    }
    else
    {
      data += *str;
    }

    str++;
  }
}

bool StormExprEvalBuilder::ParseNothing(const char * str, const char * & result, const char *&error, const char *& error_desc)
{
  if (*str != 'n')
  {
    return false;
  }
  
  str++;
  if (*str != 'u')
  {
    return false;
  }

  str++;
  if (*str != 'l')
  {
    return false;
  }

  str++;
  if (*str != 'l')
  {
    return false;
  }

  result = str;
  return true;
}

bool StormExprEvalBuilder::ParseBasicOperation(const char * str, const char * & result, const char *&error, const char *& error_desc, StormExprOperatorType & op)
{
  if (*str == '!')
  {
    if (*(str + 1) == '=')
    {
      op = StormExprOperatorType::kNeq;
      result = str + 2;
      return true;
    }

    op = StormExprOperatorType::kNeg;
    result = str + 1;
    return true;
  }

  if (*str == '+')
  {
    op = StormExprOperatorType::kAdd;
    result = str + 1;
    return true;
  }

  if (*str == '-')
  {
    op = StormExprOperatorType::kSub;
    result = str + 1;
    return true;
  }

  if (*str == '*')
  {
    op = StormExprOperatorType::kMul;
    result = str + 1;
    return true;
  }

  if (*str == '/')
  {
    op = StormExprOperatorType::kDiv;
    result = str + 1;
    return true;
  }

  if (*str == '%')
  {
    op = StormExprOperatorType::kMod;
    result = str + 1;
    return true;
  }

  if (*str == '=' && *(str + 1) == '=')
  {
    op = StormExprOperatorType::kEq;
    result = str + 1;
    return true;
  }

  if (*str == '>')
  {
    if (*(str + 1) == '=')
    {
      op = StormExprOperatorType::kGte;
      result = str + 2;
      return true;
    }

    op = StormExprOperatorType::kGt;
    result = str + 1;
    return true;
  }

  if (*str == '<')
  {
    if (*(str + 1) == '=')
    {
      op = StormExprOperatorType::kLte;
      result = str + 2;
      return true;
    }

    op = StormExprOperatorType::kLt;
    result = str + 1;
    return true;
  }

  if (*str == '?')
  {
    if (*(str + 1) == '?')
    {
      op = StormExprOperatorType::kRiv;
      result = str + 2;
      return true;
    }

    op = StormExprOperatorType::kTernary;
    result = str + 1;
    return true;
  }
  
  if (*str == ':')
  {
    op = StormExprOperatorType::kTernaryEnd;
    result = str + 1;
    return true;
  }

  return false;
}

bool StormExprEvalBuilder::ParseStatementElement(const char * str, const char * & result, const char *&error, const char *& error_desc, 
                                                 StormExprStatementBlockElement & elem, int paren_level, int function_call_level)
{
  SkipWhiteSpace(str);

  auto start_str = str;

  if (*str == 0)
  {
    return false;
  }

  if (*str == '(')
  {
    str++;
    StormExprStatementBlock * block = new StormExprStatementBlock();
    if (ParseStatement(str, str, error, error_desc, *block, paren_level + 1, 0))
    {
      elem = StormExprStatementBlockElement(start_str, block);
      result = str;
      return true;
    }

    delete block;
    return false;
  }

  if (*str == '[')
  {
    str++;

    auto ident_start = str;
    auto ident_end = str;

    uint32_t func_name_hash = 0;
    if (ParseIdentifier(str, ident_end, error, error_desc, func_name_hash) == false)
    {
      error = ident_start;
      error_desc = "Could not parse function name";
      return false;
    }

    str = ident_end;
    SkipWhiteSpace(str);

    if (*str == ']')
    {
      elem = StormExprStatementBlockElement(start_str, func_name_hash, {});
    }
    else
    {
      std::vector<StormExprStatementBlock *> sub_blocks;
      while (true)
      {
        StormExprStatementBlock * block = new StormExprStatementBlock();
        if (ParseStatement(str, str, error, error_desc, *block, 0, function_call_level + 1) == false)
        {
          delete block;
          return false;
        }

        sub_blocks.push_back(block);
        SkipWhiteSpace(str);

        if (*str == ']')
        {
          break;
        }

        if (*str != ',')
        {
          error = ident_start;
          error_desc = "Could not parse function parameter";
          return false;
        }

        str++;
      }

      elem = StormExprStatementBlockElement(start_str, func_name_hash, sub_blocks);
      result = str + 1;
      return true;
    }
  }

  if (ParseNothing(str, str, error, error_desc))
  {
    int value_id = (int)m_LiteralBlockBuilder.AddLiteral(StormExprValue{});
    elem = StormExprStatementBlockElement(start_str, value_id);

    result = str;
    return true;
  }

  if (IsIdentifierStartCharacter(*str))
  {
    uint32_t hash;
    if (ParseIdentifier(str, str, error, error_desc, hash) == false)
    {
      return false;
    }

    int value_id = m_InitBlockList->LookupValueIndexByNameHash(hash);

    if (value_id == -1)
    {
      error = start_str;
      error_desc = "Identifier not defined";
      return false;
    }

    elem = StormExprStatementBlockElement(start_str, value_id);
    result = str;
    return true;
  }

  if (*str == '\"')
  {
    StormExprValue str_value;
    if (ParseString(str, str, error, error_desc, str_value) == false)
    {
      return false;
    }

    int value_id = (int)m_LiteralBlockBuilder.AddLiteral(std::move(str_value));
    elem = StormExprStatementBlockElement(start_str, value_id);

    result = str;
    return true;
  }

  if (*str == '+' || *str == '-' || (*str >= '0' && *str <= '9') || *str == '.')
  {
    StormExprValue number_value;
    if (ParseNumber(str, str, error, error_desc, number_value))
    {
      int value_id = (int)m_LiteralBlockBuilder.AddLiteral(std::move(number_value));
      elem = StormExprStatementBlockElement(start_str, value_id);

      result = str;
      return true;
    }
  }

  StormExprOperatorType op;
  if (ParseBasicOperation(str, str, error, error_desc, op))
  {
    elem = StormExprStatementBlockElement(start_str, op);
    result = str;
    return true;
  }

  error = start_str;
  error_desc = "Parse error";
  return false;
}

bool StormExprEvalBuilder::ParseStatement(const char * str, const char * & result, const char *&error, const char *& error_desc, StormExprStatementBlock & block, int paren_level, int function_call_level)
{
  auto start_str = str;

  while (true)
  {
    SkipWhiteSpace(str);

    if (*str == ')')
    {
      if (paren_level == 0)
      {
        error = str;
        error_desc = "Closing parentheses that was never opened";
        return false;
      }

      if (block.GetNumElements() == 0)
      {
        error = str;
        error_desc = "No statements in parentheses";
        return false;
      }

      result = str + 1;
      return true;
    }

    if (*str == ',')
    {
      if (function_call_level == 0)
      {
        error = str;
        error_desc = "Unexpected comma separator";
        return false;
      }

      if (block.GetNumElements() == 0)
      {
        error = str;
        error_desc = "No statements in parameter block";
        return false;
      }

      result = str;
      return true;
    }

    if (*str == ']')
    {
      if (function_call_level == 0)
      {
        error = str;
        error_desc = "Closing function call that was never opened";
        return false;
      }

      if (block.GetNumElements() == 0)
      {
        error = str;
        error_desc = "No statements in parameter block";
        return false;
      }

      result = str;
      return true;
    }

    if (*str == 0)
    {
      if (paren_level != 0)
      {
        error = start_str;
        error_desc = "Parentheses was not closed";
        return false;
      }

      if (block.GetNumElements() == 0)
      {
        error = str;
        error_desc = "No statements";
        return false;
      }

      result = str;
      return true;
    }

    StormExprStatementBlockElement elem;
    if (ParseStatementElement(str, str, error, error_desc, elem, paren_level, function_call_level) == false)
    {
      return false;
    }

    block.PushStatementElement(std::move(elem));
  }
}

bool StormExprEvalBuilder::CompileOperand(StormExprStatementBlock & statement_block, std::size_t & index, StormExprOpList & op_list, const char * start, const char *&error, const char *& error_desc)
{
  auto & elems = statement_block.GetStatementList();
  while (true)
  {
    if (index >= (int)statement_block.GetNumElements())
    {
      error = start;
      error_desc = "Expected operand";
      return false;
    }

    auto & elem = elems[index];
    if (elem.GetType() == StormExprStatementBlockElementType::kOperator)
    {
      if (IsUniaryOperator(elem.GetOperatorType()) == false)
      {
        error = start;
        error_desc = "Expected operand";
        return false;
      }

      index++;
      if (CompileOperand(statement_block, index, op_list, elem.GetStart(), error, error_desc) == false)
      {
        return false;
      }

      CompileOperator(elem, op_list);
      return true;
    }

    if (elem.GetType() == StormExprStatementBlockElementType::kValue)
    {
      CompileLoad(elem, op_list);
      return true;
    }
    else if(elem.GetType() == StormExprStatementBlockElementType::kSubBlock)
    {
      auto statement_block = elem.GetSubBlock();

      std::size_t index = 0;
      return CompileStatement(*statement_block, op_list, index, elem.GetStart(), error, error_desc, 0);
    }
    else if (elem.GetType() == StormExprStatementBlockElementType::kFunctionCall)
    {
      auto & func_info = elem.GetFunctionInfo();
      
      StormExprFunctionCallback func_cb;
      ptrdiff_t user_data;
      if (m_Functions.LookupFunction(func_info.m_FunctionNameHash, func_cb, user_data) == false)
      {
        error = elem.GetStart();
        error_desc = "Unknown function";
        return false;
      }

      for (int index = 0; index < func_info.m_SubBlockCount; ++index)
      {
        std::size_t block_index = 0;
        if (CompileStatement(*func_info.m_SubBlocks[index], op_list, block_index, elem.GetStart(), error, error_desc, 0) == false)
        {
          return false;
        }
      }

      op_list.push_back(StormExprOp{ StormExprLoadLit, func_info.m_SubBlockCount });
      op_list.push_back(StormExprOp{ func_cb, (ptrdiff_t)user_data });
      return true;
    }
  }
}

void StormExprEvalBuilder::CompileOperator(const StormExprStatementBlockElement & op, StormExprOpList & op_list)
{
  op_list.emplace_back(StormExprGetOpForOperator(op.GetOperatorType()));
}

void StormExprEvalBuilder::CompileOperatorFlush(std::vector<StormExprStatementBlockElement> & operator_stack, StormExprOpList & op_list)
{
  while (operator_stack.size() > 0)
  {
    op_list.emplace_back(StormExprGetOpForOperator(operator_stack.back().GetOperatorType()));
    operator_stack.pop_back();
  }
}

void StormExprEvalBuilder::CompileLoad(const StormExprStatementBlockElement & op, StormExprOpList & op_list)
{
  op_list.emplace_back(StormExprOp{ StormExprLoad, op.GetValueId() });
}

bool StormExprEvalBuilder::CompileStatement(StormExprStatementBlock & statement_block, StormExprOpList & op_list, std::size_t & index,
  const char * start, const char *&error, const char *& error_desc, int ternary_stack_size)
{
  auto & elems = statement_block.GetStatementList();
  if (index >= statement_block.GetNumElements())
  {
    error = start;
    error_desc = "Expected operand";
    return false;
  }

  int value_stack_depth = 0;

  std::vector<StormExprStatementBlockElement> operator_stack;
  while(true)
  {
    if (CompileOperand(statement_block, index, op_list, start, error, error_desc) == false)
    {
      return false;
    }

    index++;
    if (index >= statement_block.GetNumElements())
    {
      CompileOperatorFlush(operator_stack, op_list);
      return true;
    }

    auto & elem = elems[index];
    
    if (elem.GetType() != StormExprStatementBlockElementType::kOperator)
    {
      error = elem.GetStart();
      error_desc = "Expected operator";
      return false;
    }

    if (elem.GetOperatorType() == StormExprOperatorType::kTernary)
    {
      CompileOperatorFlush(operator_stack, op_list);
      index++;

      if (CompileStatement(statement_block, op_list, index, elem.GetStart() + 1, error, error_desc, ternary_stack_size + 1) == false)
      {
        return false;
      }

      if (CompileStatement(statement_block, op_list, index, elem.GetStart() + 1, error, error_desc, ternary_stack_size) == false)
      {
        return false;
      }

      op_list.emplace_back(StormExprGetOpForOperator(StormExprOperatorType::kTernaryEnd));
      return true;
    }

    if (elem.GetOperatorType() == StormExprOperatorType::kTernaryEnd)
    {
      if (ternary_stack_size == 0)
      {
        error = elem.GetStart();
        error_desc = "Unexpected ternary end operator";
        return false;
      }

      CompileOperatorFlush(operator_stack, op_list);
      index++;
      return true;
    }

    auto op_precedence = StormExprGetOperatorPrecedence(elem.GetOperatorType());
    while (operator_stack.size() > 0 && op_precedence >= StormExprGetOperatorPrecedence(operator_stack.back().GetOperatorType()))
    {
      auto & back_operator = operator_stack.back();
      CompileOperator(back_operator, op_list);
      operator_stack.pop_back();
    }

    operator_stack.emplace_back(std::move(elem));
    index++;
  }
}
