
#include "Server/ServerCommon.h"
#include "Server/ServerObject/ServerObject.h"
#include "Server/ServerObject/ServerObjectManager.h"
#include "Server/ServerObject/ServerObjectSerialzie.h"
#include "Server/ServerObject/ServerObjectRegistrationMacros.h"
#include "Server/ServerObject/ServerObjectMetaFuncs.h"
#include "Server/ServerObject/ServerObjectSystem.h"
#include "Server/ServerObject/ServerObjectUpdate.h"
#include "Server/ServerObject/ServerObjectSerialzie.h"

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

czstr ServerObject::GetDefaultEntityBinding()
{
  return nullptr;
}

czstr ServerObject::GetEntityBinding()
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
