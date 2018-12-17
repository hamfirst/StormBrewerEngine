
#include <QPainter>
#include <QWheelEvent>
#include <QApplication>
#include <QOpenGLContext>
#include <QOpenGLFunctions>

#include "StormData/StormDataPath.h"

#include "Engine/Shader/ShaderManager.h"
#include "Engine/Sprite/SpriteEngineData.h"

#include "GeometryEditorBase.h"
#include "FrameEditorUtil.h"
#include "SpriteEditor.h"
#include "DrawUtil.h"

GeometryEditorBase::GeometryEditorBase(
        QWidget * parent) :
        QOpenGLWidget(parent),
        m_VertexBuffer(true)
{
  setFocusPolicy(Qt::ClickFocus);
  setMouseTracking(true);
}

void GeometryEditorBase::SyncMouse()
{
  bool should_have_mouse = m_Panning || m_Dragging;
  if (should_have_mouse && m_HasMouse == false)
  {
    grabMouse();
    m_HasMouse = true;
  }
  else if (should_have_mouse == false && m_HasMouse)
  {
    releaseMouse();
    m_HasMouse = false;
  }
}

void GeometryEditorBase::SyncDraw()
{
  auto p = QCursor::pos();
  Vector2 pos = Vector2(p.x(), p.y());

  if (m_Dragging)
  {
    DrawMove(pos,
             (QApplication::keyboardModifiers() & Qt::AltModifier) != 0,
             (QApplication::keyboardModifiers() & Qt::ShiftModifier) != 0,
             (QApplication::keyboardModifiers() & Qt::ControlModifier) != 0);
  }
  else
  {
    DrawPreview(pos,
                (QApplication::keyboardModifiers() & Qt::AltModifier) != 0,
                (QApplication::keyboardModifiers() & Qt::ShiftModifier) != 0,
                (QApplication::keyboardModifiers() & Qt::ControlModifier) != 0);
  }
}



Optional<Vector2> GeometryEditorBase::GetFrameSize()
{
  return {};
}

uint64_t GeometryEditorBase::GetFrameId()
{
  return 0;
}

NullOptPtr<TextureAsset> GeometryEditorBase::GetTexture()
{
  return nullptr;
}

Vector2 GeometryEditorBase::TransformScreenToFrame(const Vector2 & pos)
{
  auto p = pos;

  auto half_window_size = Vector2(width() / 2, height() / 2);
  p -= half_window_size;

  p.y *= -1;
  p /= m_Magnification;
  p.x += (int)m_Center.x;
  p.y += (int)m_Center.y;

  return p;
}

Vector2 GeometryEditorBase::TransformFrameToScreen(const Vector2 & pos)
{
  auto p = pos;

  p.x -= (int)m_Center.x;
  p.y -= (int)m_Center.y;

  p *= m_Magnification;
  p.y *= -1;

  auto half_window_size = Vector2(width() / 2, height() / 2);
  p += half_window_size;
  return p;
}

void GeometryEditorBase::DrawBox(const Box & box)
{
  DrawUtil::DrawBox(m_GeometryBuidler.Value(), box);
}

void GeometryEditorBase::DrawActionBox(const Box & box)
{
  DrawUtil::DrawActionBox(m_GeometryBuidler.Value(), box);
}

void GeometryEditorBase::DrawEdge(const FrameEditorEdge & edge)
{
  DrawUtil::DrawEdge(m_GeometryBuidler.Value(), edge, m_Magnification);
}

void GeometryEditorBase::DrawHighlightedEdge(const FrameEditorEdge & edge)
{
  DrawUtil::DrawHighlightedEdge(m_GeometryBuidler.Value(), edge, m_Magnification);
}

void GeometryEditorBase::DrawLine(const Vector2 & a, const Vector2 & b)
{
  DrawUtil::DrawLine(m_GeometryBuidler.Value(), a, b, m_Magnification);
}

