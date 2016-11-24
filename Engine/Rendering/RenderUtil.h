#pragma once

#include "Engine/Rendering/ShaderProgram.h"
#include "Engine/Rendering/VertexArray.h"
#include "Engine/Rendering/VertexBuffer.h"
#include "Engine/Rendering/RenderState.h"
#include "Engine/Rendering/Texture.h"
#include "Engine/Rendering/RenderState.h"

#include "Data/BasicTypes/BasicTypes.h"

class RenderUtil
{
public:
  void LoadShaders();
  void CleanupShaders();

  void DrawQuad(const Box & box, const Color & color, RenderState & render_state, bool alpha_blend);
  void DrawTexturedQuad(const Box & box, const Color & color, const Texture & texture, RenderState & render_state, bool alpha_blend);

private:
  ShaderProgram m_QuadShader;
  VertexArray m_QuadVertexArray;

  ShaderProgram m_QuadTextureShader;
  VertexArray m_QuadTextureVertexArray;

  VertexBuffer m_VertexBuffer;
};
