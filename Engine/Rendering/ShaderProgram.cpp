
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

  m_CompileLog = std::move(rhs.m_CompileLog);
  m_Uniforms = std::move(rhs.m_Uniforms);
  m_UniformData = std::move(rhs.m_UniformData);
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
      printf("Shader compile error: %s\n", error_log);
    }

    glDeleteProgram(m_ProgramName);
    m_ProgramName = 0;
    return;
  }

  GLint num_shader_uniforms;
  glGetProgramiv(m_ProgramName, GL_ACTIVE_UNIFORMS, &num_shader_uniforms); CHECK_GL_LOAD_ERROR;
  GLint max_name_length;
  glGetProgramiv(m_ProgramName, GL_ACTIVE_UNIFORM_MAX_LENGTH, &max_name_length); CHECK_GL_LOAD_ERROR;

  auto name_buffer_mem = std::make_unique<char[]>(max_name_length);
  zstr name_buffer = name_buffer_mem.get();

  m_Uniforms.reserve(num_shader_uniforms);

  int data_len = 0;
  for (GLuint index = 0; index < static_cast<GLuint>(num_shader_uniforms); index++)
  {
    GLsizei name_length;
    GLint size;
    GLenum type;
    glGetActiveUniform(m_ProgramName, index, max_name_length, &name_length, &size, &type, name_buffer); CHECK_GL_LOAD_ERROR;

    name_buffer[name_length] = 0;

    auto location_index = glGetUniformLocation(m_ProgramName, name_buffer); CHECK_GL_LOAD_ERROR;

    int data_size = 0;
    switch (type)
    {
    case GL_SAMPLER_1D:
    case GL_SAMPLER_2D:
    case GL_SAMPLER_3D:
    case GL_INT:
    case GL_UNSIGNED_INT:
    case GL_FLOAT:
      data_size = 4;
      break;
    case GL_INT_VEC2:
    case GL_UNSIGNED_INT_VEC2:
    case GL_FLOAT_VEC2:
      data_size = 8;
      break;
    case GL_INT_VEC3:
    case GL_UNSIGNED_INT_VEC3:
    case GL_FLOAT_VEC3:
      data_size = 12;
      break;
    case GL_INT_VEC4:
    case GL_UNSIGNED_INT_VEC4:
    case GL_FLOAT_VEC4:
      data_size = 16;
      break;

    default:
      ASSERT(false, "Bad uniform type length");
    }

    UniformData uniform_data;
    uniform_data.m_NameHash = crc32(name_buffer);
    uniform_data.m_LocationIndex = location_index;
    uniform_data.m_DataOffset = data_len;
    uniform_data.m_DataSize = data_size;

    m_Uniforms.push_back(uniform_data);

    data_len += data_size;
  }

  m_UniformData = std::make_unique<uint8_t[]>(data_len);
  memset(m_UniformData.get(), 0, data_len);
}

int ShaderProgram::GetUniformLocation(Hash uniform_name) const
{
  for (int index = 0; index < (int)m_Uniforms.size(); index++)
  {
    if (m_Uniforms[index].m_NameHash == uniform_name)
    {
      return m_Uniforms[index].m_LocationIndex;
    }
  }

  return -1;
}

int ShaderProgram::GetUniformLocation(czstr uniform_name) const
{
  return GetUniformIndex(crc32(uniform_name));
}

void ShaderProgram::SetUniform(Hash uniform_name, int v1)
{
  int uniform_index = GetUniformIndex(uniform_name); if (uniform_index == -1) return;
  if (CheckDataDeltaAndSize(m_UniformData.get() + m_Uniforms[uniform_index].m_DataOffset, m_Uniforms[uniform_index].m_DataSize, v1) == false) return;
  glUniform1i(m_Uniforms[uniform_index].m_LocationIndex, v1); CHECK_GL_RENDER_ERROR;
  SetData(m_UniformData.get() + m_Uniforms[uniform_index].m_DataOffset, v1);
}

void ShaderProgram::SetUniform(Hash uniform_name, int v1, int v2)
{
  int uniform_index = GetUniformIndex(uniform_name); if (uniform_index == -1) return;
  if (CheckDataDeltaAndSize(m_UniformData.get() + m_Uniforms[uniform_index].m_DataOffset, m_Uniforms[uniform_index].m_DataSize, v1, v2) == false) return;
  glUniform2i(m_Uniforms[uniform_index].m_LocationIndex, v1, v2); CHECK_GL_RENDER_ERROR;
  SetData(m_UniformData.get() + m_Uniforms[uniform_index].m_DataOffset, v1, v2);
}

void ShaderProgram::SetUniform(Hash uniform_name, int v1, int v2, int v3)
{
  int uniform_index = GetUniformIndex(uniform_name); if (uniform_index == -1) return;
  if (CheckDataDeltaAndSize(m_UniformData.get() + m_Uniforms[uniform_index].m_DataOffset, m_Uniforms[uniform_index].m_DataSize, v1, v2, v3) == false) return;
  glUniform3i(m_Uniforms[uniform_index].m_LocationIndex, v1, v2, v3); CHECK_GL_RENDER_ERROR;
  SetData(m_UniformData.get() + m_Uniforms[uniform_index].m_DataOffset, v1, v2, v3);
}

