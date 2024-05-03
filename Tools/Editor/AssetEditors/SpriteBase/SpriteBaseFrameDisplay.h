#pragma once

#include <QWidget>

#include "Engine/Asset/TextureAsset.h"
#include "Engine/Asset/AssetSync.h"

#include "Runtime/SpriteBase/SpriteBaseDef.refl.h"

#include "Tools/Editor/Utility/DocumentValueWatcher.h"
#include "SpriteBaseTextureLoadList.h"

class SpriteBaseEditor;
class QImage;

class SpriteBaseFrameDisplay : public QWidget
{
  Q_OBJECT;
public:
  SpriteBaseFrameDisplay(NotNullPtr<SpriteBaseEditor> editor, SpriteBaseDef & sprite, SpriteBaseTextureLoadList & texture_access, QWidget * parent = nullptr);
  ~SpriteBaseFrameDisplay();

  void SetAnimation(std::size_t animation_index);
  void SetFrame(std::size_t frame_index);

protected:

  void paintEvent(QPaintEvent * ev) override;
  void wheelEvent(QWheelEvent * ev) override;
  void mousePressEvent(QMouseEvent * ev) override;
  void mouseReleaseEvent(QMouseEvent * ev) override;
  void mouseMoveEvent(QMouseEvent * ev) override;

private:
  NotNullPtr<SpriteBaseEditor> m_Editor;
  SpriteBaseDef & m_Sprite;
  SpriteBaseTextureLoadList & m_TextureAccess;
  std::size_t m_AnimationIndex;
  std::size_t m_FrameIndex;

  DelegateLink<void> m_UpdateLink;

  bool m_Dragging;
  Vector2 m_Start;
  Vector2f m_Offset;
  int m_Magnification;
};


