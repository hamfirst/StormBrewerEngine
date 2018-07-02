
#include "Engine/EngineCommon.h"
#include "Engine/VisualEffect/VisualEffect.h"
#include "Engine/VisualEffect/VisualEffectInstance.h"
#include "Engine/VisualEffect/VisualEffectManager.h"
#include "Engine/VisualEffect/VisualEffectTypes.refl.meta.h"

#include "Engine/Rendering/RenderState.h"
#include "Engine/Rendering/RenderUtil.h"
#include "Engine/Rendering/GeometryVertexBufferBuilder.h"
#include "Engine/Shader/ShaderManager.h"
#include "Engine/Text/TextManager.h"
#include "Engine/Profiler/Profiler.h"

#include "StormExpr/StormExprReflBlock.h"
#include "StormExpr/StormExprEvalBuilder.h"


static auto s_GlobalInitBlock = StormExprCreateInitBlockForDataType<VisualEffectInstanceEmitterGlobalData>();
static auto s_RandInitBlock = StormExprCreateInitBlockForDataType<VisualEffectInstanceRandBlock>();
static auto s_EmitterAutoInitBlock = StormExprCreateInitBlockForDataType<VisualEffectInstanceEmitterAutoData>();
static auto s_EmitterScriptInitBlock = StormExprCreateInitBlockForDataType<VisualEffectInstanceEmitterScriptData>();
static auto s_ParticleAutoInitBlock = StormExprCreateInitBlockForDataType<VisualEffectInstanceParticleAutoData>();
static auto s_ParticleScriptInitBlock = StormExprCreateInitBlockForDataType<VisualEffectInstanceParticleScriptData>();

static std::vector<VertexInfo> m_ScratchVertexList;

