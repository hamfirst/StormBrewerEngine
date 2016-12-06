#pragma once

#include "Engine/Rendering/ShaderProgram.h"
#include "Engine/Rendering/VertexArray.h"
#include "Engine/Rendering/VertexBuffer.h"
#include "Engine/Rendering/RenderState.h"
#include "Engine/Rendering/Texture.h"
#include "Engine/Rendering/RenderState.h"

class RenderUtil
{
public:
  void LoadShaders();
  void CleanupShaders();

  static void Clear();
  static void Clear(const Color & color);
  static void SetClearColor(const Color & color);

  void DrawQuad(const Box & box, const Color & color, RenderState & render_state, bool alpha_blend);
  void DrawTexturedQuad(const Box & box, const Color & color, const Texture & texture, RenderState & render_state, bool alpha_blend);
  void DrawTexturedQuad(const Vector2 & start, const Color & color, const Texture & texture, RenderState & render_state, bool alpha_blend);

private:
  ShaderProgram m_QuadShader;
  ShaderProgram m_QuadTextureShader;

  VertexBuffer m_VertexBuffer;
};
