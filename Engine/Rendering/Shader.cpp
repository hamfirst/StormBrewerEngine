
#include "Engine/EngineCommon.h"
#include "Engine/Rendering/Shader.h"
#include "Engine/Rendering/RenderErrorMacros.h"

#include <gl3w/gl3w.h>

Shader::Shader()
{
  m_ShaderName = 0;
  m_LoadError = 0;
  m_Type = ShaderType::kInvalid;
}

Shader::Shader(Shader && rhs) noexcept
{
  Move(std::move(rhs));
}

Shader::~Shader()
{
  Destroy();
}

Shader & Shader::operator = (Shader && rhs) noexcept
{
  Destroy();
  Move(std::move(rhs));
  return *this;
}

void Shader::Move(Shader && rhs) noexcept
{
  m_ShaderName = rhs.m_ShaderName;
  m_LoadError = rhs.m_LoadError;
  m_Type = rhs.m_Type;

  rhs.m_ShaderName = 0;
  rhs.m_LoadError = 0;
  rhs.m_Type = ShaderType::kInvalid;
}

void Shader::Destroy()
{
  if (m_ShaderName != 0)
  {
    glDeleteShader(m_ShaderName);
    m_ShaderName = 0;
  }

  m_LoadError = 0;
}

void Shader::LoadShader(czstr shader_source, ShaderType type)
{
  Destroy();

  GLenum shader_type;
  switch (type)
  {
  case ShaderType::kFragmentShader:
    shader_type = GL_FRAGMENT_SHADER;
    break;
  case ShaderType::kVertexShader:
    shader_type = GL_VERTEX_SHADER;
    break;
  default:
    m_LoadError = GL_INVALID_ENUM;
    return;
  }

  m_ShaderName = glCreateShader(shader_type); CHECK_GL_LOAD_ERROR;
  auto shader_destroy_on_error = gsl::finally([&] { if (m_LoadError != 0) { glDeleteShader(m_ShaderName); m_ShaderName = 0; } });

  czstr shader_str = shader_source;
  GLint shader_len = (int)strlen(shader_source);
  glShaderSource(m_ShaderName, 1, &shader_str, &shader_len); CHECK_GL_LOAD_ERROR;
  glCompileShader(m_ShaderName); CHECK_GL_LOAD_ERROR;

  GLint compiled;
  glGetShaderiv(m_ShaderName, GL_COMPILE_STATUS, &compiled); CHECK_GL_LOAD_ERROR;
  if (compiled == 0)
  {
    GLint log_size;
    glGetShaderiv(m_ShaderName, GL_INFO_LOG_LENGTH, &log_size); CHECK_GL_LOAD_ERROR;

    m_LoadError = GL_INVALID_VALUE;
    if (log_size > 0)
    {
      auto error_log_mem = std::make_unique<char[]>(log_size + 1);
      zstr error_log = error_log_mem.get();

      GLsizei outplen = 0;
      glGetShaderInfoLog(m_ShaderName, log_size, &outplen, error_log); CHECK_GL_LOAD_ERROR;
      error_log[log_size] = 0;

      printf("Shader error: \n%s\n", error_log);
      m_CompileLog = error_log;
    }

    m_LoadError = GL_INVALID_VALUE;
    return;
  }

  m_Type = type;
}