void GeometryEditorBase::DrawHighlightedLine(const Vector2 & a, const Vector2 & b)
{
  DrawUtil::DrawHighlightedLine(m_GeometryBuidler.Value(), a, b, m_Magnification);
}

void GeometryEditorBase::DrawCornerControl(const Vector2 & pos)
{
  DrawUtil::DrawCornerControl(m_GeometryBuidler.Value(), pos, m_Magnification);
}

void GeometryEditorBase::DrawHighlightedCornerControl(const Vector2 & pos)
{
  DrawUtil::DrawHighlightedCornerControl(m_GeometryBuidler.Value(), pos, m_Magnification);
}

void GeometryEditorBase::DrawData()
{

}

void GeometryEditorBase::DrawPreview(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{

}

void GeometryEditorBase::DrawLeave()
{

}

bool GeometryEditorBase::DrawStart(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  return false;
}

void GeometryEditorBase::DrawMove(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{

}

void GeometryEditorBase::DrawEnd(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{

}

void GeometryEditorBase::DrawCancel()
{

}

void GeometryEditorBase::StopDrawing()
{
  if (m_Dragging)
  {
    DrawCancel();
    m_Dragging = false;
    SyncMouse();
  }
}

void GeometryEditorBase::Copy()
{

}

void GeometryEditorBase::Paste()
{

}

void GeometryEditorBase::initializeGL()
{
  m_RenderState.InitRenderState(width(), height());
  m_RenderUtil.LoadShaders();

  m_Shader = DrawUtil::CreateShader();
}

void GeometryEditorBase::resizeGL(int w, int h)
{
  m_RenderState.SetScreenSize(Vector2(w, h));
  m_RenderState.SetRenderSize(Vector2(w, h));
}

void GeometryEditorBase::paintGL()
{
  QColor clear_color_qt = palette().color(QPalette::Window);
  Color color(clear_color_qt.red(), clear_color_qt.green(), clear_color_qt.blue(), 255);

  auto f = context()->functions();

  f->glClearColor(color.r, color.g, color.b, color.a);
  f->glClear(GL_COLOR_BUFFER_BIT);

  auto frame_size = GetFrameSize();
  auto frame_id = GetFrameId();
  auto texture = GetTexture();

  if(texture == nullptr)
  {
    return;
  }

  Vector2 texture_size = texture->GetSize();
  Box border_rect;

  if (texture_size.x == 0 || texture_size.y == 0)
  {
    return;
  }

  RenderVec4 matrix = RenderVec4{1.0f, 0.0f, 0.0f, 1.0f};
  if (m_MirrorX)
  {
    matrix.x *= -1.0f;
  }

  if (m_MirrorY)
  {
    matrix.w *= -1.0f;
  }

  auto screen_start = TransformScreenToFrame(Vector2(0, 0));
  auto screen_end = TransformScreenToFrame(Vector2(width() - 1, height() - 1));

  RenderVec2 resolution{width(), height()};
  resolution /= m_Magnification;

  m_RenderState.MakeCurrent();
  m_RenderState.EnableBlendMode();

  auto & shader = g_ShaderManager.GetDefaultScreenSpaceShader();

  RenderVec2 center = m_Center;
  center *= -1.0f;

  m_RenderState.BindShader(shader);
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_ScreenSize"), RenderVec2{ m_RenderState.GetRenderSize() });
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Color"), Color(255, 255, 255, 200));
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_ScreenSize"), resolution);
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Offset"), center);
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Matrix"), matrix);
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Texture"), 0);
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Bounds"), RenderVec4{ -1, -1, 1, 1 });
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_ColorMatrix"), Mat4f());

  m_RenderState.BindTexture(*texture);
  QuadVertexBufferBuilder builder;

  if(frame_size)
  {
    Box frame_box = Box::FromFrameCenterAndSize(Vector2{}, *frame_size);
    border_rect = frame_box;

    builder.AddFrame(frame_box, texture_size, *frame_size, frame_id & 0xFFFF, Color(255, 255, 255, 255));
    builder.FillVertexBuffer(m_VertexBuffer);
  }
  else
  {
    Box texture_box = Box::FromFrameCenterAndSize(Vector2{}, texture_size);
    border_rect = texture_box;

    QuadVertexBuilderInfo quad;

    quad.m_Position = texture_box;
    quad.m_TexCoords = Box::FromPoints({}, texture_size);
    quad.m_TextureSize = texture->GetSize();
    quad.m_Color = Color(255, 255, 255, 255);
    builder.AddQuad(quad);
  }


  builder.FillVertexBuffer(m_VertexBuffer);

  m_RenderState.BindVertexBuffer(m_VertexBuffer);
  m_RenderState.Draw();

  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Color"), Color(255, 255, 255, 255));
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Matrix"), RenderVec4{1.0f, 0.0f, 0.0f, 1.0f});

  LineVertexBufferBuilder line_builder;
  LineVertexBuilderInfo line;
  line.m_TextureSize = Vector2(1, 1);

  if (m_Magnification >= 4)
  {
    for (int x = screen_start.x - 1; x <= screen_end.x + 1; x++)
    {
      line.m_Start.x = x;
      line.m_Start.y = screen_start.y + 1;
      line.m_End.x = x;
      line.m_End.y = screen_end.y - 1;
      line.m_Color = Color(128, 128, 128, 50);
      line_builder.AddLine(line);
    }

    for (int y = screen_end.y - 1; y <= screen_start.y + 1; y++)
    {
      line.m_Start.x = screen_start.x - 1;
      line.m_Start.y = y;
      line.m_End.x = screen_end.x + 1;
      line.m_End.y = y;
      line.m_Color = Color(128, 128, 128, 50);
      line_builder.AddLine(line);
    }

    for (int x = border_rect.m_Start.x; x <= border_rect.m_End.x; x++)
    {
      line.m_Start.x = x;
      line.m_Start.y = border_rect.m_Start.y;
      line.m_End.x = x;
      line.m_End.y = border_rect.m_End.y;
      line.m_Color = Color(0, 0, 0, 128);
      line_builder.AddLine(line);
    }

    for (int y = border_rect.m_Start.y; y <= border_rect.m_End.y; y++)
    {
      line.m_Start.x = border_rect.m_Start.x;
      line.m_Start.y = y;
      line.m_End.x = border_rect.m_End.x;
      line.m_End.y = y;
      line.m_Color = Color(0, 0, 0, 128);
      line_builder.AddLine(line);
    }

    m_RenderState.BindTexture(m_RenderUtil.GetDefaultTexture());

    line_builder.FillVertexBuffer(m_VertexBuffer);
    m_RenderState.BindVertexBuffer(m_VertexBuffer);
    m_RenderState.Draw();
  }

  m_RenderState.BindShader(m_Shader);
  m_Shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Color"), Color(255, 255, 255, 255));
  m_Shader.SetUniform(COMPILE_TIME_CRC32_STR("u_ScreenSize"), resolution);
  m_Shader.SetUniform(COMPILE_TIME_CRC32_STR("u_ActualScreenSize"), RenderVec2(width(), height()));
  m_Shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Offset"), RenderVec2{m_Center} * -1.0f);
  m_Shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Matrix"), RenderVec4{1.0f, 0.0f, 0.0f, 1.0f});

  m_GeometryBuidler.Emplace();
  m_GeometryBuidler->Rectangle(border_rect, 3.0f / m_Magnification, Color(0, 0, 0, 255));

  DrawData();

  m_RenderState.BindTexture(m_RenderUtil.GetDefaultTexture());

  m_GeometryBuidler->FillVertexBuffer(m_VertexBuffer);
  m_RenderState.BindVertexBuffer(m_VertexBuffer);
  m_RenderState.Draw();

  m_GeometryBuidler.Clear();
}

void GeometryEditorBase::tick()
{
  repaint();
}

void GeometryEditorBase::setMagnification(int mag)
{
  m_Magnification = mag;
}

void GeometryEditorBase::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_X)
  {
    m_MirrorX = !m_MirrorX;
    repaint();
  }

  if (event->key() == Qt::Key_Y)
  {
    m_MirrorY = !m_MirrorY;
    repaint();
  }

  if (event->key() == Qt::Key_Alt || event->key() == Qt::Key_Shift || event->key() == Qt::Key_Control)
  {
    SyncDraw();
  }
}

void GeometryEditorBase::keyReleaseEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Alt || event->key() == Qt::Key_Shift || event->key() == Qt::Key_Control)
  {
    SyncDraw();
  }
}

