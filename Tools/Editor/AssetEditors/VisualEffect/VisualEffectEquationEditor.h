#pragma once

#include <QWidget>
#include <qlabel.h>

#include "Tools/Editor/UI/GenericWidgets/GenericInput.h"
#include "Tools/Editor/Utility/DocumentValueWatcher.h"
#include "VisualEffectEditor.h"

#include "Runtime/VisualEffect/VisualEffectDef.refl.h"

class VisualEffectEquationEditor : public QWidget
{
  Q_OBJECT
public:
  VisualEffectEquationEditor(NotNullPtr<VisualEffectEditor> editor, czstr name, czstr path, Delegate<NullOptPtr<RMap<uint32_t, VisualEffectDefEquation>>> && getter, QWidget * parent = nullptr);

protected:

  void Refresh();
  void WriteValue();

protected:

  void resizeEvent(QResizeEvent * ev) override;

private:
  std::unique_ptr<QLabel> m_Label;
  std::unique_ptr<GenericInput> m_Input;

  std::string m_VariableName;
  uint32_t m_VariableNameHash;
  DocumentValueWatcher m_Watcher;

  Delegate<NullOptPtr<RMap<uint32_t, VisualEffectDefEquation>>> m_Getter;
};


