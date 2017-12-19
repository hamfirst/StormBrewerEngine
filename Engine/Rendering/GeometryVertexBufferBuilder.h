#pragma once


#include "Engine/Rendering/VertexList.h"
#include "Engine/Rendering/VertexBuffer.h"

class RenderState;
class RenderUtil;
class ShaderProgram;

class ENGINE_EXPORT GeometryVertexBufferBuilder
{
public:

  GeometryVertexBufferBuilder();
  GeometryVertexBufferBuilder(const Vector2 & texture_pos, const Vector2 & texture_pos_size);

  void Line(const Vector2f & a, const Vector2f & b, float thickness, const Color & c);
  void Line(const Vector2f & a, const Vector2f & b, float start_thickness, float end_thickness, const Color & c);
  void Circle(const Vector2f & pos, float radius, float thickness, const Color & c, int num_segs);
  void Ellipse(const Vector2f & pos, float radius_x, float radius_y, float thickness, const Color & c, int num_segs);
  void Arc(const Vector2f & pos, float radius, float thickness, const Color & c, float middle_angle, float arc_half_angle, int num_segs);
  void Rectangle(const Vector2f & a, const Vector2f & b, float thickness, const Color & c);
  void Rectangle(const Box & box, float thickness, const Color & c);
  void FilledCircle(const Vector2f & pos, float radius, const Color & c, int num_segs);
  void FilledEllipse(const Vector2f & pos, float radius_x, float radius_y, const Color & c, int num_segs);
  void FilledRectangle(const Vector2f & a, const Vector2f & b, const Color & c);
  void FilledRectangle(const Box & box, const Color & c);

  struct TrailInfo
  {
    Vector2f m_Position;
    float m_Thickness;
  };

  void Trail(const std::vector<TrailInfo> & points, const Color & c);

  VertexBuffer CreateVertexBuffer();
  void FillVertexBuffer(VertexBuffer & vertex_buffer);

  void DrawDefault(RenderState & render_state, RenderUtil & render_util, NullOptPtr<ShaderProgram> shader = nullptr);

  bool HasGeo() const;

private:

  void AddVert(const Vector2f & pos, const Color & c);

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

