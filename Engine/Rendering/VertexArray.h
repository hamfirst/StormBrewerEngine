#pragma once

#include "Engine/EngineCommon.h"
#include "Engine/Rendering/VertexDefinition.h"

#include "Engine/Rendering/ShaderProgram.h"

void CreateDefaultVertexBufferBinding(const ShaderProgram & program);

#ifndef _WEB

class VertexBuffer;

class ENGINE_EXPORT VertexArray
{
public:
  VertexArray();
  VertexArray(const VertexArray & rhs) = delete;
  VertexArray(VertexArray && rhs) noexcept;
  ~VertexArray();

  VertexArray & operator = (VertexArray & rhs) = delete;
  VertexArray & operator = (VertexArray && rhs) noexcept;

  void Create();
  void Move(VertexArray && rhs) noexcept;
  void Destroy();

  void CreateDefaultBinding(const ShaderProgram & program, VertexBuffer & buffer);


  int GetLoadError() const { return m_LoadError; }

  void Bind() const;
  void Unbind() const;

private:

  unsigned int m_VertexArrayName;

  int m_LoadError;
};

#endif

