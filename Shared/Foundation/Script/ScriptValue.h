#pragma once

#include "Foundation/Variant/Variant.h"

class ScriptObject;

using ScriptValue = Variant<int, float, bool, czstr, std::string, ScriptObject>;

void ScriptValueCoerce(const ScriptValue & value, int & val);
void ScriptValueCoerce(const ScriptValue & value, float & val);
void ScriptValueCoerce(const ScriptValue & value, bool & val);
void ScriptValueCoerce(const ScriptValue & value, std::string & val);
