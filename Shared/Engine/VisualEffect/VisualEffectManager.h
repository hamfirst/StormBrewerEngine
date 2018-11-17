#pragma once

#include "Engine/EngineCommon.h"
#include "Engine/VisualEffect/VisualEffectHandle.h"
#include "Engine/VisualEffect/VisualEffectInstance.h"
#include "Engine/DrawList/DrawList.h"

#include "StormExpr/StormExprFunctionList.h"

#include "Foundation/Time/StopWatch.h"

#include "Runtime/VisualEffect/VisualEffectResource.h"

class VisualEffectManager
{
public:

  VisualEffectManager();
  ~VisualEffectManager();

  NotNullPtr<VisualEffectInstance> CreateVisualEffect(const VisualEffectResourcePtr & fx_resource, int layer, const Vector2f & pos);
  NotNullPtr<VisualEffectInstance> CreateVisualEffect(const VisualEffectDef * fx_resource, int layer, const Vector2f & pos);

  void Update(const Box & viewport_bounds);
  void DrawAllEffects(const Box & viewport_bounds, DrawList & draw_list);
  void DestroyAllEffects();

  void Pause();
  void Unpause();

protected:

  void DestroyEffect(NotNullPtr<VisualEffectInstance> inst);
  NullOptPtr<VisualEffectInstance> ResolveHandle(const VisualEffectHandle & handle);

private:
  friend class VisualEffect;
  friend class VisualEffectHandle;
  friend class VisualEffectInstance;

  StopWatch m_UpdateClock;
  bool m_Paused;
  std::vector<NotNullPtr<VisualEffectInstance>> m_Effects;

  static StormExprFunctionList m_FuncList;
};
