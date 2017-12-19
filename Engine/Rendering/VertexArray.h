#pragma once

#include "Engine/EngineCommon.h"
#include "Engine/Rendering/RenderSettings.h"
#include "Engine/Rendering/VertexDefinition.h"
#include "Engine/Rendering/VertexAttrib.h"

class RenderState;
class VertexBuffer;
class ShaderProgram;

class ENGINE_EXPORT VertexArray
{
public:
  VertexArray();
  VertexArray(const VertexArray & rhs) = delete;
  VertexArray(VertexArray && rhs) noexcept;
  ~VertexArray();

  VertexArray & operator = (VertexArray & rhs) = delete;
  VertexArray & operator = (VertexArray && rhs) noexcept;

  void Move(VertexArray && rhs) noexcept;
  void Destroy();

  int GetLoadError() const { return m_LoadError; }

private:

  friend class RenderState;
  friend class VertexBuffer;

  void Sync(RenderState & render_state, const VertexBuffer & vertex_buffer, const ShaderProgram & shader_program, bool dirty);
  void GenerateAttribState(const VertexBuffer & vertex_buffer, const ShaderProgram & shader_program, NotNullPtr<VertexAttribState> new_state);

private:

#ifdef USE_VERTEX_ARRAY
  unsigned int m_VertexArrayName;
#endif

  NullOptPtr<const ShaderProgram> m_BoundShader = nullptr;
  int m_BoundShaderName = 0;

  VertexAttribState m_Current[kMaxVertexAttribs] = {};

  int m_LoadError;
};
