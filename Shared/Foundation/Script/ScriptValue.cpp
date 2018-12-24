#include "Foundation/Common.h"
#include "Foundation/Script/ScriptObject.h"
#include "Foundation/Script/ScriptValue.h"
#include "Foundation/Script/ScriptClass.h"
#include "Foundation/Script/ScriptFuncPtr.h"


bool ScriptValueParse(czstr data, ScriptValue & out)
{
  if(*data == 0)
  {
    out = {};
    return false;
  }

  char * end_ptr;
  auto integer = std::strtol(data, &end_ptr, 10);
  if(*end_ptr)
  {
    auto number = std::strtod(data, &end_ptr);
    if(*end_ptr)
    {
      if(!strcmp(data, "true"))
      {
        out = ScriptValue(true);
      }
      else if(!strcmp(data, "false"))
      {
        out = ScriptValue(false);
      }
      else
      {
        out = ScriptValue(std::string(data));
      }
      return true;
    }
    else
    {
      out = static_cast<float>(number);
      return true;
    }
  }
  else
  {
    out = static_cast<int>(integer);
    return true;
  }
}

void ScriptValueCoerce(const ScriptValue & val, int & value)
{
  switch(val.GetCurrentTypeIndex())
  {
    default:
      value = 0;
      break;
    case 0:
      value = val.GetAs<int>();
      break;
    case 1:
      value = static_cast<int>(val.GetAs<float>());
      break;
    case 2:
      value = static_cast<int>(val.GetAs<bool>());
      break;
    case 3:
      value = atoi(val.GetAs<czstr>());
      break;
    case 4:
      value = atoi(val.GetAs<std::string>().data());
      break;
  }

  static_assert(ScriptValue::kNumTypes == 11);
}

void ScriptValueCoerce(const ScriptValue & val, float & value)
{
  switch(val.GetCurrentTypeIndex())
  {
    default:
      value = 0.0f;
      break;
    case 0:
      value = static_cast<float>(val.GetAs<int>());
      break;
    case 1:
      value = val.GetAs<float>();
      break;
    case 2:
      value = static_cast<float>(val.GetAs<bool>());
      break;
    case 3:
      value = static_cast<float>(atof(val.GetAs<czstr>()));
      break;
    case 4:
      value = static_cast<float>(atof(val.GetAs<std::string>().data()));
      break;
  }

  static_assert(ScriptValue::kNumTypes == 11);
}

void ScriptValueCoerce(const ScriptValue & val, bool & value)
{
  switch(val.GetCurrentTypeIndex())
  {
    default:
      value = false;
      break;
    case 0:
      value = static_cast<bool>(val.GetAs<int>());
      break;
    case 1:
      value = static_cast<bool>(val.GetAs<float>());
      break;
    case 2:
      value = val.GetAs<bool>();
      break;
  }

  static_assert(ScriptValue::kNumTypes == 11);
}

void ScriptValueCoerce(const ScriptValue & val, std::string & value)
{
  switch(val.GetCurrentTypeIndex())
  {
    default:
      value.clear();
      break;
    case 0:
      value = std::to_string(val.GetAs<int>());
      break;
    case 1:
      value = std::to_string(val.GetAs<float>());
      break;
    case 2:
      value = std::to_string(val.GetAs<bool>());
      break;
    case 3:
      value = val.GetAs<czstr>();
      break;
    case 4:
      value = val.GetAs<std::string>();
      break;
  }

  static_assert(ScriptValue::kNumTypes == 11);
}