VisualEffect::VisualEffect(const VisualEffectDef & def)
{
  StormExprValueInitBlock input_init_block;

  m_UpdateBounds.x = def.m_UpdateBoundsX;
  m_UpdateBounds.y = def.m_UpdateBoundsY;

  for (auto input : def.m_Inputs)
  {
    m_Inputs.push_back(std::make_pair(crc32(input.second.m_VariableName.data()), 0.0f));
    input_init_block.AddValue(input.second.m_VariableName.data(), StormExprValueProvider(m_Inputs.data(), &m_Inputs.back().second));
  }

  m_InputBlock.Emplace(input_init_block);
  std::vector<std::string> errors;

  std::vector<StormExprValueInitBlock *> emitter_value_init_blocks = { &input_init_block, &s_GlobalInitBlock, &s_RandInitBlock, &s_EmitterAutoInitBlock, &s_EmitterScriptInitBlock };
  std::vector<StormExprValueInitBlock *> spawn_value_init_blocks = { &input_init_block, &s_GlobalInitBlock, &s_RandInitBlock, &s_EmitterAutoInitBlock, &s_EmitterScriptInitBlock };
  std::vector<StormExprValueInitBlock *> particle_value_init_blocks = { &input_init_block, &s_GlobalInitBlock, &s_RandInitBlock, &s_EmitterAutoInitBlock, &s_EmitterScriptInitBlock, &s_ParticleAutoInitBlock, &s_ParticleScriptInitBlock };

  StormExprValueInitBlockList emitter_block_list(std::move(emitter_value_init_blocks));
  StormExprEvalBuilder emitter_eval_builder(VisualEffectManager::m_FuncList, false);
  emitter_eval_builder.SetBlockList(emitter_block_list);

  StormExprValueInitBlockList spawn_block_list(std::move(spawn_value_init_blocks));
  StormExprEvalBuilder spawn_eval_builder(VisualEffectManager::m_FuncList, false);
  spawn_eval_builder.SetBlockList(spawn_block_list);

  StormExprValueInitBlockList particle_block_list(std::move(particle_value_init_blocks));
  StormExprEvalBuilder particle_eval_builder(VisualEffectManager::m_FuncList, false);
  particle_eval_builder.SetBlockList(particle_block_list);

  VisualEffectInstanceEmitterScriptData * null_emitter_script_data = nullptr;

  m_EmitterCount = 0;

  for (auto emitter : def.m_Emitters)
  {
    if (emitter.second.m_Properties.m_Texture.size() > 0)
    {
      auto texture_ref = TextureAsset::Load(emitter.second.m_Properties.m_Texture.data());
      if (emitter.second.m_Properties.m_LinearFilter)
      {
        texture_ref->SetLinearFilter();
      }

      m_Textures.emplace_back(std::move(texture_ref));
    }
    else
    {
      m_Textures.emplace_back(AssetReference<TextureAsset>{});
    }

    EmitterProps props;
    props.m_Additive = emitter.second.m_Properties.m_Additive;
    props.m_Trail = emitter.second.m_Properties.m_Trail;
    props.m_Prespawn = emitter.second.m_Properties.m_PrespawnParticles;
    props.m_Delay = 0;
    props.m_DelayMax = emitter.second.m_Properties.m_UpdateDelay;
    props.m_UpdateTime = 0;

    m_EmitterProps.push_back(props);

    m_DefaultParticle.emplace_back();

    std::vector<std::pair<StormExprBinding, int>> emitter_bindings;

    for (auto eq : emitter.second.m_EmitterEquations)
    {
      auto var_name_hash = crc32(eq.second.m_VariableName);
      bool found_var = false;
      
      auto visitor = [&](auto f)
      {
        found_var = true;

        czstr error, error_desc;
        auto function_index = emitter_eval_builder.ParseExpression(eq.second.m_Equation.data(), error, error_desc);
        if (function_index == -1)
        {
          std::string error_msg = emitter.second.m_Properties.m_Name.ToString() + "." + eq.second.m_VariableName.data() + ": " + error_desc + " at " + error;
          errors.emplace_back(std::move(error_msg));
        }
        else
        {
          emitter_bindings.emplace_back(std::make_pair(StormExprBinding(null_emitter_script_data, &f.Get()), function_index));
        }
      };

      StormReflVisitField(*null_emitter_script_data, visitor, var_name_hash);
    }

    std::vector<std::pair<StormExprBinding, int>> spawn_bindings;

    for (auto eq : emitter.second.m_SpawnEquations)
    {
      auto var_name_hash = crc32(eq.second.m_VariableName);
      bool found_var = false;

      auto visitor = [&](auto f)
      {
        found_var = true;

        if (StormExprEvalBuilder::IsLiteralFloatValue(eq.second.m_Equation.data(), f.Get()))
        {
          return;
        }

        czstr error, error_desc;
        auto function_index = spawn_eval_builder.ParseExpression(eq.second.m_Equation.data(), error, error_desc);
        if (function_index == -1)
        {
          std::string error_msg = emitter.second.m_Properties.m_Name.ToString() + "." + eq.second.m_VariableName.data() + ": " + error_desc + " at " + error;
          errors.emplace_back(std::move(error_msg));
        }
        else
        {
          spawn_bindings.emplace_back(std::make_pair(StormExprBinding(&m_DefaultSpawn, &f.Get()), function_index));
        }
      };

      StormReflVisitField(m_DefaultSpawn, visitor, var_name_hash);
    }

    std::vector<std::pair<StormExprBinding, int>> particle_bindings;
    for (auto eq : emitter.second.m_ParticleEquations)
    {
      auto var_name_hash = crc32(eq.second.m_VariableName);
      bool found_var = false;

      auto visitor = [&](auto f)
      {
        found_var = true;

        if (StormExprEvalBuilder::IsLiteralFloatValue(eq.second.m_Equation.data(), f.Get()))
        {
          return;
        }

        czstr error, error_desc;
        auto function_index = particle_eval_builder.ParseExpression(eq.second.m_Equation.data(), error, error_desc);
        if (function_index == -1)
        {
          std::string error_msg = emitter.second.m_Properties.m_Name.ToString() + "." + eq.second.m_VariableName.data() + ": " + error_desc + " at " + error;
          errors.emplace_back(std::move(error_msg));
        }
        else
        {
          particle_bindings.emplace_back(std::make_pair(StormExprBinding(&m_DefaultParticle.back(), &f.Get()), function_index));
        }
      };

      StormReflVisitField(m_DefaultParticle.back(), visitor, var_name_hash);
    }

    m_EmitterBindings.emplace_back(std::move(emitter_bindings));
    m_SpawnBindings.emplace_back(std::move(spawn_bindings));
    m_ParticleBindings.emplace_back(std::move(particle_bindings));
    m_EmitterCount++;
  }

  m_EmitterEval.Emplace(std::move(emitter_eval_builder));
  m_SpawnEval.Emplace(std::move(spawn_eval_builder));
  m_ParticleEval.Emplace(std::move(particle_eval_builder));

  for (auto & error : errors)
  {
    printf("%s\n", error.data());
  }
}

