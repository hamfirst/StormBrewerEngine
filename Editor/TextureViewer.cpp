
#include <gl3w/gl3w.h>

#include <QTimer>
#include <QWheelEvent>

#include "TextureViewer.h"

#include "Engine/EngineCommon.h"
#include "Engine/Rendering/ShaderLiteral.h"
#include "Engine/Text/TextManager.h"



static const char * kTextureViewerVertexShader = SHADER_LITERAL(
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

static const char * kTextureViewerFragmentShader = SHADER_LITERAL(

  varying vec2 v_TexCoord;
  varying vec4 v_Color;

  uniform sampler2D u_Texture;

  void main()
  {
    vec4 color = texture2D(u_Texture, v_TexCoord);
    gl_FragColor = color;
  }
);

TextureViewer::TextureViewer(const char * file_path, QWidget *parent) :
  QOpenGLWidget(parent),
  m_FilePath(file_path),
  m_TextureAsset(TextureAsset::LoadWithCallback(file_path, TextureAsset::LoadCallback(&TextureViewer::HandleTextureLoad, this)))
{
  setFocusPolicy(Qt::ClickFocus);

  QTimer * timer = new QTimer(this);
  connect(timer, &QTimer::timeout, this, &TextureViewer::tick);
  timer->start(16);

  m_Magnification.Set(1.0f);
}

TextureViewer::~TextureViewer()
{
}

void TextureViewer::initializeGL()
{
  m_RenderState.InitRenderState(width(), height());
  m_RenderUtil.LoadShaders();

  m_Shader = MakeQuickShaderProgram(kTextureViewerVertexShader, kTextureViewerFragmentShader);

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

void TextureViewer::resizeGL(int w, int h)
{
  m_RenderState.SetScreenSize(Vector2(w, h));
}

void TextureViewer::paintGL()
{
  QColor clear_color_qt = palette().color(QPalette::Window);
  Color color(clear_color_qt.red(), clear_color_qt.green(), clear_color_qt.blue(), 255);

  glClearColor(color.r, color.g, color.b, color.a);
  glClear(GL_COLOR_BUFFER_BIT);

  TextureAsset * asset = m_TextureAsset.Get();
  if (asset->IsLoaded())
  {
    m_Shader.Bind();
    m_VertexArray.Bind();

    asset->GetTexture().BindTexture(0);

    RenderVec2 tex_center = RenderVec2{ asset->GetWidth(), asset->GetHeight() } * 0.5f;
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
    info += std::to_string(asset->GetWidth());
    info += " Height: ";
    info += std::to_string(asset->GetHeight());

    char mag_str[50];
    snprintf(mag_str, sizeof(mag_str), "%.2f%%", m_Magnification.Get() * 100);

    info += " Magnification: ";
    info += mag_str;

    auto size = g_TextManager.GetTextSize(info.data(), -1);
    Vector2 text_start = Vector2(10, m_RenderState.GetScreenHeight() - 20);
    Box text_bkg = { size.m_Start + text_start, size.m_End + text_start };

    m_RenderUtil.DrawQuad(text_bkg, Color(30, 30, 30, 200), m_RenderState, true);

    g_TextManager.SetTextPos(text_start);
    g_TextManager.RenderText(info.data(), -1, m_RenderState);
  }
}

void TextureViewer::mousePressEvent(QMouseEvent * event)
{
  if (event->button() != Qt::LeftButton)
  {
    return;
  }

  m_CursorPos = QCursor::pos();
  m_Dragging = true;

  grabMouse();
}

void TextureViewer::mouseMoveEvent(QMouseEvent *event)
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

void TextureViewer::mouseReleaseEvent(QMouseEvent * event)
{
  if (event->button() != Qt::LeftButton)
  {
    return;
  }

  releaseMouse();
  m_Dragging = false;
}

void TextureViewer::wheelEvent(QWheelEvent *event)
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

void TextureViewer::tick()
{
  repaint();
}

void TextureViewer::HandleTextureLoad(TextureAsset * asset, bool success)
{

}
