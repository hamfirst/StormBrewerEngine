
#include "Engine/EngineCommon.h"
#include "Engine/Rendering/VertexBufferBuilder.h"
#include "Engine/Rendering/VertexList.h"

QuadVertexBufferBuilder::QuadVertexBufferBuilder(std::size_t reserve_quads)
{
  m_Quads.reserve(reserve_quads);
}

void QuadVertexBufferBuilder::AddQuad(const QuadVertexBuilderInfo & quad)
{
  m_Quads.push_back(quad);
}

void QuadVertexBufferBuilder::AddRepeatingQuad(const QuadVertexBuilderInfo & quad)
{
  auto start_x = quad.m_Position.m_Start.x;
  auto tile_size = quad.m_TexCoords.m_End - quad.m_TexCoords.m_Start;

  if (tile_size.x < 0 || tile_size.y < 0)
  {
    return;
  }
  
  int width = quad.m_Position.m_End.x - quad.m_Position.m_Start.x + 1;
  int height = quad.m_Position.m_End.y - quad.m_Position.m_Start.y + 1;

  QuadVertexBuilderInfo result_quad = quad;

  int y = quad.m_Position.m_Start.y;
  while (height > 0)
  {
    int width_copy = width;
    int x = start_x;

    int tile_height = std::min(height, (int)tile_size.y);

    while (width_copy > 0)
    {
      int tile_width = std::min(width_copy, (int)tile_size.x);

      result_quad.m_Position.m_Start = Vector2(x, y);
      result_quad.m_Position.m_End = result_quad.m_Position.m_Start + Vector2(tile_width, tile_height);
      result_quad.m_TexCoords.m_End = result_quad.m_TexCoords.m_Start + Vector2(tile_width, tile_height);
      m_Quads.push_back(result_quad);

      width_copy -= tile_width;
      x += tile_width;
    }

    height -= tile_height;
    y += tile_height;
  }
}

bool QuadVertexBufferBuilder::AddSlicedQuad(const QuadVertexBuilderInfo & quad, const Box & bounds)
{
  Optional<Box> clipped_box = ClipBox(quad.m_Position, bounds);

  if (clipped_box)
  {
    Vector2 start_offset = clipped_box->m_Start - quad.m_Position.m_Start;
    Vector2 end_offset = clipped_box->m_End - quad.m_Position.m_End;
    QuadVertexBuilderInfo clipped_vert_data = quad;
    clipped_vert_data.m_Position = *clipped_box;
    clipped_vert_data.m_TexCoords.m_Start += start_offset;
    clipped_vert_data.m_TexCoords.m_End += end_offset;

    AddQuad(clipped_vert_data);
    return true;
  }

  return false;
}

void QuadVertexBufferBuilder::AddFrame(const Box & position, const Vector2 & texture_size, const Vector2 & frame_size, int frame_index, const Color & color)
{
  if (frame_size.x == 0 || frame_size.y == 0 || texture_size.x == 0 || texture_size.y == 0)
  {
    return;
  }

  QuadVertexBuilderInfo quad;
  quad.m_Position = position;
  quad.m_Position.m_End += Vector2(1, 1);
  quad.m_Color = color;
  quad.m_TextureSize = texture_size;

  int width_in_frames = (texture_size.x + frame_size.x - 1) / frame_size.x;
  int fx = (frame_index % width_in_frames) * frame_size.x;
  int fy = (frame_index / width_in_frames) * frame_size.y;

  quad.m_TexCoords.m_Start = Vector2(fx, fy);
  quad.m_TexCoords.m_End = quad.m_TexCoords.m_Start + frame_size;
  AddQuad(quad);
}

VertexBuffer QuadVertexBufferBuilder::CreateVertexBuffer()
{
  VertexList verts;

  // 0 = 00
  // 1 = 01
  // 2 = 11
  // 3 = 10

  uint32_t index_vals[6] = { 0, 1, 2, 0, 2, 3 };

  for (auto & quad : m_Quads)
  {
    for (uint32_t vert = 0; vert < 6; vert++)
    {
      uint32_t index = index_vals[vert];

      VertexInfo vert_info;
      vert_info.m_Position = SelectVectorXY(quad.m_Position.m_Start, quad.m_Position.m_End, index < 2 ? index : 5 - index);
      vert_info.m_TexCoord = SelectVectorXY(quad.m_TexCoords.m_Start, quad.m_TexCoords.m_End, (index < 2 ? index : 5 - index) ^ 0b10);
      vert_info.m_TexCoord /= static_cast<RenderVec2>(quad.m_TextureSize);
      vert_info.m_Color = quad.m_Color;

      verts.AddVert(vert_info);
    }
  }

  VertexBuffer vertex_buffer;
  vertex_buffer.SetBufferData(verts, VertexBufferType::kTriangles);
  return vertex_buffer;
}

