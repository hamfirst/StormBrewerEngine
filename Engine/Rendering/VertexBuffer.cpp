
#include "Engine\EngineCommon.h"
#include "Engine\Rendering\VertexBuffer.h"

#include <Windows.h>

#include <gl\GL.h>

VertexBuffer::VertexBuffer()
{
  m_VertexBufferName = 0;
  m_IndexBufferName = 0;
}

VertexBuffer::VertexBuffer(VertexBuffer && rhs)
{
  
}

VertexBuffer::~VertexBuffer()
{
  if (m_VertexBufferName != 0)
  {
    glDeleteBuffers(1, &m_VertexBufferName);
    glDeleteBuffers(1, &m_IndexBufferName);
  }
}

void VertexBuffer::SetVertexBufferData(VertexInfo * verts, uint32_t num_verts)
{

}

void VertexBuffer::SetIndexBufferData(uint16_t * indices, uint32_t num_verts)
{

}