void GeometryEditorBase::mousePressEvent(QMouseEvent * event)
{
  bool alt = (bool)(event->modifiers() & Qt::AltModifier);
  bool shift = (bool)(event->modifiers() & Qt::ShiftModifier);
  bool ctrl = (bool)(event->modifiers() & Qt::ControlModifier);

  auto p = QCursor::pos();
  p = mapFromGlobal(p);

  if (event->button() == Qt::LeftButton)
  {

    Vector2 pos = Vector2(p.x(), p.y());

    if (DrawStart(pos, alt, shift, ctrl))
    {
      m_Dragging = true;
      SyncMouse();
    }
  }
  else if (event->button() == Qt::MiddleButton)
  {
    m_CursorPos = p;

    m_Panning = true;
    SyncMouse();
    return;
  }
  else if(event->button() == Qt::RightButton)
  {
    if (m_Dragging)
    {
      StopDrawing();
    }
  }
}

void GeometryEditorBase::mouseMoveEvent(QMouseEvent *event)
{
  auto p = QCursor::pos();
  p = mapFromGlobal(p);
  Vector2 pos = Vector2(p.x(), p.y());

  bool alt = (bool)(event->modifiers() & Qt::AltModifier);
  bool shift = (bool)(event->modifiers() & Qt::ShiftModifier);
  bool ctrl = (bool)(event->modifiers() & Qt::ControlModifier);

  if (m_Dragging)
  {
    DrawMove(pos, alt, shift, ctrl);
  }
  else
  {
    DrawPreview(pos, alt, shift, ctrl);
  }

  if (m_Panning)
  {
    auto diff_pos = p - m_CursorPos;

    m_Center.x -= (float)diff_pos.x() / m_Magnification;
    m_Center.y += (float)diff_pos.y() / m_Magnification;
    repaint();
  }

  m_CursorPos = p;
}

