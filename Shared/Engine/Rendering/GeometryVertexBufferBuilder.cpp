
#include "Engine/EngineCommon.h"
#include "Engine/Shader/ShaderManager.h"
#include "Engine/Rendering/GeometryVertexBufferBuilder.h"
#include "Engine/Rendering/RenderState.h"

#include "Foundation/Math/Intersection.h"

GeometryVertexBufferBuilder::GeometryVertexBufferBuilder()
{
  m_TexCoord = { 0, 0 };
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
}

void GeometryVertexBufferBuilder::Line(const Vector2f & a, const Vector2f & b, float thickness, const Color & c, float bias)
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
  auto bias_vector = Vector2f(bias, bias);

  auto start = a + bias_vector - dir * bias_vector;
  auto end = b + bias_vector + dir * bias_vector;

  AddVert(start + thick, c);
  AddVert(end + thick, c);
  AddVert(end - thick, c);
  AddVert(start + thick, c);
  AddVert(end - thick, c);
  AddVert(start - thick, c);
}

void GeometryVertexBufferBuilder::Line(const Vector2f & a, const Vector2f & b, float start_thickness, float end_thickness, const Color & c, float bias)
{
  auto offset = b - a;
  auto len = glm::length(offset);

  if (len == 0)
  {
    return;
  }

  auto dir = offset / len;
  auto normal = Vector2f(dir.y, -dir.x);
  auto start_thick = normal * (start_thickness / 2);
  auto end_thick = normal * (end_thickness / 2);
  auto bias_vector = Vector2f(bias, bias);

  auto start = a + bias_vector - dir * bias_vector;
  auto end = b + bias_vector + dir * bias_vector;

  AddVert(start + start_thick, c);
  AddVert(end + end_thick, c);
  AddVert(end - end_thick, c);
  AddVert(start + start_thick, c);
  AddVert(end - end_thick, c);
  AddVert(start - start_thick, c);
}

