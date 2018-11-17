#pragma once

#include <memory>

#include <QWidget>
#include <QLabel>
#include <QLineEdit>

#include "Runtime/SpriteBase/SpriteBaseDef.refl.h"

#include "SpriteBaseTextureLoadList.h"

class SpriteBaseEditor;
class SpriteBaseTimelineElement;

class SpriteBaseAnimationListFrameElement : public QWidget
{
  Q_OBJECT;
public:
  SpriteBaseAnimationListFrameElement(NotNullPtr<SpriteBaseEditor> editor, SpriteBaseDef & sprite, SpriteBaseTextureLoadList & texture_access, 
    std::size_t animation_index, std::size_t frame_index);
  ~SpriteBaseAnimationListFrameElement();

protected:

  void paintEvent(QPaintEvent * ev);
  void mousePressEvent(QMouseEvent * ev);

private:
  NotNullPtr<SpriteBaseEditor> m_Editor;
  SpriteBaseDef & m_Sprite;
  SpriteBaseTextureLoadList & m_TextureAccess;
  std::size_t m_AnimationIndex;
  std::size_t m_FrameIndex;

  std::unique_ptr<QLabel> m_FrameDurationLabel;
  std::unique_ptr<QWidget> m_FrameDuration;

  DelegateLink<void> m_UpdateDelegateLink;
};
