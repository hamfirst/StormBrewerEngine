
#include "Engine/EngineCommon.h"
#include "Engine/Component/ComponentHandle.h"

ComponentHandle::ComponentHandle() :
  m_ComponentStore(nullptr)
{

}

NullOptPtr<Component> ComponentHandle::Resolve()
{
  return m_ComponentStore ? ResolveFunc(*this, m_ComponentStore) : nullptr;
}

