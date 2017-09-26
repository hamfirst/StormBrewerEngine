
#include "Engine/EngineCommon.h"
#include "Engine/VisualEffect/VisualEffectInstance.h"
#include "Engine/VisualEffect/VisualEffectHandle.h"
#include "Engine/VisualEffect/VisualEffectManager.h"

VisualEffectInstance::VisualEffectInstance(const VisualEffectResourcePtr & visual_effect, int layer) :
  m_VisualEffectLink(visual_effect),
  m_Layer(layer)
{
  m_VisualEffect = *visual_effect.GetResource()->m_EngineData.Get<std::shared_ptr<VisualEffect>>();
}

VisualEffectInstance::VisualEffectInstance(const VisualEffectDef * visual_effect, int layer) :
  m_VisualEffect(std::make_shared<VisualEffect>(*visual_effect)),
  m_Layer(layer)
{

}

VisualEffectInstance::~VisualEffectInstance()
{
  m_Allocated = false;
}

void VisualEffectInstance::SetPosition(const Vector2f & pos)
{
  m_InstanceData.m_PositionX = pos.x;
  m_InstanceData.m_PositionY = pos.y;
}

void VisualEffectInstance::SetInput(uint32_t var_name_hash, float value)
{
  for (auto & elem : m_Inputs)
  {
    if (elem.first == var_name_hash)
    {
      elem.second = value;
      return;
    }
  }
}

void VisualEffectInstance::Destroy()
{
  m_Handle.m_Manager->DestroyEffect(this);
}

VisualEffectHandle VisualEffectInstance::GetHandle()
{
  return m_Handle;
}

bool VisualEffectInstance::IsComplete() const
{
  for (auto & elem : m_Emitters)
  {
    if (elem.m_Complete == false || elem.m_Particles.size() > 0)
    {
      return false;
    }
  }

  return true;
}

void VisualEffectInstance::StopSpawning()
{
  m_Spawning = false;
}

void VisualEffectInstance::Init(const Vector2f & pos)
{
  m_VisualEffect->InitInstance(*this, pos);
}

void VisualEffectInstance::Update(float update_time, StormExprStack & stack)
{
  m_VisualEffect->UpdateInstance(*this, update_time, stack);
}

void VisualEffectInstance::Render(const Box & viewport_bounds, const RenderVec2 & screen_center, RenderState & render_state, RenderUtil & render_util)
{
  m_VisualEffect->RenderInstance(*this, viewport_bounds, screen_center, render_state, render_util);
}

void VisualEffectInstance::SetHandle(Handle & handle)
{
  Handle & my_handle = m_Handle;
  my_handle = handle;
}

void VisualEffectInstance::SetIterator(const SkipFieldIterator & itr)
{
  m_Iterator = itr;
}

const SkipFieldIterator & VisualEffectInstance::GetIterator() const
{
  return m_Iterator;
}

