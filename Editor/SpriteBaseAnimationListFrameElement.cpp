
#include <QPainter>

#include "StormData/StormDataPath.h"

#include "SpriteBaseAnimationListFrameElement.h"
#include "SpriteBaseEditor.h"

#include "PropertyEditorWidget.h"

SpriteBaseAnimationListFrameElement::SpriteBaseAnimationListFrameElement(NotNullPtr<SpriteBaseEditor> editor, SpriteBaseDef & sprite, SpriteBaseTextureLoadList & texture_access,
  std::size_t animation_index, std::size_t frame_index) :
  m_Editor(editor),
  m_Sprite(sprite),
  m_TextureAccess(texture_access),
  m_AnimationIndex(animation_index),
  m_FrameIndex(frame_index),
  m_FrameDurationLabel(std::make_unique<QLabel>("Duration:", this))
{
  setMinimumHeight(60);

  m_UpdateDelegateLink = m_TextureAccess.AddUpdateCallback([this] { update(); });

  m_FrameDuration = PropertyEditorCreate(m_Editor, m_Editor->GetPropertyFieldDatabase().GetBasicSignedField(4),
    [this]()-> void * { auto anim = m_Sprite.m_Animations.TryGet(m_AnimationIndex); if (!anim) return nullptr; 
                        auto frame = anim->m_Frames.TryGet(m_FrameIndex); return frame ? &frame->m_FrameDuration : nullptr; },
    StormDataGetPath(m_Sprite.m_Animations[m_AnimationIndex].m_Frames[m_FrameIndex].m_FrameDuration), {}, "Duration", this);

  m_FrameDurationLabel->setGeometry(65, 2, 100, 20);
  m_FrameDuration->setGeometry(125, 2, 150, 20);
}

SpriteBaseAnimationListFrameElement::~SpriteBaseAnimationListFrameElement()
{

}

void SpriteBaseAnimationListFrameElement::paintEvent(QPaintEvent * ev)
{
  QPainter p(this);

  if (m_Sprite.m_Animations.HasAt(m_AnimationIndex) == false)
  {
    return;
  }

  auto & frames = m_Sprite.m_Animations[m_AnimationIndex].m_Frames;
  if (frames.HighestIndex() < 0)
  {
    return;
  }

  auto frame = frames.TryGet(m_FrameIndex);
  if (frame == nullptr)
  {
    return;
  }

  int src_x, src_y, src_w, src_h;
  auto img = m_TextureAccess.GetFrameAndImage(frame->m_FrameId, src_x, src_y, src_w, src_h);

  if (img)
  {
    p.drawImage(QRect(0, 0, 60, 60), img.Value(), QRect(src_x, src_y, src_w, src_h));
  }
}

void SpriteBaseAnimationListFrameElement::mousePressEvent(QMouseEvent * ev)
{

}
