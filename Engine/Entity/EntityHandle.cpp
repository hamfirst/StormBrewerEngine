
#include "Engine/EngineCommon.h"

#include "Engine/Entity/Entity.h"
#include "Engine/Entity/EntityHandle.h"
#include "Engine/Entity/EntitySystem.h"

NullOptPtr<Entity> EntityHandle::Resolve()
{
  return m_EntityManager ? m_EntityManager->ResolveHandle(*this) : nullptr;
}

void EntityHandle::Destroy()
{
  auto entity = Resolve();
  if (entity)
  {
    entity->Destroy();
    m_EntityManager = nullptr;
  }
}
