
#include <StormData/StormDataParent.h>

#include "Runtime/Entity/EntityDef.refl.meta.h"

#include "EditorContainer.h"
#include "DocumentEditor.h"
#include "EntityEditor.h"


EntityEditor::EntityEditor(PropertyFieldDatabase & property_db, const std::string & root_path, EntityDef & entity, DocumentChangeLinkDelegate && change_link_callback,
  DocumentBeginTransactionDelegate && begin_transaction_callback, DocumentCommitChangesDelegate && commit_change_callback, QWidget *parent) :
  DocumentEditorWidgetBase(property_db, root_path, std::move(change_link_callback), std::move(begin_transaction_callback), std::move(commit_change_callback), parent),
  m_Entity(entity),
  m_Layout(std::make_unique<QGridLayout>()),
  m_EntityProperties(std::make_unique<GenericFrame>("Entity Properties", this))
{
  m_Layout->setColumnStretch(0, 3);
  m_Layout->setColumnMinimumWidth(0, 100);

  m_Layout->setColumnStretch(1, 1);
  m_Layout->setColumnMinimumWidth(1, 300);

  m_Layout->addWidget(m_EntityProperties.get(), 0, 1);

  m_PropertyEditor = m_EntityProperties->CreateWidget<PropertyEditor>();
  m_PropertyEditor->LoadStruct(this, m_Entity, true);

  setLayout(m_Layout.get());
}

REGISTER_EDITOR("Entity", EntityEditor, EntityDef, ".entity", "Entities");
