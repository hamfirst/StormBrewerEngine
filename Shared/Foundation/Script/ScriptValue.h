#pragma once

#include "Foundation/Variant/Variant.h"

class ScriptObject;
class ScriptClassInstance;
class ScriptFuncPtr;

using ScriptValue = Variant<int, float, bool, czstr, std::string,
        ScriptObject, std::shared_ptr<ScriptObject>,
        ScriptClassInstance, std::shared_ptr<ScriptClassInstance>,
        ScriptFuncPtr, std::shared_ptr<ScriptFuncPtr>>;


#include "Foundation/Script/ScriptFuncPtr.h"
#include "Foundation/Script/ScriptObject.h"
#include "Foundation/Script/ScriptClassInstance.h"

void ScriptValueCoerce(const ScriptValue & value, int & val);
void ScriptValueCoerce(const ScriptValue & value, float & val);
void ScriptValueCoerce(const ScriptValue & value, bool & val);
void ScriptValueCoerce(const ScriptValue & value, std::string & val);
