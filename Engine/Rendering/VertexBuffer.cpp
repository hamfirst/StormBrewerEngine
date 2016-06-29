
#include "Engine\EngineCommon.h"
#include "Engine\Rendering\VertexBuffer.h"
#include "Engine\Rendering\RenderErrorMacros.h"

#include <gl3w/gl3w.h>


VertexBuffer::VertexBuffer()
{
  m_VertexBufferName = 0;
  m_IndexBufferName = 0;
  m_VertexArrayName = 0;
  m_LoadError = 0;
  m_Type = VertexBufferType::kInvalid;
  m_IndexCount = 0;
}

VertexBuffer::VertexBuffer(VertexBuffer && rhs) noexcept
{
  Move(std::move(rhs));
}

VertexBuffer::~VertexBuffer()
{
  Destroy();
}

VertexBuffer & VertexBuffer::operator = (VertexBuffer && rhs) noexcept
{
  Destroy();
  Move(std::move(rhs));
  return *this;
}

void VertexBuffer::Move(VertexBuffer && rhs) noexcept
{
  m_VertexBufferName = rhs.m_VertexBufferName;
  m_IndexBufferName = rhs.m_IndexBufferName;
  m_VertexArrayName = rhs.m_VertexArrayName;
  m_LoadError = rhs.m_LoadError;
  m_Type = rhs.m_Type;
  m_IndexCount = rhs.m_IndexCount;

  rhs.m_VertexBufferName = 0;
  rhs.m_IndexBufferName = 0;
  rhs.m_VertexArrayName = 0;
  rhs.m_LoadError = 0;
  rhs.m_Type = VertexBufferType::kInvalid;
  rhs.m_IndexCount = 0;
}

void VertexBuffer::Destroy()
{
  if (m_VertexBufferName != 0)
  {
    glDeleteBuffers(1, &m_VertexBufferName);
    m_VertexBufferName = 0;
  }

  if (m_IndexBufferName != 0)
  {
    glDeleteBuffers(1, &m_IndexBufferName);
    m_IndexBufferName = 0;
  }

  if (m_VertexArrayName != 0)
  {
    glDeleteVertexArrays(1, &m_VertexArrayName);
    m_VertexArrayName = 0;
  }

  m_LoadError = 0;
  m_Type = VertexBufferType::kInvalid;
  m_IndexCount = 0;
}

void VertexBuffer::SetBufferData(const gsl::span<VertexInfo> & verts, const gsl::span<uint16_t> & indices, VertexBufferType type)
{
  Destroy();

  glGenVertexArrays(1, &m_VertexArrayName); CHECK_GL_LOAD_ERROR;
  auto destroy_vertex_array_on_error = gsl::finally([&] { if(m_LoadError != 0) { glDeleteVertexArrays(1, &m_VertexArrayName); m_VertexArrayName = 0; } });
  glBindVertexArray(m_VertexArrayName); CHECK_GL_LOAD_ERROR;

  glGenBuffers(1, &m_VertexBufferName); CHECK_GL_LOAD_ERROR;
  auto destroy_vertex_buffer_on_error = gsl::finally([&] { if (m_LoadError != 0) { glDeleteBuffers(1, &m_VertexBufferName); m_VertexBufferName = 0; } });
  glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferName); CHECK_GL_LOAD_ERROR;

  glBufferData(GL_ARRAY_BUFFER, sizeof(VertexInfo) * verts.size(), verts.data(), GL_STATIC_DRAW); CHECK_GL_LOAD_ERROR;

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(VertexInfo), &verts[0].m_Position.x); CHECK_GL_LOAD_ERROR;
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexInfo), &verts[0].m_TexCoord.s); CHECK_GL_LOAD_ERROR;
  glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(VertexInfo), &verts[0].m_Color.r); CHECK_GL_LOAD_ERROR;

  m_Type = type;
  m_IndexCount = indices.size();

  glGenBuffers(1, &m_IndexBufferName); CHECK_GL_LOAD_ERROR;
  auto destroy_index_buffer_on_error = gsl::finally([&] { if (m_LoadError != 0) { glDeleteBuffers(1, &m_IndexBufferName); m_IndexBufferName = 0; } });
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferName); CHECK_GL_LOAD_ERROR;
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint16_t), indices.data(), GL_STATIC_DRAW); CHECK_GL_LOAD_ERROR;
}

void VertexBuffer::Draw(int index_start, int index_end) const
{
  if (m_VertexArrayName == 0 || m_IndexBufferName == 0 || m_LoadError != 0)
  {
    return;
  }

  GLenum mode;
  switch (m_Type)
  {
  case VertexBufferType::kPoints:
    mode = GL_POINTS;
    break;
  case VertexBufferType::kLines:
    mode = GL_LINES;
    break;
  case VertexBufferType::kTriangles:
    mode = GL_TRIANGLES;
    break;
  case VertexBufferType::kQuads:
    mode = GL_QUADS;
    break;
  default:
  case VertexBufferType::kInvalid:
    return;
  }

  if (index_end < 0)
  {
    index_end = m_IndexCount;
  }

  glBindVertexArray(m_VertexArrayName); CHECK_GL_RENDER_ERROR;
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferName); CHECK_GL_RENDER_ERROR;
  glDrawRangeElements(mode, index_start, m_IndexCount, index_end - index_start, GL_UNSIGNED_SHORT, 0); CHECK_GL_RENDER_ERROR;
}
