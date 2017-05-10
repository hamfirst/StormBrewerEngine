
#include "Engine/EngineCommon.h"
#include "Engine/Camera/Camera.h"
#include "Engine/Rendering/RenderState.h"
#include "Engine/Rendering/RenderUtil.h"
#include "Engine/Shader/ShaderManager.h"
#include "Engine/DrawList/DrawList.h"
#include "Engine/Map/MapRender.h"
#include "Engine/Entity/EntityRender.h"

#include "Runtime/RuntimeState.h"
#include "Runtime/Collision/CollisionSystem.h"

Camera::Camera(const RenderVec2 & resolution, const RenderVec2 & initial_position) :
  m_Resolution(resolution), m_Position(initial_position)
{

}

void Camera::SetResolution(const RenderVec2 & resolution)
{
  m_Resolution = resolution;
}

void Camera::SetPosition(const RenderVec2 & position)
{
  m_Position = position;
}

const RenderVec2 & Camera::GetResolution()
{
  return m_Resolution;
}

const RenderVec2 & Camera::GetPosition()
{
  return m_Position;
}

void Camera::Draw(NotNullPtr<RuntimeState> runtime_state, RenderState & render_state)
{
  Box viewport;

  render_state.EnableBlendMode();

  viewport.m_Start = m_Position - (m_Resolution / 2.0f);
  viewport.m_End = viewport.m_Start + m_Resolution;

  auto & default_shader = g_ShaderManager.GetDefaultShader();
  default_shader.Bind();
  default_shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Color"), Color(255, 255, 255, 255));
  default_shader.SetUniform(COMPILE_TIME_CRC32_STR("u_ScreenSize"), m_Resolution);

  DrawList draw_list;
  MapRenderer::DrawAllMaps(runtime_state, draw_list);
  EntityRenderer::DrawAllEntities(viewport, runtime_state, draw_list);
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

void Camera::DebugDrawCollision(NotNullPtr<RuntimeState> runtime_state, std::size_t collision_layer, RenderState & render_state, RenderUtil & render_util, const Color & color)
{
  Box viewport;
  viewport.m_Start = m_Position - (m_Resolution / 2.0f);
  viewport.m_End = viewport.m_Start + m_Resolution;

  auto collision = runtime_state->m_CollisionSystem.get();
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
