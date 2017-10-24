#pragma once

#include "Foundation/Common.h"

class ServerObject;

class GameLogicContainer;

class ServerObjectEventDispatch
{
public:
  void TriggerEventHandler(NotNullPtr<ServerObject> obj, uint32_t type, const void * ev, GameLogicContainer & game_container);

  template <typename ServerObjectType, typename EventType>
  void RegisterEventHandler(void (ServerObjectType::* handler)(const EventType &, GameLogicContainer &))
  {
    using Handler = void (ServerObjectType::*)(const EventType &, GameLogicContainer &);

    EventHandlerInfo handler_info;
    handler_info.m_Type = EventType::TypeNameHash;
    handler_info.m_Callback = [](NotNullPtr<ServerObject> obj, const void * ev, void * func, GameLogicContainer & game_container)
    {
      Handler * handler_mem = reinterpret_cast<Handler *>(func);
      auto handler = *handler_mem;

      NotNullPtr<ServerObjectType> ptr = static_cast<NotNullPtr<ServerObjectType>>(obj);
      (ptr->*handler)(*static_cast<const EventType *>(ev), game_container);
    };

    Handler * handler_mem = reinterpret_cast<Handler *>(handler_info.m_Buffer);
    *handler_mem = handler;

    m_EventHandlers.emplace_back(std::move(handler_info));
  }

private:

  using FuncType = void (ServerObject::*)(GameLogicContainer &);

  struct EventHandlerInfo
  {
    uint32_t m_Type;
    void(*m_Callback)(NotNullPtr<ServerObject> obj, const void * ev, void * func, GameLogicContainer & game_container);

    alignas(alignof(FuncType)) char m_Buffer[sizeof(FuncType)];
  };

  std::vector<EventHandlerInfo> m_EventHandlers;
};



