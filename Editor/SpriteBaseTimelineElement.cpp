
#include <QPainter>

#include "SpriteBaseTimelineElement.h"
#include "SpriteBaseEditor.h"
#include "SpriteBaseTextureLoadList.h"

SpriteBaseTimelineElement::SpriteBaseTimelineElement(NotNullPtr<SpriteBaseEditor> editor, 
  SpriteBaseDef & sprite, SpriteBaseTextureLoadList & texture_access, uint64_t frame_id, QWidget * parent) :
  m_Editor(editor),
  m_Sprite(sprite),
  m_TextureAccess(texture_access),
  m_FrameId(frame_id),
  m_RemoveButton(std::make_unique<QPushButton>("-", this))
{
  m_UpdateDelegateLink = m_TextureAccess.AddUpdateCallback([this] { update(); });

  connect(m_RemoveButton.get(), &QPushButton::pressed, this, &SpriteBaseTimelineElement::removePressed);
}

SpriteBaseTimelineElement::~SpriteBaseTimelineElement()
{

}

void SpriteBaseTimelineElement::SetRemoveCallback(Delegate<void> && callback)
{
  m_RemoveDelegate = std::move(callback);
}

void SpriteBaseTimelineElement::SetClickCallback(Delegate<void> && callback)
{
  m_ClickDelegate = std::move(callback);
}

QSize SpriteBaseTimelineElement::sizeHint() const
{
  return QSize(120, 120);
}

void SpriteBaseTimelineElement::resizeEvent(QResizeEvent * ev)
{
  m_RemoveButton->setGeometry(width() - 16, 1, 15, 15);
}

void SpriteBaseTimelineElement::paintEvent(QPaintEvent * ev)
{
  QPainter p(this);

  int src_x, src_y, src_w, src_h;
  auto img = m_TextureAccess.GetFrameAndImage(m_FrameId, src_x, src_y, src_w, src_h);

  if (img)
  {
    p.drawImage(QRect(0, 0, width(), height()), img.Value(), QRect(src_x, src_y, src_w, src_h));
  }
}

void SpriteBaseTimelineElement::mousePressEvent(QMouseEvent * ev)
{
  m_ClickDelegate();
}

void SpriteBaseTimelineElement::removePressed()
{
  m_RemoveDelegate();
}
