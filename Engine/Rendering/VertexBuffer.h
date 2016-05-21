#pragma once

#include "Foundation\Common.h"

struct VertexInfo
{
  
};

class VertexBuffer
{
  VertexBuffer();
  ~VertexBuffer();

  void SetVertexBufferData(VertexInfo * verts, uint32_t num_verts);
  void SetIndexBufferData(uint16_t * indices, uint32_t num_verts);

public:

  int m_VertexBufferName;
  int m_IndexBufferName;
};


