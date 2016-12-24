#pragma once

#include "Engine\EngineCommon.h"
#include "Engine\Rendering\VertexDefinition.h"
#include "Engine\Rendering\VertexBuffer.h"


struct QuadVertexBuilderInfo
{
  Box m_Position;
  Box m_TexCoords;
  Vector2 m_TextureSize;
  Color m_Color;
};

class QuadVertexBufferBuilder
{
public:
  QuadVertexBufferBuilder() = default;
  explicit QuadVertexBufferBuilder(std::size_t reserve_quads);

  void AddQuad(const QuadVertexBuilderInfo & quad);
  void AddRepeatingQuad(const QuadVertexBuilderInfo & quad);

  VertexBuffer CreateVertexBuffer();
  VertexBuffer SliceVertexBuffer(const Box & bounds);

  void FillVertexBuffer(VertexBuffer & vertex_buffer);

private:

  std::vector<QuadVertexBuilderInfo> m_Quads;
};

struct PointVertexBuilderInfo
{
  Vector2 m_Position;
  Vector2 m_TexCoord;
  Vector2 m_TextureSize;
  Color m_Color;
};

class PointVertexBufferBuilder
{
public:
  PointVertexBufferBuilder() = default;
  explicit PointVertexBufferBuilder(std::size_t reserve_points);

  void AddPoint(const PointVertexBuilderInfo & point);
  VertexBuffer CreateVertexBuffer();
  VertexBuffer SliceVertexBuffer(const Box & bounds);

  void FillVertexBuffer(VertexBuffer & vertex_buffer);

private:

  std::vector<PointVertexBuilderInfo> m_Points;
};