void GeometryVertexBufferBuilder::Circle(const Vector2f & pos, float radius, float thickness, const Color & c, int num_segs, float bias)
{
  float offset_far = radius + thickness / 2.0f;
  float offset_near = radius - thickness / 2.0f;

  auto bias_vector = Vector2f(bias, bias);
  auto center = pos + bias_vector;

  Vector2f start_far = center + Vector2f(offset_far, 0);
  Vector2f start_near = center + Vector2f(offset_near, 0);

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

void GeometryVertexBufferBuilder::Ellipse(const Vector2f & pos, float radius_x, float radius_y, float thickness, const Color & c, int num_segs, float bias)
{
  float angle_inc = k2Pi / num_segs;
  float angle = angle_inc;

  auto ab = radius_x * radius_y;

  auto bias_vector = Vector2f(bias, bias);
  auto center = pos + bias_vector;

  Vector2f start_far = center + Vector2f(radius_x + thickness, 0);
  Vector2f start_near = center + Vector2f(radius_x - thickness, 0);

  for (int index = 1; index < num_segs + 1; index++)
  {
    auto dir = SinCosf(angle);

    auto den_x = dir.y * radius_x;
    auto den_y = dir.x * radius_y;

    auto radius = ab / sqrtf(den_x * den_x + den_y * den_y);

    float offset_far = radius + thickness / 2.0f;
    float offset_near = radius - thickness / 2.0f;

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

void GeometryVertexBufferBuilder::Arc(const Vector2f & pos, float radius, float thickness, const Color & c, float middle_angle, float arc_half_angle, int num_segs, float bias)
{
  float offset_far = radius + thickness / 2.0f;
  float offset_near = radius - thickness / 2.0f;

  auto start_angle = middle_angle - arc_half_angle;
  auto start_dir = SinCosf(start_angle);

  auto bias_vector = Vector2f(bias, bias);
  auto center = pos + bias_vector;

  Vector2f start_far = center + start_dir * offset_far;
  Vector2f start_near = center + start_dir * offset_near;

  float angle_inc = arc_half_angle * 2 / num_segs;
  float angle = start_angle + angle_inc;

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

void GeometryVertexBufferBuilder::Rectangle(const Vector2f & a, const Vector2f & b, float thickness, const Color & c, float bias)
{
  float sx = std::min(a.x, b.x);
  float sy = std::min(a.y, b.y);
  float ex = std::max(a.x, b.x);
  float ey = std::max(a.y, b.y);

  Line(Vector2f{ sx, sy }, Vector2f{ ex, sy }, thickness, c, bias);
  Line(Vector2f{ sx, sy }, Vector2f{ sx, ey }, thickness, c, bias);
  Line(Vector2f{ ex, sy }, Vector2f{ ex, ey }, thickness, c, bias);
  Line(Vector2f{ sx, ey }, Vector2f{ ex, ey }, thickness, c, bias);
}

void GeometryVertexBufferBuilder::Rectangle(const Box & box, float thickness, const Color & c, float bias)
{
  float sx = (float)(box.m_Start.x);
  float sy = (float)(box.m_Start.y);
  float ex = (float)(box.m_End.x);
  float ey = (float)(box.m_End.y);

  Line(Vector2f{ sx, sy }, Vector2f{ ex, sy }, thickness, c, bias);
  Line(Vector2f{ sx, sy }, Vector2f{ sx, ey }, thickness, c, bias);
  Line(Vector2f{ ex, sy }, Vector2f{ ex, ey }, thickness, c, bias);
  Line(Vector2f{ sx, ey }, Vector2f{ ex, ey }, thickness, c, bias);
}

void GeometryVertexBufferBuilder::FilledCircle(const Vector2f & pos, float radius, const Color & c, int num_segs, float bias)
{
  float angle_inc = k2Pi / num_segs;
  float angle = angle_inc;

  Vector2f prev_pos = { radius, 0 };

  auto center = pos + Vector2f(bias, bias);

  for (int index = 1; index < num_segs + 1; index++)
  {
    auto cur_pos = SinCosf(angle) * radius;

    AddVert(center, c);
    AddVert(center + cur_pos, c);
    AddVert(center + prev_pos, c);

    prev_pos = cur_pos;
    angle += angle_inc;
  }
}

void GeometryVertexBufferBuilder::FilledEllipse(const Vector2f & pos, float radius_x, float radius_y, const Color & c, int num_segs, float bias)
{
  float angle_inc = k2Pi / num_segs;
  float angle = angle_inc;

  auto ab = radius_x * radius_y;

  Vector2f prev_pos = { radius_x, 0 };

  auto center = pos + Vector2f(bias, bias);

  for (int index = 1; index < num_segs + 1; index++)
  {
    auto dir = SinCosf(angle);

    auto den_x = dir.y * radius_x;
    auto den_y = dir.x * radius_y;

    auto radius = ab / sqrtf(den_x * den_x + den_y * den_y);

    auto cur_pos = dir * radius;

    AddVert(center, c);
    AddVert(center + cur_pos, c);
    AddVert(center + prev_pos, c);

    prev_pos = cur_pos;
    angle += angle_inc;
  }
}

void GeometryVertexBufferBuilder::FilledRectangle(const Vector2f & a, const Vector2f & b, const Color & c, float bias)
{
  auto bias_vector = Vector2f(bias, bias);
  AddVert(Vector2f{ a.x, a.y } + bias_vector, c);
  AddVert(Vector2f{ a.x, b.y } + bias_vector, c);
  AddVert(Vector2f{ b.x, b.y } + bias_vector, c);
  AddVert(Vector2f{ a.x, a.y } + bias_vector, c);
  AddVert(Vector2f{ b.x, b.y } + bias_vector, c);
  AddVert(Vector2f{ b.x, a.y } + bias_vector, c);
}

void GeometryVertexBufferBuilder::FilledRectangle(const Box & box, const Color & c, float bias)
{
  Vector2f start = (Vector2f)box.m_Start;
  Vector2f end = (Vector2f)box.m_End + Vector2f(1, 1);
  FilledRectangle(start, end, c, bias);
}

void GeometryVertexBufferBuilder::Trail(const gsl::span<TrailInfo> & points, float texture_width)
{
  if (points.size() <= 1)
  {
    return;
  }

  int prev_index = 0;
  int cur_index = 1;
  int num_points = (int)points.size();

  Vector2f prev_point = points[0].m_Position;
  Vector2f cur_point = points[1].m_Position;

  Vector2f prev_dir;
  Color prev_color = points[0].m_Color;
  float prev_thickness = points[0].m_Thickness;
  float prev_len;

  Color cur_color;
  float cur_thickness;

  float tx = 0;

  while (true)
  {
    while (cur_index < num_points)
    {
      cur_point = points[cur_index].m_Position;
      cur_thickness = points[cur_index].m_Thickness;
      cur_color = points[cur_index].m_Color;

      prev_dir = cur_point - prev_point;
      prev_len = IntersectionVecFuncs<Vector2f>::NormalizeInPlace(prev_dir);

      if (prev_len > 0)
      {
        break;
      }

      cur_index++;
    }

    if (cur_index >= num_points)
    {
      break;
    }

    auto prev_dir_perp = IntersectionVecFuncs<Vector2f>::GetPerpVec(prev_dir);
    auto prev_offset = prev_dir_perp * (prev_thickness / 2.0f);
    auto cur_offset = prev_dir_perp * (cur_thickness / 2.0f);

    float etx = tx + (prev_len / texture_width);

    AddVert(prev_point + prev_offset, prev_color, Vector2f{ tx, 1 });
    AddVert(prev_point - prev_offset, prev_color, Vector2f{ tx, 0 });
    AddVert(cur_point + cur_offset, cur_color, Vector2f{ etx, 1 });
    AddVert(prev_point - prev_offset, prev_color, Vector2f{ tx, 0 });
    AddVert(cur_point + cur_offset, cur_color, Vector2f{ etx, 1 });
    AddVert(cur_point - cur_offset, cur_color, Vector2f{ etx, 0 });

    prev_color = cur_color;
    prev_thickness = cur_thickness;
    prev_point = cur_point;

    prev_index = cur_index;
    cur_index++;
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

void GeometryVertexBufferBuilder::DrawDefault(RenderState & render_state, NullOptPtr<ShaderProgram> shader)
{
  if (shader == nullptr)
  {
    shader = &g_ShaderManager.GetDefaultWorldSpaceShader();
  }

  render_state.BindShader(*shader);

  auto & vertex_buffer = render_state.GetScratchBuffer();
  FillVertexBuffer(vertex_buffer);

  render_state.BindVertexBuffer(vertex_buffer);
  render_state.BindTexture(render_state.GetDefaultTexture());
  render_state.Draw();
}

bool GeometryVertexBufferBuilder::HasGeo() const
{
  return m_List.HasVerts();
}

void GeometryVertexBufferBuilder::AddVert(const Vector2f & pos, const Color & c)
{
  VertexInfo & v = m_List.AddVert();
  v.m_Position = pos;
  v.m_Color = c;
  v.m_TexCoord = m_TexCoord;
}

void GeometryVertexBufferBuilder::AddVert(const Vector2f & pos, const Color & c, const Vector2f & texcoord)
{
  VertexInfo & v = m_List.AddVert();
  v.m_Position = pos;
  v.m_Color = c;
  v.m_TexCoord = texcoord;
}