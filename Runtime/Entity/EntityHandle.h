#pragma once

#include "Foundation/Handle/Handle.h"

#include "Runtime/RuntimeCommon.h"

class Entity;
class EntitySystem;

class RUNTIME_EXPORT EntityHandle : public SpecificHandle<EntitySystem>
{
public:
  NullOptPtr<Entity> Resolve();

private:

  friend class Entity;
  friend class EntitySystem;

  NotNullPtr<EntitySystem> m_EntityManager;
};
