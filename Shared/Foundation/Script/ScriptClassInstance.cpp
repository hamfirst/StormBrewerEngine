

#include "Foundation/Common.h"
#include "Foundation/Script/ScriptClassInstance.h"
#include "Foundation/Script/ScriptInternal.h"


ScriptClassInstance::ScriptClassInstance(NotNullPtr<ScriptState> script_state, int global_id) :
  m_ScriptState(script_state),
  m_GlobalId(global_id)
{

}

void * ScriptClassInstance::CheckType(std::size_t type_id_hash) const
{
  if(m_GlobalId == 0 || m_ScriptState == nullptr)
  {
    return nullptr;
  }

  auto instance_info = ScriptInternal::ReadInstanceInfo(*this, m_ScriptState);
  if(instance_info == nullptr || instance_info->m_RefData == nullptr || instance_info->m_TypeNameHash != type_id_hash)
  {
    return nullptr;
  }

  return instance_info->m_RefData->m_Instance;
}

ScriptClassInstance::ScriptClassInstance(ScriptClassInstance && rhs)
{
  m_ScriptState = rhs.m_ScriptState;
  m_GlobalId = rhs.m_GlobalId;

  rhs.m_ScriptState = nullptr;
  rhs.m_GlobalId = 0;
}

ScriptClassInstance & ScriptClassInstance::operator = (ScriptClassInstance && rhs)
{
  Clear();
  m_ScriptState = rhs.m_ScriptState;
  m_GlobalId = rhs.m_GlobalId;

  rhs.m_ScriptState = nullptr;
  rhs.m_GlobalId = 0;
  return *this;
}

ScriptClassInstance::~ScriptClassInstance()
{
  Clear();
}

void ScriptClassInstance::Clear()
{
  if(m_ScriptState)
  {
    ScriptInternal::DeleteGlobalObject(m_ScriptState, m_GlobalId);
    m_ScriptState = nullptr;
    m_GlobalId = 0;
  }
}

