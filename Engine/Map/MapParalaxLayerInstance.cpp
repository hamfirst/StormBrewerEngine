
#include "Engine/EngineCommon.h"
#include "Engine/Map/MapParalaxLayerInstance.h"
#include "Engine/Rendering/VertexList.h"
#include "Engine/Rendering/RenderState.h"
#include "Engine/Rendering/RenderUtil.h"
#include "Engine/Shader/ShaderManager.h"


MapParalaxLayerInstance::MapParalaxLayerInstance(MapDef & map, std::size_t layer_index)
{
  auto & layer_data = map.m_ParalaxLayers[(int)layer_index];
  m_LayerOrder = layer_data.m_LayerOrder;

  m_Texture = TextureAsset::Load(layer_data.m_Image.data());
  m_RepeatX = layer_data.m_RepeatX;
  m_RepeatY = layer_data.m_RepeatY;
  m_ParalaxX = layer_data.m_ParalaxX;
  m_ParalaxY = layer_data.m_ParalaxY;
}

void MapParalaxLayerInstance::Update()
{

}

void MapParalaxLayerInstance::Draw(const Box & viewport_bounds, const RenderVec2 & screen_center, RenderState & render_state, RenderUtil & render_util)
{
  auto texture = m_Texture.Resolve();
  if (texture == nullptr || texture->IsLoaded() == false || texture->GetWidth() == 0 || texture->GetHeight() == 0)
  {
    return;
  }

  auto viewport_size = viewport_bounds.Size();
  auto half_viewport_size = RenderVec2(viewport_size) * 0.5f;

  int width = m_RepeatX ? texture->GetWidth() : viewport_size.x;
  int height = m_RepeatY ? texture->GetHeight() : viewport_size.y;

  float offset_x = m_ParalaxX == 0.0f ? 0.0f : (screen_center.x / -m_ParalaxX);
  float offset_y = m_ParalaxY == 0.0f ? 0.0f : (screen_center.y / -m_ParalaxY);

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

  auto & buffer = render_util.GetScratchBuffer();
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

int MapParalaxLayerInstance::GetLayerOrder() const
{
  return m_LayerOrder;
}

