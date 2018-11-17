

#include "Engine/Rendering/ShaderLiteral.h"
#include "Engine/Shader/DefaultShader.h"

#include "DrawUtil.h"

static const char * kDrawUtilFragmentShader = SHADER_LITERAL(

  varying vec2 v_Position;
  varying vec2 v_TexCoord;
  varying vec4 v_Color;

  uniform sampler2D u_Texture;
  uniform vec4 u_Color;
  uniform vec2 u_ActualScreenSize;

  void main()
  {
    vec2 frag_coord = floor(v_Position.xy * u_ActualScreenSize * 0.25);
    float x = fract((frag_coord.x + frag_coord.y) * 0.5);

    float a_inv = (1.0 - v_Color.a);
    float a_min = 1.0 - sqrt(a_inv);
    float a_max = 1.0 - a_inv * a_inv;

    float a = (x < 0.5 ? a_min : a_max);

    vec4 color = texture2D(u_Texture, fract(v_TexCoord)) * v_Color * u_Color;

    color.a *= a;
    gl_FragColor = color;
  }
);

ShaderProgram DrawUtil::CreateShader()
{
  return MakeQuickShaderProgram(kDefaultVertexShader, kDrawUtilFragmentShader);
}

void DrawUtil::DrawBox(GeometryVertexBufferBuilder & builder, const Box & box)
{
  builder.FilledRectangle(box.m_Start, box.m_End + Vector2(1, 1), Color(0, 0, 0, 200));
}

void DrawUtil::DrawActionBox(GeometryVertexBufferBuilder & builder, const Box & box)
{
  builder.FilledRectangle(box.m_Start, box.m_End + Vector2(1, 1), Color(250, 0, 250, 200));
}

void DrawUtil::DrawLine(GeometryVertexBufferBuilder & builder, const Vector2 & a, const Vector2 & b, float magnification)
{
  builder.Line(a, b, 5.0f / magnification, Color(50, 50, 50, 255));
  builder.Line(a, b, 3.0f / magnification, Color(200, 200, 200, 255));
}

void DrawUtil::DrawHighlightedLine(GeometryVertexBufferBuilder & builder, const Vector2 & a, const Vector2 & b, float magnification)
{
  builder.Line(a, b, 7.0f / magnification, Color(0, 0, 0, 255));
  builder.Line(a, b, 5.0f / magnification, Color(255, 255, 255, 255));
}

void DrawUtil::DrawEdge(GeometryVertexBufferBuilder & builder, const FrameEditorEdge & edge, float magnification)
{
  auto offset = FrameEditorByteArray::GetOffsetForEdgeType(edge.m_Type);
  builder.Line(edge.m_P1 + offset, edge.m_P2 + offset, 3.0f / magnification, Color(250, 12, 250, 255));
}

void DrawUtil::DrawHighlightedEdge(GeometryVertexBufferBuilder & builder, const FrameEditorEdge & edge, float magnification)
{
  auto offset = FrameEditorByteArray::GetOffsetForEdgeType(edge.m_Type);
  builder.Line(edge.m_P1 + offset, edge.m_P2 + offset, 7.0f / magnification, Color(128, 128, 250, 255));
}

void DrawUtil::DrawCornerControl(GeometryVertexBufferBuilder & builder, const Vector2 & pos, float magnification)
{
  builder.FilledCircle(pos, 7.0f / magnification, Color(255, 255, 10, 255), 20);
  builder.Circle(pos, 7.0f / magnification, 2.0f / magnification, Color(0, 0, 0, 255), 20);
  builder.Circle(pos, 2.0f / magnification, 1.0f / magnification, Color(0, 0, 0, 255), 20);
}

void DrawUtil::DrawSelectedCornerControl(GeometryVertexBufferBuilder & builder, const Vector2 & pos, float magnification)
{
  builder.FilledCircle(pos, 7.0f / magnification, Color(255, 255, 10, 255), 20);
  builder.Circle(pos, 7.0f / magnification, 3.0f / magnification, Color(200, 150, 255, 250), 20);
  builder.Circle(pos, 2.0f / magnification, 1.0f / magnification, Color(0, 0, 0, 255), 20);
}

void DrawUtil::DrawHighlightedCornerControl(GeometryVertexBufferBuilder & builder, const Vector2 & pos, float magnification)
{
  builder.FilledCircle(pos, 7.0f / magnification, Color(255, 255, 10, 255), 20);
  builder.Circle(pos, 7.0f / magnification, 3.0f / magnification, Color(128, 128, 255, 250), 20);
  builder.Circle(pos, 2.0f / magnification, 1.0f / magnification, Color(0, 0, 0, 255), 20);
}

