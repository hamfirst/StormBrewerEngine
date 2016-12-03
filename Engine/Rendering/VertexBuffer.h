#pragma once

#include "Engine\EngineCommon.h"
#include "Engine\Rendering\VertexDefinition.h"

class ShaderProgram;

class VertexBuffer
{
public:
  VertexBuffer();
  VertexBuffer(const VertexBuffer & rhs) = delete;
  VertexBuffer(VertexBuffer && rhs) noexcept;
  ~VertexBuffer();

  VertexBuffer & operator = (VertexBuffer & rhs) = delete;
  VertexBuffer & operator = (VertexBuffer && rhs) noexcept;

  void Move(VertexBuffer && rhs) noexcept;
  void Destroy();

  void SetBufferData(const gsl::span<VertexInfo> & verts, const gsl::span<uint16_t> & indices, VertexBufferType type);
  int GetLoadError() const { return m_LoadError; }

  void CreateDefaultBinding(const ShaderProgram & program) const;
  void Draw(int index_start = 0, int index_end = -1) const;

  void Bind() const;
  void Unbind() const;

private:

  VertexBufferType m_Type;
  uint32_t m_IndexCount;

  unsigned int m_VertexBufferName;
  unsigned int m_IndexBufferName;

  int m_LoadError;
};


