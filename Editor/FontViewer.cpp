
#include <gl3w/gl3w.h>

#include <QTimer>
#include <QWheelEvent>
#include <QLineEdit>

#include "FontViewer.h"

#include "Engine/EngineCommon.h"
#include "Engine/Rendering/ShaderLiteral.h"
#include "Engine/Text/TextManager.h"
#include "Engine/Settings/EngineSettings.refl.h"



static const char * kFontViewerVertexShader = SHADER_LITERAL(
  attribute vec2 a_Position;
  attribute vec2 a_TexCoord;
  attribute vec4 a_Color;

  varying vec2 v_TexCoord;
  varying vec4 v_Color;

  uniform vec2 u_ScreenSize;
  uniform vec2 u_StartPos;
  uniform vec2 u_EndPos;

  void main()
  {
    vec2 position = mix(u_StartPos, u_EndPos, a_Position);
    position /= u_ScreenSize;
    position -= vec2(0.5, 0.5);
    position *= 2.0;

    gl_Position = vec4(position, 0, 1);
    v_TexCoord = a_TexCoord;
    v_Color = a_Color;
  }
);

static const char * kFontViewerFragmentShader = SHADER_LITERAL(

  varying vec2 v_TexCoord;
  varying vec4 v_Color;

  uniform sampler2D u_Texture;

  void main()
  {
    vec4 color = texture2D(u_Texture, v_TexCoord);
    gl_FragColor = color;
  }
);

int FontViewer::m_NextFontId = -100;

FontViewer::FontViewer(const char * file_path, QWidget *parent) :
  QOpenGLWidget(parent),
  m_FilePath(file_path),
  m_FontId(m_NextFontId--),
  m_LineEdit(new QLineEdit(this))
{
  QTimer * timer = new QTimer(this);
  connect(timer, &QTimer::timeout, this, &FontViewer::tick);
  timer->start(16);

  m_Magnification.Set(1.0f);

}

FontViewer::~FontViewer()
{
}

void FontViewer::initializeGL()
{
  m_RenderState.InitRenderState(width(), height());
  m_RenderUtil.LoadShaders();

  g_TextManager.LoadFont(m_FilePath.data(), m_FontId, 15);

  m_Shader = MakeQuickShaderProgram(kFontViewerVertexShader, kFontViewerFragmentShader);

  QuadVertexBufferBuilder builder;
  QuadVertexBuilderInfo quad;
  quad.m_Position.m_Start = Vector2(0, 0);
  quad.m_Position.m_End = Vector2(1, 1);
  quad.m_TexCoords.m_Start = Vector2(0, 0);
  quad.m_TexCoords.m_End = Vector2(1, 1);
  quad.m_TextureSize = Vector2(1, 1);
  quad.m_Color = Color(1.0f, 1.0f, 1.0f, 1.0f);

  builder.AddQuad(quad);
  builder.FillVertexBuffer(m_VertexBuffer);
  m_VertexArray.CreateDefaultBinding(m_Shader, m_VertexBuffer);
}

void FontViewer::resizeGL(int w, int h)
{
  m_RenderState.SetScreenSize(Vector2(w, h));

  m_LineEdit->setGeometry(0, h - m_LineEdit->height(), w, m_LineEdit->height());
}

void FontViewer::paintGL()
{
  QColor clear_color_qt = palette().color(QPalette::Window);
  Color color(clear_color_qt.red(), clear_color_qt.green(), clear_color_qt.blue(), 255);

  glClearColor(color.r, color.g, color.b, color.a);
  glClear(GL_COLOR_BUFFER_BIT);

  if (g_TextManager.IsFontLoaded(m_FontId) == false)
  {
    return;
  }

  m_Shader.Bind();
  m_VertexArray.Bind();

  g_TextManager.BindGlyphTexture(m_FontId, 0);

  RenderVec2 tex_center = RenderVec2{ g_EngineSettings.m_FontCacheSize, g_EngineSettings.m_FontCacheSize } * 0.5f;
  RenderVec2 window_center = RenderVec2{ width(), height() } * 0.5f;

  m_Shader.SetUniform(COMPILE_TIME_CRC32_STR("u_ScreenSize"), m_RenderState.GetRenderScreenSize());
  m_Shader.SetUniform(COMPILE_TIME_CRC32_STR("u_StartPos"), window_center - (tex_center - m_Center) * m_Magnification.Get());
  m_Shader.SetUniform(COMPILE_TIME_CRC32_STR("u_EndPos"), window_center + (tex_center + m_Center) * m_Magnification.Get());
  m_Shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Texture"), 0);

  m_VertexBuffer.Draw();

  m_Shader.Unbind();
  m_VertexArray.Unbind();

  std::string info;
  info += "Width: ";
  info += std::to_string(g_EngineSettings.m_FontCacheSize);
  info += " Height: ";
  info += std::to_string(g_EngineSettings.m_FontCacheSize);

  char mag_str[50];
  snprintf(mag_str, sizeof(mag_str), "%.2f%%", m_Magnification.Get() * 100);

  info += " Magnification: ";
  info += mag_str;

  std::string input = m_LineEdit->text().toStdString();
  if (input.length())
  {
    info += "\n";
    info += input;
  }

  auto size = g_TextManager.GetTextSize(info.data(), m_FontId);
  Vector2 text_start = Vector2(10, m_RenderState.GetScreenHeight() - 20);
  Box text_bkg = { size.m_Start + text_start, size.m_End + text_start };

  m_RenderUtil.DrawQuad(text_bkg, Color(30, 30, 30, 200), m_RenderState.GetScreenSize());

  g_TextManager.SetTextMode(TextRenderMode::kShadowed);
  g_TextManager.SetTextPos(text_start);
  g_TextManager.RenderText(info.data(), m_FontId, m_RenderState);
  g_TextManager.SetTextMode();
}

void FontViewer::mousePressEvent(QMouseEvent * event)
{
  if (event->button() != Qt::LeftButton)
  {
    return;
  }

  m_CursorPos = QCursor::pos();
  m_Dragging = true;

  grabMouse();
}

void FontViewer::mouseMoveEvent(QMouseEvent *event)
{
  if (m_Dragging == false)
  {
    return;
  }

  auto p = QCursor::pos();
  auto diff_pos = p - m_CursorPos;

  m_CursorPos = p;

  m_Center.x += diff_pos.x() / m_Magnification.Get();
  m_Center.y -= diff_pos.y() / m_Magnification.Get();
}

void FontViewer::mouseReleaseEvent(QMouseEvent * event)
{
  if (event->button() != Qt::LeftButton)
  {
    return;
  }

  releaseMouse();
  m_Dragging = false;
}

void FontViewer::wheelEvent(QWheelEvent *event)
{
  if (event->delta() < 0)
  {
    m_Magnification *= 0.8f;
  }
  else
  {
    m_Magnification *= 1.25f;
  }
}

void FontViewer::tick()
{
  repaint();
}

