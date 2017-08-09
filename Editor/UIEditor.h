#pragma once

#include <QTabWidget>
#include <QGridLayout>

#include <memory>

#include "Runtime/UI/UIDef.refl.h"

#include "DocumentEditorWidgetBase.h"
#include "GenericFrame.h"
#include "PropertyEditor.h"
#include "ScrollingPanel.h"
#include "UIEditorNode.h"
#include "UIEditorNodeList.h"
#include "UIEditorViewer.h"
#include "UIEditorPropertyContainer.h"

class UIEditorPropertyContainer;

class UIEditor : public DocumentEditorWidgetBase
{
  Q_OBJECT;
public:
  UIEditor(PropertyFieldDatabase & property_db, const std::string & root_path, UIDef & ui,
    DocumentChangeLinkDelegate && change_link_callback, DocumentBeginTransactionDelegate && begin_transaction_callback,
    DocumentCommitChangesDelegate && commit_change_callback, QWidget *parent = nullptr);

  void ChangeSelection(const UIEditorNodeSelection & layer);
  void ClearSelection();

  static NullOptPtr<UIDef> GetUIForPath(UIDef & root, czstr path);

private:

  UIDef & m_UI;

  std::unique_ptr<QGridLayout> m_Layout;
  std::unique_ptr<ScrollingPanel> m_PropertiesPanel;
  NotNullPtr<UIEditorPropertyContainer> m_PropertiesContainer;

  std::unique_ptr<UIEditorNodeList> m_NodeList;
  std::unique_ptr<UIEditorViewer> m_Viewer;

  PropertyEditor * m_PropertyEditor;
  bool m_IgnoreSelectionChanges;
};
