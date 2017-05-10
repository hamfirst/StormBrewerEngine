
#include "Engine/EngineCommon.h"
#include "Engine/Entity/EntityRender.h"
#include "Engine/Sprite/SpriteEngineData.h"
#include "Engine/Shader/ShaderManager.h"
#include "Runtime/Entity/EntitySystem.h"
#include "Runtime/Entity/Entity.h"

#include "Foundation/SkipField/SkipField.h"

void EntityRenderer::DrawAllEntities(const Box & viewport_bounds, NotNullPtr<RuntimeState> runtime_state, DrawList & draw_list)
{
  auto entity_system = runtime_state->m_EntitySystem.get();
  auto entity_alloc = static_cast<SkipField<Entity> *>(entity_system->m_EntityAllocator);

  entity_alloc->VisitAll([&](Entity & entity)
  {
    auto & pos = entity.GetPosition();
    auto & render_state = entity.GetRenderState();
    if (render_state.m_Draw == false || entity.m_Activated == false)
    {
      return;
    }

    if (pos.x + render_state.m_FrameWidth / 2 < viewport_bounds.m_Start.x ||
      pos.y + render_state.m_FrameHeight / 2 < viewport_bounds.m_Start.y ||
      pos.x - render_state.m_FrameWidth / 2 > viewport_bounds.m_End.x ||
      pos.y - render_state.m_FrameHeight / 2 > viewport_bounds.m_End.y)
    {
      return;
    }

    draw_list.PushDraw(entity.GetLayer(), [e = &entity](const Box & viewport_bounds, const RenderVec2 & screen_center)
    {
      auto & sprite = e->GetSprite();
      auto & render_state = e->GetRenderState();
      auto & shader = g_ShaderManager.GetDefaultShader();

      shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Offset"), RenderVec2{ e->GetPosition() } - screen_center);
      shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Matrix"), render_state.m_Matrix);
      shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Color"), render_state.m_Color);

      SpriteEngineData::RenderSprite(sprite, render_state.m_AnimIndex, render_state.m_AnimFrame, shader);
    });
  });
}
