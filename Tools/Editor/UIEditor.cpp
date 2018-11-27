
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
  m_PropertiesPanel(std::make_unique<ScrollingPanel>(this)),
  m_IgnoreSelectionChanges(false)
{

  m_Layout->setColumnStretch(0, 1);
  m_Layout->setColumnMinimumWidth(0, 100);

  m_Layout->setColumnStretch(1, 3);
  m_Layout->setColumnMinimumWidth(1, 100);

  m_Layout->setColumnStretch(2, 1);
  m_Layout->setColumnMinimumWidth(2, 300);

  m_Layout->addWidget(m_Viewer.get(), 0, 0);
  m_Layout->addWidget(m_PropertiesPanel.get(), 0, 1);

  auto property_container = std::make_unique<UIEditorPropertyContainer>(this, m_UI, [this]() { m_PropertiesPanel->recalculate(); });
  m_PropertiesContainer = property_container.get();
  m_PropertiesPanel->SetChildWidget(std::move(property_container));

  setLayout(m_Layout.get());
}


REGISTER_EDITOR("UI", UIEditor, UIDef, ".ui", "UIs");
