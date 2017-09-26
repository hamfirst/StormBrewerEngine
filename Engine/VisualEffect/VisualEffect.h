#pragma once

#include "Engine/EngineCommon.h"
#include "Engine/Asset/TextureAsset.h"
#include "Engine/VisualEffect/VisualEffectTypes.refl.h"

#include "Runtime/VisualEffect/VisualEffectDef.refl.h"

#include "StormExpr/StormExprEval.h"
#include "StormExpr/StormExprBinding.h"

class VisualEffectManager;
class VisualEffectInstance;

struct VisualEffectInstanceEmitter;

class RenderState;
class RenderUtil;

class VisualEffect
{
public:
  VisualEffect(const VisualEffectDef & def);

  void InitInstance(VisualEffectInstance & inst, const Vector2f & position);
  void UpdateInstance(VisualEffectInstance & inst, float update_time, StormExprStack & stack);
  void RenderInstance(VisualEffectInstance & inst, const Box & viewport_bounds, const RenderVec2 & screen_center, RenderState & render_state, RenderUtil & render_util);

protected:

  static void InitRandBlock(VisualEffectInstanceRandBlock & block);
  void SpawnParticles(VisualEffectInstance & inst, int emitter_index, int num_particles, 
    float pre_sim, float pre_sim_dec, float interval, const RenderVec2 & travel_dist, StormExprStack & stack);

private:

  std::vector<AssetReference<TextureAsset>> m_Textures;

  struct EmitterProps
  {
    int m_Prespawn;
    int m_Delay;
    int m_DelayMax;
    float m_UpdateTime;
    bool m_Additive;
  };

  VisualEffectInstanceEmitterSpawnData m_DefaultSpawn;
  VisualEffectInstanceParticleScriptData m_DefaultParticle;

  std::size_t m_EmitterCount;
  std::vector<EmitterProps> m_EmitterProps;

  Optional<StormExprEval> m_EmitterEval;
  std::vector<std::vector<std::pair<StormExprBinding, int>>> m_EmitterBindings;

  Optional<StormExprEval> m_SpawnEval;
  std::vector<std::vector<std::pair<StormExprBinding, int>>> m_SpawnBindings;

  Optional<StormExprEval> m_ParticleEval;
  std::vector<std::vector<std::pair<StormExprBinding, int>>> m_ParticleBindings;

  std::vector<std::pair<uint32_t, float>> m_Inputs;
  Optional<StormExprValueBlock> m_InputBlock;
};

