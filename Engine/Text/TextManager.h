#pragma once

#include <memory>
#include <map>

#include "Foundation/Common.h"

#include "Engine/Rendering/ShaderProgram.h"
#include "Engine/Rendering/VertexArray.h"
#include "Engine/Rendering/VertexBuffer.h"
#include "Engine/Rendering/RenderState.h"
#include "Engine/Text/TextBufferBuilder.h"

class TextRenderer;
class TextBackupFont;
class TextInputContext;

static const int kInvalidFontId = -1000000;

enum class TextRenderMode
{
  kNormal,
  kShadowed,
  kOutlined,
};

struct TextSettings
{
  Vector2 m_TextPos;
  Optional<Box> m_TextBounds;

  TextRenderMode m_Mode;

  Color m_PrimaryColor;
  Color m_ShadowColor;

  Color m_SelectionColor;
  Color m_SelectionBkgColor;

  std::vector<Box> m_GlyphPositions;
};

class ENGINE_EXPORT TextManager
{
public:

  TextManager();

  void Init();
  void ShutDown();
  
  void LoadFont(czstr font_path, int font_id, int font_size);
  bool IsFontLoaded(int font_id);

  void AddTextToBuffer(czstr text, int font_id, TextBufferBuilder & vertex_builder, int sel_start = -1, int sel_end = -1, int cursor_pos = -1);
  void AddTextToBuffer(std::shared_ptr<TextInputContext> & context, int font_id, TextBufferBuilder & vertex_builder, const char * prompt = "");
  void RenderBuffer(TextBufferBuilder & vertex_builder, RenderState & render_state);

  void RenderText(czstr text, int font_id, RenderState & render_state, int sel_start = -1, int sel_end = -1, int cursor_pos = -1);
  void RenderInputText(std::shared_ptr<TextInputContext> & context, int font_id, RenderState & render_state, const char * prompt = "");

  Box GetTextSize(czstr text, int font_id);
  Box GetTextSize(std::shared_ptr<TextInputContext> & context, int font_id, const char * prompt = "");

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

  std::vector<Box> m_GlyphPositions;

  TextSettings m_Settings;

  ShaderProgram m_TextShader;
  VertexBuffer m_TextVertexBuffer;
};

extern TextManager g_TextManager;
