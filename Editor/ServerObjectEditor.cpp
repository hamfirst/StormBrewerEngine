
#include <StormData/StormDataParent.h>

#include "Runtime/ServerObject/ServerObjectDef.refl.meta.h"

#include "EditorContainer.h"
#include "DocumentEditor.h"
#include "ServerObjectEditor.h"


ServerObjectEditor::ServerObjectEditor(PropertyFieldDatabase & property_db, const std::string & root_path, ServerObjectDef & server_object, DocumentChangeLinkDelegate && change_link_callback,
  DocumentBeginTransactionDelegate && begin_transaction_callback, DocumentCommitChangesDelegate && commit_change_callback, QWidget *parent) :
  DocumentEditorWidgetBase(property_db, root_path, std::move(change_link_callback), std::move(begin_transaction_callback), std::move(commit_change_callback), parent),
  m_ServerObject(server_object),
  m_Layout(std::make_unique<QGridLayout>()),
  m_ServerObjectProperties(std::make_unique<GenericFrame>("Server Object Properties", this))
{
  m_Layout->setColumnStretch(0, 3);
  m_Layout->setColumnMinimumWidth(0, 100);

  m_Layout->setColumnStretch(1, 1);
  m_Layout->setColumnMinimumWidth(1, 300);

  m_Layout->addWidget(m_ServerObjectProperties.get(), 0, 1);

  m_PropertyEditor = m_ServerObjectProperties->CreateWidget<PropertyEditor>();
  m_PropertyEditor->LoadStruct(this, m_ServerObject, true);

  setLayout(m_Layout.get());
}

REGISTER_EDITOR("ServerObject", ServerObjectEditor, ServerObjectDef, ".serverobject", "ServerObjects");
