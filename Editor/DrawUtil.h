#pragma once

#include "Foundation/Common.h"

#include "Engine/Rendering/GeometryVertexBufferBuilder.h"
#include "Engine/Rendering/ShaderProgram.h"

#include "FrameEditorUtil.h"

class DrawUtil
{
public:

  static ShaderProgram CreateShader();

  static void DrawBox(GeometryVertexBufferBuilder & builder, const Box & box);
  static void DrawActionBox(GeometryVertexBufferBuilder & builder, const Box & box);
  static void DrawLine(GeometryVertexBufferBuilder & builder, const Vector2 & a, const Vector2 & b, float magnification);
  static void DrawHighlightedLine(GeometryVertexBufferBuilder & builder, const Vector2 & a, const Vector2 & b, float magnification);

  static void DrawEdge(GeometryVertexBufferBuilder & builder, const FrameEditorEdge & edge, float magnification);
  static void DrawHighlightedEdge(GeometryVertexBufferBuilder & builder, const FrameEditorEdge & edge, float magnification);

  static void DrawCornerControl(GeometryVertexBufferBuilder & builder, const Vector2 & pos, float magnification);
  static void DrawSelectedCornerControl(GeometryVertexBufferBuilder & builder, const Vector2 & pos, float magnification);
  static void DrawHighlightedCornerControl(GeometryVertexBufferBuilder & builder, const Vector2 & pos, float magnification);

  static void DrawFrame();
};

