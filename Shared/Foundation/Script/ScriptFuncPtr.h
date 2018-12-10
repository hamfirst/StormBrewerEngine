#pragma once

class ScriptState;

class ScriptFuncPtr
{
public:
  ScriptFuncPtr() = default;
  ScriptFuncPtr(const ScriptFuncPtr & rhs) = delete;
  ScriptFuncPtr(ScriptFuncPtr && rhs);

  ScriptFuncPtr & operator = (const ScriptFuncPtr & rhs) = delete;
  ScriptFuncPtr & operator = (ScriptFuncPtr && rhs);

  ~ScriptFuncPtr();

  void Clear();

protected:
  friend class ScriptInternal;
  friend class ScriptFuncs;

  ScriptFuncPtr(NotNullPtr<ScriptState> script_state, int global_id);

  NotNullPtr<ScriptState> m_ScriptState = nullptr;
  int m_GlobalId = 0;
};
