
#include "UIOutputEquationEditor.h"

#include "Runtime/UI/UIDef.refl.meta.h"

#include "StormData/StormDataJson.h"


UIOutputEquationEditor::UIOutputEquationEditor(NotNullPtr<UIEditor> editor, NotNullPtr<UIEditorOutputEquationList> parent_list, std::size_t child_index, czstr child_name, czstr var_name, czstr path,
                                               Delegate<NullOptPtr<RMergeList<UIDefOutputEquation>>> && getter, QWidget * parent) :
  QWidget(parent),
  m_ParentList(parent_list),
  m_Label(std::make_unique<QLabel>(QString(child_name) + "." + QString(var_name), this)),
  m_Input(std::make_unique<GenericInput>(this)),
  m_ChildIndex(child_index),
  m_ChildName(child_name),
  m_VariableName(var_name),
  m_Watcher(editor),
  m_Getter(std::move(getter))
{
  m_Watcher.SetPath(path, true, true, [this] {return m_Getter() != nullptr; });
  m_Watcher.SetAllUpdateCallbacks([this] { Refresh(); });

  m_Input->SetUpdateCallback([this] { WriteValue(); });
  Refresh();
}

void UIOutputEquationEditor::Refresh()
{
  auto list = m_Getter();
  if (list == nullptr)
  {
    return;
  }

  for (auto elem : *list)
  {
    if (elem.second.m_VariableName == m_VariableName && elem.second.m_ChildIndex == (int)m_ChildIndex)
    {
      m_Input->RemoteUpdate(elem.second.m_Equation.data());
      return;
    }
  }

  m_Input->RemoteUpdate("");
}

void UIOutputEquationEditor::WriteValue()
{
  auto list = m_Getter();
  if (list == nullptr)
  {
    return;
  }

  m_ParentList->SetIgnoreChanges(true);

  for (auto elem : *list)
  {
    if (elem.second.m_ChildIndex == (int)m_ChildIndex && elem.second.m_VariableName == m_VariableName)
    {
      elem.second.m_Equation = m_Input->GetText();
      m_ParentList->SetIgnoreChanges(false);
      return;
    }
  }

  UIDefOutputEquation new_val;
  new_val.m_VariableName = m_VariableName;
  new_val.m_Equation = m_Input->GetText();
  new_val.m_ChildIndex = m_ChildIndex;
  list->EmplaceBack(std::move(new_val));
  m_ParentList->SetIgnoreChanges(false);
}

void UIOutputEquationEditor::resizeEvent(QResizeEvent * ev)
{
  int w = width() / 3;
  m_Label->setGeometry(QRect(0, 0, w, 20));
  m_Input->setGeometry(QRect(w + 1, 0, width() - w - 1, 20));
}
