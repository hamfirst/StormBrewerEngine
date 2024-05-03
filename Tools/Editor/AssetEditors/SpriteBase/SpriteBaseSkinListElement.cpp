
#include <QPainter>
#include <QMouseEvent>

#include "Runtime/Sprite/SpriteDef.refl.meta.h"

#include "StormData/StormDataJson.h"
#include "StormData/StormDataPath.h"

#include "SpriteBaseSkinListElement.h"
#include "SpriteBaseSkinListTextureElement.h"
#include "SpriteBaseEditor.h"

#include "Tools/Editor/UI/PropertyEditors/PropertyEditorWidget.h"
#include "Tools/Editor/UI/GenericWidgets/GenericList.h"

SpriteBaseSkinListElement::SpriteBaseSkinListElement(NotNullPtr<SpriteBaseEditor> editor, SpriteBaseDef & sprite,
  SpriteBaseTextureLoadList & texture_access, std::size_t skin_index) :
  m_Editor(editor),
  m_Sprite(sprite),
  m_TextureAccess(texture_access),
  m_SkinIndex(skin_index),
  m_TextureListContainer(std::make_unique<GenericListFrame>("Texture Replacements", true, false, this)),
  m_SkinNameLabel(std::make_unique<QLabel>("Name:", this)),
  m_Delete(std::make_unique<QPushButton>("Delete", this))
{
  setMinimumHeight(200);
  setMouseTracking(true);

  m_UpdateDelegateLink = m_TextureAccess.AddUpdateCallback([this] { update(); });

  m_TextureList = CreateGenericList<RMergeList, SpriteBaseDefSkinElement>(m_Editor, sprite.m_Skins[m_SkinIndex].m_TextureReplacements,
    [](GenericList * list, SpriteBaseDefSkinElement & def, std::size_t index, void * user_data) -> std::unique_ptr<QWidget>
    {
      auto parent = static_cast<SpriteBaseSkinListElement *>(user_data);
      auto ptr = std::make_unique<SpriteBaseSkinListTextureElement>(parent->m_Editor, parent->m_Sprite, parent->m_TextureAccess, parent->m_SkinIndex, index);
      ptr->SetRemoveCallback([parent, index]() {
        auto skin = parent->m_Sprite.m_Skins.TryGet(parent->m_SkinIndex);
        if (skin == nullptr) return;
        skin->m_TextureReplacements.RemoveAt(index);
      });
      return std::move(ptr);
    }, this,
    [](QWidget * widget, SpriteBaseDefSkinElement & def, void * user_data)
    {

    }, nullptr,
    m_TextureListContainer.get(), [this]() -> void * { auto skin = m_Sprite.m_Skins.TryGet(m_SkinIndex); return skin ? &skin->m_TextureReplacements : nullptr; }, false);

  m_SkinName = PropertyEditorCreate(m_Editor, m_Editor->GetPropertyFieldDatabase().GetBasicField(PropertyFieldType::kString), true,
    [this]()-> void * { auto skin = m_Sprite.m_Skins.TryGet(m_SkinIndex); return skin ? &skin->m_Name : nullptr; },
    StormDataGetPath(m_Sprite.m_Skins[m_SkinIndex].m_Name), {}, "Skin", this);

  m_SkinNameLabel->setGeometry(5, 2, 50, 20);
  m_SkinName->setGeometry(55, 2, 150, 20);

  m_Delete->setGeometry(655, 2, 100, 20);
  connect(m_Delete.get(), &QPushButton::pressed, this, &SpriteBaseSkinListElement::remove);

  m_TextureListContainer->SetAddDelegate([this]()
  {
    auto texture = m_Editor->GetFileNameForAssetType("image");
    if (texture)
    {
      auto replacement = m_Editor->GetFileNameForAssetType("image");
      if (replacement)
      {
        auto skin = m_Sprite.m_Skins.TryGet(m_SkinIndex);
        if (skin == nullptr)
        {
          return;
        }

        SpriteBaseDefSkinElement elem;
        elem.m_Texture = texture.Value();
        elem.m_Replacement = replacement.Value();

        skin->m_TextureReplacements.EmplaceBack(std::move(elem));
      }
    }
  });

  m_TextureList->SetSizeChangeCallback([this] { HandleTextureListChanged(); });

  HandleTextureListChanged();
}

SpriteBaseSkinListElement::~SpriteBaseSkinListElement()
{

}

void SpriteBaseSkinListElement::SetSizeChangeCallback(Delegate<void> && callback)
{
  m_SizeChangedCallback = std::move(callback);
}

void SpriteBaseSkinListElement::SetRemoveCallback(Delegate<void> && callback)
{
  m_RemoveCallback = std::move(callback);
}

void SpriteBaseSkinListElement::HandleTextureListChanged()
{
  setMinimumHeight(100 + m_TextureList->minimumHeight());
  m_SizeChangedCallback();
}

void SpriteBaseSkinListElement::resizeEvent(QResizeEvent * ev)
{
  m_TextureListContainer->setGeometry(40, 30, width() - 40, height() - 100);
}

void SpriteBaseSkinListElement::remove()
{
  m_RemoveCallback();
}
