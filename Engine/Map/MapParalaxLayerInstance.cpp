
#include "Engine/EngineCommon.h"
#include "Engine/Map/MapParalaxLayerInstance.h"
#include "Engine/Rendering/VertexList.h"
#include "Engine/Rendering/RenderState.h"
#include "Engine/Rendering/RenderUtil.h"
#include "Engine/Rendering/VertexBufferBuilder.h"
#include "Engine/Sprite/SpriteEngineData.h"
#include "Engine/Shader/ShaderManager.h"
#include "Engine/VisualEffect/VisualEffectManager.h"


MapParalaxLayerInstance::MapParalaxLayerInstance(MapDef & map, std::size_t layer_index, NotNullPtr<VisualEffectManager> vfx_manager)
{

  auto & layer_data = map.m_ParalaxLayers[(int)layer_index];
  m_LayerOrder = layer_data.m_LayerOrder;

  if (layer_data.m_Image.size() > 0)
  {
    m_Texture = TextureAsset::Load(layer_data.m_Image.data());
  }

  m_RepeatX = layer_data.m_RepeatX;
  m_RepeatY = layer_data.m_RepeatY;
  m_OffsetX = layer_data.m_OffsetX;
  m_OffsetY = layer_data.m_OffsetY;
  m_ParalaxX = layer_data.m_ParalaxX;
  m_ParalaxY = layer_data.m_ParalaxY;
  m_VelocityX = layer_data.m_VelocityX;
  m_VelocityY = layer_data.m_VelocityY;

  for (auto elem : layer_data.m_Objects)
  {
    auto pos = Vector2(elem.second.m_XPosition, elem.second.m_YPosition);
    if (elem.second.m_Type == MapParalaxLayerObjectType::kTexture)
    {
      MapParalaxLayerTexture tex;
      tex.m_Texture = TextureAsset::Load(elem.second.m_File.data());
      tex.m_Pos = pos;
      m_Textures.emplace_back(std::move(tex));
    }
    else if (elem.second.m_Type == MapParalaxLayerObjectType::kSprite)
    {
      MapParalaxLayerSprite spr;
      spr.m_Sprite = SpriteResource::Load(elem.second.m_File.data());
      spr.m_Pos = pos;
      spr.m_AnimationHash = crc32(elem.second.m_Animation);
      spr.m_State = {};
      m_Sprites.emplace_back(std::move(spr));
    }
    else if (elem.second.m_Type == MapParalaxLayerObjectType::kVfx)
    {
      MapParalaxLayerVfx vfx;
      vfx.m_Vfx = VisualEffectResource::Load(elem.second.m_File.data());
      vfx.m_Handle = vfx_manager->CreateVisualEffect(vfx.m_Vfx, m_LayerOrder, pos)->GetHandle();

      if ((float)elem.second.m_PresimTime > 0)
      {
        auto vfx_inst = vfx.m_Handle.Resolve();
        if (vfx_inst)
        {
          vfx_inst->Presim(elem.second.m_PresimTime);
        }
      }

      m_VisualEffects.emplace_back(std::move(vfx));
    }
  }
}

MapParalaxLayerInstance::~MapParalaxLayerInstance()
{
  for (auto & elem : m_VisualEffects)
  {
    auto vfx = elem.m_Handle.Resolve();
    if (vfx)
    {
      vfx->Destroy();
    }
  }
}


void MapParalaxLayerInstance::Update()
{
  for (auto & sprite_info : m_Sprites)
  {
    auto sprite = sprite_info.m_Sprite;
    if (sprite.IsLoaded())
    {
      sprite->FrameAdvance(sprite_info.m_AnimationHash, sprite_info.m_State);
    }
  }
}

