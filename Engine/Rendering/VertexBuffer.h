#pragma once

#include "Engine\EngineCommon.h"

struct VertexInfo
{
  Vec2 m_Position;
  Vec2 m_TexCoord;
  Vec4 m_Color;
};

class VertexBuffer
{
  VertexBuffer();
  VertexBuffer(const VertexBuffer & rhs) = delete;
  VertexBuffer(VertexBuffer && rhs);
  ~VertexBuffer();

  void SetVertexBufferData(VertexInfo * verts, uint32_t num_verts);
  void SetIndexBufferData(uint16_t * indices, uint32_t num_indices);

public:

  int m_VertexBufferName;
  int m_IndexBufferName;
};


