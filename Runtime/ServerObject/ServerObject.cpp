
#include "Runtime/RuntimeCommon.h"
#include "Runtime/ServerObject/ServerObject.h"
#include "Runtime/ServerObject/ServerObjectManager.h"
#include "Runtime/ServerObject/ServerObjectSerialize.h"
#include "Runtime/ServerObject/ServerObjectEventRegister.h"
#include "Runtime/ServerObject/ServerObjectRegistrationMacros.h"
#include "Runtime/ServerObject/ServerObjectMetaFuncs.h"
#include "Runtime/ServerObject/ServerObjectSystem.h"
#include "Runtime/ServerObject/ServerObjectUpdate.h"
#include "Runtime/ServerObject/ServerObjectEventDispatch.h"

#include "Foundation/SkipField/SkipField.h"
#include "Foundation/Update/UpdateRegistrationTemplates.h"

REGISTER_BASE_SERVER_OBJECT(ServerObject);

ServerObjectHandle ServerObject::GetObjectHandle() const
{
  return m_ServerObjectHandle;
}

const Handle & ServerObject::GetHandle() const
{
  return m_Handle;
}

void ServerObject::SetHandle(Handle & handle)
{
  m_Handle = handle;
}

void ServerObject::SetIterator(const SkipFieldIterator & itr)
{
  m_Iterator = itr;
}

const SkipFieldIterator & ServerObject::GetIterator() const
{
  return m_Iterator;
}

void ServerObject::Destroy(ServerObjectManager & obj_manager)
{
  obj_manager.DestroyDynamicObjectInternal(this);
}

void ServerObject::InitPosition(const Vector2 & pos)
{

}

czstr ServerObject::GetDefaultEntityBinding() const
{
  return nullptr;
}

czstr ServerObject::GetEntityBinding() const
{
  return GetDefaultEntityBinding();
}

bool ServerObject::IsDestroyed() const
{
  return false;
}

int ServerObject::GetSlotIndex() const
{
  return m_SlotIndex;
}

int ServerObject::GetLifetime() const
{
  return std::min(m_FramesAlive, 7);
}

int ServerObject::GetTypeIndex() const
{
  return m_TypeIndex;
}

bool ServerObject::TriggerEventHandler(uint32_t event_type, const void * ev, const EventMetaData & meta)
{
  if (m_EventDispatch == nullptr)
  {
    return true;
  }

  return m_EventDispatch->TriggerEventHandler(this, event_type, ev, meta);
}

void ServerObject::SetEventDispatch(NotNullPtr<ServerObjectEventDispatch> event_dispatch)
{
  m_EventDispatch = event_dispatch;
}
