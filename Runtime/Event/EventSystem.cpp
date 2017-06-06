
#include "Runtime/RuntimeCommon.h"
#include "Runtime/Entity/Entity.h"
#include "Runtime/Event/EventSystem.h"

void EventSystem::FinalizeEvents()
{
  std::vector<std::size_t> event_ids;
  for (auto & r : m_EventReceivers)
  {
    auto entity = r.m_EntityHandle.Resolve();
    if (entity == nullptr)
    {
      continue;
    }

    event_ids.clear();
    m_EventDatabase.Query(r.m_Box, event_ids);

    for (auto id : event_ids)
    {
      m_Events[id].m_Callback(&m_Events[id], &r, entity);
    }
  }

  m_Events.clear();
  m_EventReceivers.clear();

  m_EventDatabase.Clear();
}

EntityHandle EventSystem::GetEntityHandle(NotNullPtr<Entity> entity)
{
  return entity->GetHandle();
}

void EventSystem::TriggerEntityEventHandler(NotNullPtr<Entity> entity, uint32_t event_type, void * ev)
{
  entity->TriggerEventHandler(event_type, ev);
}