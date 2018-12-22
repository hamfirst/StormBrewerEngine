#pragma once

#include <QTabWidget>
#include <QGridLayout>
#include <QTextEdit>

#include <memory>

#include "Runtime/UI/UIDef.refl.h"

#include "DocumentEditorWidgetBase.h"
#include "GenericFrame.h"
#include "PropertyEditor.h"
#include "ScrollingPanel.h"
#include "UIEditorViewer.h"

class UIEditorPropertyContainer;

class UIEditor : public DocumentEditorWidgetBase
{
  Q_OBJECT;
public:
  UIEditor(EditorContainer & editor_container, PropertyFieldDatabase & property_db, const std::string & root_path, UIDef & ui,
    DocumentChangeLinkDelegate && change_link_callback, DocumentBeginTransactionDelegate && begin_transaction_callback,
    DocumentCommitChangesDelegate && commit_change_callback, QWidget *parent = nullptr);

  void DisplayError(czstr error);
  void ClearErrors();

private:

  UIDef & m_UI;

  std::unique_ptr<QGridLayout> m_Layout;
  std::unique_ptr<GenericFrame> m_UIProperties;
  std::unique_ptr<QTextEdit> m_Output;
  int m_NumOutputLines = 0;
  double m_LastOutput = 0;

  std::unique_ptr<UIEditorViewer> m_Viewer;

  PropertyEditor * m_PropertyEditor;
  bool m_IgnoreSelectionChanges;
};