void VisualEffect::InitInstance(VisualEffectInstance & inst, const Vector2f & position)
{
  inst.m_Inputs = m_Inputs;
  inst.m_InstanceData.m_EffectTimeAlive = 0;
  inst.m_InstanceData.m_PositionX = position.x;
  inst.m_InstanceData.m_PositionY = position.y;
  inst.m_InstanceData.m_PrevPositionX = position.x;
  inst.m_InstanceData.m_PrevPositionY = position.y;

  inst.m_Emitters.resize(m_EmitterCount);

  for(std::size_t index = 0; index < m_EmitterCount; ++index)
  {
    auto & em = inst.m_Emitters.back();
    InitRandBlock(em.m_Rand);
  }
}

void VisualEffect::UpdateInstance(VisualEffectInstance & inst, float update_time, StormExprStack & stack, bool on_screen)
{
  auto & emitter_eval = m_EmitterEval.Value();
  auto & particle_eval = m_ParticleEval.Value();

  RenderVec2 prev_pos = { inst.m_InstanceData.m_PrevPositionX, inst.m_InstanceData.m_PrevPositionY };
  RenderVec2 cur_pos = { inst.m_InstanceData.m_PositionX, inst.m_InstanceData.m_PositionY };
  auto travel_dist = cur_pos - prev_pos;

  emitter_eval.SetBlockBasePtr(0, inst.m_Inputs.data());
  emitter_eval.SetBlockBasePtr(1, &inst.m_InstanceData);

  for (std::size_t index = 0; index < m_EmitterCount; ++index)
  {
    auto & emitter = inst.m_Emitters[index];

    emitter_eval.SetBlockBasePtr(2, &emitter.m_Rand);
    emitter_eval.SetBlockBasePtr(3, &emitter.m_AutoData);
    emitter_eval.SetBlockBasePtr(4, &emitter.m_ScriptData);

    auto & bindings = m_EmitterBindings[index];
    for (auto & binding : bindings)
    {
      binding.first.Update(binding.second, emitter_eval, &emitter.m_ScriptData, stack);
    }
  }

  if (inst.m_Prespawn)
  {
    for (std::size_t index = 0; index < m_EmitterCount; ++index)
    {
      SpawnParticles(inst, (int)index, m_EmitterProps[index].m_Prespawn, 0, 0, 1, RenderVec2{}, stack);
    }

    inst.m_Prespawn = false;
  }

  if (inst.m_PostSpawn)
  {
    for (std::size_t index = 0; index < m_EmitterCount; ++index)
    {
      SpawnParticles(inst, (int)index, 1, 0, 0, 1, RenderVec2{}, stack);
    }

    inst.m_PostSpawn = false;
  }

  particle_eval.SetBlockBasePtr(0, inst.m_Inputs.data());
  particle_eval.SetBlockBasePtr(1, &inst.m_InstanceData);

  if (update_time > 0 && on_screen)
  {
    for (std::size_t index = 0; index < m_EmitterCount; ++index)
    {
      auto & props = m_EmitterProps[index];
      props.m_UpdateTime += update_time;
      props.m_Delay++;

      if (props.m_Delay <= props.m_DelayMax)
      {
        continue;
      }

      auto & emitter = inst.m_Emitters[index];
      if ((emitter.m_ScriptData.m_EmitterLifetime >= 0 && inst.m_InstanceData.m_EffectTimeAlive >= emitter.m_ScriptData.m_EmitterLifetime) ||
        inst.m_Spawning == false)
      {
        emitter.m_Complete = true;
      }

      emitter.m_SpawnOverflow += props.m_UpdateTime;

      if (emitter.m_ScriptData.m_SpawnRate > 0 && emitter.m_Complete == false && inst.m_Spawning)
      {
        auto spawn_interval = 1.0f / emitter.m_ScriptData.m_SpawnRate;
        int num_to_spawn = (int)(emitter.m_SpawnOverflow / spawn_interval);

        if (num_to_spawn > 0)
        {
          auto pre_sim_time = emitter.m_SpawnOverflow - spawn_interval;

          emitter.m_SpawnOverflow -= (float)num_to_spawn * spawn_interval;
          SpawnParticles(inst, (int)index, num_to_spawn, pre_sim_time, spawn_interval, props.m_UpdateTime, travel_dist, stack);
        }
      }

      particle_eval.SetBlockBasePtr(3, &emitter.m_AutoData);
      particle_eval.SetBlockBasePtr(4, &emitter.m_ScriptData);

      auto & bindings = m_ParticleBindings[index];

      for (auto & particle : emitter.m_Particles)
      {
        particle_eval.SetBlockBasePtr(2, &particle.m_Rand);
        particle_eval.SetBlockBasePtr(5, &particle.m_AutoData);
        particle_eval.SetBlockBasePtr(6, &particle.m_ScriptData);

        for (auto & binding : bindings)
        {
          binding.first.Update(binding.second, particle_eval, &particle.m_ScriptData, stack);
        }

        auto update_sqrd = props.m_UpdateTime * props.m_UpdateTime;

        particle.m_AutoData.m_PositionX += particle.m_AutoData.m_VelocityX * props.m_UpdateTime + 0.5f * particle.m_AutoData.m_VelocityX * update_sqrd;
        particle.m_AutoData.m_PositionY += particle.m_AutoData.m_VelocityY * props.m_UpdateTime + 0.5f * particle.m_AutoData.m_VelocityY * update_sqrd;

        particle.m_AutoData.m_VelocityX += particle.m_ScriptData.m_ForceX * props.m_UpdateTime;
        particle.m_AutoData.m_VelocityY += particle.m_ScriptData.m_ForceY * props.m_UpdateTime;

        if (particle.m_ScriptData.m_Drag != 0)
        {
          float e = expf(-particle.m_ScriptData.m_Drag * props.m_UpdateTime);
          float vx = particle.m_AutoData.m_VelocityX;
          float vy = particle.m_AutoData.m_VelocityY;

          particle.m_AutoData.m_VelocityX = particle.m_AutoData.m_VelocityX * e;
          particle.m_AutoData.m_VelocityY = particle.m_AutoData.m_VelocityY * e;

          particle.m_AutoData.m_PositionX -= (0.5f * (vx - particle.m_AutoData.m_VelocityX) * update_sqrd);
          particle.m_AutoData.m_PositionY -= (0.5f * (vy - particle.m_AutoData.m_VelocityY) * update_sqrd);
        }

        particle.m_AutoData.m_Speed = sqrtf(particle.m_AutoData.m_VelocityX * particle.m_AutoData.m_VelocityX + particle.m_AutoData.m_VelocityY * particle.m_AutoData.m_VelocityY);
        particle.m_AutoData.m_TimeAlive += props.m_UpdateTime;
        particle.m_AutoData.m_TimePct = particle.m_AutoData.m_TimeAlive / particle.m_ScriptData.m_MaxLifetime;
        particle.m_AutoData.m_InvTimePct = 1.0f - particle.m_AutoData.m_TimePct;
      }

      props.m_UpdateTime = 0;
      props.m_Delay = 0;

      auto end_itr = std::remove_if(emitter.m_Particles.begin(), emitter.m_Particles.end(), [](const VisualEffectInstanceParticle & particle) 
      { 
        return particle.m_AutoData.m_TimeAlive >= particle.m_ScriptData.m_MaxLifetime; 
      });

      emitter.m_Particles.erase(end_itr, emitter.m_Particles.end());
    }
  }

  inst.m_InstanceData.m_EffectTimeAlive += update_time;
  inst.m_InstanceData.m_PrevPositionX = inst.m_InstanceData.m_PositionX;
  inst.m_InstanceData.m_PrevPositionY = inst.m_InstanceData.m_PositionY;
}


