
#include "Engine/EngineCommon.h"
#include "Engine/Rendering/ShaderProgram.h"
#include "Engine/Rendering/Shader.h"
#include "Engine/Rendering/RenderErrorMacros.h"

#include <gl3w/gl3w.h>
#include <sb/vector.h>

ShaderProgram::ShaderProgram()
{
  m_ProgramName = 0;
  m_LoadError = 0;
}

ShaderProgram::ShaderProgram(ShaderProgram && rhs) noexcept
{
  Move(std::move(rhs));
}

ShaderProgram::~ShaderProgram()
{
  Destroy();
}

ShaderProgram & ShaderProgram::operator = (ShaderProgram && rhs) noexcept
{
  Destroy();
  Move(std::move(rhs));
  return *this;
}

void ShaderProgram::Move(ShaderProgram && rhs) noexcept
{
  m_ProgramName = rhs.m_ProgramName;
  m_LoadError = rhs.m_LoadError;

  rhs.m_ProgramName = 0;
  rhs.m_LoadError = 0;

  m_Uniforms = std::move(rhs.m_Uniforms);
}

void ShaderProgram::Destroy()
{
  if (m_ProgramName != 0)
  {
    glDeleteProgram(m_ProgramName);
    m_ProgramName = 0;
  }

  m_LoadError = 0;
}

void ShaderProgram::CreateProgram(const Shader & vertex_shader, const Shader & fragment_shader)
{
  Destroy();

  m_ProgramName = glCreateProgram(); CHECK_GL_LOAD_ERROR;
  auto shader_destroy_on_error = gsl::finally([&] { if (m_LoadError != 0) { glDeleteProgram(m_ProgramName); m_ProgramName = 0; } });

  glAttachShader(m_ProgramName, vertex_shader.m_ShaderName); CHECK_GL_LOAD_ERROR;
  glAttachShader(m_ProgramName, fragment_shader.m_ShaderName); CHECK_GL_LOAD_ERROR;
  glLinkProgram(m_ProgramName); CHECK_GL_LOAD_ERROR;

  GLint linked;
  glGetProgramiv(m_ProgramName, GL_LINK_STATUS, &linked);
  if (linked == 0)
  {
    GLint log_size;
    glGetProgramiv(m_ProgramName, GL_INFO_LOG_LENGTH, &log_size); CHECK_GL_LOAD_ERROR;

    m_LoadError = GL_INVALID_VALUE;
    if (log_size > 0)
    {
      auto error_log_mem = std::make_unique<char[]>(log_size + 1);
      zstr error_log = error_log_mem.get();

      GLsizei outplen = 0;
      glGetProgramInfoLog(m_ProgramName, log_size, &outplen, error_log); CHECK_GL_LOAD_ERROR;
      error_log[log_size] = 0;

      m_CompileLog = error_log;
    }

    return;
  }

  GLint num_shader_uniforms;
  glGetProgramiv(m_ProgramName, GL_ACTIVE_UNIFORMS, &num_shader_uniforms); CHECK_GL_LOAD_ERROR;
  GLint max_name_length;
  glGetProgramiv(m_ProgramName, GL_ACTIVE_UNIFORM_MAX_LENGTH, &max_name_length); CHECK_GL_LOAD_ERROR;

  auto name_buffer_mem = std::make_unique<char[]>(max_name_length);
  zstr name_buffer = name_buffer_mem.get();

  m_Uniforms.reserve(num_shader_uniforms);
  for (GLuint index = 0; index < static_cast<GLuint>(num_shader_uniforms); index++)
  {
    GLsizei name_length;
    glGetActiveUniformName(m_ProgramName, index, max_name_length, &name_length, name_buffer); CHECK_GL_LOAD_ERROR;

    name_buffer[name_length] = 0;

    m_Uniforms.push_back(crc32(name_buffer));
  }
}

int ShaderProgram::GetUniformIndex(Hash uniform_name)
{
  for (int index = 0; index < (int)m_Uniforms.size(); index++)
  {
    if (m_Uniforms[index] == uniform_name)
    {
      return index;
    }
  }

  return -1;
}

