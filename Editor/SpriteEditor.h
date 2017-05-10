#pragma once

#include "SpriteBaseEditor.h"

class SpriteEditor : public SpriteBaseEditor
{
  Q_OBJECT;
public:
  SpriteEditor(PropertyFieldDatabase & property_db, const std::string & root_path, SpriteDef & sprite, DocumentChangeLinkDelegate && change_link_callback,
    DocumentBeginTransactionDelegate && begin_transaction_callback, DocumentCommitChangesDelegate && commit_change_callback, QWidget *parent = nullptr);

};


