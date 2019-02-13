
#include "Engine/EngineCommon.h"
#include "Engine/VisualEffect/VisualEffectManager.h"
#include "Engine/VisualEffect/VisualEffectFuncs.h"
#include "Engine/Rendering/RenderSettings.h"

#include "Foundation/SkipField/SkipField.h"

#include "StormExpr/StormExprStack.h"

#include <sb/vector.h>

StormExprFunctionList VisualEffectManager::m_FuncList = VisualEffectCreateFunctionList();

SkipField<VisualEffectInstance> s_EffectAllocator;

VisualEffectManager::VisualEffectManager() :
  m_Paused(false)
{
  m_UpdateClock.Start();
}

VisualEffectManager::~VisualEffectManager()
{
  while (m_Effects.size() > 0)
  {
    m_Effects.back()->Destroy();
  }
}

NotNullPtr<VisualEffectInstance> VisualEffectManager::CreateVisualEffect(const VisualEffectResourcePtr & fx_resource, int layer, const Vector2f & pos)
{
  auto ptr = s_EffectAllocator.Allocate(fx_resource, layer);
  ptr->m_Handle.m_Manager = this;
  ptr->Init(pos);
  m_Effects.push_back(ptr);
  return ptr;
}

NotNullPtr<VisualEffectInstance> VisualEffectManager::CreateVisualEffect(const VisualEffectDef * fx_resource, int layer, const Vector2f & pos)
{
  auto ptr = s_EffectAllocator.Allocate(fx_resource, layer);
  ptr->m_Handle.m_Manager = this;
  ptr->Init(pos);
  m_Effects.push_back(ptr);
  return ptr;
}

void VisualEffectManager::Update(const Box & viewport_bounds)
{
  StormExprStack stack;
  auto update_time = (float)m_UpdateClock.GetTimeSinceLastCheck();

  auto viewport_size = viewport_bounds.Size() * 2;
  auto viewport_center = viewport_bounds.Center();

  if (m_Paused)
  {
    update_time = 0;
  }

  for (auto elem : m_Effects)
  {
    auto diff_offset = elem->GetPosition() - viewport_center;
    auto on_screen = (abs(diff_offset.x) < viewport_size.x && abs(diff_offset.y) < viewport_size.y);
 
    elem->Update(update_time, stack, on_screen);
  }

  auto end_itr = std::remove_if(m_Effects.begin(), m_Effects.end(), 
    [](NotNullPtr<VisualEffectInstance> fx) 
    { 
      if(fx->IsComplete())
      {
        s_EffectAllocator.Release(fx);
        return true;
      }

      return false;
    });

  m_Effects.erase(end_itr, m_Effects.end());
}

void VisualEffectManager::DrawAllEffects(const Box & viewport_bounds, DrawList & draw_list)
{
  auto viewport_size = viewport_bounds.Size() * 2;
  auto viewport_center = viewport_bounds.Center();

  for (auto elem : m_Effects)
  {
#ifdef USE_Z_ORDERING
    int draw_order = (int)elem->m_InstanceData.m_PositionY;
#else
    int draw_order = 0;
#endif


    auto diff_offset = elem->GetPosition() - viewport_center;
    auto on_screen = (abs(diff_offset.x) < viewport_size.x && abs(diff_offset.y) < viewport_size.y);

    if (on_screen)
    {
      draw_list.PushDraw(elem->m_Layer, draw_order,
        [this, e = elem](GameContainer & game_container, const Box & viewport_bounds, const RenderVec2 & screen_center, RenderState & render_state)
        {
          e->Render(viewport_bounds, screen_center, render_state);
        }
      );
    }
  }
}

void VisualEffectManager::DestroyAllEffects()
{
  for (auto elem : m_Effects)
  {
    s_EffectAllocator.Release(elem);
  }

  m_Effects.clear();
}

void VisualEffectManager::Pause()
{
  m_Paused = true;
}

void VisualEffectManager::Unpause()
{
  m_Paused = false;
}

void VisualEffectManager::DestroyEffect(NotNullPtr<VisualEffectInstance> inst)
{
  vremove_ordered(m_Effects, inst);
  s_EffectAllocator.Release(inst);
}

NullOptPtr<VisualEffectInstance> VisualEffectManager::ResolveHandle(const VisualEffectHandle & handle)
{
  return s_EffectAllocator.ResolveHandle(handle);
}

Any CreateVisualEffectEngineData(VisualEffectDef & visual_effect)
{
  return Any(std::make_shared<VisualEffect>(visual_effect));
}
