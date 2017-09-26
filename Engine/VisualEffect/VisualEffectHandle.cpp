
#include "Engine/EngineCommon.h"
#include "Engine/VisualEffect/VisualEffectHandle.h"
#include "Engine/VisualEffect/VisualEffectManager.h"


bool VisualEffectHandle::operator == (const VisualEffectHandle && rhs)
{
  return *static_cast<const Handle *>(this) == *static_cast<const Handle *>(&rhs) && m_Manager == rhs.m_Manager;
}

bool VisualEffectHandle::operator != (const VisualEffectHandle && rhs)
{
  return *static_cast<const Handle *>(this) != *static_cast<const Handle *>(&rhs) || m_Manager != rhs.m_Manager;
}

NullOptPtr<VisualEffectInstance> VisualEffectHandle::Resolve()
{
  if (m_Manager == nullptr)
  {
    return nullptr;
  }

  return m_Manager->ResolveHandle(*this);
}


