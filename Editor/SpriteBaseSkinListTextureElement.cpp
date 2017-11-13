
#include <QPainter>

#include "StormData/StormDataPath.h"

#include "SpriteBaseSkinListTextureElement.h"
#include "SpriteBaseEditor.h"

#include "PropertyEditorWidget.h"

SpriteBaseSkinListTextureElement::SpriteBaseSkinListTextureElement(NotNullPtr<SpriteBaseEditor> editor, SpriteBaseDef & sprite, SpriteBaseTextureLoadList & texture_access,
  std::size_t skin_index, std::size_t element_index) :
  m_Editor(editor),
  m_Sprite(sprite),
  m_TextureAccess(texture_access),
  m_SkinIndex(skin_index),
  m_ElementIndex(element_index),
  m_TextureLabel(std::make_unique<QLabel>("Texture:", this)),
  m_ReplacementLabel(std::make_unique<QLabel>("Replacement:", this)),
  m_Delete(std::make_unique<QPushButton>("Delete", this))
{
  setMinimumHeight(24);

  m_UpdateDelegateLink = m_TextureAccess.AddUpdateCallback([this] { update(); });

  m_EditorFieldData.m_Type = PropertyFieldType::kFile;
  m_EditorFieldData.m_File.m_Extension = "image";

  m_Texture = PropertyEditorCreate(m_Editor, &m_EditorFieldData, true, [this]()-> void * {
      auto skin = m_Sprite.m_Skins.TryGet(m_SkinIndex);
      if (!skin) return nullptr;
      auto elem = skin->m_TextureReplacements.TryGet(m_ElementIndex);
      return elem ? &elem->m_Texture : nullptr;
    },
    StormDataGetPath(m_Sprite.m_Skins[m_SkinIndex].m_TextureReplacements[m_ElementIndex].m_Texture), {}, "Texture", this);

  m_Replacement = PropertyEditorCreate(m_Editor, &m_EditorFieldData, true, [this]()-> void * {
      auto skin = m_Sprite.m_Skins.TryGet(m_SkinIndex);
      if (!skin) return nullptr;
      auto elem = skin->m_TextureReplacements.TryGet(m_ElementIndex);
      return elem ? &elem->m_Replacement : nullptr;
    },
    StormDataGetPath(m_Sprite.m_Skins[m_SkinIndex].m_TextureReplacements[m_ElementIndex].m_Replacement), {}, "Replacement", this);

  m_TextureLabel->setGeometry(65, 2, 100, 20);
  m_Texture->setGeometry(125, 2, 150, 20);

  m_ReplacementLabel->setGeometry(317, 2, 100, 20);
  m_Replacement->setGeometry(407, 2, 150, 20);

  m_Delete->setGeometry(655, 2, 100, 20);
  connect(m_Delete.get(), &QPushButton::pressed, this, &SpriteBaseSkinListTextureElement::remove);
}

SpriteBaseSkinListTextureElement::~SpriteBaseSkinListTextureElement()
{

}

void SpriteBaseSkinListTextureElement::SetRemoveCallback(Delegate<void> && callback)
{
  m_RemoveCallback = std::move(callback);
}

void SpriteBaseSkinListTextureElement::remove()
{
  m_RemoveCallback();
}
