#pragma once


#include "Engine/Rendering/VertexList.h"
#include "Engine/Rendering/VertexBuffer.h"

class RenderState;
class ShaderProgram;

class ENGINE_EXPORT GeometryVertexBufferBuilder
{
public:

  GeometryVertexBufferBuilder();
  GeometryVertexBufferBuilder(const Vector2 & texture_pos, const Vector2 & texture_pos_size);

  void Line(const Vector2f & a, const Vector2f & b, float thickness, const Color & c, float bias = 0);
  void Line(const Vector2f & a, const Vector2f & b, float start_thickness, float end_thickness, const Color & c, float bias = 0);
  void Circle(const Vector2f & pos, float radius, float thickness, const Color & c, int num_segs, float bias = 0);
  void Ellipse(const Vector2f & pos, float radius_x, float radius_y, float thickness, const Color & c, int num_segs, float bias = 0);
  void Arc(const Vector2f & pos, float radius, float thickness, const Color & c, float middle_angle, float arc_half_angle, int num_segs, float bias = 0);
  void Rectangle(const Vector2f & a, const Vector2f & b, float thickness, const Color & c, float bias = 0);
  void Rectangle(const Box & box, float thickness, const Color & c, float bias = 0);
  void FilledCircle(const Vector2f & pos, float radius, const Color & c, int num_segs, float bias = 0);
  void FilledEllipse(const Vector2f & pos, float radius_x, float radius_y, const Color & c, int num_segs, float bias = 0);
  void FilledRectangle(const Vector2f & a, const Vector2f & b, const Color & c, float bias = 0);
  void FilledRectangle(const Box & box, const Color & c, float bias = 0);

  struct TrailInfo
  {
    Vector2f m_Position;
    float m_Thickness;
    Color m_Color;
  };

  void Trail(const gsl::span<TrailInfo> & points, float texture_width);

  VertexBuffer CreateVertexBuffer();
  void FillVertexBuffer(VertexBuffer & vertex_buffer);

  void DrawDefault(RenderState & render_state, NullOptPtr<ShaderProgram> shader = nullptr);

  bool HasGeo() const;

private:

  void AddVert(const Vector2f & pos, const Color & c);
  void AddVert(const Vector2f & pos, const Color & c, const Vector2f & texcoord);

private:

  Vector2f m_TexCoord;

  bool m_HasPrevPos;
  Vector2f m_PrevPos;
  Color m_PrevColor;
  float m_PrevThickness;

  bool m_HasCurPos;
  Vector2f m_CurPos;
  Vector2f m_CurDir;
  Color m_CurColor;
  float m_CurThickness;

  VertexList m_List;
};

