#pragma once

#include "Foundation/Any/Any.h"
#include "Foundation/Script/ScriptValue.h"
#include "Foundation/Allocator/IdAllocator.h"

class ScriptObject;

class ScriptState
{
public:
  ScriptState();
  ScriptState(const ScriptState & rhs) = delete;
  ScriptState(ScriptState && rhs) = delete;

  ScriptState & operator =(const ScriptState & rhs) = delete;
  ScriptState & operator =(ScriptState && rhs) = delete;

  void SetErrorDelegate(Delegate<void, czstr> && error_output);

  void LoadScript(const std::string_view & data, czstr module_name);
  void LoadScript(const void * data, std::size_t length, czstr module_name);

  ScriptObject CreateScriptObject();

  bool Call(czstr name, std::initializer_list<ScriptValue> args, NullOptPtr<ScriptValue> return_val);


private:
  friend class ScriptInternal;

private:

  void * m_LuaState;
  IdAllocator m_GlobalIdAllocator;

  Delegate<void, czstr> m_ErrorOutput;
};
