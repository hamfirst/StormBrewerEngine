
#include "Foundation/Common.h"
#include "Foundation/Script/ScriptState.h"
#include "Foundation/Script/ScriptObject.h"
#include "Foundation/Script/ScriptInternal.h"

ScriptState::ScriptState()
{
  m_LuaState = ScriptInternal::InitState(this);

  m_ErrorOutput = [](czstr message) { printf("%s\n", message); };
}

ScriptState::~ScriptState()
{
  ScriptInternal::CloseState(m_LuaState);
}

void ScriptState::SetErrorDelegate(Delegate<void, czstr> && error_output)
{
  m_ErrorOutput = std::move(error_output);
}

void ScriptState::LoadScript(const std::string_view & data, czstr module_name)
{
  ScriptInternal::LoadScriptBlock(this, data.data(), data.size(), module_name);
}

void ScriptState::LoadScript(const void * data, std::size_t length, czstr module_name)
{
  ScriptInternal::LoadScriptBlock(this, data, length, module_name);
}

ScriptObject ScriptState::CreateScriptObject()
{
  return ScriptInternal::CreateScriptObject(this);
}

bool ScriptState::Call(czstr name, std::initializer_list<ScriptValue> args, NullOptPtr<ScriptValue> return_val)
{
  ScriptInternal::LoadGlobalValue(name, this);
  if(ScriptInternal::CallScriptFunc(this, args, return_val != nullptr ? 1 : 0))
  {
    if(return_val)
    {
      *return_val = ScriptInternal::SaveScriptValueFromStack(this);
    }

    return true;
  }

  return false;
}

void ScriptState::BindAsGlobal(czstr name, const ScriptValue & value)
{
  ScriptInternal::CreateGlobalFromScriptObject(name, value, this);
}

void ScriptState::ClearGlobal(czstr name)
{
  ScriptInternal::DeleteGlobal(name, this);
}
