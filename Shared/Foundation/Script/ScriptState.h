#pragma once

#include "Foundation/Any/Any.h"
#include "Foundation/Script/ScriptValue.h"
#include "Foundation/Allocator/IdAllocator.h"

class ScriptObject;

struct lua_State;

class ScriptState
{
public:
  ScriptState();
  ~ScriptState();
  ScriptState(const ScriptState & rhs) = delete;
  ScriptState(ScriptState && rhs) = delete;

  ScriptState & operator =(const ScriptState & rhs) = delete;
  ScriptState & operator =(ScriptState && rhs) = delete;

  void SetErrorDelegate(Delegate<void, czstr> && error_output);

  void LoadScript(const std::string_view & data, czstr module_name);
  void LoadScript(const void * data, std::size_t length, czstr module_name);

  ScriptObject CreateScriptObject();

  bool Call(czstr name, std::initializer_list<ScriptValue> args, NullOptPtr<ScriptValue> return_val = nullptr);
  void SetGlobal(czstr name, const ScriptValue & value);
  void SetGlobalFunction(czstr name, int (*Func)(lua_State * state));
  void ClearGlobal(czstr name);

private:
  friend class ScriptInternal;
  friend class ScriptClassBase;
  friend class ScriptClassInternal;
  friend class ScriptFuncs;

private:

  void * m_LuaState;
  IdAllocator m_GlobalIdAllocator;

  Delegate<void, czstr> m_ErrorOutput;
};
