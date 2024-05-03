#pragma once

#include <memory>

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QTimer>
#include <QPushButton>

#include "Runtime/SpriteBase/SpriteBaseDef.refl.h"

#include "SpriteBaseTextureLoadList.h"
#include "Tools/Editor/UI/GenericWidgets/GenericListFrame.h"

class SpriteBaseEditor;
class SpriteBaseTimelineElement;

class GenericList;

class SpriteBaseSkinListElement : public QWidget
{
  Q_OBJECT;
public:
  SpriteBaseSkinListElement(NotNullPtr<SpriteBaseEditor> editor, SpriteBaseDef & sprite, SpriteBaseTextureLoadList & texture_access, std::size_t skin_index);
  ~SpriteBaseSkinListElement();

  void SetSizeChangeCallback(Delegate<void> && callback);
  void SetRemoveCallback(Delegate<void> && callback);
protected:

  void HandleTextureListChanged();

  void resizeEvent(QResizeEvent * ev) override;

public slots:

  void remove();

private:
  NotNullPtr<SpriteBaseEditor> m_Editor;
  SpriteBaseDef & m_Sprite;
  SpriteBaseTextureLoadList & m_TextureAccess;
  std::size_t m_SkinIndex;

  Delegate<void> m_SizeChangedCallback;
  Delegate<void> m_RemoveCallback;

  std::unique_ptr<GenericListFrame> m_TextureListContainer;
  GenericList * m_TextureList;

  std::unique_ptr<QLabel> m_SkinNameLabel;
  std::unique_ptr<QWidget> m_SkinName;

  std::unique_ptr<QPushButton> m_Delete;

  DelegateLink<void> m_UpdateDelegateLink;
};
