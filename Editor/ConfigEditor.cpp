
#include <StormData/StormDataParent.h>

#include "EditorContainer.h"
#include "DocumentEditor.h"
#include "ConfigEditor.h"


ConfigEditor::ConfigEditor(PropertyFieldDatabase & property_db, const std::string & root_path, void * config_ptr, ConfigRegistrationInfo & config_info,
  DocumentChangeLinkDelegate && change_link_callback, DocumentBeginTransactionDelegate && begin_transaction_callback, 
  DocumentCommitChangesDelegate && commit_change_callback, QWidget *parent) :
  DocumentEditorWidgetBase(property_db, root_path, std::move(change_link_callback), std::move(begin_transaction_callback), std::move(commit_change_callback), parent),
  m_Layout(std::make_unique<QGridLayout>()),
  m_ConfigProperties(std::make_unique<GenericFrame>("Config Properties", this)),
  m_ConfigPtr(config_ptr),
  m_ConfigInfo(config_info)
{
  m_Layout->setColumnStretch(0, 3);
  m_Layout->setColumnMinimumWidth(0, 100);

  m_Layout->setColumnStretch(1, 1);
  m_Layout->setColumnMinimumWidth(1, 300);

  m_Layout->addWidget(m_ConfigProperties.get(), 0, 1);

  m_PropertyEditor = m_ConfigProperties->CreateWidget<PropertyEditor>();
  m_PropertyEditor->LoadObject(this, config_info.m_Props, true, [=] { return config_ptr; }, "");

  setLayout(m_Layout.get());
}

