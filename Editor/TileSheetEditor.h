#pragma once

#include "SpriteBaseEditor.h"

#include "Runtime/TileSheet/TileSheetDef.refl.h"

class TileSheetEditor : public SpriteBaseEditor
{
  Q_OBJECT;
public:
  TileSheetEditor(PropertyFieldDatabase & property_db, const std::string & root_path, TileSheetDef & tile_sheet, DocumentChangeLinkDelegate && change_link_callback,
    DocumentBeginTransactionDelegate && begin_transaction_callback, DocumentCommitChangesDelegate && commit_change_callback, QWidget *parent = nullptr);
};


