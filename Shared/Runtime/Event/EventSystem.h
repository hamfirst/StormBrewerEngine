#pragma once

#include "Runtime/RuntimeCommon.h"
#include "Runtime/Event/Event.h"

#include "Foundation/Any/Any.h"
#include "Foundation/SpatialDatabase/SpatialDatabase.h"

template <typename EventType>
struct EventDef
{

};

template <typename ObjectType, typename HandleType>
class EventSystem
{
public:

  template <typename Event, typename ... InitArgs>
  NotNullPtr<Event> PushEventSource(const Box & box, const EventMetaData & meta, EventDef<Event> event_type, InitArgs && ... init_args)
  {
    EventSrc event_data;
    event_data.m_Type = Event::TypeNameHash;
    event_data.m_EventData = Any(Event(std::forward<InitArgs>(init_args)...));
    event_data.m_Callback = [](NotNullPtr<EventSrc> src_data, NotNullPtr<EventDest> dest_data, NotNullPtr<ObjectType> dst)
    {
      return dst->TriggerEventHandler(src_data->m_Type, src_data->m_EventData.template Get<Event>(), src_data->m_Meta);
    };

    event_data.m_Meta = meta;

    auto id = m_Events.size();
    m_Events.emplace_back(std::move(event_data));

    m_EventDatabase.Insert(box, (uint32_t)id);
    return m_Events.back().m_EventData.template Get<Event>();
  }

  template <typename Event>
  void PushEventReceiver(const HandleType & handle, const Box & box)
  {
    EventDest dest;
    dest.m_Handle = handle;
    dest.m_Box = box;
    dest.m_Type = Event::TypeNameHash;
    m_EventReceivers.emplace_back(std::move(dest));
  }

  template <typename ... ResolveArgs>
  void FinalizeEvents(ResolveArgs && ... resolve_args)
  {
    std::vector<std::size_t> event_ids;
    for (auto & r : m_EventReceivers)
    {
      auto obj = r.m_Handle.Resolve(std::forward<ResolveArgs>(resolve_args)...);
      if (obj == nullptr)
      {
        continue;
      }

      event_ids.clear();
      m_EventDatabase.Query(r.m_Box, event_ids);

      for (auto id : event_ids)
      {
        if (m_Events[id].m_Callback(&m_Events[id], &r, obj) == false)
        {
          break;
        }
      }
    }

    m_Events.clear();
    m_EventReceivers.clear();

    m_EventDatabase.Clear();
  }

private:

  struct EventDest;
  struct EventSrc;

  struct EventSrc
  {
    uint32_t m_Type;
    Any m_EventData;
    EventMetaData m_Meta;
    bool (*m_Callback)(NotNullPtr<EventSrc>, NotNullPtr<EventDest>, NotNullPtr<ObjectType>);
  };

  struct EventDest
  {
    HandleType m_Handle;
    uint32_t m_Type;
    Box m_Box;
  };

  std::vector<EventSrc> m_Events;
  std::vector<EventDest> m_EventReceivers;

  SpatialDatabase m_EventDatabase;
};

