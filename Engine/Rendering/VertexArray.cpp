
#include "Engine/EngineCommon.h"
#include "Engine/Rendering/VertexArray.h"
#include "Engine/Rendering/RenderErrorMacros.h"

#include <gl3w/gl3w.h>


VertexArray::VertexArray()
{
  m_VertexArrayName = 0;
  m_LoadError = 0;
}

VertexArray::VertexArray(VertexArray && rhs) noexcept
{
  Move(std::move(rhs));
}

VertexArray::~VertexArray()
{
  Destroy();
}

VertexArray & VertexArray::operator = (VertexArray && rhs) noexcept
{
  Destroy();
  Move(std::move(rhs));
  return *this;
}

void VertexArray::Move(VertexArray && rhs) noexcept
{
  m_VertexArrayName = rhs.m_VertexArrayName;
  m_LoadError = rhs.m_LoadError;

  rhs.m_VertexArrayName = 0;
  rhs.m_LoadError = 0;
}

void VertexArray::Destroy()
{
  if (m_VertexArrayName != 0)
  {
    glDeleteVertexArrays(1, &m_VertexArrayName);
    m_VertexArrayName = 0;
  }

  m_LoadError = 0;
}

void VertexArray::CreateDefaultBinding(const ShaderProgram & program, const VertexBuffer & buffer)
{
  if (m_VertexArrayName == 0)
  {
    glGenVertexArrays(1, &m_VertexArrayName); CHECK_GL_RENDER_ERROR;
  }

  glBindVertexArray(m_VertexArrayName); CHECK_GL_RENDER_ERROR;

  buffer.Bind();
  buffer.CreateDefaultBinding(program);

  glBindVertexArray(0); CHECK_GL_RENDER_ERROR;

  buffer.Unbind();
}

void VertexArray::Bind() const
{
  glBindVertexArray(m_VertexArrayName); CHECK_GL_RENDER_ERROR;
}

void VertexArray::Unbind() const
{
  glBindVertexArray(0); CHECK_GL_RENDER_ERROR;
}
