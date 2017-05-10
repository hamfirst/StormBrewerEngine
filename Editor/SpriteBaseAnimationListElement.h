#pragma once

#include <memory>

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QTimer>

#include "Runtime/SpriteBase/SpriteBaseDef.refl.h"

#include "SpriteBaseTextureLoadList.h"
#include "GenericListFrame.h"

class SpriteBaseEditor;
class SpriteBaseTimelineElement;

class GenericList;

class SpriteBaseAnimationListElement : public QWidget
{
  Q_OBJECT;
public:
  SpriteBaseAnimationListElement(NotNullPtr<SpriteBaseEditor> editor, SpriteBaseDef & sprite, SpriteBaseTextureLoadList & texture_access, std::size_t animation_index);
  ~SpriteBaseAnimationListElement();

  void SetSizeChangeCallback(Delegate<void> && callback);
  void SetOpenEditorCallback(Delegate<void> && callback);
  void SetRemoveCallback(Delegate<void> && callback);
protected:

  void HandleFrameListChanged();

  void paintEvent(QPaintEvent * ev) override;
  void resizeEvent(QResizeEvent * ev) override;
  void mousePressEvent(QMouseEvent * ev) override;

public slots:

  void editFrames();
  void remove();
  void updateTimer();

private:
  NotNullPtr<SpriteBaseEditor> m_Editor;
  SpriteBaseDef & m_Sprite;
  SpriteBaseTextureLoadList & m_TextureAccess;
  std::size_t m_AnimationIndex;

  Delegate<void> m_SizeChangedCallback;
  Delegate<void> m_EditCallback;
  Delegate<void> m_RemoveCallback;

  std::unique_ptr<GenericListFrame> m_FrameListContainer;
  GenericList * m_FrameList;

  std::unique_ptr<QLabel> m_AnimNameLabel;
  std::unique_ptr<QWidget> m_AnimName;

  std::unique_ptr<QPushButton> m_EditFrames;
  std::unique_ptr<QPushButton> m_Delete;

  DelegateLink<void> m_UpdateDelegateLink;
  bool m_ShowFrameList;

  std::unique_ptr<QTimer> m_Timer;
  int m_AnimFrame;
  int m_AnimFrameDelay;

};
