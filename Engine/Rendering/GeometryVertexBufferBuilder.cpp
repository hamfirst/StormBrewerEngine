
#include "Engine/EngineCommon.h"
#include "Engine/Rendering/GeometryVertexBufferBuilder.h"


GeometryVertexBufferBuilder::GeometryVertexBufferBuilder()
{
  m_TexCoord = { 0, 0 };
  Begin();
}

GeometryVertexBufferBuilder::GeometryVertexBufferBuilder(const Vector2 & texture_pos, const Vector2 & texture_pos_size)
{
  if (texture_pos_size.x == 0 || texture_pos_size.y == 0)
  {
    m_TexCoord = { 0, 0 };
  }
  else
  {
    m_TexCoord.x = (float)texture_pos.x / (float)texture_pos_size.x;
    m_TexCoord.y = (float)texture_pos.y / (float)texture_pos_size.y;
  }

  Begin();
}


void GeometryVertexBufferBuilder::Begin()
{
  m_HasCurPos = false;
  m_HasPrevPos = false;
}

void GeometryVertexBufferBuilder::LineTo(const Vector2f & pos, float thickness, const Color & c)
{
  if (m_HasPrevPos == false)
  {
    m_PrevPos = pos;
    m_PrevThickness = thickness;
    m_PrevColor = c;
    m_HasPrevPos = true;
    return;
  }

  if (m_HasCurPos == false)
  {
    auto offset = pos - m_PrevPos;
    auto len = glm::length(offset);

    if (len == 0)
    {
      return;
    }

    m_CurPos = pos;
    m_CurDir = offset / len;
    m_CurThickness = thickness;
    m_CurColor = c;
    return;
  }
}

void GeometryVertexBufferBuilder::End()
{

}

void GeometryVertexBufferBuilder::Line(const Vector2f & a, const Vector2f & b, float thickness, const Color & c)
{
  auto offset = b - a;
  auto len = glm::length(offset);

  if (len == 0)
  {
    return;
  }

  auto dir = offset / len;
  auto normal = Vector2f(dir.y, -dir.x);
  auto thick = normal * (thickness / 2);

  AddVert(a + thick, c);
  AddVert(b + thick, c);
  AddVert(b - thick, c);
  AddVert(a + thick, c);
  AddVert(b - thick, c);
  AddVert(a - thick, c);
}

void GeometryVertexBufferBuilder::Circle(const Vector2f & pos, float radius, float thickness, const Color & c, int num_segs)
{
  float offset_far = radius + thickness / 2.0f;
  float offset_near = radius - thickness / 2.0f;

  Vector2f start_far = pos + Vector2f(offset_far, 0);
  Vector2f start_near = pos + Vector2f(offset_near, 0);

  float angle_inc = k2Pi / num_segs;
  float angle = angle_inc;

  for (int index = 1; index < num_segs + 1; index++)
  {
    auto dir = SinCosf(angle);

    auto cur_far = pos + dir * offset_far;
    auto cur_near = pos + dir * offset_near;

    AddVert(start_far, c);
    AddVert(cur_far, c);
    AddVert(cur_near, c);
    AddVert(start_far, c);
    AddVert(cur_near, c);
    AddVert(start_near, c);

    start_far = cur_far;
    start_near = cur_near;

    angle += angle_inc;
  }
}


VertexBuffer GeometryVertexBufferBuilder::CreateVertexBuffer()
{
  VertexBuffer vertex_buffer;
  vertex_buffer.SetBufferData(m_List, VertexBufferType::kTriangles);
  return vertex_buffer;
}

void GeometryVertexBufferBuilder::FillVertexBuffer(VertexBuffer & vertex_buffer)
{
  vertex_buffer.SetBufferData(m_List, VertexBufferType::kTriangles);
}

void GeometryVertexBufferBuilder::AddVert(const Vector2f & pos, const Color & c)
{
  VertexInfo & v = m_List.AddVert();
  v.m_Position = pos;
  v.m_Color = c;
  v.m_TexCoord = m_TexCoord;
}
