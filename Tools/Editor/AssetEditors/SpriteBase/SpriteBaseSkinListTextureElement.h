#pragma once

#include <memory>

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#include "Foundation/PropertyMeta/PropertyFieldMetaData.h"

#include "Runtime/SpriteBase/SpriteBaseDef.refl.h"


#include "SpriteBaseTextureLoadList.h"

class SpriteBaseEditor;
class SpriteBaseTimelineElement;

class SpriteBaseSkinListTextureElement : public QWidget
{
  Q_OBJECT;
public:
  SpriteBaseSkinListTextureElement(NotNullPtr<SpriteBaseEditor> editor, SpriteBaseDef & sprite, SpriteBaseTextureLoadList & texture_access,
    std::size_t skin_index, std::size_t element_index);
  ~SpriteBaseSkinListTextureElement();

  void SetRemoveCallback(Delegate<void> && callback);

protected:

public slots:

  void remove();

private:
  NotNullPtr<SpriteBaseEditor> m_Editor;
  SpriteBaseDef & m_Sprite;
  SpriteBaseTextureLoadList & m_TextureAccess;
  std::size_t m_SkinIndex;
  std::size_t m_ElementIndex;

  Delegate<void> m_RemoveCallback;

  std::unique_ptr<QLabel> m_TextureLabel;
  std::unique_ptr<QWidget> m_Texture;

  std::unique_ptr<QLabel> m_ReplacementLabel;
  std::unique_ptr<QWidget> m_Replacement;

  std::unique_ptr<QPushButton> m_Delete;

  PropertyField m_EditorFieldData;

  DelegateLink<void> m_UpdateDelegateLink;
};
