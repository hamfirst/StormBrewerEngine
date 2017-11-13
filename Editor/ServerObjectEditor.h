#pragma once

#include <memory>

#include <QTabWidget>
#include <QGridLayout>

#include "Runtime/ServerObject/ServerObjectDef.refl.h"

#include "DocumentEditorWidgetBase.h"
#include "GenericFrame.h"
#include "PropertyEditor.h"

class ServerObjectEditor : public DocumentEditorWidgetBase
{
  Q_OBJECT;
public:
  ServerObjectEditor(PropertyFieldDatabase & property_db, const std::string & root_path, ServerObjectDef & entity, DocumentChangeLinkDelegate && change_link_callback,
    DocumentBeginTransactionDelegate && begin_transaction_callback, DocumentCommitChangesDelegate && commit_change_callback, QWidget *parent = nullptr);

private:

  ServerObjectDef & m_ServerObject;

  std::unique_ptr<QGridLayout> m_Layout;
  std::unique_ptr<GenericFrame> m_ServerObjectProperties;

  PropertyEditor * m_PropertyEditor;
};