void ShaderProgram::SetUniform(Hash uniform_name, int v1, int v2, int v3, int v4)
{
  int uniform_index = GetUniformIndex(uniform_name); if (uniform_index == -1) return;
  if (CheckDataDeltaAndSize(m_UniformData.get() + m_Uniforms[uniform_index].m_DataOffset, m_Uniforms[uniform_index].m_DataSize, v1, v2, v3, v4) == false) return;
  glUniform4i(m_Uniforms[uniform_index].m_LocationIndex, v1, v2, v3, v4); CHECK_GL_RENDER_ERROR;
  SetData(m_UniformData.get() + m_Uniforms[uniform_index].m_DataOffset, v1, v2, v3, v4);
}

void ShaderProgram::SetUniform(Hash uniform_name, float v1)
{
  int uniform_index = GetUniformIndex(uniform_name); if (uniform_index == -1) return;
  if (CheckDataDeltaAndSize(m_UniformData.get() + m_Uniforms[uniform_index].m_DataOffset, m_Uniforms[uniform_index].m_DataSize, v1) == false) return;
  glUniform1f(m_Uniforms[uniform_index].m_LocationIndex, v1); CHECK_GL_RENDER_ERROR;
  SetData(m_UniformData.get() + m_Uniforms[uniform_index].m_DataOffset, v1);
}

void ShaderProgram::SetUniform(Hash uniform_name, float v1, float v2)
{
  int uniform_index = GetUniformIndex(uniform_name); if (uniform_index == -1) return;
  if (CheckDataDeltaAndSize(m_UniformData.get() + m_Uniforms[uniform_index].m_DataOffset, m_Uniforms[uniform_index].m_DataSize, v1, v2) == false) return;
  glUniform2f(m_Uniforms[uniform_index].m_LocationIndex, v1, v2); CHECK_GL_RENDER_ERROR;
  SetData(m_UniformData.get() + m_Uniforms[uniform_index].m_DataOffset, v1, v2);
}

void ShaderProgram::SetUniform(Hash uniform_name, float v1, float v2, float v3)
{
  int uniform_index = GetUniformIndex(uniform_name); if (uniform_index == -1) return;
  if (CheckDataDeltaAndSize(m_UniformData.get() + m_Uniforms[uniform_index].m_DataOffset, m_Uniforms[uniform_index].m_DataSize, v1, v2, v3) == false) return;
  glUniform3f(m_Uniforms[uniform_index].m_LocationIndex, v1, v2, v3); CHECK_GL_RENDER_ERROR;
  SetData(m_UniformData.get() + m_Uniforms[uniform_index].m_DataOffset, v1, v2, v3);
}

void ShaderProgram::SetUniform(Hash uniform_name, float v1, float v2, float v3, float v4)
{
  int uniform_index = GetUniformIndex(uniform_name); if (uniform_index == -1) return;
  if (CheckDataDeltaAndSize(m_UniformData.get() + m_Uniforms[uniform_index].m_DataOffset, m_Uniforms[uniform_index].m_DataSize, v1, v2, v3, v4) == false) return;
  glUniform4f(m_Uniforms[uniform_index].m_LocationIndex, v1, v2, v3, v4); CHECK_GL_RENDER_ERROR;
  SetData(m_UniformData.get() + m_Uniforms[uniform_index].m_DataOffset, v1, v2, v3, v4);
}

void ShaderProgram::SetUniform(Hash uniform_name, const RenderVec2 & v)
{
  int uniform_index = GetUniformIndex(uniform_name); if (uniform_index == -1) return;
  if (CheckDataDeltaAndSize(m_UniformData.get() + m_Uniforms[uniform_index].m_DataOffset, m_Uniforms[uniform_index].m_DataSize, v) == false) return;
  glUniform2f(m_Uniforms[uniform_index].m_LocationIndex, v.x, v.y); CHECK_GL_RENDER_ERROR;
  SetData(m_UniformData.get() + m_Uniforms[uniform_index].m_DataOffset, v);
}

void ShaderProgram::SetUniform(Hash uniform_name, const RenderVec3 & v)
{
  int uniform_index = GetUniformIndex(uniform_name); if (uniform_index == -1) return;
  if (CheckDataDeltaAndSize(m_UniformData.get() + m_Uniforms[uniform_index].m_DataOffset, m_Uniforms[uniform_index].m_DataSize, v) == false) return;
  glUniform3f(m_Uniforms[uniform_index].m_LocationIndex, v.x, v.y, v.z); CHECK_GL_RENDER_ERROR;
  SetData(m_UniformData.get() + m_Uniforms[uniform_index].m_DataOffset, v);
}

void ShaderProgram::SetUniform(Hash uniform_name, const RenderVec4 & v)
{
  int uniform_index = GetUniformIndex(uniform_name); if (uniform_index == -1) return;
  if (CheckDataDeltaAndSize(m_UniformData.get() + m_Uniforms[uniform_index].m_DataOffset, m_Uniforms[uniform_index].m_DataSize, v) == false) return;
  glUniform4f(m_Uniforms[uniform_index].m_LocationIndex, v.x, v.y, v.z, v.w); CHECK_GL_RENDER_ERROR;
  SetData(m_UniformData.get() + m_Uniforms[uniform_index].m_DataOffset, v);
}

int ShaderProgram::GetUniformIndex(Hash uniform_name) const
{
  for (int index = 0; index < (int)m_Uniforms.size(); index++)
  {
    if (m_Uniforms[index].m_NameHash == uniform_name)
    {
      return index;
    }
  }

  return -1;
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
