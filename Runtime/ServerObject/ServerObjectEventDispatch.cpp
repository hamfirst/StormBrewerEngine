
#include "Runtime/RuntimeCommon.h"
#include "Runtime/ServerObject/ServerObjectEventDispatch.h"

bool ServerObjectEventDispatch::TriggerEventHandler(NotNullPtr<ServerObject> obj, uint32_t type, const void * ev, const EventMetaData & meta)
{
  for (auto & handler : m_EventHandlers)
  {
    if (handler.m_Type == type)
    {
      return handler.m_Callback(obj, ev, handler.m_Buffer, meta);
    }
  }

  return true;
}


