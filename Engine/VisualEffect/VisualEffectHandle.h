#pragma once

#include "Engine/EngineCommon.h"

class VisualEffectInstance;
class VisualEffectManager;

class VisualEffectHandle : public Handle
{
public:

  VisualEffectHandle() = default;
  VisualEffectHandle(const VisualEffectHandle & rhs) = default;
  VisualEffectHandle(VisualEffectHandle && rhs) = default;

  VisualEffectHandle & operator =(const VisualEffectHandle & rhs) = default;
  VisualEffectHandle & operator =(VisualEffectHandle && rhs) = default;

  bool operator == (const VisualEffectHandle && rhs);
  bool operator != (const VisualEffectHandle && rhs);

  NullOptPtr<VisualEffectInstance> Resolve();

protected:

  friend class VisualEffectManager;
  friend class VisualEffectInstance;

private:

  NotNullPtr<VisualEffectManager> m_Manager = nullptr;
};