void VisualEffect::InitRandBlock(VisualEffectInstanceRandBlock & block)
{
  block.m_RandA = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
  block.m_RandB = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
  block.m_RandC = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
  block.m_RandD = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
  block.m_RandE = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
  block.m_RandF = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
  block.m_RandG = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
  block.m_RandH = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
  block.m_RandAngleA = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
  block.m_RandAngleA *= k2Pi;
  block.m_RandAngleB = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
  block.m_RandAngleB *= k2Pi;
}

void VisualEffect::SpawnParticles(VisualEffectInstance & inst, int emitter_index, int num_particles, 
  float pre_sim, float pre_sim_dec, float interval, const RenderVec2 & travel_dist, StormExprStack & stack)
{
  auto & spawn_eval = m_SpawnEval.Value();
  auto & emitter = inst.m_Emitters[emitter_index];

  spawn_eval.SetBlockBasePtr(0, inst.m_Inputs.data());
  spawn_eval.SetBlockBasePtr(1, &inst.m_InstanceData);
  spawn_eval.SetBlockBasePtr(3, &emitter.m_AutoData);
  spawn_eval.SetBlockBasePtr(4, &emitter.m_ScriptData);

  auto & em = inst.m_Emitters.back();
  InitRandBlock(em.m_Rand);

  while (num_particles > 0)
  {
    if (emitter.m_Particles.size() >= (std::size_t)emitter.m_ScriptData.m_MaxParticles)
    {
      break;
    }

    VisualEffectInstanceRandBlock rand_block;
    InitRandBlock(rand_block);

    spawn_eval.SetBlockBasePtr(2, &rand_block);

    VisualEffectInstanceEmitterSpawnData spawn_data = m_DefaultSpawn;
    for (auto & binding : m_SpawnBindings[emitter_index])
    {
      binding.first.Update(binding.second, spawn_eval, &spawn_data, stack);
    }

    emitter.m_Particles.emplace_back();
    auto & particle = emitter.m_Particles.back();

    auto pos = RenderVec2{ inst.m_InstanceData.m_PositionX, inst.m_InstanceData.m_PositionY };
    pos -= travel_dist * (pre_sim / interval);

    particle.m_ScriptData = m_DefaultParticle[emitter_index];
    particle.m_AutoData.m_PositionX = pos.x + spawn_data.m_SpawnOffsetX + spawn_data.m_SpawnVelocityX * pre_sim;
    particle.m_AutoData.m_PositionY = pos.y + spawn_data.m_SpawnOffsetY + spawn_data.m_SpawnVelocityY * pre_sim;
    particle.m_AutoData.m_VelocityX = spawn_data.m_SpawnVelocityX;
    particle.m_AutoData.m_VelocityY = spawn_data.m_SpawnVelocityY;
    particle.m_AutoData.m_TimeAlive = 0;
    particle.m_AutoData.m_Speed = sqrtf(particle.m_AutoData.m_VelocityX * particle.m_AutoData.m_VelocityX + particle.m_AutoData.m_VelocityY * particle.m_AutoData.m_VelocityY);
    particle.m_AutoData.m_ParticleId = (float)inst.m_NextParticleId;
    particle.m_Rand = rand_block;

    num_particles--;
    inst.m_NextParticleId++;
    inst.m_InstanceData.m_ParticleId = (float)inst.m_NextParticleId;

    pre_sim -= pre_sim_dec;
  }
}

