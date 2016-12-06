
#include "Engine/EngineCommon.h"
#include "Engine/Rendering/VertexBufferBuilder.h"

QuadVertexBufferBuilder::QuadVertexBufferBuilder(std::size_t reserve_quads)
{
  m_Quads.reserve(reserve_quads);
}

void QuadVertexBufferBuilder::AddQuad(const QuadVertexBuilderInfo & quad)
{
  m_Quads.push_back(quad);
}

VertexBuffer QuadVertexBufferBuilder::CreateVertexBuffer()
{
  std::vector<VertexInfo> verts;
  std::vector<uint16_t> indices;

  // 0 = 00
  // 1 = 01
  // 2 = 11
  // 3 = 10

  for (QuadVertexBuilderInfo & quad : m_Quads)
  {
    for (uint32_t index = 0; index < 4; index++)
    {
      VertexInfo vert_info;
      vert_info.m_Position = SelectVectorXY(quad.m_Position.m_Start, quad.m_Position.m_End, index < 2 ? index : 5 - index);
      vert_info.m_TexCoord = SelectVectorXY(quad.m_TexCoords.m_Start, quad.m_TexCoords.m_End, (index < 2 ? index : 5 - index) ^ 0b10);
      vert_info.m_TexCoord /= static_cast<RenderVec2>(quad.m_TextureSize);
      vert_info.m_Color = quad.m_Color;

      indices.push_back((uint16_t)verts.size());
      verts.push_back(vert_info);
    }
  }

  VertexBuffer vertex_buffer;
  vertex_buffer.SetBufferData(verts, indices, VertexBufferType::kQuads);
  return vertex_buffer;
}

VertexBuffer QuadVertexBufferBuilder::SliceVertexBuffer(const Box & bounds)
{
  std::vector<VertexInfo> verts;
  std::vector<uint16_t> indices;

  for (QuadVertexBuilderInfo & quad : m_Quads)
  {
    Optional<Box> clipped_box = ClipBox(quad.m_Position, bounds);

    if (clipped_box)
    {
      Vector2 start_offset = clipped_box->m_Start - quad.m_Position.m_Start;
      Vector2 end_offset = clipped_box->m_End - quad.m_Position.m_End;
      QuadVertexBuilderInfo clipped_vert_data = quad;
      clipped_vert_data.m_Position = *clipped_box;
      clipped_vert_data.m_TexCoords.m_Start += start_offset;
      clipped_vert_data.m_TexCoords.m_End += start_offset;

      for (uint32_t index = 0; index < 4; index++)
      {
        VertexInfo vert_info;
        vert_info.m_Position = SelectVectorXY(clipped_vert_data.m_Position.m_Start, clipped_vert_data.m_Position.m_End, index < 2 ? index : 5 - index);
        vert_info.m_TexCoord = SelectVectorXY(clipped_vert_data.m_TexCoords.m_Start, clipped_vert_data.m_TexCoords.m_End, (index < 2 ? index : 5 - index) ^ 0b10);
        vert_info.m_TexCoord /= static_cast<RenderVec2>(clipped_vert_data.m_TextureSize);
        vert_info.m_Color = clipped_vert_data.m_Color;

        indices.push_back((uint16_t)verts.size());
        verts.push_back(vert_info);
      }
    }
  }

  VertexBuffer vertex_buffer;
  vertex_buffer.SetBufferData(verts, indices, VertexBufferType::kQuads);
  return vertex_buffer;
}

void QuadVertexBufferBuilder::FillVertexBuffer(VertexBuffer & vertex_buffer)
{
  std::vector<VertexInfo> verts;
  std::vector<uint16_t> indices;

  uint16_t vert_index = 0;

  for (QuadVertexBuilderInfo & quad : m_Quads)
  {
    for (uint32_t index = 0; index < 4; index++)
    {
      VertexInfo vert_info;
      vert_info.m_Position = SelectVectorXY(quad.m_Position.m_Start, quad.m_Position.m_End, index < 2 ? index : 5 - index);
      vert_info.m_TexCoord = SelectVectorXY(quad.m_TexCoords.m_Start, quad.m_TexCoords.m_End, (index < 2 ? index : 5 - index) ^ 0b10);
      vert_info.m_TexCoord /= static_cast<RenderVec2>(quad.m_TextureSize);
      vert_info.m_Color = quad.m_Color;

      indices.push_back(vert_index);
      verts.push_back(vert_info);

      vert_index++;
    }
  }

  vertex_buffer.SetBufferData(verts, indices, VertexBufferType::kQuads);
}

