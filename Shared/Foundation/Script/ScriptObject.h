#pragma once


#include "Foundation/Script/ScriptValue.h"

class ScriptState;

class ScriptObject
{
public:
  ScriptObject() = default;
  ScriptObject(const ScriptObject & rhs) = delete;
  ScriptObject(ScriptObject && rhs);

  ScriptObject & operator = (const ScriptObject & rhs) = delete;
  ScriptObject & operator = (ScriptObject && rhs);

  ~ScriptObject();

  void Clear();

  ScriptValue ReadValue(czstr name) const;
  void WriteValue(czstr name, const ScriptValue & value);

  bool Call(czstr name, std::initializer_list<ScriptValue> args, NullOptPtr<ScriptValue> return_val);


  int GetGlobalId() const;
protected:
  friend class ScriptInternal;

  ScriptObject(NotNullPtr<ScriptState> script_state, int global_id);

  NotNullPtr<ScriptState> m_ScriptState = nullptr;
  int m_RefCount = 0;
  int m_GlobalId = 0;
};
