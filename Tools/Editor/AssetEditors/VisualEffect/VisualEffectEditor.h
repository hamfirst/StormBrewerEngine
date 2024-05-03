#pragma once

#include <QTabWidget>
#include <QGridLayout>

#include <memory>

#include "Runtime/VisualEffect/VisualEffectDef.refl.h"

#include "Tools/Editor/AssetEditors/DocumentEditor/DocumentEditorWidgetBase.h"
#include "Tools/Editor/UI/GenericWidgets/GenericFrame.h"
#include "Tools/Editor/UI/PropertyEditors/PropertyEditor.h"
#include "Tools/Editor/UI/UtilityWidgets/ScrollingPanel.h"
#include "VisualEffectEditorNodeSelection.h"
#include "VisualEffectEditorNodeList.h"
#include "VisualEffectEditorViewer.h"
#include "VisualEffectEditorPropertyContainer.h"

class VisualEffectEditorPropertyContainer;

class VisualEffectEditor : public DocumentEditorWidgetBase
{
  Q_OBJECT;
public:
  VisualEffectEditor(EditorContainer & editor_container, PropertyFieldDatabase & property_db, const std::string & root_path, VisualEffectDef & ui,
    DocumentChangeLinkDelegate && change_link_callback, DocumentBeginTransactionDelegate && begin_transaction_callback,
    DocumentCommitChangesDelegate && commit_change_callback, QWidget *parent = nullptr);

  void ChangeSelection(const VisualEffectEditorNodeSelection & layer);
  void ClearSelection();

private:

  VisualEffectDef & m_VisualEffect;

  std::unique_ptr<QGridLayout> m_Layout;
  std::unique_ptr<ScrollingPanel> m_PropertiesPanel;
  NotNullPtr<VisualEffectEditorPropertyContainer> m_PropertiesContainer;

  std::unique_ptr<VisualEffectEditorNodeList> m_NodeList;
  std::unique_ptr<VisualEffectEditorViewer> m_Viewer;

  PropertyEditor * m_PropertyEditor;
  bool m_IgnoreSelectionChanges;
};
