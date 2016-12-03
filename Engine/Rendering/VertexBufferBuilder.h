#pragma once

#include "Engine\EngineCommon.h"
#include "Engine\Rendering\VertexDefinition.h"
#include "Engine\Rendering\VertexBuffer.h"
#include "Data\BasicTypes\BasicTypes.refl.h"


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
  VertexBuffer CreateVertexBuffer();
  VertexBuffer SliceVertexBuffer(const Box & bounds);

  void FillVertexBuffer(VertexBuffer & vertex_buffer);

private:

  std::vector<QuadVertexBuilderInfo> m_Quads;
};


