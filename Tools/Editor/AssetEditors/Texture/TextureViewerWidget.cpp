
#include "External/gl3w/gl3w.h"

#include <QTimer>
#include <QWheelEvent>

#include "TextureViewerWidget.h"

#include "Engine/EngineCommon.h"
#include "Engine/Rendering/ShaderLiteral.h"
#include "Engine/Rendering/GeometryVertexBufferBuilder.h"
#include "Engine/Shader/ShaderManager.h"
#include "Engine/Text/TextManager.h"

static const char * kTextureViewerWidgetGridVertexShader = SHADER_LITERAL(
  attribute vec2 a_Position;
  attribute vec4 a_Color;

  varying vec4 v_Color;

  void main()
  {
    gl_Position = vec4(a_Position, 0, 1);
    v_Color = a_Color;
  }
);

static const char * kTextureViewerWidgetGridFragmentShader = SHADER_LITERAL(

  varying vec4 v_Color;

  uniform sampler2D u_Texture;

  void main()
  {
    gl_FragColor = v_Color;
  }
);


TextureViewerWidget::TextureViewerWidget(QWidget *parent) :
  QOpenGLWidget(parent),
  m_GridWidth(0),
  m_GridHeight(0),
  m_GridBuffer(true)
{
  setFocusPolicy(Qt::ClickFocus);

  QTimer * timer = new QTimer(this);
  connect(timer, &QTimer::timeout, this, &TextureViewerWidget::tick);
  timer->start(16);

  m_Magnification.Set(1.0f);
}

TextureViewerWidget::~TextureViewerWidget()
{
}

void TextureViewerWidget::LoadTexture(czstr file_path)
{
  if (m_FilePath == file_path)
  {
    return;
  }

  m_FilePath = file_path;
  m_TextureAsset = TextureAsset::LoadWithCallback(file_path, TextureAsset::LoadCallback(&TextureViewerWidget::HandleTextureLoad, this));

  m_Center = {};
  m_Magnification.Set(1.0f);
}

void TextureViewerWidget::UnloadTexture()
{
  m_TextureAsset = {};
  m_FilePath.clear();
}

void TextureViewerWidget::SetGridWidth(int width)
{
  m_GridWidth = width;
}

void TextureViewerWidget::SetGridHeight(int height)
{
  m_GridHeight = height;
}

RenderVec2 TextureViewerWidget::TransformFromTextureSpaceToClipSpace(RenderVec2 texture_space)
{
  auto texture_size = RenderVec2{};
  
  TextureAsset * asset = m_TextureAsset.Get();
  if (asset && asset->IsLoaded())
  {
    texture_size = (RenderVec2{ asset->GetWidth(), asset->GetHeight() } * 0.5f);
  }

  auto offset = texture_space;
  offset -= texture_size - RenderVec2{ m_Center.x, -m_Center.y };
  offset *= m_Magnification.Get();
  offset /= RenderVec2{ width(), height() };
  offset *= 2.0f;

  auto clip_space = offset;
  clip_space.y *= -1.0f;
  return clip_space;
}

RenderVec2 TextureViewerWidget::TransformFromClipSpaceToTextureSpace(RenderVec2 clip_space)
{
  auto texture_size = RenderVec2{};

  TextureAsset * asset = m_TextureAsset.Get();
  if (asset && asset->IsLoaded())
  {
    texture_size = (RenderVec2{ asset->GetWidth(), asset->GetHeight() } * 0.5f);
  }

  clip_space.y *= -1.0f;

  auto offset = clip_space;
  offset *= 0.5f;
  offset *= (1.0f / m_Magnification.Get());
  offset *= RenderVec2{ width(), height() };
  offset += texture_size - RenderVec2{ m_Center.x, -m_Center.y };

  auto texture_space = offset; 
  return texture_space;
}

RenderVec2 TextureViewerWidget::TransformFromClipSpaceToScreenSpace(RenderVec2 clip_space)
{
  clip_space.y *= -1.0f;
  auto texture_space = ((clip_space + RenderVec2(1.0f, 1.0f) * 0.5f)) * RenderVec2(width(), height());
  return texture_space;
}

RenderVec2 TextureViewerWidget::TransformFromScreenSpaceToClipSpace(RenderVec2 screen_space)
{
  auto clip_space = ((screen_space / RenderVec2(width(), height())) * 2.0f) - RenderVec2(1.0f, 1.0f);
  clip_space.y *= -1.0f;
  return clip_space;
}

RenderVec2 TextureViewerWidget::TransformFromTextureSpaceToScreenSpace(RenderVec2 texture_space)
{
  auto clip_space = TransformFromTextureSpaceToClipSpace(texture_space);
  return TransformFromClipSpaceToScreenSpace(clip_space);
}

RenderVec2 TextureViewerWidget::TransformFromScreenSpaceToTextureSpace(RenderVec2 screen_space)
{
  auto clip_space = TransformFromScreenSpaceToClipSpace(screen_space);
  return TransformFromClipSpaceToTextureSpace(clip_space);
}

