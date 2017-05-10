
#include "TileSheetEditor.h"
#include "EditorContainer.h"
#include "DocumentEditor.h"
#include "FrameEditorContainer.h"

#include "Runtime/TileSheet/TileSheetDef.refl.meta.h"

extern FrameDataDef g_FrameData;

TileSheetEditor::TileSheetEditor(PropertyFieldDatabase & property_db, const std::string & root_path, TileSheetDef & tile_sheet, DocumentChangeLinkDelegate && change_link_callback,
  DocumentBeginTransactionDelegate && begin_transaction_callback, DocumentCommitChangesDelegate && commit_change_callback, QWidget *parent) :
  SpriteBaseEditor(property_db, root_path, tile_sheet, std::move(change_link_callback), std::move(begin_transaction_callback), std::move(commit_change_callback), parent)
{
  FrameEditorContainer::CreateFrameEditorTabs(this, m_Sprite, m_TextureAccess, m_TabWidget.get(),
    &m_GlobalFrameDataCallback, 0, g_FrameData.m_TileGlobalData);
}

REGISTER_EDITOR("Tile Sheet", TileSheetEditor, TileSheetDef, ".tilesheet", "TileSheets");