void GeometryEditorBase::mouseReleaseEvent(QMouseEvent * event)
{
  auto p = QCursor::pos();
  p = mapFromGlobal(p);

  bool alt = (bool)(event->modifiers() & Qt::AltModifier);
  bool shift = (bool)(event->modifiers() & Qt::ShiftModifier);
  bool ctrl = (bool)(event->modifiers() & Qt::ControlModifier);

  if (event->button() == Qt::LeftButton)
  {
    if (m_Dragging)
    {
      m_Dragging = false;
      SyncMouse();

      Vector2 pos = Vector2(p.x(), p.y());
      DrawEnd(pos, alt, shift, ctrl);
    }
  }

  if (event->button() == Qt::MiddleButton)
  {
    m_Panning = false;
    SyncMouse();
    return;
  }
}

void GeometryEditorBase::wheelEvent(QWheelEvent *event)
{
  m_WheelDelta += event->delta();
  while (m_WheelDelta < 0)
  {
    if (m_Magnification > 1)
    {
      m_Magnification -= m_Magnification / 6 + 1;
    }

    m_WheelDelta += 120;
  }

  while(m_WheelDelta > 120)
  {
    m_Magnification += m_Magnification / 6 + 1;
    m_WheelDelta -= 120;
  }

  emit magnificationChanged(m_Magnification);
  repaint();
}

void GeometryEditorBase::leaveEvent(QEvent * event)
{
  DrawLeave();
}
