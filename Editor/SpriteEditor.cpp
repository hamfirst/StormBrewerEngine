
#include "SpriteEditor.h"
#include "EditorContainer.h"
#include "DocumentEditor.h"
#include "FrameEditorContainer.h"

#include "Runtime/Sprite/SpriteDef.refl.meta.h"

extern FrameDataDef g_FrameData;

SpriteEditor::SpriteEditor(PropertyFieldDatabase & property_db, const std::string & root_path, SpriteDef & sprite, DocumentChangeLinkDelegate && change_link_callback,
  DocumentBeginTransactionDelegate && begin_transaction_callback, DocumentCommitChangesDelegate && commit_change_callback, QWidget *parent) :
  SpriteBaseEditor(property_db, root_path, sprite, std::move(change_link_callback), std::move(begin_transaction_callback), std::move(commit_change_callback), parent)
{
  FrameEditorContainer::CreateFrameEditorTabs(this, m_Sprite, m_TextureAccess, m_TabWidget.get(),
    &m_GlobalFrameDataCallback, 0, g_FrameData.m_SpriteGlobalData);

  m_FrameList->SetFrameSelectionCallback([this](uint64_t frame_id)
  {
    auto frame_editor = new FrameEditorContainer(this, m_Sprite, m_TextureAccess, [this]() { return m_GlobalFrameDataCallback(); }, frame_id, g_FrameData.m_SpriteFrameData);
    frame_editor->exec();
  });
}

REGISTER_EDITOR("Sprite", SpriteEditor, SpriteDef, ".sprite", "Sprites");

