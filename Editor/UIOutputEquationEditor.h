#pragma once

#include <QWidget>
#include <qlabel.h>

#include "GenericInput.h"
#include "DocumentValueWatcher.h"
#include "UIEditor.h"

#include "Runtime/UI/UIDef.refl.h"

class UIOutputEquationEditor : public QWidget
{
  Q_OBJECT
public:
  UIOutputEquationEditor(NotNullPtr<UIEditor> editor, std::size_t child_index, czstr child_name, czstr var_name, czstr path, 
    Delegate<NullOptPtr<RMergeList<UIDefOutputEquation>>> && getter, QWidget * parent = nullptr);

protected:

  void Refresh();
  void WriteValue();

protected:

  void resizeEvent(QResizeEvent * ev) override;

private:
  std::unique_ptr<QLabel> m_Label;
  std::unique_ptr<GenericInput> m_Input;

  std::size_t m_ChildIndex;
  std::string m_ChildName;
  std::string m_VariableName;
  DocumentValueWatcher m_Watcher;

  Delegate<NullOptPtr<RMergeList<UIDefOutputEquation>>> m_Getter;
};


