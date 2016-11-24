#pragma once

#include "Engine\EngineCommon.h"

enum class ShaderType
{
  kVertexShader,
  kFragmentShader,
  kInvalid,
};

class Shader
{
public:
  Shader();
  Shader(const Shader & rhs) = delete;
  Shader(Shader && rhs) noexcept;
  ~Shader();

  Shader & operator = (Shader & rhs) = delete;
  Shader & operator = (Shader && rhs) noexcept;

  void Move(Shader && rhs) noexcept;
  void Destroy();

  void LoadShader(czstr shader_source, ShaderType type);
  int GetLoadError() const { return m_LoadError; }
  const std::string & GetCompileLog() const { return m_CompileLog; }
  ShaderType GetType() const { return m_Type; }

private:

  unsigned int m_ShaderName;
  unsigned int m_LoadError;

  friend class ShaderProgram;

  ShaderType m_Type;
  std::string m_CompileLog;
};

