
#include "StormData/StormDataJson.h"

#include "Foundation/BasicTypes/BasicTypeFuncs.h"

#include "Runtime/Map/MapTileJson.h"

#include "Engine/Rendering/VertexBufferBuilder.h"
#include "Engine/Rendering/RenderUtil.h"
#include "Engine/Rendering/VertexList.h"
#include "Engine/Shader/ShaderManager.h"

#include "MapEditorParalaxLayer.h"
#include "MapEditor.h"


MapEditorParalaxLayer::MapEditorParalaxLayer(NotNullPtr<MapEditor> editor, MapDef & map, int layer_index) :
  m_Editor(editor),
  m_Map(map),
  m_LayerIndex(layer_index),
  m_TextureWatcher(m_Editor)
{
  HandleTextureChanged();
}

void MapEditorParalaxLayer::Draw(VertexBuffer & buffer, const Box & viewport_bounds, RenderVec2 & screen_center)
{
  auto texture = m_TextureAsset.Resolve();
  if (texture == nullptr || texture->IsLoaded() == false || texture->GetWidth() == 0 || texture->GetHeight() == 0)
  {
    return;
  }

  auto layer = m_Map.m_ParalaxLayers.TryGet(m_LayerIndex);
  if (layer == nullptr)
  {
    return;
  }

  auto viewport_size = viewport_bounds.Size();
  auto half_viewport_size = RenderVec2(viewport_size) * 0.5f;

  int width = layer->m_RepeatX ? texture->GetWidth() : viewport_size.x;
  int height = layer->m_RepeatY ? texture->GetHeight() : viewport_size.y;

  auto time = (float)GetTimeSeconds();

  float offset_x = (layer->m_ParalaxX == 0.0f ? 0.0f : (screen_center.x / -layer->m_ParalaxX.AsFloat())) + time * layer->m_VelocityX.AsFloat() + layer->m_OffsetX.AsFloat();
  float offset_y = (layer->m_ParalaxY == 0.0f ? 0.0f : (screen_center.y / -layer->m_ParalaxY.AsFloat())) + time * layer->m_VelocityY.AsFloat() + layer->m_OffsetY.AsFloat();

  offset_x *= (float)texture->GetWidth() / (float)width;
  offset_y *= (float)texture->GetHeight() / (float)height;

  offset_x = glm::fract(offset_x / texture->GetWidth()) * width;
  offset_y = glm::fract(offset_y / texture->GetHeight()) * height;

  VertexList verts;
  VertexInfo vert;

  RenderVec2 tex_size(width, height);
  RenderVec2 offset(offset_x, offset_y);

  RenderVec2 start_pos = -half_viewport_size;
  RenderVec2 end_pos = half_viewport_size;

  RenderVec2 start_tex_pos = (-half_viewport_size - offset) / tex_size;
  RenderVec2 end_tex_pos = (half_viewport_size - offset) / tex_size;

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
  auto & shader = g_ShaderManager.GetDefaultShader();
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Offset"), RenderVec2{});
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Matrix"), RenderVec4{ 1, 0, 0, 1 });
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Color"), RenderVec4{ 1, 1, 1, 1 });
  texture->GetTexture().BindTexture(0);

  buffer.Bind();

  buffer.CreateDefaultBinding(shader);
  buffer.Draw();
  buffer.Unbind();
}

void MapEditorParalaxLayer::ToggleHidden()
{
  m_Hidden = !m_Hidden;
}

void MapEditorParalaxLayer::SetHidden(bool hidden)
{
  m_Hidden = hidden;
}

bool MapEditorParalaxLayer::IsHidden()
{
  return m_Hidden;
}

void MapEditorParalaxLayer::HandleTextureChanged()
{
  auto layer = m_Map.m_ParalaxLayers.TryGet(m_LayerIndex);
  if(layer == nullptr)
  {
    return;
  }

  m_TextureAsset = TextureAsset::Load(layer->m_Image.data());
}
