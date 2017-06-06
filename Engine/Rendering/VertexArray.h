#pragma once

#include "Engine/EngineCommon.h"
#include "Engine/Rendering/VertexDefinition.h"

#include "Engine/Rendering/ShaderProgram.h"
#include "Engine/Rendering/VertexBuffer.h"

#ifndef _WEB

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

  void CreateDefaultBinding(const ShaderProgram & program, const VertexBuffer & buffer);
  int GetLoadError() const { return m_LoadError; }

  void Bind() const;
  void Unbind() const;

private:

  unsigned int m_VertexArrayName;

  int m_LoadError;
};

#endif

