
#include "Engine/EngineCommon.h"
#include "Engine/Rendering/RenderState.h"
#include "Engine/Rendering/VertexArray.h"
#include "Engine/Rendering/VertexBuffer.h"
#include "Engine/Rendering/ShaderProgram.h"
#include "Engine/Rendering/RenderErrorMacros.h"

#include <gl3w/gl3w.h>

VertexArray::VertexArray()
{
#ifdef USE_VERTEX_ARRAY
  m_VertexArrayName = 0;
#endif

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
#ifdef USE_VERTEX_ARRAY
  m_VertexArrayName = rhs.m_VertexArrayName;
  rhs.m_VertexArrayName = 0;
#endif

  std::copy(&rhs.m_Current[0], &rhs.m_Current[kMaxVertexAttribs], &m_Current[0]);
  for (int index = 0; index < kMaxVertexAttribs; ++index)
  {
    rhs.m_Current[index] = { };
  }

  m_BoundShader = rhs.m_BoundShader;
  m_BoundShaderName = rhs.m_BoundShaderName;

  rhs.m_BoundShader = nullptr;
  rhs.m_BoundShaderName = 0;

  rhs.m_LoadError = 0;
  m_LoadError = rhs.m_LoadError;
}

void VertexArray::Destroy()
{
#ifdef USE_VERTEX_ARRAY
  if (m_VertexArrayName != 0)
  {
    glDeleteVertexArrays(1, &m_VertexArrayName);
    m_VertexArrayName = 0;
  }
#endif

  m_LoadError = 0;
}


void VertexArray::Sync(RenderState & render_state, const VertexBuffer & vertex_buffer, const ShaderProgram & shader_program, bool dirty)
{
#ifndef USE_VERTEX_ARRAY
  dirty = false;
#endif

  if (m_BoundShader != &shader_program || m_BoundShaderName != shader_program.m_ProgramName || dirty)
  {
    m_BoundShader = &shader_program;
    m_BoundShaderName = shader_program.m_ProgramName;

#ifdef USE_VERTEX_ARRAY
    VertexAttribState new_state[kMaxVertexAttribs] = {};
    GenerateAttribState(vertex_buffer, shader_program, new_state);

    if (m_VertexArrayName == 0)
    {
      glGenVertexArrays(1, &m_VertexArrayName); CHECK_GL_RENDER_ERROR;
    }

    vertex_buffer.Bind();
    glBindVertexArray(m_VertexArrayName); CHECK_GL_RENDER_ERROR;

    for (int index = 0; index < kMaxVertexAttribs; ++index)
    {
      auto & cur_elem = m_Current[index];
      auto & my_elem = new_state[index];

      if (my_elem.m_Enabled)
      {
        if (cur_elem.m_Enabled == false)
        {
          glEnableVertexAttribArray(index); CHECK_GL_RENDER_ERROR;
          cur_elem.m_Enabled = true;
        }

        if (cur_elem.m_Size != my_elem.m_Size ||
            cur_elem.m_Type != my_elem.m_Type ||
            cur_elem.m_Normalized != my_elem.m_Normalized ||
            cur_elem.m_Stride != my_elem.m_Stride ||
            cur_elem.m_Ptr != my_elem.m_Ptr)
        {
          cur_elem = my_elem;
          glVertexAttribPointer(index, my_elem.m_Size, my_elem.m_Type, my_elem.m_Normalized, my_elem.m_Stride, my_elem.m_Ptr); CHECK_GL_RENDER_ERROR;
        }
      }
      else
      {
        if (cur_elem.m_Enabled == true)
        {
          glDisableVertexAttribArray(index); CHECK_GL_RENDER_ERROR;
          cur_elem.m_Enabled = false;
        }
      }
    }

    return;
#else
    GenerateAttribState(vertex_buffer, shader_program, m_Current);
#endif
  }

#ifdef USE_VERTEX_ARRAY

  glBindVertexArray(m_VertexArrayName); CHECK_GL_RENDER_ERROR;

#else
  vertex_buffer.Bind();

  for (int index = 0; index < kMaxVertexAttribs; ++index)
  {
    auto & cur_elem = m_Current[index];
    if (cur_elem.m_Enabled)
    {
      if (render_state.m_VertexAttribEnabled[index] == false)
      {
        glEnableVertexAttribArray(index); CHECK_GL_RENDER_ERROR;
        render_state.m_VertexAttribEnabled[index] = true;
      }

      glVertexAttribPointer(index, cur_elem.m_Size, cur_elem.m_Type, cur_elem.m_Normalized, cur_elem.m_Stride, cur_elem.m_Ptr); CHECK_GL_RENDER_ERROR;
    }
    else
    {
      if (render_state.m_VertexAttribEnabled[index] == true)
      {
        glDisableVertexAttribArray(index); CHECK_GL_RENDER_ERROR;
        render_state.m_VertexAttribEnabled[index] = false;
      }
    }
  }
#endif
}

void VertexArray::GenerateAttribState(const VertexBuffer & vertex_buffer, const ShaderProgram & shader_program, NotNullPtr<VertexAttribState> new_state)
{
  for (int index = 0; index < vertex_buffer.m_VertexSpec->m_NumAttribs; ++index)
  {
    auto & attrib = vertex_buffer.m_VertexSpec->m_Attribs[index];
    auto attrib_index = glGetAttribLocation(shader_program.m_ProgramName, attrib.m_Name); CHECK_GL_RENDER_ERROR;

    if (attrib_index >= 0)
    {
      new_state[attrib_index].m_Enabled = true;
      new_state[attrib_index].m_Size = attrib.m_Size;
      new_state[attrib_index].m_Type = attrib.m_Type;
      new_state[attrib_index].m_Normalized = attrib.m_Normalized;
      new_state[attrib_index].m_Stride = attrib.m_Stride;
      new_state[attrib_index].m_Ptr = attrib.m_Ptr;
    }
  }
}