#pragma once

#include "Foundation/Handle/Handle.h"

#include "Engine/EngineCommon.h"

class Entity;
class EntitySystem;

class ENGINE_EXPORT EntityHandle : public SpecificHandle<EntitySystem>
{
public:
  NullOptPtr<Entity> Resolve();

  void Destroy();
private:

  friend class Entity;
  friend class EntitySystem;

  NotNullPtr<EntitySystem> m_EntityManager = nullptr;
};
