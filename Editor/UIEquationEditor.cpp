
#include "UIEquationEditor.h"

#include "Runtime/UI/UIDef.refl.meta.h"

#include "StormData/StormDataJson.h"


UIEquationEditor::UIEquationEditor(NotNullPtr<UIEditor> editor, czstr name, czstr path, Delegate<NullOptPtr<RMergeList<UIDefEquation>>> && getter, QWidget * parent) :
  QWidget(parent),
  m_Label(std::make_unique<QLabel>(name + 2, this)),
  m_Input(std::make_unique<GenericInput>(this)),
  m_VariableName(name),
  m_Watcher(editor),
  m_Getter(std::move(getter))
{
  m_Watcher.SetPath(path, true, true, [this] {return m_Getter() != nullptr; });
  m_Watcher.SetAllUpdateCallbacks([this] { Refresh(); });

  m_Input->SetUpdateCallback([this] { WriteValue(); });
  Refresh();
}

void UIEquationEditor::Refresh()
{
  auto list = m_Getter();
  if (list == nullptr)
  {
    return;
  }

  for (auto elem : *list)
  {
    if (elem.second.m_VariableName == m_VariableName)
    {
      m_Input->RemoteUpdate(elem.second.m_Equation.data());
      return;
    }
  }

  m_Input->RemoteUpdate("");
}

void UIEquationEditor::WriteValue()
{
  auto list = m_Getter();
  if (list == nullptr)
  {
    return;
  }

  for (auto elem : *list)
  {
    if (elem.second.m_VariableName == m_VariableName)
    {
      elem.second.m_Equation = m_Input->GetText();
      return;
    }
  }

  UIDefEquation new_val;
  new_val.m_VariableName = m_VariableName;
  new_val.m_Equation = m_Input->GetText();
  list->EmplaceBack(std::move(new_val));
}

void UIEquationEditor::resizeEvent(QResizeEvent * ev)
{
  int w = width() / 3;
  m_Label->setGeometry(QRect(0, 0, w, 20));
  m_Input->setGeometry(QRect(w + 1, 0, width() - w - 1, 20));
}