int ShaderProgram::GetUniformIndex(czstr uniform_name)
{
  return GetUniformIndex(crc32(uniform_name));
}

void ShaderProgram::SetUniform(Hash uniform_name, int v1)
{
  int uniform_index = GetUniformIndex(uniform_name); if (uniform_index == -1) return;
  glUniform1i(uniform_index, v1); CHECK_GL_RENDER_ERROR;
}

void ShaderProgram::SetUniform(Hash uniform_name, int v1, int v2)
{
  int uniform_index = GetUniformIndex(uniform_name); if (uniform_index == -1) return;
  glUniform2i(uniform_index, v1, v2); CHECK_GL_RENDER_ERROR;
}

void ShaderProgram::SetUniform(Hash uniform_name, int v1, int v2, int v3)
{
  int uniform_index = GetUniformIndex(uniform_name); if (uniform_index == -1) return;
  glUniform3i(uniform_index, v1, v2, v3); CHECK_GL_RENDER_ERROR;
}

void ShaderProgram::SetUniform(Hash uniform_name, int v1, int v2, int v3, int v4)
{
  int uniform_index = GetUniformIndex(uniform_name); if (uniform_index == -1) return;
  glUniform4i(uniform_index, v1, v2, v3, v4); CHECK_GL_RENDER_ERROR;
}

void ShaderProgram::SetUniform(Hash uniform_name, float v1)
{
  int uniform_index = GetUniformIndex(uniform_name); if (uniform_index == -1) return;
  glUniform1f(uniform_index, v1); CHECK_GL_RENDER_ERROR;
}

void ShaderProgram::SetUniform(Hash uniform_name, float v1, float v2)
{
  int uniform_index = GetUniformIndex(uniform_name); if (uniform_index == -1) return;
  glUniform2f(uniform_index, v1, v2); CHECK_GL_RENDER_ERROR;
}

void ShaderProgram::SetUniform(Hash uniform_name, float v1, float v2, float v3)
{
  int uniform_index = GetUniformIndex(uniform_name); if (uniform_index == -1) return;
  glUniform3f(uniform_index, v1, v2, v3); CHECK_GL_RENDER_ERROR;
}

void ShaderProgram::SetUniform(Hash uniform_name, float v1, float v2, float v3, float v4)
{
  int uniform_index = GetUniformIndex(uniform_name); if (uniform_index == -1) return;
  glUniform4f(uniform_index, v1, v2, v3, v4); CHECK_GL_RENDER_ERROR;
}

void ShaderProgram::SetUniform(Hash uniform_name, const RenderVec2 & v)
{
  int uniform_index = GetUniformIndex(uniform_name); if (uniform_index == -1) return;
  glUniform2f(uniform_index, v.x, v.y);
}

void ShaderProgram::SetUniform(Hash uniform_name, const RenderVec3 & v)
{
  int uniform_index = GetUniformIndex(uniform_name); if (uniform_index == -1) return;
  glUniform3f(uniform_index, v.x, v.y, v.z);
}

void ShaderProgram::SetUniform(Hash uniform_name, const RenderVec4 & v)
{
  int uniform_index = GetUniformIndex(uniform_name); if (uniform_index == -1) return;
  glUniform4f(uniform_index, v.x, v.y, v.z, v.w);
}

void ShaderProgram::Bind() const
{
  glUseProgram(m_ProgramName); CHECK_GL_RENDER_ERROR;
}

void ShaderProgram::Unbind() const
{
  glUseProgram(0); CHECK_GL_RENDER_ERROR;
}

ShaderProgram MakeQuickShaderProgram(const char * vertex_shader, const char * fragment_shader)
{
  Shader vshader;
  vshader.LoadShader(vertex_shader, ShaderType::kVertexShader);

  if (vshader.GetLoadError())
  {
    return{};
  }

  Shader fshader;
  fshader.LoadShader(fragment_shader, ShaderType::kFragmentShader);

  if (fshader.GetLoadError())
  {
    return{};
  }

  ShaderProgram shader;
  shader.CreateProgram(vshader, fshader);

  return shader;
}