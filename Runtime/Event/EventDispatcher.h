#pragma once

#include "Runtime/RuntimeCommon.h"

#include "Foundation/Any/Any.h"

using EventDelegateBuffer = StaticAny<sizeof(Delegate<void>)>;

template <typename Source, typename UserData>
struct EventHandler
{
  UserData m_UserData;
  uint32_t m_EventType;
  uint32_t m_HandlerKey;

  EventDelegateBuffer m_Handler;
  void(*m_Caller)(EventDelegateBuffer &, const void *, NullOptPtr<Source>);
  bool m_Dead;
};

template <typename Source, typename UserData>
class EventDispatch
{
public:

  template <typename EventType>
  uint32_t AddEventHandler(Delegate<void, const EventType &, NullOptPtr<Source>> && handler, const UserData & user_data)
  {
    m_EventHandlers.emplace_back(EventHandler<Source, UserData> {
      user_data,
      EventType::TypeNameHash,
      GetRandomNumber(),
      EventDelegateBuffer(std::move(handler)),
      [](EventDelegateBuffer & handler, const void * event, NullOptPtr<Source> source)
      { 
        auto del = handler.Get<Delegate<void, const EventType &, NullOptPtr<Source>>>();
        del->Call(*static_cast<const EventType *>(event), source);
      },
      false
    });

    return m_EventHandlers.back().m_HandlerKey;
  }

  void RemoveEvent(uint32_t event_handler_key)
  {
    for (auto & handler : m_EventHandlers)
    {
      if (handler.m_EventType == event_handler_key && handler.m_Dead == false)
      {
        handler.m_Dead = true;
        return;
      }
    }
  }

  void RemoveEventsByUserData(const UserData & user_data)
  {
    for (auto & handler : m_EventHandlers)
    {
      if (handler.m_UserData == user_data && handler.m_Dead == false)
      {
        handler.m_Dead = true;
      }
    }
  }

  void TriggerEvent(uint32_t type_name_hash, const void * event, NullOptPtr<Source> source)
  {
    for (auto & handler : m_EventHandlers)
    {
      if (handler.m_EventType == type_name_hash && handler.m_Dead == false)
      {
        handler.m_Caller(handler.m_Handler, event, source);
      }
    }
  }

  template <typename T> 
  void TriggerEvent(T & event)
  {
    TriggerEvent(T::TypeNameHash, &event);
  }

  void ClearDeadHandlers()
  {
    std::remove_if(m_EventHandlers.begin(), m_EventHandlers.end(), [](const EventHandler<Source, UserData> & a) { return a.m_Dead; });
  }

  void ClearAllHandlers()
  {
    m_EventHandlers.clear();
  }

private:
  std::vector<EventHandler<Source, UserData>> m_EventHandlers;
};
