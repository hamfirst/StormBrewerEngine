
#include "Runtime/RuntimeCommon.h"

#include "Runtime/Entity/EntityHandle.h"
#include "Runtime/Entity/EntitySystem.h"

NullOptPtr<Entity> EntityHandle::Resolve()
{
  return m_EntityManager->ResolveHandle(*this);
}
