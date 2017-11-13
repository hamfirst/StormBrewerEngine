
#include "Runtime/RuntimeCommon.h"
#include "Runtime/ServerObject/ServerObjectHandle.h"
#include "Runtime/ServerObject/ServerObjectManager.h"

ServerObjectHandle::ServerObjectHandle() :
  m_SlotId(-1),
  m_Gen(0)
{
  
}

void ServerObjectHandle::Reset()
{
  m_SlotId = -1;
  m_Gen = 0;
}

void ServerObjectHandle::ResetGen(const ServerObjectManager & object_manager)
{
  if (Resolve(object_manager) == nullptr)
  {
    m_SlotId = -1;
    m_Gen = 0;
  }
  else
  {
    m_Gen = 0;
  }
}


int ServerObjectHandle::GetRawSlotIndex() const
{
  return m_SlotId;
}

NullOptPtr<ServerObject> ServerObjectHandle::Resolve(const ServerObjectManager & object_manager)
{
  return object_manager.ResolveHandle(m_SlotId, m_Gen);
}

template <>
NullOptPtr<ServerObject> ServerObjectHandle::ResolveTo<ServerObject>(const ServerObjectManager & object_manager)
{
  return Resolve(object_manager);
}
