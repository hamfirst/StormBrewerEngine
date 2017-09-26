
#include "VisualEffectEquationEditor.h"

#include "Runtime/VisualEffect/VisualEffectDef.refl.meta.h"

#include "StormData/StormDataJson.h"


VisualEffectEquationEditor::VisualEffectEquationEditor(NotNullPtr<VisualEffectEditor> editor, czstr name, czstr path, 
                                                       Delegate<NullOptPtr<RMap<uint32_t, VisualEffectDefEquation>>> && getter, QWidget * parent) :
  QWidget(parent),
  m_Label(std::make_unique<QLabel>(name + 2, this)),
  m_Input(std::make_unique<GenericInput>(this)),
  m_VariableName(name),
  m_VariableNameHash(crc32(name)),
  m_Watcher(editor),
  m_Getter(std::move(getter))
{
  m_Watcher.SetPath(path, true, true, [this] {return m_Getter() != nullptr; });
  m_Watcher.SetAllUpdateCallbacks([this] { Refresh(); });

  m_Input->SetUpdateCallback([this] { WriteValue(); });
  Refresh();
}

void VisualEffectEquationEditor::Refresh()
{
  auto list = m_Getter();
  if (list == nullptr)
  {
    return;
  }

  auto eq = list->TryGet(m_VariableNameHash);
  if (eq)
  {
    m_Input->RemoteUpdate(eq->m_Equation.data());
  }
  else
  {
    m_Input->RemoteUpdate("");
  }
}

void VisualEffectEquationEditor::WriteValue()
{
  auto list = m_Getter();
  if (list == nullptr)
  {
    return;
  }

  auto text = m_Input->GetText();
  if (text.size() == 0)
  {
    list->RemoveAt(m_VariableNameHash);
  }
  else
  {
    auto eq = list->TryGet(m_VariableNameHash);
    if (eq)
    {
      eq->m_Equation = m_Input->GetText();
    }
    else
    {
      VisualEffectDefEquation new_val;
      new_val.m_VariableName = m_VariableName;
      new_val.m_Equation = text;
      list->EmplaceAt(m_VariableNameHash, std::move(new_val));
    }
  }
}

void VisualEffectEquationEditor::resizeEvent(QResizeEvent * ev)
{
  int w = width() / 3;
  m_Label->setGeometry(QRect(0, 0, w, 20));
  m_Input->setGeometry(QRect(w + 1, 0, width() - w - 1, 20));
}
