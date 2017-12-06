
#include "Engine/EngineCommon.h"
#include "Engine/Rendering/VertexArray.h"
#include "Engine/Rendering/VertexBuffer.h"
#include "Engine/Rendering/RenderErrorMacros.h"

#include <gl3w/gl3w.h>

void CreateDefaultVertexBufferBinding(const ShaderProgram & program)
{
  int position_attrib_loc = glGetAttribLocation(program.m_ProgramName, "a_Position"); CHECK_GL_RENDER_ERROR;
  int texcoord_attrib_loc = glGetAttribLocation(program.m_ProgramName, "a_TexCoord"); CHECK_GL_RENDER_ERROR;
  int color_attrib_loc = glGetAttribLocation(program.m_ProgramName, "a_Color"); CHECK_GL_RENDER_ERROR;

  if (position_attrib_loc >= 0)
  {
    glEnableVertexAttribArray(position_attrib_loc); CHECK_GL_RENDER_ERROR;
    glVertexAttribPointer(position_attrib_loc, 2, GL_FLOAT, GL_FALSE, sizeof(VertexInfo), (void *)offsetof(VertexInfo, m_Position)); CHECK_GL_RENDER_ERROR;
  }

  if (texcoord_attrib_loc >= 0)
  {
    glEnableVertexAttribArray(texcoord_attrib_loc); CHECK_GL_RENDER_ERROR;
    glVertexAttribPointer(texcoord_attrib_loc, 2, GL_FLOAT, GL_FALSE, sizeof(VertexInfo), (void *)offsetof(VertexInfo, m_TexCoord)); CHECK_GL_RENDER_ERROR;
  }

  if (color_attrib_loc >= 0)
  {
    glEnableVertexAttribArray(color_attrib_loc); CHECK_GL_RENDER_ERROR;
    glVertexAttribPointer(color_attrib_loc, 4, GL_FLOAT, GL_FALSE, sizeof(VertexInfo), (void *)offsetof(VertexInfo, m_Color)); CHECK_GL_RENDER_ERROR;
  }
}

#ifndef _WEB

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

void VertexArray::Create()
{
  if (m_VertexArrayName == 0)
  {
    glGenVertexArrays(1, &m_VertexArrayName); CHECK_GL_RENDER_ERROR;
    printf("Created vertex array %d\n", m_VertexArrayName);
  }
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

void VertexArray::CreateDefaultBinding(const ShaderProgram & program, VertexBuffer & buffer)
{
  Create();

  glBindVertexArray(m_VertexArrayName); CHECK_GL_RENDER_ERROR;

  buffer.Bind();
  CreateDefaultVertexBufferBinding(program);
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

#endif
