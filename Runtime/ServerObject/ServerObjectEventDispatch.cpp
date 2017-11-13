
#include "Runtime/RuntimeCommon.h"
#include "Runtime/ServerObject/ServerObjectEventDispatch.h"

void ServerObjectEventDispatch::TriggerEventHandler(NotNullPtr<ServerObject> obj, uint32_t type, const void * ev, GameLogicContainer & game_container)
{
  for (auto & handler : m_EventHandlers)
  {
    if (handler.m_Type == type)
    {
      handler.m_Callback(obj, ev, handler.m_Buffer, game_container);
      break;
    }
  }
}