void VisualEffect::RenderInstance(VisualEffectInstance & inst, const Box & viewport_bounds, const RenderVec2 & screen_center, RenderState & render_state, RenderUtil & render_util)
{
  PROFILE_SCOPE("Draw Visual Effect");
  VertexInfo vert[6];
  vert[0].m_TexCoord = RenderVec2{ 0, 0 };
  vert[1].m_TexCoord = RenderVec2{ 1, 0 };
  vert[2].m_TexCoord = RenderVec2{ 1, 1 };
  vert[3].m_TexCoord = RenderVec2{ 0, 0 };
  vert[4].m_TexCoord = RenderVec2{ 1, 1 };
  vert[5].m_TexCoord = RenderVec2{ 0, 1 };

  auto & shader = g_ShaderManager.GetDefaultWorldSpaceShader();
  render_state.BindShader(shader);
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Color"), Color(255, 255, 255, 255));
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Matrix"), 1.0f, 0.0f, 0.0f, 1.0f);
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Offset"), -screen_center);
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Texture"), 0);

  for(std::size_t index = 0, end = m_EmitterCount; index < end; ++index)
  {
    auto & emitter = inst.m_Emitters[index];
    auto & texture_ref = m_Textures[index];

    auto & props = m_EmitterProps[index];

    render_state.EnableBlendMode(props.m_Additive ? RenderingBlendMode::kAdditive : RenderingBlendMode::kAlpha);

    Vector2f texture_size;

    auto texture = texture_ref.Resolve();
    if (texture && texture->IsLoaded() && texture->GetWidth() != 0 && texture->GetHeight() != 0)
    {
      render_state.BindTexture(*texture);
      texture_size = texture->GetSize();
    }
    else
    {
      render_state.BindTexture(render_util.GetDefaultTexture());
      texture_size = Vector2f{ 1, 1 };
    }

    auto & scratch_buffer = render_util.GetScratchBuffer();
    m_ScratchVertexList.clear();

    if (props.m_Trail)
    {
      std::vector<GeometryVertexBufferBuilder::TrailInfo> particle_tralis;
      particle_tralis.reserve(emitter.m_Particles.size());

      GeometryVertexBufferBuilder::TrailInfo trail_info;

      for (auto & particle : emitter.m_Particles)
      {
        auto color = Color(particle.m_ScriptData.m_ColorR, particle.m_ScriptData.m_ColorG, particle.m_ScriptData.m_ColorB, particle.m_ScriptData.m_ColorA);
        auto pos = RenderVec2{ particle.m_AutoData.m_PositionX, particle.m_AutoData.m_PositionY };
        auto dest = RenderVec2{ particle.m_ScriptData.m_DestinationX, particle.m_ScriptData.m_DestinationY };

        pos = (1.0f - particle.m_ScriptData.m_DestinationLerp) * pos + (particle.m_ScriptData.m_DestinationLerp) * dest;

        trail_info.m_Position = pos;
        trail_info.m_Color = color;
        trail_info.m_Thickness = texture_size.y * particle.m_ScriptData.m_SizeY;

        particle_tralis.emplace_back(trail_info);
      }

      GeometryVertexBufferBuilder builder;
      builder.Trail(gsl::make_span(particle_tralis), texture_size.x);

      builder.FillVertexBuffer(scratch_buffer);
    }
    else
    {
      RenderVec2 quad_bl = texture_size * -0.5f;
      RenderVec2 quad_tr = texture_size * 0.5f;
      RenderVec2 quad_br = RenderVec2{ quad_tr.x, quad_bl.y };
      RenderVec2 quad_tl = RenderVec2{ quad_bl.x, quad_tr.y };

      for (auto & particle : emitter.m_Particles)
      {
        auto color = Color(particle.m_ScriptData.m_ColorR, particle.m_ScriptData.m_ColorG, particle.m_ScriptData.m_ColorB, particle.m_ScriptData.m_ColorA);
        auto pos = RenderVec2{ particle.m_AutoData.m_PositionX, particle.m_AutoData.m_PositionY };
        auto dest = RenderVec2{ particle.m_ScriptData.m_DestinationX, particle.m_ScriptData.m_DestinationY };

        pos = (1.0f - particle.m_ScriptData.m_DestinationLerp) * pos + (particle.m_ScriptData.m_DestinationLerp) * dest;

        RenderVec2 scale = RenderVec2{ particle.m_ScriptData.m_SizeX, particle.m_ScriptData.m_SizeY };

        auto bl = quad_bl * scale;
        auto br = quad_br * scale;
        auto tr = quad_tr * scale;
        auto tl = quad_tl * scale;

        if (particle.m_ScriptData.m_Rotation != 0)
        {
          auto sc = SinCosf(particle.m_ScriptData.m_Rotation);
          auto cs = Vector2f{ -sc.y, sc.x };

          bl = RenderVec2{ bl.x * sc.x + bl.y * sc.y, bl.x * cs.x + bl.y * cs.y };
          br = RenderVec2{ br.x * sc.x + br.y * sc.y, br.x * cs.x + br.y * cs.y };
          tr = RenderVec2{ tr.x * sc.x + tr.y * sc.y, tr.x * cs.x + tr.y * cs.y };
          tl = RenderVec2{ tl.x * sc.x + tl.y * sc.y, tl.x * cs.x + tl.y * cs.y };
        }

        vert[0].m_Color = color;
        vert[0].m_Position = pos + bl;
        vert[1].m_Color = color;
        vert[1].m_Position = pos + br;
        vert[2].m_Color = color;
        vert[2].m_Position = pos + tr;
        vert[3].m_Color = color;
        vert[3].m_Position = pos + bl;
        vert[4].m_Color = color;
        vert[4].m_Position = pos + tr;
        vert[5].m_Color = color;
        vert[5].m_Position = pos + tl;

        m_ScratchVertexList.emplace_back(vert[0]);
        m_ScratchVertexList.emplace_back(vert[1]);
        m_ScratchVertexList.emplace_back(vert[2]);
        m_ScratchVertexList.emplace_back(vert[3]);
        m_ScratchVertexList.emplace_back(vert[4]);
        m_ScratchVertexList.emplace_back(vert[5]);
      }

      scratch_buffer.SetBufferData(gsl::make_span(m_ScratchVertexList), VertexBufferType::kTriangles);
    }

    render_state.BindVertexBuffer(scratch_buffer);
    render_state.Draw();
  }

  render_state.EnableBlendMode(RenderingBlendMode::kAlpha);
}

Vector2 VisualEffect::GetUpdateBounds()
{
  return m_UpdateBounds;
}
