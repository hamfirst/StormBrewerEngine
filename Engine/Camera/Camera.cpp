
#include "Engine/EngineCommon.h"
#include "Engine/Camera/Camera.h"
#include "Engine/Rendering/RenderState.h"
#include "Engine/Rendering/RenderUtil.h"
#include "Engine/Rendering/ShaderProgram.h"
#include "Engine/Shader/ShaderManager.h"
#include "Engine/DrawList/DrawList.h"
#include "Engine/Entity/EntitySystem.h"
#include "Engine/Map/MapSystem.h"
#include "Engine/EngineState.h"

#include "Runtime/Collision/CollisionSystem.h"

Camera::Camera(const Vector2 & game_resolution, const Vector2 & screen_resolution, const RenderVec2 & initial_position) :
  m_GameResolution(game_resolution), m_ScreenResolution(screen_resolution), m_Position(initial_position)
{

}

void Camera::SetGameResolution(const RenderVec2 & resolution)
{
  m_GameResolution = resolution;
}

void Camera::SetScreenResolution(const RenderVec2 & resolution)
{
  m_ScreenResolution = resolution;
}

void Camera::SetPosition(const RenderVec2 & position)
{
  m_Position = position;
}

void Camera::BootstrapShader(const ShaderProgram & shader)
{
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_ScreenSize"), m_GameResolution);
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Color"), Color(255, 255, 255, 255));
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Matrix"), 1.0f, 1.0f, 1.0f, 1.0f);
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Offset"), 0.0f, 0.0f);
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Texture"), 0);
}

const RenderVec2 & Camera::GetGameResolution()
{
  return m_GameResolution;
}

const RenderVec2 & Camera::GetScreenResolution()
{
  return m_ScreenResolution;
}

const RenderVec2 & Camera::GetPosition()
{
  return m_Position;
}

RenderVec2 Camera::TransformFromScreenSpaceToClipSpace(const RenderVec2 & pos)
{
  RenderVec2 screen_size = m_ScreenResolution;
  auto transformed_pos = pos;
  transformed_pos -= screen_size * 0.5f;

  transformed_pos /= screen_size * 0.5f;
  return transformed_pos;
}

RenderVec2 Camera::TransformFromScreenSpaceToWorldSpace(const RenderVec2 & pos)
{
  auto clip_pos = TransformFromScreenSpaceToClipSpace(pos);
  return TransformFromClipSpaceToWorldSpace(clip_pos);
}

RenderVec2 Camera::TransformFromClipSpaceToWorldSpace(const RenderVec2 & pos)
{
  auto transformed_pos = pos;
  transformed_pos *= m_GameResolution * 0.5f;
  transformed_pos += m_Position;
  return transformed_pos;
}

void Camera::Draw(NotNullPtr<EngineState> engine_state, RenderState & render_state)
{
  Box viewport;

  render_state.EnableBlendMode();

  viewport.m_Start = m_Position - (m_GameResolution / 2.0f);
  viewport.m_End = viewport.m_Start + m_GameResolution;

  auto & default_shader = g_ShaderManager.GetDefaultShader();
  default_shader.Bind();
  default_shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Color"), Color(255, 255, 255, 255));
  default_shader.SetUniform(COMPILE_TIME_CRC32_STR("u_ScreenSize"), m_GameResolution);

  DrawList draw_list;

  engine_state->GetMapSystem()->DrawAllMaps(draw_list);
  engine_state->GetEntitySystem()->DrawAllEntities(viewport, draw_list);
  draw_list.Draw(viewport, m_Position);
  default_shader.Unbind();
}

void Camera::DebugDraw(RenderState & render_state, RenderUtil & render_util, const Box & box, const Color & color)
{
  auto b = box;
  b.m_Start -= (Vector2)m_Position + (render_state.GetScreenSize() / 2);
  b.m_End -= (Vector2)m_Position + (render_state.GetScreenSize() / 2);

  render_util.DrawQuad(b, color, render_state.GetScreenSize());
}

void Camera::DebugDraw(RenderState & render_state, RenderUtil & render_util, const Box & box, const Vector2 & offset, const Color & color)
{
  auto b = box;
  b.m_Start += offset;
  b.m_End += offset;
  DebugDraw(render_state, render_util, b, color);
}

void Camera::DebugDrawCollision(NotNullPtr<EngineState> engine_state, std::size_t collision_layer, RenderState & render_state, RenderUtil & render_util, const Color & color)
{
  Box viewport;
  viewport.m_Start = m_Position - (m_GameResolution / 2.0f);
  viewport.m_End = viewport.m_Start + m_GameResolution;

  auto collision = engine_state->m_CollisionSystem.get();
  if (collision_layer >= collision->m_CollisionLayers.size())
  {
    return;
  }

  collision->m_CollisionLayers[collision_layer].VisitAll([&](uint32_t grid_id, SpatialDatabaseNode & node)
  {
    for (auto & elem : node.m_Elements)
    {
      DebugDraw(render_state, render_util, elem.second, color);
    }
  });
}
