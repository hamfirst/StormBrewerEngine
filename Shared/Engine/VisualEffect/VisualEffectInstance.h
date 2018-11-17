#pragma once

#include "Engine/EngineCommon.h"
#include "Engine/VisualEffect/VisualEffect.h"
#include "Engine/VisualEffect/VisualEffectTypes.refl.h"
#include "Engine/VisualEffect/VisualEffectHandle.h"

#include "Foundation/SkipField/SkipFieldIterator.h"

#include "Runtime/VisualEffect/VisualEffectResource.h"

class StormExprStack;

struct VisualEffectInstanceParticle
{
  VisualEffectInstanceParticleScriptData m_ScriptData;
  VisualEffectInstanceRandBlock m_Rand;
  VisualEffectInstanceParticleAutoData m_AutoData;
};


struct VisualEffectInstanceEmitter
{
  VisualEffectInstanceRandBlock m_Rand;
  VisualEffectInstanceEmitterAutoData m_AutoData;
  VisualEffectInstanceEmitterScriptData m_ScriptData;
  std::vector<VisualEffectInstanceParticle> m_Particles;
  float m_SpawnOverflow = 0;
  bool m_Complete = false;
};

class VisualEffectInstance
{
public:
  VisualEffectInstance(const VisualEffectResourcePtr & visual_effect, int layer);
  VisualEffectInstance(const VisualEffectDef * visual_effect, int layer);

  ~VisualEffectInstance();

  void SetPosition(const Vector2f & pos);
  Vector2 GetPosition() const;
  void SetInput(uint32_t var_name_hash, float value);
  void Destroy();


  VisualEffectHandle GetHandle();

  bool IsComplete() const;
  void Presim(float time);
  void StopSpawning(bool spawn_final_particle = false);

private:

  void Init(const Vector2f & pos);
  void Update(float update_time, StormExprStack & stack, bool on_screen);
  void Render(const Box & viewport_bounds, const RenderVec2 & screen_center, RenderState & render_state, RenderUtil & render_util);

  template <typename Type>
  friend class SkipField;

  friend class VisualEffect;
  friend class VisualEffectManager;

  void SetHandle(Handle & handle);
  void SetIterator(const SkipFieldIterator & itr);
  const SkipFieldIterator & GetIterator() const;

private:

  VisualEffectHandle m_Handle;
  SkipFieldIterator m_Iterator;

  VisualEffectResourcePtr m_VisualEffectLink;
  std::shared_ptr<VisualEffect> m_VisualEffect;

  int m_Layer = 0;
  bool m_Prespawn = true;
  bool m_PostSpawn = false;
  bool m_Spawning = true;
  int m_NextParticleId = 0;
  bool m_Allocated = true;

  VisualEffectInstanceEmitterGlobalData m_InstanceData;
  std::vector<VisualEffectInstanceEmitter> m_Emitters;
  std::vector<std::pair<uint32_t, float>> m_Inputs;
};

