#pragma once

#include <QWidget>
#include <qlabel.h>

#include "GenericInput.h"
#include "DocumentValueWatcher.h"
#include "UIEditor.h"

#include "Runtime/UI/UIDef.refl.h"

class UIEquationEditor : public QWidget
{
  Q_OBJECT
public:
  UIEquationEditor(NotNullPtr<UIEditor> editor, czstr name, czstr path, Delegate<NullOptPtr<RMergeList<UIDefEquation>>> && getter, QWidget * parent = nullptr);

protected:

  void Refresh();
  void WriteValue();

protected:

  void resizeEvent(QResizeEvent * ev) override;

private:
  std::unique_ptr<QLabel> m_Label;
  std::unique_ptr<GenericInput> m_Input;

  std::string m_VariableName;
  DocumentValueWatcher m_Watcher;

  Delegate<NullOptPtr<RMergeList<UIDefEquation>>> m_Getter;
};


