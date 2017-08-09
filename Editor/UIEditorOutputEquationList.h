#pragma once

#include <QWidget>
#include <QScrollBar>

#include "Runtime/UI/UIDef.refl.h"

#include "PropertyEditorWidget.h"
#include "DocumentValueWatcher.h"
#include "UIEditorNode.h"
#include "UIOutputEquationEditor.h"

class UIEditor;
class UIEditorNodeList;
class UIOutputEquationEditor;

class UIEditorOutputEquationList : public QWidget
{
  Q_OBJECT;

public:
  UIEditorOutputEquationList(NotNullPtr<UIEditor> editor, UIDef & ui, Delegate<void> && size_change_cb, QWidget * parent = nullptr);

  void ChangeSelection(const UIEditorNodeSelection & selection);
  void ClearSelection();

protected:
  void RefreshElements();
  void RepositionChildren();
  void SizeChanged();

protected:

  void resizeEvent(QResizeEvent * ev);

private:
  NotNullPtr<UIEditor> m_Editor;
  UIDef & m_UI;

  Delegate<void> m_SizeChanged;
  DocumentValueWatcher m_ChildWatcher;
  DocumentValueWatcher m_OutputWatcher;

  Optional<UIEditorNodeSelection> m_Selection;
  std::vector<std::unique_ptr<UIOutputEquationEditor>> m_Editors;
};

