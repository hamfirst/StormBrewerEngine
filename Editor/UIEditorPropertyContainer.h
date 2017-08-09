#pragma once

#include <QWidget>
#include <QScrollBar>

#include "Runtime/UI/UIDef.refl.h"

#include "PropertyEditorWidget.h"
#include "DocumentValueWatcher.h"
#include "UIEditorNode.h"
#include "UIEditorEquationList.h"
#include "UIEditorOutputEquationList.h"

class UIEditor;
class UIEditorNodeList;
class UIEditorEquationList;
class UIEditorOutputEquationList;

class UIEditorPropertyContainer : public QWidget
{
  Q_OBJECT;

public:
  UIEditorPropertyContainer(NotNullPtr<UIEditor> editor, UIDef & ui, Delegate<void> && size_change_cb, QWidget * parent = nullptr);

  void ChangeSelection(const UIEditorNodeSelection & selection);
  void ClearSelection();

protected:
  void RepositionChildren();
  void SizeChanged();

protected:

  void resizeEvent(QResizeEvent * ev);

private:
  NotNullPtr<UIEditor> m_Editor;
  UIDef & m_UI;

  Delegate<void> m_SizeChanged;

  std::unique_ptr<QWidget> m_InitDataProperties;
  std::unique_ptr<QWidget> m_ElementName;
  std::unique_ptr<QWidget> m_InputsList;
  std::unique_ptr<UIEditorEquationList> m_Equations;
  std::unique_ptr<UIEditorOutputEquationList> m_OutputEquations;
};
