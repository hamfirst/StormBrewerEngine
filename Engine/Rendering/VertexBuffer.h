#pragma once

#include "Engine/EngineCommon.h"
#include "Engine/Rendering/VertexDefinition.h"
#include "Engine/Rendering/VertexArray.h"
#include "Engine/Rendering/VertexBuffer.h"
#include "Engine/Rendering/VertexAttrib.h"

class RenderState;
class ShaderProgram;
class VertexList;
class VertexArray;

class ENGINE_EXPORT VertexBuffer
{
public:
  explicit VertexBuffer(bool dynamic = false, NotNullPtr<VertexAttribSpec> spec = &g_DefaultVertexSpec);
  VertexBuffer(const VertexBuffer & rhs) = delete;
  VertexBuffer(VertexBuffer && rhs) noexcept;
  ~VertexBuffer();

  VertexBuffer & operator = (VertexBuffer & rhs) = delete;
  VertexBuffer & operator = (VertexBuffer && rhs) noexcept;

  void Move(VertexBuffer && rhs) noexcept;
  void Destroy();

  void SetBufferData(const gsl::span<VertexInfo> & verts, VertexBufferType type);
  void SetBufferData(const VertexList & list, VertexBufferType type);
  int GetLoadError() const { return m_LoadError; }
  bool IsEmpty() const { return m_IndexCount == 0; }

private:

  friend class RenderState;
  friend class VertexArray;

  void Draw(int index_start = 0, int index_end = -1) const;
  void Sync(RenderState & render_state, const ShaderProgram & shader_program);

  void Bind() const;
  void Unbind() const;

private:

  unsigned int m_VertexBufferName;
  NotNullPtr<VertexAttribSpec> m_VertexSpec;

  VertexArray m_VertexArray;

  VertexBufferType m_Type;
  uint32_t m_IndexCount;

  int m_LoadError;
  bool m_Dynamic;
  bool m_Dirty;
};


