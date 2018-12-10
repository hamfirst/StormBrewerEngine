
#pragma once

#include "Foundation/Common.h"

class ScriptState;

class ScriptClassInstance
{
public:
  ScriptClassInstance() = default;
  ScriptClassInstance(const ScriptClassInstance & rhs) = delete;
  ScriptClassInstance(ScriptClassInstance && rhs);

  ScriptClassInstance & operator = (const ScriptClassInstance & rhs) = delete;
  ScriptClassInstance & operator = (ScriptClassInstance && rhs);

  ~ScriptClassInstance();

  void Clear();

  template <typename T>
  NullOptPtr<T> GetAs()
  {
    return static_cast<T *>(CheckType(typeid(T).hash_code()));
  }

  template <typename T>
  NullOptPtr<const T> GetAs() const
  {
    return static_cast<const T *>(CheckType(typeid(T).hash_code()));
  }

private:
  friend class ScriptInternal;

  ScriptClassInstance(NotNullPtr<ScriptState> script_state, int global_id);
  void * CheckType(std::size_t type_id_hash) const;

private:
  friend class ScriptInternal;
  friend class ScriptFuncs;

  NotNullPtr<ScriptState> m_ScriptState = nullptr;
  int m_GlobalId = 0;
};

