
#include "SpriteBaseAnimationEditor.h"
#include "SpriteBaseAnimationListElement.h"
#include "SpriteBaseAnimationFrameListEditorDialog.h"
#include "SpriteBaseEditor.h"

#include "Runtime/Sprite/SpriteDef.refl.meta.h"

#include "StormData/StormDataJson.h"

#include <sb/vector.h>

SpriteBaseAnimationEditor::SpriteBaseAnimationEditor(NotNullPtr<SpriteBaseEditor> editor, SpriteBaseDef & sprite, SpriteBaseTextureLoadList & texture_access, QWidget * parent) :
  GenericListFrame("Animations", true, false, parent),
  m_Editor(editor),
  m_Sprite(sprite),
  m_TextureAccess(texture_access)
{
  CreateGenericList<RMergeList, SpriteBaseDefAnimation>(m_Editor, sprite.m_Animations,
    [](GenericList * list, SpriteBaseDefAnimation & def, std::size_t index, void * user_data) -> std::unique_ptr<QWidget>
    {
      auto parent = static_cast<SpriteBaseAnimationEditor *>(user_data);
      auto ptr = std::make_unique<SpriteBaseAnimationListElement>(parent->m_Editor, parent->m_Sprite, parent->m_TextureAccess, index);
      ptr->SetSizeChangeCallback([=] { list->ChildSizeChanged((int)index); });
      ptr->SetOpenEditorCallback([=] { parent->OpenAnimEditorDialog(index); });
      ptr->SetRemoveCallback([=] { parent->m_Sprite.m_Animations.RemoveAt(index); });
      return std::move(ptr);
    }, this,
    [](QWidget * widget, SpriteBaseDefAnimation & def, void * user_data)
    {

    }, nullptr, 
    this, [this]() -> void * { return &m_Sprite.m_Animations; });

  SetAddDelegate([this]() { OpenAnimEditorDialog(); });
}

SpriteBaseAnimationEditor::~SpriteBaseAnimationEditor()
{

}

void SpriteBaseAnimationEditor::OpenAnimEditorDialog(int animation_index)
{
  auto dialog = std::make_unique<SpriteBaseAnimationFrameListEditorDialog>(m_Editor, m_Sprite, m_TextureAccess, animation_index);
  dialog->show();

  connect(dialog.get(), &SpriteBaseAnimationFrameListEditorDialog::accepted, this, &SpriteBaseAnimationEditor::handleAnimDialogAccepted);
  connect(dialog.get(), &SpriteBaseAnimationFrameListEditorDialog::rejected, this, &SpriteBaseAnimationEditor::handleAnimDialogClosed);
  connect(dialog.get(), &SpriteBaseAnimationFrameListEditorDialog::closed, this, &SpriteBaseAnimationEditor::handleAnimDialogClosed);

  m_EditorDialogs.emplace_back(std::move(dialog));
}

void SpriteBaseAnimationEditor::handleAnimDialogAccepted()
{
  auto dialog = static_cast<SpriteBaseAnimationFrameListEditorDialog *>(QObject::sender());
  dialog->Finalize();
  handleAnimDialogClosed();
}

void SpriteBaseAnimationEditor::handleAnimDialogClosed()
{
  auto dialog = static_cast<SpriteBaseAnimationFrameListEditorDialog *>(QObject::sender());
  for (std::size_t index = 0, end = m_EditorDialogs.size(); index < end; ++index)
  {
    if (m_EditorDialogs[index].get() == dialog)
    {
      vremove_index_quick(m_EditorDialogs, index);
      return;
    }
  }
}
