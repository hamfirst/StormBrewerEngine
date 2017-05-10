#pragma once

#include "Runtime/RuntimeCommon.h"
#include "Runtime/Entity/Entity.h"
#include "Runtime/Entity/EntityHandle.h"

#include "Foundation/Any/Any.h"
#include "Foundation/SpatialDatabase/SpatialDatabase.h"

class Entity;

class EventSystem
{
public:

  template <typename Event, typename ... InitArgs>
  NotNullPtr<Event> PushEvent(const Box & box, InitArgs && ... init_args)
  {
    EventSrc event_data;
    event_data.m_Type = Event::TypeNameHash;
    event_data.m_EventData = Any(Event(std::forward<InitArgs>(init_args)...));
    event_data.m_Callback = [](NotNullPtr<EventSrc> src_data, NotNullPtr<EventDest> dest_data, NotNullPtr<Entity> entity)
    {
      entity->TriggerEventHandler(src_data->m_Type, src_data->m_EventData.Get<Event>());
    };

    auto id = m_Events.size();
    m_Events.emplace_back(std::move(event_data));

    m_EventDatabase.Insert(box, id);
    return m_Events.back().m_EventData.Get<Event>();
  }


  template <typename Event>
  void PushEventReceiver(NotNullPtr<Entity> entity, const Box & box)
  {
    EventDest dest;
    dest.m_EntityHandle = entity->GetHandle();
    dest.m_Box = box;
    m_EventReceivers.emplace_back(std::move(dest));
  }

  void FinalizeEvents();

private:
  struct EventDest;
  struct EventSrc;

  struct EventSrc
  {
    uint32_t m_Type;
    Any m_EventData;
    Delegate<void, NotNullPtr<EventSrc>, NotNullPtr<EventDest>, NotNullPtr<Entity>> m_Callback;
  };

  
  struct EventDest
  {
    EntityHandle m_EntityHandle;
    uint32_t m_Type;
    Box m_Box;
  };

  std::vector<EventSrc> m_Events;
  std::vector<EventDest> m_EventReceivers;

  SpatialDatabase m_EventDatabase;
};

