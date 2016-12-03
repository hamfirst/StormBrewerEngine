#pragma once

#include <memory>
#include <map>

#include "Foundation/Common.h"

#include "Data/BasicTypes/BasicTypes.refl.h"

#include "Engine/Rendering/ShaderProgram.h"
#include "Engine/Rendering/VertexArray.h"
#include "Engine/Rendering/VertexBuffer.h"
#include "Engine/Rendering/RenderState.h"

class TextRenderer;

class TextManager
{
public:

  void Init();
  void ShutDown();

  void LoadFont(czstr font_path, int font_id, int font_size);
  bool IsFontLoaded(int font_id);

  void RenderText(czstr text, int font_id, Color color, const Vector2 & pos, RenderState & render_state);
  void RenderTextShadowed(czstr text, int font_id, Color color, Color shadow_color, const Vector2 & pos, RenderState & render_state);
  void RenderTextOutlined(czstr text, int font_id, Color color, Color outline_color, const Vector2 & pos, RenderState & render_state);

  Box GetTextSize(czstr text, int font_id);

  bool BindGlyphTexture(int font_id, int texture_stage);

private:
  std::map<int, std::unique_ptr<TextRenderer>> m_Fonts;

  ShaderProgram m_FontShader;
  VertexBuffer m_VertexBuffer;
};

extern TextManager g_TextManager;