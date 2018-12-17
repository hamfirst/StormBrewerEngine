#pragma once

#include "Engine/EngineCommon.h"
#include "Engine/Rendering/VertexArray.h"

class Shader;

class ENGINE_EXPORT ShaderProgram
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

  int GetUniformLocation(Hash uniform_name) const;
  int GetUniformLocation(czstr uniform_name) const;

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

  void SetUniform(Hash uniform_name, const Mat4f & v);

protected:

  int GetUniformIndex(Hash uniform_name) const;

  static bool CheckDataDelta(const uint8_t * data_start)
  {
    return false;
  }

  template <typename T, typename ... Args>
  static bool CheckDataDelta(const uint8_t * data_start, T && t, Args && ... args)
  {
    if (memcmp(data_start, &t, sizeof(T)) != 0)
    {
      return true;
    }

    return CheckDataDelta(data_start + sizeof(T), std::forward<Args>(args)...);
  }

  template <typename ... Args>
  static bool CheckDataDeltaAndSize(const uint8_t * data_start, int data_size, Args && ... args)
  {
    int args_size = sizeof(std::tuple<std::decay_t<Args>...>);
    ASSERT(args_size == data_size, "Uniform data size mismatch");
    return CheckDataDelta(data_start, std::forward<Args>(args)...);
  }

  static void SetData(uint8_t * data_start)
  {

  }

  template <typename T, typename ... Args>
  static void SetData(uint8_t * data_start, T && t, Args && ... args)
  {
    memcpy(data_start, &t, sizeof(T));
    SetData(data_start + sizeof(T), std::forward<Args>(args)...);
  }

  friend class RenderState;
  friend class VertexArray;

  void Bind() const;  
  void Unbind() const;

private:

  friend class VertexArray;
  friend class VertexBuffer;

  struct UniformData
  {
    Hash m_NameHash;
    int m_LocationIndex;
    int m_DataOffset;
    int m_DataSize;
  };

  unsigned int m_ProgramName;
  unsigned int m_LoadError;

  std::string m_CompileLog;
  std::vector<UniformData> m_Uniforms;
  std::unique_ptr<uint8_t[]> m_UniformData;
};

ShaderProgram ENGINE_EXPORT MakeQuickShaderProgram(const char * vertex_shader, const char * fragment_shader);
