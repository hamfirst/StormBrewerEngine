
#include <QPainter>
#include <QWheelEvent>
#include <QApplication>

#include "StormData/StormDataPath.h"

#include "Engine/Shader/ShaderManager.h"
#include "Engine/Sprite/SpriteEngineData.h"

#include "FrameEditorBase.h"
#include "FrameEditorUtil.h"
#include "SpriteEditor.h"
#include "DrawUtil.h"

FrameEditorBase::FrameEditorBase(
  NotNullPtr<SpriteBaseEditor> editor,
  SpriteBaseDef & sprite,
  SpriteBaseTextureLoadList & texture_access,
  uint64_t frame_id,
  QWidget * parent) :
  QOpenGLWidget(parent),
  m_Editor(editor),
  m_Sprite(sprite),
  m_TextureAccess(texture_access),
  m_FrameId(frame_id),
  m_VertexBuffer(true)
{
  setFocusPolicy(Qt::ClickFocus);
  setMouseTracking(true);

  UpdateFrameSize();
}

void FrameEditorBase::SyncMouse()
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

void FrameEditorBase::SyncDraw()
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

void FrameEditorBase::UpdateFrameSize()
{
  m_FrameWidth = 0;
  m_FrameHeight = 0;

  if (m_Sprite.m_Textures.HighestIndex() == -1)
  {
    return;
  }

  auto default_texture = m_Sprite.m_Textures.begin();
  SpriteBaseDefTexture * texture_info = &default_texture->second;

  uint32_t texture_hash = m_FrameId >> 32;

  for (auto texture : m_Sprite.m_Textures)
  {
    if (texture_hash == crc32(texture.second.m_Filename))
    {
      texture_info = &texture.second;
    }
  }

  m_FrameWidth = texture_info->m_FrameWidth;
  m_FrameHeight = texture_info->m_FrameHeight;
};


Vector2 FrameEditorBase::TransformScreenToFrame(const Vector2 & pos)
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

Vector2 FrameEditorBase::TransformFrameToScreen(const Vector2 & pos)
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

void FrameEditorBase::DrawBox(const Box & box)
{
  DrawUtil::DrawBox(m_GeometryBuidler.Value(), box);
}

void FrameEditorBase::DrawActionBox(const Box & box)
{
  DrawUtil::DrawActionBox(m_GeometryBuidler.Value(), box);
}

void FrameEditorBase::DrawEdge(const FrameEditorEdge & edge)
{
  DrawUtil::DrawEdge(m_GeometryBuidler.Value(), edge, m_Magnification);
}

void FrameEditorBase::DrawHighlightedEdge(const FrameEditorEdge & edge)
{
  DrawUtil::DrawHighlightedEdge(m_GeometryBuidler.Value(), edge, m_Magnification);
}

void FrameEditorBase::DrawLine(const Vector2 & a, const Vector2 & b)
{
  DrawUtil::DrawLine(m_GeometryBuidler.Value(), a, b, m_Magnification);
}

void FrameEditorBase::DrawHighlightedLine(const Vector2 & a, const Vector2 & b)
{
  DrawUtil::DrawHighlightedLine(m_GeometryBuidler.Value(), a, b, m_Magnification);
}

void FrameEditorBase::DrawCornerControl(const Vector2 & pos)
{
  DrawUtil::DrawCornerControl(m_GeometryBuidler.Value(), pos, m_Magnification);
}

void FrameEditorBase::DrawHighlightedCornerControl(const Vector2 & pos)
{
  DrawUtil::DrawHighlightedCornerControl(m_GeometryBuidler.Value(), pos, m_Magnification);
}

void FrameEditorBase::DrawData()
{

}