VertexBuffer QuadVertexBufferBuilder::SliceVertexBuffer(const Box & bounds)
{
  VertexList verts;

  uint32_t index_vals[6] = { 0, 1, 2, 0, 2, 3 };

  for (auto & quad : m_Quads)
  {
    Optional<Box> clipped_box = ClipBox(quad.m_Position, bounds);

    if (clipped_box)
    {
      Vector2 start_offset = clipped_box->m_Start - quad.m_Position.m_Start;
      Vector2 end_offset = clipped_box->m_End - quad.m_Position.m_End;
      QuadVertexBuilderInfo clipped_vert_data = quad;
      clipped_vert_data.m_Position = *clipped_box;
      clipped_vert_data.m_TexCoords.m_Start += start_offset;
      clipped_vert_data.m_TexCoords.m_End += end_offset;

      for (uint32_t vert = 0; vert < 6; vert++)
      {
        uint32_t index = index_vals[vert];

        VertexInfo vert_info;
        vert_info.m_Position = SelectVectorXY(clipped_vert_data.m_Position.m_Start, clipped_vert_data.m_Position.m_End, index < 2 ? index : 5 - index);
        vert_info.m_TexCoord = SelectVectorXY(clipped_vert_data.m_TexCoords.m_Start, clipped_vert_data.m_TexCoords.m_End, (index < 2 ? index : 5 - index) ^ 0b10);
        vert_info.m_TexCoord /= static_cast<RenderVec2>(clipped_vert_data.m_TextureSize);
        vert_info.m_Color = clipped_vert_data.m_Color;

        verts.AddVert(vert_info);
      }
    }
  }

  VertexBuffer vertex_buffer;
  vertex_buffer.SetBufferData(verts, VertexBufferType::kTriangles);
  return vertex_buffer;
}

void QuadVertexBufferBuilder::FillVertexBuffer(VertexBuffer & vertex_buffer)
{
  VertexList verts;

  uint32_t index_vals[6] = { 0, 1, 2, 0, 2, 3 };

  for (auto & quad : m_Quads)
  {
    for (uint32_t vert = 0; vert < 6; vert++)
    {
      uint32_t index = index_vals[vert];

      VertexInfo vert_info;
      vert_info.m_Position = SelectVectorXY(quad.m_Position.m_Start, quad.m_Position.m_End, index < 2 ? index : 5 - index);
      vert_info.m_TexCoord = SelectVectorXY(quad.m_TexCoords.m_Start, quad.m_TexCoords.m_End, (index < 2 ? index : 5 - index));
      vert_info.m_TexCoord /= static_cast<RenderVec2>(quad.m_TextureSize);
      vert_info.m_Color = quad.m_Color;

      verts.AddVert(vert_info);
    }
  }

  vertex_buffer.SetBufferData(verts, VertexBufferType::kTriangles);
}


LineVertexBufferBuilder::LineVertexBufferBuilder(std::size_t reserve_points)
{
  m_Lines.reserve(reserve_points);
}


bool LineVertexBufferBuilder::HasData() const
{
  return m_Lines.size() > 0;
}

void LineVertexBufferBuilder::AddLine(const LineVertexBuilderInfo & line)
{
  m_Lines.push_back(line);
}

void LineVertexBufferBuilder::AddBox(const QuadVertexBuilderInfo & quad)
{
  LineVertexBuilderInfo line;
  line.m_Color = quad.m_Color;
  line.m_TextureSize = quad.m_TextureSize;

  line.m_Start = SelectVectorXY(quad.m_Position.m_Start, quad.m_Position.m_End, 0b11);
  line.m_End = SelectVectorXY(quad.m_Position.m_Start, quad.m_Position.m_End, 0b10);
  line.m_TexCoordStart = SelectVectorXY(quad.m_TexCoords.m_Start, quad.m_TexCoords.m_End, 0b11);
  line.m_TexCoordEnd = SelectVectorXY(quad.m_TexCoords.m_Start, quad.m_TexCoords.m_End, 0b10);
  m_Lines.push_back(line);

  line.m_Start = SelectVectorXY(quad.m_Position.m_Start, quad.m_Position.m_End, 0b01);
  line.m_End = SelectVectorXY(quad.m_Position.m_Start, quad.m_Position.m_End, 0b00);
  line.m_TexCoordStart = SelectVectorXY(quad.m_TexCoords.m_Start, quad.m_TexCoords.m_End, 0b01);
  line.m_TexCoordEnd = SelectVectorXY(quad.m_TexCoords.m_Start, quad.m_TexCoords.m_End, 0b00);
  m_Lines.push_back(line);

  line.m_Start = SelectVectorXY(quad.m_Position.m_Start, quad.m_Position.m_End, 0b11);
  line.m_End = SelectVectorXY(quad.m_Position.m_Start, quad.m_Position.m_End, 0b01);
  line.m_TexCoordStart = SelectVectorXY(quad.m_TexCoords.m_Start, quad.m_TexCoords.m_End, 0b11);
  line.m_TexCoordEnd = SelectVectorXY(quad.m_TexCoords.m_Start, quad.m_TexCoords.m_End, 0b01);
  m_Lines.push_back(line);

  line.m_Start = SelectVectorXY(quad.m_Position.m_Start, quad.m_Position.m_End, 0b10);
  line.m_End = SelectVectorXY(quad.m_Position.m_Start, quad.m_Position.m_End, 0b00);
  line.m_TexCoordStart = SelectVectorXY(quad.m_TexCoords.m_Start, quad.m_TexCoords.m_End, 0b10);
  line.m_TexCoordEnd = SelectVectorXY(quad.m_TexCoords.m_Start, quad.m_TexCoords.m_End, 0b00);
  m_Lines.push_back(line);
}

