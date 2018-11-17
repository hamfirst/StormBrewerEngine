
#include "EditorContainer.h"
#include "DocumentEditor.h"
#include "VisualEffectEditor.h"

#include "Foundation/PropertyMeta/PropertyFieldMetaFuncs.h"

#include "Runtime/VisualEffect/VisualEffectDef.refl.meta.h"

#include "StormData/StormDataParent.h"
#include "StormRefl/StormReflMetaEnum.h"

VisualEffectEditor::VisualEffectEditor(EditorContainer & editor_container, PropertyFieldDatabase & property_db, const std::string & root_path, VisualEffectDef & ui,
  DocumentChangeLinkDelegate && change_link_callback, DocumentBeginTransactionDelegate && begin_transaction_callback,
  DocumentCommitChangesDelegate && commit_change_callback, QWidget *parent) :
  DocumentEditorWidgetBase(editor_container, property_db, root_path, std::move(change_link_callback), std::move(begin_transaction_callback), std::move(commit_change_callback), parent),
  m_VisualEffect(ui),
  m_Layout(std::make_unique<QGridLayout>()),
  m_PropertiesPanel(std::make_unique<ScrollingPanel>(this)),
  m_NodeList(std::make_unique<VisualEffectEditorNodeList>(this, m_VisualEffect)),
  m_Viewer(std::make_unique<VisualEffectEditorViewer>(this, m_VisualEffect)),
  m_IgnoreSelectionChanges(false)
{
  m_Layout->setColumnStretch(0, 1);
  m_Layout->setColumnMinimumWidth(0, 100);

  m_Layout->setColumnStretch(1, 3);
  m_Layout->setColumnMinimumWidth(1, 100);

  m_Layout->setColumnStretch(2, 1);
  m_Layout->setColumnMinimumWidth(2, 300);

  m_Layout->addWidget(m_NodeList.get(), 0, 0);
  m_Layout->addWidget(m_Viewer.get(), 0, 1);
  m_Layout->addWidget(m_PropertiesPanel.get(), 0, 2);

  auto property_container = std::make_unique<VisualEffectEditorPropertyContainer>(this, m_VisualEffect, [this]() { m_PropertiesPanel->recalculate(); });
  m_PropertiesContainer = property_container.get();
  m_PropertiesPanel->SetChildWidget(std::move(property_container));

  setLayout(m_Layout.get());
}

void VisualEffectEditor::ChangeSelection(const VisualEffectEditorNodeSelection & layer)
{
  if (m_IgnoreSelectionChanges)
  {
    return;
  }

  m_Viewer->ChangeSelection(layer);
  m_NodeList->ChangeSelection(layer);
  m_PropertiesContainer->ChangeSelection(layer);
}

void VisualEffectEditor::ClearSelection()
{
  if (m_IgnoreSelectionChanges)
  {
    return;
  }

  m_PropertyEditor->Unload();
  m_Viewer->ClearSelection();
  m_NodeList->ClearSelection();
  m_PropertiesContainer->ClearSelection();
}

REGISTER_EDITOR("VisualEffect", VisualEffectEditor, VisualEffectDef, ".vfx", "VisualEffects");
