
#include "Foundation/Common.h"
#include "Foundation/Script/ScriptObject.h"
#include "Foundation/Script/ScriptState.h"
#include "Foundation/Script/ScriptInternal.h"


ScriptObject::ScriptObject(NotNullPtr<ScriptState> script_state, int global_id) :
  m_ScriptState(script_state),
  m_GlobalId(global_id)
{

}

ScriptObject::ScriptObject(ScriptObject && rhs)
{
  m_ScriptState = rhs.m_ScriptState;
  m_GlobalId = rhs.m_GlobalId;

  rhs.m_GlobalId = 0;
  rhs.m_ScriptState = nullptr;
}

ScriptObject & ScriptObject::operator = (ScriptObject && rhs)
{
  Clear();
  m_ScriptState = rhs.m_ScriptState;
  m_GlobalId = rhs.m_GlobalId;

  rhs.m_GlobalId = 0;
  rhs.m_ScriptState = nullptr;
  return *this;
}

ScriptObject::~ScriptObject()
{
  Clear();
}

void ScriptObject::Clear()
{
  if(m_ScriptState)
  {
    ScriptInternal::DeleteGlobalObject(m_ScriptState, m_GlobalId);
    m_ScriptState = nullptr;
    m_GlobalId = 0;
  }
}

ScriptValue ScriptObject::ReadValue(czstr name) const
{
  if(m_ScriptState == nullptr)
  {
    return {};
  }

  ScriptInternal::LoadTableValue(name, *this, m_ScriptState);
  return ScriptInternal::SaveScriptValueFromStack(m_ScriptState);
}

void ScriptObject::WriteValue(czstr name, const ScriptValue & value)
{
  if(m_ScriptState == nullptr)
  {
    return;
  }

  ScriptInternal::WriteTableValue(name, *this, value, m_ScriptState);
}

bool ScriptObject::Call(czstr name, std::initializer_list<ScriptValue> args, NullOptPtr<ScriptValue> return_val)
{
  if(m_ScriptState == nullptr)
  {
    return false;
  }

  ScriptInternal::LoadTableValue(name, *this, m_ScriptState);
  if(ScriptInternal::CallScriptFunc(m_ScriptState, args, return_val != nullptr ? 1 : 0))
  {
    if(return_val)
    {
      *return_val = ScriptInternal::SaveScriptValueFromStack(m_ScriptState);
    }

    return true;
  }

  return false;
}