VertexBuffer LineVertexBufferBuilder::CreateVertexBuffer()
{
  VertexList verts;

  for (auto & line : m_Lines)
  {
    auto tex_size = static_cast<RenderVec2>(line.m_TextureSize);

    VertexInfo vert_info;
    vert_info.m_Color = line.m_Color;

    vert_info.m_Position = line.m_Start;
    vert_info.m_TexCoord = line.m_TexCoordStart;
    vert_info.m_TexCoord /= tex_size;
    verts.AddVert(vert_info);

    vert_info.m_Position = line.m_End;
    vert_info.m_TexCoord = line.m_TexCoordEnd;
    vert_info.m_TexCoord /= tex_size;
    verts.AddVert(vert_info);
  }

  VertexBuffer vertex_buffer;
  vertex_buffer.SetBufferData(verts, VertexBufferType::kLines);
  return vertex_buffer;
}

void LineVertexBufferBuilder::FillVertexBuffer(VertexBuffer & vertex_buffer)
{
  VertexList verts;

  for (auto & line : m_Lines)
  {
    auto tex_size = static_cast<RenderVec2>(line.m_TextureSize);

    VertexInfo vert_info;
    vert_info.m_Color = line.m_Color;

    vert_info.m_Position = line.m_Start;
    vert_info.m_TexCoord = line.m_TexCoordStart;
    vert_info.m_TexCoord /= tex_size;
    verts.AddVert(vert_info);

    vert_info.m_Position = line.m_End;
    vert_info.m_TexCoord = line.m_TexCoordEnd;
    vert_info.m_TexCoord /= tex_size;
    verts.AddVert(vert_info);
  }

  vertex_buffer.SetBufferData(verts, VertexBufferType::kLines);
}

PointVertexBufferBuilder::PointVertexBufferBuilder(std::size_t reserve_points)
{
  m_Points.reserve(reserve_points);
}

void PointVertexBufferBuilder::AddPoint(const PointVertexBuilderInfo & point)
{
  m_Points.push_back(point);
}

VertexBuffer PointVertexBufferBuilder::CreateVertexBuffer()
{
  VertexList verts;

  for (auto & point : m_Points)
  {
    auto tex_size = static_cast<RenderVec2>(point.m_TextureSize);

    VertexInfo vert_info;
    vert_info.m_Position = point.m_Position;
    vert_info.m_TexCoord = point.m_TexCoord;
    vert_info.m_TexCoord /= tex_size;
    if (tex_size.x != 0 && tex_size.y != 0)
    {
      // Half texel offset
      tex_size.x = 0.5f / tex_size.x;
      tex_size.y = 0.5f / tex_size.y;
      vert_info.m_TexCoord += tex_size;
    }

    vert_info.m_Color = point.m_Color;

    verts.AddVert(vert_info);
  }

  VertexBuffer vertex_buffer;
  vertex_buffer.SetBufferData(verts, VertexBufferType::kPoints);
  return vertex_buffer;
}

VertexBuffer PointVertexBufferBuilder::SliceVertexBuffer(const Box & bounds)
{
  VertexList verts;

  for (auto & point : m_Points)
  {
    if (PointInBox(bounds, point.m_Position))
    {
      VertexInfo vert_info;
      vert_info.m_Position = point.m_Position;
      vert_info.m_TexCoord = point.m_TexCoord;
      vert_info.m_TexCoord /= static_cast<RenderVec2>(point.m_TextureSize);
      vert_info.m_Color = point.m_Color;

      verts.AddVert(vert_info);
    }
  }

  VertexBuffer vertex_buffer;
  vertex_buffer.SetBufferData(verts, VertexBufferType::kPoints);
  return vertex_buffer;
}

void PointVertexBufferBuilder::FillVertexBuffer(VertexBuffer & vertex_buffer)
{
  VertexList verts;

  for (auto & point : m_Points)
  {
    VertexInfo vert_info;
    vert_info.m_Position = point.m_Position;
    vert_info.m_TexCoord = point.m_TexCoord;
    vert_info.m_TexCoord /= static_cast<RenderVec2>(point.m_TextureSize);
    vert_info.m_Color = point.m_Color;

    verts.AddVert(vert_info);
  }

  vertex_buffer.SetBufferData(verts, VertexBufferType::kPoints);
}