void MapParalaxLayerInstance::Draw(const Box & viewport_bounds, const RenderVec2 & screen_center, const Vector2 & offset, RenderState & render_state, RenderUtil & render_util)
{
  auto & buffer = render_util.GetScratchBuffer();

  auto texture = m_Texture.Resolve();
  if (texture != nullptr && texture->IsLoaded() != false && texture->GetWidth() != 0 && texture->GetHeight() != 0)
  {
    auto viewport_size = viewport_bounds.Size();
    auto half_viewport_size = RenderVec2(viewport_size) * 0.5f;

    int width = m_RepeatX ? texture->GetWidth() : viewport_size.x;
    int height = m_RepeatY ? texture->GetHeight() : viewport_size.y;

    auto time = (float)GetTimeSeconds();

    float offset_x = (m_ParalaxX == 0.0f ? 0.0f : ((screen_center.x - offset.x) / -m_ParalaxX)) + time * m_VelocityX + m_OffsetX;
    float offset_y = (m_ParalaxY == 0.0f ? 0.0f : ((screen_center.y - offset.y) / -m_ParalaxY)) + time * m_VelocityY + m_OffsetY;

    offset_x *= (float)texture->GetWidth() / (float)width;
    offset_y *= (float)texture->GetHeight() / (float)height;

    offset_x = glm::fract(offset_x / texture->GetWidth()) * width;
    offset_y = glm::fract(offset_y / texture->GetHeight()) * height;

    VertexList verts;
    VertexInfo vert;

    RenderVec2 tex_size(width, height);
    RenderVec2 render_offset(offset_x, offset_y);

    RenderVec2 start_pos = -half_viewport_size;
    RenderVec2 end_pos = half_viewport_size;

    RenderVec2 start_tex_pos = (-half_viewport_size - render_offset) / tex_size;
    RenderVec2 end_tex_pos = (half_viewport_size - render_offset) / tex_size;

    vert.m_Color = RenderVec4{ 1,1,1,1 };
    vert.m_Position = start_pos;
    vert.m_TexCoord = start_tex_pos;
    verts.AddVert(vert);

    vert.m_Position = RenderVec2(start_pos.x, end_pos.y);
    vert.m_TexCoord = RenderVec2(start_tex_pos.x, end_tex_pos.y);
    verts.AddVert(vert);

    vert.m_Position = RenderVec2(end_pos.x, start_pos.y);
    vert.m_TexCoord = RenderVec2(end_tex_pos.x, start_tex_pos.y);
    verts.AddVert(vert);

    vert.m_Position = RenderVec2(start_pos.x, end_pos.y);
    vert.m_TexCoord = RenderVec2(start_tex_pos.x, end_tex_pos.y);
    verts.AddVert(vert);

    vert.m_Position = RenderVec2(end_pos.x, start_pos.y);
    vert.m_TexCoord = RenderVec2(end_tex_pos.x, start_tex_pos.y);
    verts.AddVert(vert);

    vert.m_Position = end_pos;
    vert.m_TexCoord = end_tex_pos;
    verts.AddVert(vert);


    buffer.SetBufferData(verts, VertexBufferType::kTriangles);
    auto & shader = g_ShaderManager.GetDefaultWorldSpaceShader();
    render_state.BindShader(shader);
    shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Offset"), RenderVec2{});
    shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Matrix"), RenderVec4{ 1, 0, 0, 1 });
    shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Color"), Color(255, 255, 255, 255));
    shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Texture"), 0);

    render_state.BindTexture(*texture);
    render_state.BindVertexBuffer(buffer);
    render_state.Draw();
  }

  for (auto & tex_info : m_Textures)
  {
    auto texture = tex_info.m_Texture.Resolve();

    if (texture && texture->IsLoaded())
    {
      auto texture_box = Box::FromFrameCenterAndSize(tex_info.m_Pos, texture->GetSize());
      if (BoxIntersect(texture_box, viewport_bounds))
      {
        QuadVertexBufferBuilder builder;
        QuadVertexBuilderInfo quad;
        quad.m_Color = Color(255, 255, 255, 255);
        quad.m_Position = texture_box;
        quad.m_TexCoords = Box::FromPoints({}, texture->GetSize());
        quad.m_TextureSize = texture->GetSize();
        builder.AddQuad(quad);

        builder.FillVertexBuffer(buffer);
        auto & shader = g_ShaderManager.GetDefaultWorldSpaceShader();
        render_state.BindShader(shader);
        shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Offset"), -screen_center);
        shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Matrix"), RenderVec4{ 1, 0, 0, 1 });
        shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Color"), RenderVec4{ 1, 1, 1, 1 });
        shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Texture"), 0);

        render_state.BindTexture(*texture);
        render_state.BindVertexBuffer(buffer);
        render_state.Draw();
      }
    }
  }

  for (auto & sprite_info : m_Sprites)
  {
    auto & sprite = sprite_info.m_Sprite;
    if (sprite->IsLoaded())
    {
      auto & shader = g_ShaderManager.GetDefaultWorldSpaceShader();
      shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Offset"), -screen_center);
      shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Matrix"), RenderVec4{ 1, 0, 0, 1 });
      shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Color"), RenderVec4{ 1, 1, 1, 1 });
      shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Texture"), 0);

      SpriteEngineData::RenderSprite(sprite, render_state, sprite_info.m_State.m_AnimIndex, sprite_info.m_State.m_AnimFrame, 0, sprite_info.m_Pos);
    }
  }
}

int MapParalaxLayerInstance::GetLayerOrder() const
{
  return m_LayerOrder;
}

