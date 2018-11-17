
#include "SpriteBaseTextureFrameList.h"
#include "SpriteBaseTextureFrameElement.h"
#include "SpriteBaseEditor.h"

#include "Runtime/Sprite/SpriteDef.refl.meta.h"

#include "StormData/StormDataJson.h"

SpriteBaseTextureFrameList::SpriteBaseTextureFrameList(NotNullPtr<SpriteBaseEditor> editor, SpriteBaseDef & sprite, QWidget * parent) :
  GenericListFrame("Frame List", false, false, parent),
  m_Editor(editor),
  m_Sprite(sprite)
{
  CreateGenericList<RMergeList, SpriteBaseDefTexture>(m_Editor, sprite.m_Textures,
    [](GenericList * list, SpriteBaseDefTexture & def, std::size_t index, void * user_data) -> std::unique_ptr<QWidget>
    {
      auto parent = static_cast<SpriteBaseTextureFrameList *>(user_data);
      auto ptr = std::make_unique<SpriteBaseTextureFrameElement>(parent->m_Editor, [parent, index]{ return parent->m_Sprite.m_Textures.TryGet(index); });
      ptr->SetSizeChangeCallback([=] { list->ChildSizeChanged((int)index); });
      ptr->SetFrameSelectCallback([=](uint64_t frame_id) { parent->m_SelectionCallback(frame_id); });
      return std::move(ptr);
    }, this,
    [](QWidget * widget, SpriteBaseDefTexture & def, void * user_data)
    {


    }, nullptr, 
    this, [this]() -> void * { return &m_Sprite.m_Textures; });
}

SpriteBaseTextureFrameList::~SpriteBaseTextureFrameList()
{

}

void SpriteBaseTextureFrameList::SetFrameSelectionCallback(Delegate<void, uint64_t> && callback)
{
  m_SelectionCallback = std::move(callback);
}
