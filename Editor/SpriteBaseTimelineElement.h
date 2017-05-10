#pragma once

#include <QWidget>
#include <QPushButton>

#include "Foundation/Delegate/DelegateLink.h"

#include "Runtime/Sprite/SpriteDef.refl.h"


class SpriteBaseEditor;
class SpriteBaseTextureLoadList;

class SpriteBaseTimelineElement : public QWidget
{
public:
  SpriteBaseTimelineElement(NotNullPtr<SpriteBaseEditor> editor, SpriteBaseDef & sprite, SpriteBaseTextureLoadList & texture_access, uint64_t frame_id, QWidget * parent = nullptr);
  ~SpriteBaseTimelineElement();

  void SetRemoveCallback(Delegate<void> && callback);
  void SetClickCallback(Delegate<void> && callback);

  virtual QSize sizeHint() const override;

protected:

  virtual void resizeEvent(QResizeEvent * ev) override;
  virtual void paintEvent(QPaintEvent * ev) override;
  virtual void mousePressEvent(QMouseEvent * ev) override;

public slots:

  void removePressed();

private:
  NotNullPtr<SpriteBaseEditor> m_Editor;

  SpriteBaseDef & m_Sprite;
  SpriteBaseTextureLoadList & m_TextureAccess;
  uint64_t m_FrameId;

  DelegateLink<void> m_UpdateDelegateLink;

  Delegate<void> m_RemoveDelegate;
  Delegate<void> m_ClickDelegate;

  std::unique_ptr<QPushButton> m_RemoveButton;


};