void TextureViewerWidget::initializeGL()
{
  m_RenderState.InitRenderState(width(), height());

  m_GridShader = MakeQuickShaderProgram(kTextureViewerWidgetGridVertexShader, kTextureViewerWidgetGridFragmentShader);
}

void TextureViewerWidget::resizeGL(int w, int h)
{
  m_RenderState.SetScreenSize(Vector2(w, h));
  m_RenderState.SetRenderSize(Vector2(w, h));
}

void TextureViewerWidget::paintGL()
{
  QColor clear_color_qt = palette().color(QPalette::Window);
  Color color(clear_color_qt.red(), clear_color_qt.green(), clear_color_qt.blue(), 255);

  glClearColor(color.r, color.g, color.b, color.a);
  glClear(GL_COLOR_BUFFER_BIT);

  m_RenderState.MakeCurrent();

  TextureAsset * asset = m_TextureAsset.Get();
  if (asset && asset->IsLoaded())
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
    shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Matrix"), RenderVec4{ m_Magnification.Get(), 0, 0, m_Magnification.Get() });
    shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Texture"), 0);
    shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Color"), RenderVec4{ 1, 1, 1, 1 });
    shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Bounds"), RenderVec4{ -1, -1, 1, 1 });
    shader.SetUniform(COMPILE_TIME_CRC32_STR("u_ColorMatrix"), Mat4f());

    m_RenderState.Draw();


    if (m_GridWidth != 0 && m_GridHeight != 0)
    {
      RenderVec2 window_start = TransformFromScreenSpaceToTextureSpace(RenderVec2(0, 0));
      RenderVec2 window_end = TransformFromScreenSpaceToTextureSpace(RenderVec2(width() - 1, height() - 1));

      GeometryVertexBufferBuilder vertex_builder;

      auto x_start = floorf(window_start.x / m_GridWidth) * m_GridWidth;
      auto x_end = (floorf(window_end.x / m_GridWidth) + 1) * m_GridWidth;

      x_start = std::max(x_start, 0.0f);
      x_end = std::min(x_end, (float)asset->GetWidth());
      
      auto y_start = floorf(window_start.y / m_GridHeight) * m_GridHeight;
      auto y_end = (floorf(window_end.y / m_GridHeight) + 1) * m_GridHeight;

      y_start = std::max(y_start, 0.0f);
      y_end = std::min(y_end, (float)asset->GetHeight()); 

      for (float x = x_start; x <= x_end; x += m_GridWidth)
      {
        auto start = TransformFromTextureSpaceToClipSpace(RenderVec2{ x, y_start });
        auto end = TransformFromTextureSpaceToClipSpace(RenderVec2{ x, y_end });

        vertex_builder.Line(start, end, 6.0f / width(), Color(0.0f, 0.0f, 0.0f, 1.0f));
        vertex_builder.Line(start, end, 2.0f / width(), Color(1.0f, 1.0f, 1.0f, 1.0f));
      }

      for (float y = y_start; y <= y_end; y += m_GridHeight)
      {
        auto start = TransformFromTextureSpaceToClipSpace(RenderVec2{ x_start, y });
        auto end = TransformFromTextureSpaceToClipSpace(RenderVec2{ x_end, y });

        vertex_builder.Line(start, end, 6.0f / height(), Color(0.0f, 0.0f, 0.0f, 1.0f));
        vertex_builder.Line(start, end, 2.0f / height(), Color(1.0f, 1.0f, 1.0f, 1.0f));
      }

      m_RenderState.EnableBlendMode();

      vertex_builder.FillVertexBuffer(m_GridBuffer);

      m_RenderState.BindShader(m_GridShader);
      m_RenderState.BindVertexBuffer(m_GridBuffer);
      m_RenderState.Draw();

      m_RenderState.DisableBlendMode();
    }

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

void TextureViewerWidget::mousePressEvent(QMouseEvent * event)
{
  if (event->button() != Qt::LeftButton)
  {
    return;
  }

  m_CursorPos = QCursor::pos();
  m_Dragging = true;

  grabMouse();
}

void TextureViewerWidget::mouseMoveEvent(QMouseEvent *event)
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

void TextureViewerWidget::mouseReleaseEvent(QMouseEvent * event)
{
  if (event->button() != Qt::LeftButton)
  {
    return;
  }

  releaseMouse();
  m_Dragging = false;
}

void TextureViewerWidget::wheelEvent(QWheelEvent *event)
{
  if (event->angleDelta().y() < 0)
  {
    m_Magnification *= 0.8f;
  }
  else
  {
    m_Magnification *= 1.25f;
  }
}

void TextureViewerWidget::tick()
{
  repaint();
}

void TextureViewerWidget::HandleTextureLoad(TextureAsset * asset)
{

}
