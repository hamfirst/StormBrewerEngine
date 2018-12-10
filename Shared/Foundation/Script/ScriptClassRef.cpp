
#include "Foundation/Common.h"
#include "Foundation/Script/ScriptClassRef.h"
#include "Foundation/Script/ScriptClass.h"

void ScriptClassRefData::IncRef()
{
  m_RefCount++;
}

void ScriptClassRefData::DecRef()
{
  m_RefCount--;
  ASSERT(m_RefCount >= 0, "Invalid ref count");

  if(m_RefCount == 0)
  {
    DeleteInst();
    delete this;
  }
}

void ScriptClassRefData::DeleteInst()
{
  if(m_Instance)
  {
    m_Class->DestroyObject(m_Instance);
    m_Instance = nullptr;
  }
}
