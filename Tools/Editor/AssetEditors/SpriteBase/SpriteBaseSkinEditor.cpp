
#include "SpriteBaseSkinEditor.h"
#include "SpriteBaseSkinListElement.h"
#include "SpriteBaseEditor.h"

#include "Runtime/Sprite/SpriteDef.refl.meta.h"

#include "StormData/StormDataJson.h"

#include "External/sb/vector.h"

SpriteBaseSkinEditor::SpriteBaseSkinEditor(NotNullPtr<SpriteBaseEditor> editor, SpriteBaseDef & sprite, SpriteBaseTextureLoadList & texture_access, QWidget * parent) :
  GenericListFrame("Skins", true, false, parent),
  m_Editor(editor),
  m_Sprite(sprite),
  m_TextureAccess(texture_access)
{
  CreateGenericList<RMergeList, SpriteBaseDefSkin>(m_Editor, sprite.m_Skins,
    [](GenericList * list, SpriteBaseDefSkin & def, std::size_t index, void * user_data) -> std::unique_ptr<QWidget>
    {
      auto parent = static_cast<SpriteBaseSkinEditor *>(user_data);
      auto ptr = std::make_unique<SpriteBaseSkinListElement>(parent->m_Editor, parent->m_Sprite, parent->m_TextureAccess, index);
      ptr->SetSizeChangeCallback([=] { list->ChildSizeChanged((int)index); });
      ptr->SetRemoveCallback([=] { parent->m_Sprite.m_Skins.RemoveAt(index); });
      return std::move(ptr);
    }, this,
    [](QWidget * widget, SpriteBaseDefSkin & def, void * user_data)
    {

    }, nullptr,
    this, [this]() -> void * { return &m_Sprite.m_Skins; });

  SetAddDelegate([this]() 
  { 
    auto texture = m_Editor->GetFileNameForAssetType("image");
    if (texture)
    {
      auto replacement = m_Editor->GetFileNameForAssetType("image");
      if (replacement)
      {
        SpriteBaseDefSkin new_skin;
        new_skin.m_Name = "Skin";

        SpriteBaseDefSkinElement elem;
        elem.m_Texture = texture.Value();
        elem.m_Replacement = replacement.Value();

        new_skin.m_TextureReplacements.EmplaceBack(std::move(elem));
        m_Sprite.m_Skins.EmplaceBack(std::move(new_skin));
      }
    }
  });
}

SpriteBaseSkinEditor::~SpriteBaseSkinEditor()
{

}