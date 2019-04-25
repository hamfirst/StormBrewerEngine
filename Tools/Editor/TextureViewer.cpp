
#include <gl3w/gl3w.h>

#include <QTimer>
#include <QWheelEvent>

#include "TextureViewer.h"

#include "Engine/EngineCommon.h"
#include "Engine/Rendering/ShaderLiteral.h"
#include "Engine/Shader/ShaderManager.h"
#include "Engine/Text/TextManager.h"


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
}

void TextureViewer::resizeGL(int w, int h)
{
  m_RenderState.SetScreenSize(Vector2(w, h));
  m_RenderState.SetRenderSize(Vector2(w, h));
}

void TextureViewer::paintGL()
{
  QColor clear_color_qt = palette().color(QPalette::Window);
  Color color(clear_color_qt.red(), clear_color_qt.green(), clear_color_qt.blue(), 255);

  glClearColor(color.r, color.g, color.b, color.a);
  glClear(GL_COLOR_BUFFER_BIT);

  m_RenderState.MakeCurrent();

  TextureAsset * asset = m_TextureAsset.Get();
  if (asset->IsLoaded())
  {
    auto & vertex_buffer = m_RenderState.GetScratchBuffer();

    QuadVertexBufferBuilder builder;
    QuadVertexBuilderInfo quad;
    quad.m_Position = Box::FromFrameCenterAndSize({}, asset->GetSize());
    quad.m_TexCoords = Box::FromExtent(asset->GetSize());
    quad.m_TextureSize = asset->GetSize();
    quad.m_Color = Color(1.0f, 1.0f, 1.0f, 1.0f);

    builder.AddQuad(quad);
    builder.FillVertexBuffer(vertex_buffer);


    auto & shader = g_ShaderManager.GetDefaultScreenSpaceShader();
    m_RenderState.BindShader(shader);
    m_RenderState.BindTexture(*asset);
    m_RenderState.BindVertexBuffer(vertex_buffer);

    shader.SetUniform(COMPILE_TIME_CRC32_STR("u_ScreenSize"), m_RenderState.GetFullRenderDimensions());
    shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Offset"), m_Center * m_Magnification.Get());
    shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Matrix"), RenderVec4{ m_Magnification.Get(), 0, 0, m_Magnification.Get() } );
    shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Texture"), 0);
    shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Color"), RenderVec4{ 1, 1, 1, 1 });
    shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Bounds"), RenderVec4{ -1, -1, 1, 1 });
    shader.SetUniform(COMPILE_TIME_CRC32_STR("u_ColorMatrix"), Mat4f());

    m_RenderState.Draw();

    std::string info;
    info += "Width: ";
    info += std::to_string(asset->GetWidth());
    info += " Height: ";
    info += std::to_string(asset->GetHeight());

    char mag_str[50];
    snprintf(mag_str, sizeof(mag_str), "%.2f%%", m_Magnification.Get() * 100);

    info += " Magnification: ";
    info += mag_str;

    auto screen_size = m_RenderState.GetScreenSize();
    auto size = g_TextManager.GetTextSize(info.data(), -1, 1);
    Vector2 text_start = Vector2(30, -30) - Vector2(screen_size.x, -screen_size.y) / 2;
    Box text_bkg = { size.m_Start + text_start, size.m_End + text_start };

    m_RenderState.DrawDebugQuad(text_bkg, Color(30, 30, 30, 200), true);

    g_TextManager.SetTextPos(text_start);
    g_TextManager.RenderText(info.data(), -1, 1, m_RenderState);
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

void TextureViewer::HandleTextureLoad(TextureAsset * asset)
{

}
