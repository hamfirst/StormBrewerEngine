
#include "EditorContainer.h"
#include "DocumentEditor.h"
#include "UIEditor.h"

#include "Foundation/PropertyMeta/PropertyFieldMetaFuncs.h"

#include "Runtime/UI/UIDef.refl.meta.h"

#include "StormData/StormDataParent.h"
#include "StormRefl/StormReflMetaEnum.h"

UIEditor::UIEditor(EditorContainer & editor_container, PropertyFieldDatabase & property_db, const std::string & root_path, UIDef & ui,
  DocumentChangeLinkDelegate && change_link_callback, DocumentBeginTransactionDelegate && begin_transaction_callback,
  DocumentCommitChangesDelegate && commit_change_callback, QWidget *parent) :
  DocumentEditorWidgetBase(editor_container, property_db, root_path, std::move(change_link_callback), std::move(begin_transaction_callback), std::move(commit_change_callback), parent),
  m_UI(ui),
  m_Layout(std::make_unique<QGridLayout>()),
  m_UIProperties(std::make_unique<GenericFrame>("UI Properties", this)),
  m_Output(std::make_unique<QTextEdit>(this)),
  m_Viewer(std::make_unique<UIEditorViewer>(this, m_UI, this)),
  m_IgnoreSelectionChanges(false)
{

  m_Layout->setColumnStretch(0, 3);
  m_Layout->setColumnMinimumWidth(0, 100);

  m_Layout->setColumnStretch(1, 1);
  m_Layout->setColumnMinimumWidth(1, 100);

  m_Layout->setRowStretch(0, 5);
  m_Layout->setRowMinimumHeight(0, 400);

  m_Layout->setRowStretch(1, 1);
  m_Layout->setRowMinimumHeight(1, 100);

  m_Layout->addWidget(m_Viewer.get(), 0, 0);
  m_Layout->addWidget(m_UIProperties.get(), 0, 1);
  m_Layout->addWidget(m_Output.get(), 1, 0, 1, 2);

  m_PropertyEditor = m_UIProperties->CreateWidget<PropertyEditor>();
  m_PropertyEditor->LoadStruct(this, m_UI, true);

  setLayout(m_Layout.get());
}


REGISTER_EDITOR("UI", UIEditor, UIDef, ".ui", "UIs");
