#pragma once

#include "Engine/Rendering/ShaderProgram.h"
#include "Engine/Rendering/VertexArray.h"
#include "Engine/Rendering/VertexBuffer.h"
#include "Engine/Rendering/RenderState.h"
#include "Engine/Rendering/Texture.h"
#include "Engine/Rendering/RenderState.h"

class ENGINE_EXPORT RenderUtil
{
public:
  RenderUtil();
  RenderUtil(const RenderUtil & rhs) = delete;
  RenderUtil(RenderUtil && rhs) = delete;

  void LoadShaders();
  void CleanupShaders();

  static void Clear();
  static void Clear(const Color & color);
  static void SetClearColor(const Color & color);

  void DrawQuad(const Box & box, const Color & color, const RenderVec2 & screen_size, RenderState & render_state);

  void DrawTexturedQuad(const Box & box, const Color & color, const Texture & texture, const RenderVec2 & screen_size, RenderState & render_state);
  void DrawTexturedQuad(const Vector2 & start, const Color & color, const Texture & texture, const RenderVec2 & screen_size, RenderState & render_state);

  const Texture & GetDefaultTexture() const;
  VertexBuffer & GetScratchBuffer();

private:
  ShaderProgram m_QuadShader;
  ShaderProgram m_QuadTextureShader;

  VertexBuffer m_QuadVertexBuffer;
  VertexBuffer m_ScratchVertexBuffer;
  Texture m_DefaultTexture;
};
