
#include "Engine/EngineCommon.h"
#include "Engine/Shader/ShaderManager.h"
#include "Engine/Rendering/GeometryVertexBufferBuilder.h"
#include "Engine/Rendering/RenderUtil.h"
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

void GeometryVertexBufferBuilder::Line(const Vector2f & a, const Vector2f & b, float start_thickness, float end_thickness, const Color & c)
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

  AddVert(a + start_thick, c);
  AddVert(b + end_thick, c);
  AddVert(b - end_thick, c);
  AddVert(a + start_thick, c);
  AddVert(b - end_thick, c);
  AddVert(a - start_thick, c);
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

void GeometryVertexBufferBuilder::Ellipse(const Vector2f & pos, float radius_x, float radius_y, float thickness, const Color & c, int num_segs)
{
  float angle_inc = k2Pi / num_segs;
  float angle = angle_inc;

  auto ab = radius_x * radius_y; 

  Vector2f start_far = pos + Vector2f(radius_x + thickness, 0);
  Vector2f start_near = pos + Vector2f(radius_x - thickness, 0);

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

void GeometryVertexBufferBuilder::Arc(const Vector2f & pos, float radius, float thickness, const Color & c, float middle_angle, float arc_half_angle, int num_segs)
{
  float offset_far = radius + thickness / 2.0f;
  float offset_near = radius - thickness / 2.0f;

  auto start_angle = middle_angle - arc_half_angle;
  auto start_dir = SinCosf(start_angle);

  Vector2f start_far = pos + start_dir * offset_far;
  Vector2f start_near = pos + start_dir * offset_near;

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

void GeometryVertexBufferBuilder::Rectangle(const Vector2f & a, const Vector2f & b, float thickness, const Color & c)
{
  float sx = std::min(a.x, b.x);
  float sy = std::min(a.y, b.y);
  float ex = std::max(a.x, b.x);
  float ey = std::max(a.y, b.y);

  Line(Vector2f{ sx, sy }, Vector2f{ ex, sy }, thickness, c);
  Line(Vector2f{ sx, sy }, Vector2f{ sx, ey }, thickness, c);
  Line(Vector2f{ ex, sy }, Vector2f{ ex, ey }, thickness, c);
  Line(Vector2f{ sx, ey }, Vector2f{ ex, ey }, thickness, c);
}

void GeometryVertexBufferBuilder::Rectangle(const Box & box, float thickness, const Color & c)
{
  float sx = (float)(box.m_Start.x);
  float sy = (float)(box.m_Start.y);
  float ex = (float)(box.m_End.x + 1);
  float ey = (float)(box.m_End.y + 1);

  Line(Vector2f{ sx, sy }, Vector2f{ ex, sy }, thickness, c);
  Line(Vector2f{ sx, sy }, Vector2f{ sx, ey }, thickness, c);
  Line(Vector2f{ ex, sy }, Vector2f{ ex, ey }, thickness, c);
  Line(Vector2f{ sx, ey }, Vector2f{ ex, ey }, thickness, c);
}

void GeometryVertexBufferBuilder::FilledCircle(const Vector2f & pos, float radius, const Color & c, int num_segs)
{
  float angle_inc = k2Pi / num_segs;
  float angle = angle_inc;

  Vector2f prev_pos = { radius, 0 };

  for (int index = 1; index < num_segs + 1; index++)
  {
    auto cur_pos = SinCosf(angle) * radius;

    AddVert(pos, c);
    AddVert(pos + cur_pos, c);
    AddVert(pos + prev_pos, c);

    prev_pos = cur_pos;
    angle += angle_inc;
  }
}

void GeometryVertexBufferBuilder::FilledEllipse(const Vector2f & pos, float radius_x, float radius_y, const Color & c, int num_segs)
{
  float angle_inc = k2Pi / num_segs;
  float angle = angle_inc;

  auto ab = radius_x * radius_y;

  Vector2f prev_pos = { radius_x, 0 };

  for (int index = 1; index < num_segs + 1; index++)
  {
    auto dir = SinCosf(angle);

    auto den_x = dir.y * radius_x;
    auto den_y = dir.x * radius_y;

    auto radius = ab / sqrtf(den_x * den_x + den_y * den_y);

    auto cur_pos = dir * radius;

    AddVert(pos, c);
    AddVert(pos + cur_pos, c);
    AddVert(pos + prev_pos, c);

    prev_pos = cur_pos;
    angle += angle_inc;
  }
}

void GeometryVertexBufferBuilder::FilledRectangle(const Vector2f & a, const Vector2f & b, const Color & c)
{
  AddVert(Vector2f{ a.x, a.y }, c);
  AddVert(Vector2f{ a.x, b.y }, c);
  AddVert(Vector2f{ b.x, b.y }, c);
  AddVert(Vector2f{ a.x, a.y }, c);
  AddVert(Vector2f{ b.x, b.y }, c);
  AddVert(Vector2f{ b.x, a.y }, c);
}

void GeometryVertexBufferBuilder::FilledRectangle(const Box & box, const Color & c)
{
  FilledRectangle(box.m_Start, box.m_End + Vector2(1, 1), c);
}

void GeometryVertexBufferBuilder::Trail(const std::vector<TrailInfo> & points, const Color & c)
{
  if (points.size() <= 1)
  {
    return;
  }

  if (points.size() == 2)
  {
    Line(points[0].m_Position, points[1].m_Position, points[0].m_Thickness, points[1].m_Thickness, c);
    return;
  }

  int prev_index = 0;
  int cur_index = 1;
  int next_index = 2;
  int num_points = (int)points.size();

  Vector2f prev_point = points[0].m_Position;
  Vector2f cur_point = points[1].m_Position;
  Vector2f next_point = points[2].m_Position;

  Vector2f prev_dir;
  float prev_len;

  Vector2f cur_dir;
  float cur_len;

  Optional<std::pair<Vector2f, Vector2>> last_offset_points;

  while (true)
  {
    while (cur_index < num_points - 1)
    {
      cur_point = points[cur_index].m_Position;
      prev_dir = cur_point - prev_point;
      prev_len = IntersectionVecFuncs<Vector2f>::NormalizeInPlace(prev_dir);

      if (prev_len > 0)
      {
        break;
      }

      cur_index++;
    }

    next_index = cur_index + 1;
    while (next_index < num_points)
    {
      next_point = points[next_index].m_Position;
      cur_dir = next_point - cur_point;
      cur_len = IntersectionVecFuncs<Vector2f>::NormalizeInPlace(cur_dir);

      if (cur_len > 0)
      {
        break;
      }

      next_index++;
    }

    if (next_index >= num_points)
    {
      break;
    }

    auto prev_dir_perp = IntersectionVecFuncs<Vector2f>::GetPerpVec(prev_dir);
    auto cur_dir_perp = IntersectionVecFuncs<Vector2f>::GetPerpVec(cur_dir);
    if (last_offset_points == false)
    {
      auto & point = points[prev_index];
      auto t = point.m_Thickness / 2.0f;

      Vector2f first_point = point.m_Position + t * prev_dir_perp;
      Vector2f second_point = point.m_Position - t * prev_dir_perp;
      
      last_offset_points.Emplace(std::make_pair(first_point, second_point));
    }

    auto dp = IntersectionVecFuncs<Vector2f>::Dot(prev_dir_perp, cur_dir_perp);
    auto angle_between = acos(dp);

    if (angle_between == 0)
    {
      auto & point = points[cur_index];
      auto t = point.m_Thickness / 2.0f;

      Vector2f first_point = point.m_Position + t * cur_dir_perp;
      Vector2f second_point = point.m_Position - t * cur_dir_perp;

      AddVert(first_point, c);
      AddVert(second_point, c);
      AddVert(last_offset_points->first, c);
      AddVert(second_point, c);
      AddVert(last_offset_points->first, c);
      AddVert(last_offset_points->second, c);

      last_offset_points.Emplace(std::make_pair(first_point, second_point));
    }
    else
    {

    }

    prev_index = cur_index;
    cur_index = next_index + 1;

    prev_point = cur_point;
  }

  if (last_offset_points)
  {
    auto & point = points[num_points - 1];
    auto t = point.m_Thickness / 2.0f;

    auto dir = point.m_Position - cur_point;
    auto len = IntersectionVecFuncs<Vector2f>::NormalizeInPlace(dir);

    if (len > 0)
    {
      auto perp_dir = IntersectionVecFuncs<Vector2f>::GetPerpVec(dir);

      Vector2f first_point = point.m_Position + t * perp_dir;
      Vector2f second_point = point.m_Position - t * perp_dir;

      AddVert(first_point, c);
      AddVert(second_point, c);
      AddVert(last_offset_points->first, c);
      AddVert(second_point, c);
      AddVert(last_offset_points->first, c);
      AddVert(last_offset_points->second, c);
    }
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

void GeometryVertexBufferBuilder::DrawDefault(RenderState & render_state, RenderUtil & render_util, NullOptPtr<const ShaderProgram> shader)
{
  if (shader == nullptr)
  {
    shader = &g_ShaderManager.GetDefaultShader();
  }

  shader->Bind();

  auto & vertex_buffer = render_util.GetScratchBuffer();
  FillVertexBuffer(vertex_buffer);

  vertex_buffer.Bind();
  render_util.GetDefaultTexture().BindTexture(0);

  vertex_buffer.CreateDefaultBinding(*shader);
  vertex_buffer.Draw();
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
