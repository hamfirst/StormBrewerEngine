#pragma once


#include "Engine/Rendering/VertexList.h"
#include "Engine/Rendering/VertexBuffer.h"

class GeometryVertexBufferBuilder
{
public:

  GeometryVertexBufferBuilder();
  GeometryVertexBufferBuilder(const Vector2 & texture_pos, const Vector2 & texture_pos_size);

  void Line(const Vector2f & a, const Vector2f & b, float thickness, const Color & c);
  void Circle(const Vector2f & pos, float radius, float thickness, const Color & c, int num_segs);

  VertexBuffer CreateVertexBuffer();
  void FillVertexBuffer(VertexBuffer & vertex_buffer);

private:

  void Begin();
  void LineTo(const Vector2f & pos, float thickness, const Color & c);
  void End();

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

