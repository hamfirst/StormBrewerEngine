#pragma once

#include <memory>
#include <map>

#include "Foundation/Common.h"

#include "Engine/Rendering/ShaderProgram.h"
#include "Engine/Rendering/VertexArray.h"
#include "Engine/Rendering/VertexBuffer.h"
#include "Engine/Rendering/RenderState.h"

class TextRenderer;
class TextBackupFont;
class TextInputContext;

enum class TextRenderMode
{
  kNormal,
  kShadowed,
  kOutlined,
};

class TextManager
{
public:

  void Init();
  void ShutDown();
  
  void LoadFont(czstr font_path, int font_id, int font_size);
  bool IsFontLoaded(int font_id);

  void RenderText(czstr text, int font_id, RenderState & render_state, int sel_start = -1, int sel_end = -1, int cursor_pos = -1);
  void RenderInputText(std::shared_ptr<TextInputContext> & context, int font_id, RenderState & render_state);

  Box GetTextSize(czstr text, int font_id);

  bool BindGlyphTexture(int font_id, int texture_stage);

  void SetTextMode(TextRenderMode mode = TextRenderMode::kNormal);

  void SetTextPos(const Vector2 & pos);
  void SetTextBounds(const Box & bounds);
  void ClearTextBounds();

  void SetPrimaryColor(const Color & color = Color(255, 255, 255, 255));
  void SetShadowColor(const Color & color = Color(0, 0, 0, 127));

  void SetSelectionColor(const Color & color = Color(128, 128, 255, 255));
  void SetSelectionBkgColor(const Color & color = Color(64, 64, 100, 255));

private:
  void LoadBackupFont(czstr font_path);

  std::map<int, std::unique_ptr<TextRenderer>> m_Fonts;
  std::vector<std::unique_ptr<TextBackupFont>> m_BackupFonts;

  Vector2 m_TextPos;
  Optional<Box> m_TextBounds;

  std::vector<Box> m_GlyphPositions;

  TextRenderMode m_Mode;

  Color m_PrimaryColor;
  Color m_ShadowColor;

  Color m_SelectionColor;
  Color m_SelectionBkgColor;

  ShaderProgram m_TextShader;
  ShaderProgram m_SelectionShader;
  VertexBuffer m_TextVertexBuffer;
  VertexBuffer m_SelectionVertexBuffer;
};

extern TextManager g_TextManager;