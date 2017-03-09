#pragma once

#include "Engine/EngineCommon.h"

class Shader;

class ShaderProgram
{
public:
  ShaderProgram();
  ShaderProgram(const ShaderProgram & rhs) = delete;
  ShaderProgram(ShaderProgram && rhs) noexcept;
  ~ShaderProgram();

  ShaderProgram & operator = (ShaderProgram & rhs) = delete;
  ShaderProgram & operator = (ShaderProgram && rhs) noexcept;

  void Move(ShaderProgram && rhs) noexcept;
  void Destroy();

  void CreateProgram(const Shader & vertex_shader, const Shader & fragment_shader);
  int GetLoadError() const { return m_LoadError; }
  const std::string & GetCompileLog() const { return m_CompileLog; }

  int GetUniformIndex(Hash uniform_name);
  int GetUniformIndex(czstr uniform_name);

  void SetUniform(Hash uniform_name, int v1);
  void SetUniform(Hash uniform_name, int v1, int v2);
  void SetUniform(Hash uniform_name, int v1, int v2, int v3);
  void SetUniform(Hash uniform_name, int v1, int v2, int v3, int v4);

  void SetUniform(Hash uniform_name, float v1);
  void SetUniform(Hash uniform_name, float v1, float v2);
  void SetUniform(Hash uniform_name, float v1, float v2, float v3);
  void SetUniform(Hash uniform_name, float v1, float v2, float v3, float v4);

  void SetUniform(Hash uniform_name, const RenderVec2 & v);
  void SetUniform(Hash uniform_name, const RenderVec3 & v);
  void SetUniform(Hash uniform_name, const RenderVec4 & v);


  void Bind() const;  
  void Unbind() const;

private:

  unsigned int m_ProgramName;
  unsigned int m_LoadError;

  friend class VertexArray;
  friend class VertexBuffer;

  std::string m_CompileLog;
  std::vector<Hash> m_Uniforms;
};

ShaderProgram MakeQuickShaderProgram(const char * vertex_shader, const char * fragment_shader);
