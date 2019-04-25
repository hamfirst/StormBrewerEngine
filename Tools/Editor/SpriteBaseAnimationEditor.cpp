
#include "SpriteBaseAnimationEditor.h"
#include "SpriteBaseAnimationListElement.h"
#include "SpriteBaseAnimationFrameListEditorDialog.h"
#include "SpriteBaseAnimationEventEditorDialog.h"
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
      ptr->SetOpenEventCallback([=] { parent->OpenAnimEventDialog(index); });
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
  closeChildWidgets();
}

void SpriteBaseAnimationEditor::closeEvent(QCloseEvent * ev)
{
  closeChildWidgets();
}

void SpriteBaseAnimationEditor::closeChildWidgets()
{
  auto editor_dialogs = std::move(m_EditorDialogs);
  for (auto widget : editor_dialogs)
  {
    widget->close();
  }

  auto event_dialogs = std::move(m_EventDialogs);
  for (auto widget : event_dialogs)
  {
    widget->close();
  }
}

void SpriteBaseAnimationEditor::OpenAnimEditorDialog(int animation_index)
{
  auto dialog = new SpriteBaseAnimationFrameListEditorDialog(m_Editor, m_Sprite, m_TextureAccess, animation_index);
  dialog->show();

  connect(dialog, &SpriteBaseAnimationFrameListEditorDialog::accepted, this, &SpriteBaseAnimationEditor::handleAnimDialogAccepted);
  connect(dialog, &SpriteBaseAnimationFrameListEditorDialog::rejected, this, &SpriteBaseAnimationEditor::handleAnimDialogClosed);
  connect(dialog, &SpriteBaseAnimationFrameListEditorDialog::closed, this, &SpriteBaseAnimationEditor::handleAnimDialogClosed);

  m_EditorDialogs.emplace_back(dialog);
}

void SpriteBaseAnimationEditor::OpenAnimEventDialog(int animation_index)
{
  auto dialog = new SpriteBaseAnimationEventEditorDialog(m_Editor, m_Sprite, m_TextureAccess, animation_index);
  dialog->show();

  connect(dialog, &SpriteBaseAnimationEventEditorDialog::closed, this, &SpriteBaseAnimationEditor::handleEventDialogClosed);

  m_EventDialogs.emplace_back(dialog);
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
    if (m_EditorDialogs[index] == dialog)
    {
      vremove_index_quick(m_EditorDialogs, index);
      return;
    }
  }
}

void SpriteBaseAnimationEditor::handleEventDialogClosed()
{
  auto dialog = static_cast<SpriteBaseAnimationEventEditorDialog *>(QObject::sender());
  for (std::size_t index = 0, end = m_EventDialogs.size(); index < end; ++index)
  {
    if (m_EventDialogs[index] == dialog)
    {
      vremove_index_quick(m_EventDialogs, index);
      return;
    }
  }
}
