#pragma once

#include "Foundation/Common.h"
#include "Runtime/Event/Event.h"

class ServerObject;

class GameLogicContainer;

class ServerObjectEventDispatch
{
public:
  bool TriggerEventHandler(NotNullPtr<ServerObject> obj, uint32_t type, void * ev, const EventMetaData & meta);

  template <typename ServerObjectType, typename EventType>
  void RegisterEventHandler(bool (ServerObjectType::* handler)(EventType &, const EventMetaData & meta))
  {
    using Handler = bool (ServerObjectType::*)(EventType &, const EventMetaData &);

    EventHandlerInfo handler_info;
    handler_info.m_Type = EventType::TypeNameHash;
    handler_info.m_Callback = [](NotNullPtr<ServerObject> obj, void * ev, void * func, const EventMetaData & meta)
    {
      Handler * handler_mem = reinterpret_cast<Handler *>(func);
      auto handler = *handler_mem;

      NotNullPtr<ServerObjectType> ptr = static_cast<NotNullPtr<ServerObjectType>>(obj);
      return (ptr->*handler)(*static_cast<EventType *>(ev), meta);
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
    bool(*m_Callback)(NotNullPtr<ServerObject> obj, void * ev, void * func, const EventMetaData & meta);

    alignas(alignof(FuncType)) char m_Buffer[sizeof(FuncType)];
  };

  std::vector<EventHandlerInfo> m_EventHandlers;
};