void FrameEditorBase::DrawPreview(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{

}

void FrameEditorBase::DrawLeave()
{

}

bool FrameEditorBase::DrawStart(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  return false;
}

void FrameEditorBase::DrawMove(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{

}

void FrameEditorBase::DrawEnd(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{

}

void FrameEditorBase::DrawCancel()
{

}

void FrameEditorBase::StopDrawing()
{
  if (m_Dragging)
  {
    DrawCancel();
    m_Dragging = false;
    SyncMouse();
  }
}

void FrameEditorBase::SetFrame(uint64_t frame_id)
{
  m_FrameId = frame_id;
  UpdateFrameSize();
  repaint();
}

void FrameEditorBase::initializeGL()
{
  m_RenderState.InitRenderState(width(), height());
  m_RenderUtil.LoadShaders();

  m_Shader = DrawUtil::CreateShader();
}

void FrameEditorBase::resizeGL(int w, int h)
{
  m_RenderState.SetScreenSize(Vector2(w, h));
  m_RenderState.SetRenderSize(Vector2(w, h));
}

void FrameEditorBase::paintGL()
{
  QColor clear_color_qt = palette().color(QPalette::Window);
  Color color(clear_color_qt.red(), clear_color_qt.green(), clear_color_qt.blue(), 255);

  glClearColor(color.r, color.g, color.b, color.a);
  glClear(GL_COLOR_BUFFER_BIT);

  if (m_Sprite.m_Textures.HighestIndex() == -1)
  {
    return;
  }

  uint32_t texture_hash = m_FrameId >> 32;

  auto default_texture = m_Sprite.m_Textures.begin();
  SpriteBaseDefTexture * texture_info = &default_texture->second;
  std::size_t texture_index = default_texture->first;

  for (auto texture : m_Sprite.m_Textures)
  {
    if (texture_hash == crc32(texture.second.m_Filename))
    {
      texture_index = texture.first;
      texture_info = &texture.second;
    }
  }

  auto texture = m_TextureAccess.GetTexture(texture_index);

  if (texture == nullptr)
  {
    return;
  }

  Vector2 frame_size = { texture_info->m_FrameWidth, texture_info->m_FrameHeight };
  Vector2 texture_size = texture->GetSize();

  if (frame_size.x == 0 || frame_size.y == 0 || texture_size.x == 0 || texture_size.y == 0)
  {
    return;
  }

  m_RenderState.EnableBlendMode();

  Box frame_box = Box::FromFrameCenterAndSize(Vector2{}, frame_size);

  RenderVec2 resolution{ width(), height() };
  resolution /= m_Magnification;

  auto screen_start = TransformScreenToFrame(Vector2(0, 0));
  auto screen_end = TransformScreenToFrame(Vector2(width() - 1, height() - 1));

  LineVertexBufferBuilder line_builder;
  LineVertexBuilderInfo line;
  line.m_TextureSize = Vector2(1, 1);

  RenderVec4 matrix = RenderVec4{ 1.0f, 0.0f, 0.0f, 1.0f };
  if (m_MirrorX)
  {
    matrix.x *= -1.0f;
  }

  if (m_MirrorY)
  {
    matrix.w *= -1.0f;
  }

  auto & default_shader = g_ShaderManager.GetDefaultScreenSpaceShader();
  m_RenderState.BindShader(default_shader);
  default_shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Color"), Color(255, 255, 255, 200));
  default_shader.SetUniform(COMPILE_TIME_CRC32_STR("u_ScreenSize"), resolution);
  default_shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Offset"), RenderVec2{ m_Center } * -1.0f);
  default_shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Matrix"), matrix);

  m_RenderState.BindTexture(*texture);

  QuadVertexBufferBuilder builder;
  builder.AddFrame(frame_box, texture_size, frame_size, m_FrameId & 0xFFFF, Color(255, 255, 255, 255));
  builder.FillVertexBuffer(m_VertexBuffer);

  m_RenderState.BindVertexBuffer(m_VertexBuffer);
  m_RenderState.Draw();

  frame_box.m_End += Vector2(1, 1);
  default_shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Color"), Color(255, 255, 255, 255));
  default_shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Matrix"), RenderVec4{ 1.0f, 0.0f, 0.0f, 1.0f });

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


    for (int x = frame_box.m_Start.x; x <= frame_box.m_End.x; x++)
    {
      line.m_Start.x = x;
      line.m_Start.y = frame_box.m_Start.y;
      line.m_End.x = x;
      line.m_End.y = frame_box.m_End.y;
      line.m_Color = Color(0, 0, 0, 128);
      line_builder.AddLine(line);
    }

    for (int y = frame_box.m_Start.y; y <= frame_box.m_End.y; y++)
    {
      line.m_Start.x = frame_box.m_Start.x;
      line.m_Start.y = y;
      line.m_End.x = frame_box.m_End.x;
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
  m_Shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Offset"), RenderVec2{ m_Center } *-1.0f);
  m_Shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Matrix"), RenderVec4{ 1.0f, 0.0f, 0.0f, 1.0f });

  m_GeometryBuidler.Emplace();
  m_GeometryBuidler->Rectangle(frame_box.m_Start, frame_box.m_End, 3.0f / m_Magnification, Color(0, 0, 0, 255));

  DrawData();

  m_RenderState.BindTexture(m_RenderUtil.GetDefaultTexture());

  m_GeometryBuidler->FillVertexBuffer(m_VertexBuffer);
  m_RenderState.BindVertexBuffer(m_VertexBuffer);
  m_RenderState.Draw();

  m_GeometryBuidler.Clear();
}

void FrameEditorBase::tick()
{
  repaint();

  UpdateFrameSize();
}

void FrameEditorBase::keyPressEvent(QKeyEvent * event)
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

void FrameEditorBase::keyReleaseEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Alt || event->key() == Qt::Key_Shift || event->key() == Qt::Key_Control)
  {
    SyncDraw();
  }
}

void FrameEditorBase::mousePressEvent(QMouseEvent * event)
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

void FrameEditorBase::mouseMoveEvent(QMouseEvent *event)
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

void FrameEditorBase::mouseReleaseEvent(QMouseEvent * event)
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
      Vector2 pos = Vector2(p.x(), p.y());
      DrawEnd(pos, alt, shift, ctrl);
      m_Dragging = false;
      SyncMouse();
    }
  }

  if (event->button() == Qt::MiddleButton)
  {
    m_Panning = false;
    SyncMouse();
    return;
  }
}

void FrameEditorBase::wheelEvent(QWheelEvent *event)
{
  if (event->delta() < 0)
  {
    if (m_Magnification > 1)
    {
      m_Magnification -= m_Magnification / 6 + 1;
    }
  }
  else
  {
    m_Magnification += m_Magnification / 6 + 1;
  }

  repaint();
}

void FrameEditorBase::leaveEvent(QEvent * event)
{
  DrawLeave();
}
