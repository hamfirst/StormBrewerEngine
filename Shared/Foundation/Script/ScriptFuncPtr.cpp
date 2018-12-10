
#include "Foundation/Script/ScriptFuncPtr.h"
#include "Foundation/Script/ScriptInternal.h"

ScriptFuncPtr::ScriptFuncPtr(NotNullPtr<ScriptState> script_state, int global_id)
{
  m_ScriptState = script_state;
  m_GlobalId = global_id;
}

ScriptFuncPtr::ScriptFuncPtr(ScriptFuncPtr && rhs)
{
  m_ScriptState = rhs.m_ScriptState;
  m_GlobalId = rhs.m_GlobalId;

  rhs.m_ScriptState = nullptr;
  rhs.m_GlobalId = 0;
}

ScriptFuncPtr & ScriptFuncPtr::operator = (ScriptFuncPtr && rhs)
{
  Clear();
  m_ScriptState = rhs.m_ScriptState;
  m_GlobalId = rhs.m_GlobalId;

  rhs.m_ScriptState = nullptr;
  rhs.m_GlobalId = 0;
  return *this;
}

ScriptFuncPtr::~ScriptFuncPtr()
{
  Clear();
}

void ScriptFuncPtr::Clear()
{
  if(m_GlobalId != 0 && m_ScriptState == nullptr)
  {
    ScriptInternal::DeleteGlobalObject(m_ScriptState, m_GlobalId);

    m_GlobalId = 0;
    m_ScriptState = nullptr;
  }
}
