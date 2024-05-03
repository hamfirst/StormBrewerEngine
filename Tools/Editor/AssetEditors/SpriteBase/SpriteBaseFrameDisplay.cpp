
#include <QPainter>
#include <QMouseEvent>
#include <QStyle>
#include <QStyleOptionFocusRect>

#include "StormData/StormDataPath.h"

#include "SpriteBaseFrameDisplay.h"
#include "SpriteBaseEditor.h"

#include "Tools/Editor/UI/PropertyEditors/PropertyEditorWidget.h"

SpriteBaseFrameDisplay::SpriteBaseFrameDisplay(NotNullPtr<SpriteBaseEditor> editor, SpriteBaseDef & sprite, SpriteBaseTextureLoadList & texture_access, QWidget * parent) :
  QWidget(parent),
  m_Editor(editor),
  m_Sprite(sprite),
  m_TextureAccess(texture_access),
  m_AnimationIndex(0),
  m_FrameIndex(0),
  m_Dragging(false),
  m_Start(0, 0),
  m_Offset(0, 0),
  m_Magnification(2)
{
  setMinimumHeight(60);

  m_UpdateLink = m_TextureAccess.AddUpdateCallback([this] {update(); });
}

SpriteBaseFrameDisplay::~SpriteBaseFrameDisplay()
{

}

void SpriteBaseFrameDisplay::SetAnimation(std::size_t animation_index)
{
  m_AnimationIndex = animation_index;
  update();
}

void SpriteBaseFrameDisplay::SetFrame(std::size_t frame_index)
{
  m_FrameIndex = frame_index;
  update();
}

void SpriteBaseFrameDisplay::paintEvent(QPaintEvent * ev)
{
  QPainter p(this);

  QStyleOptionFrame option;
  option.initFrom(this);

  style()->drawPrimitive(QStyle::PE_Frame, &option, &p, this);

  auto anim_info = m_Sprite.m_Animations.TryGet(m_AnimationIndex);
  if (anim_info == nullptr)
  {
    return;
  }

  auto frame = anim_info->m_Frames.TryGet(m_FrameIndex);
  if (frame == nullptr)
  {
    return;
  }

  auto frame_id = (uint64_t)frame->m_FrameId;

  int src_x, src_y, src_w, src_h;
  auto img = m_TextureAccess.GetFrameAndImage(frame_id, src_x, src_y, src_w, src_h);
  if (img.IsValid() == false)
  {
    return;
  }

  auto src_rect = QRect(src_x, src_y, src_w, src_h);
  auto midpoint = Vector2(width(), height()) / 2;
  auto img_size = Vector2(src_w, src_h) * m_Magnification;
  auto start = midpoint - img_size / 2;
  auto end = start + img_size;
  start += m_Offset;
  end += m_Offset;

  auto dst_rect = QRect(start.x, start.y, end.x - start.x, end.y - start.y);

  p.drawImage(dst_rect, img.Value(), src_rect);
}

void SpriteBaseFrameDisplay::wheelEvent(QWheelEvent * ev)
{
  if (ev->angleDelta().y() < 0)
  {
    if (m_Magnification > 1)
    {
      m_Magnification--;
    }
  }
  else
  {
    m_Magnification++;
  }

  update();
}

void SpriteBaseFrameDisplay::mousePressEvent(QMouseEvent * ev)
{
  m_Dragging = true;
  m_Start = Vector2(ev->x(), ev->y());

  grabMouse();
}

void SpriteBaseFrameDisplay::mouseReleaseEvent(QMouseEvent * ev)
{
  releaseMouse();
}

void SpriteBaseFrameDisplay::mouseMoveEvent(QMouseEvent * ev)
{
  auto pos = Vector2(ev->x(), ev->y());
  m_Offset += Vector2f(pos - m_Start);

  m_Start = pos;
  update();
}

