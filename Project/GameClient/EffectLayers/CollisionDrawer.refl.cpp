

#include "GameClient/GameClientCommon.h"

#include "Engine/EngineState.h"
#include "Engine/Rendering/GeometryVertexBufferBuilder.h"
#include "Engine/Shader/ShaderManager.h"
#include "Engine/Sprite/SpriteEngineData.h"
#include "Engine/VisualEffect/VisualEffectManager.h"

#include "GameClient/GameContainer.h"
#include "GameClient/GameClientEventSender.h"

#include "GameClient/EffectLayers/CollisionDrawer.refl.h"
#include "GameClient/EffectLayers/CollisionDrawer.refl.meta.h"

CollisionDrawer::CollisionDrawer(const CollisionDrawerInitData & init_data)
{
  
}

CollisionDrawer::~CollisionDrawer()
{

}

void CollisionDrawer::Init(GameContainer & world)
{

}

void CollisionDrawer::Update(GameContainer & world)
{
  auto & stage = world.GetInstanceData()->GetStage();
  auto & game_data = world.GetInstanceData()->GetGlobalInstanceData();

  auto mask = GetCollisionMask(world);
}

void CollisionDrawer::Render(GameContainer & world, const Box & viewport_bounds,
  const RenderVec2 & screen_center, const Vector2 & offset, RenderState & render_state)
{
  auto & stage = world.GetInstanceData()->GetStage();
  auto & game_data = world.GetInstanceData()->GetGlobalInstanceData();

  auto & shader = g_ShaderManager.GetDefaultWorldSpaceShader();
  render_state.BindShader(shader);
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Offset"), -screen_center);

  auto collision_mask = GetCollisionMask(world);
  
  GeometryVertexBufferBuilder builder;
  for (auto & elem : stage.GetCollisionLines())
  {
    if (elem.m_Team == -1)
    {
      builder.Line(elem.m_Start, elem.m_End, 2.0f, Color(0, 0, 0, 127));
    }
    else if (collision_mask & (1 << elem.m_Team) || true)
    {
      builder.Line(elem.m_Start, elem.m_End, 2.0f, Color(0, 0, 0, 127));
    }
  }

  builder.DrawDefault(render_state, &shader);
}

uint32_t CollisionDrawer::GetCollisionMask(GameContainer & world)
{
  auto & stage = world.GetInstanceData()->GetStage();
  auto & game_data = world.GetInstanceData()->GetLowFrequencyData();

  uint8_t collision_mask = 0;
  for (auto team = 0; team < kMaxTeams; ++team)
  {
    bool has_player = false;
    for (auto player : game_data.m_Players)
    {
      if (player.second.m_Team == team)
      {
        has_player = true;
        break;
      }
    }

    if (has_player == false)
    {
      collision_mask |= (1 << team);
    }
  }

  return collision_mask;
}
