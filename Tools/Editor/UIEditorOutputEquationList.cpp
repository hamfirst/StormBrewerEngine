
#include <QMenu>
#include <QKeyEvent>
#include <QPainter>
#include <QStyle>
#include <QStyleOptionFrame>
#include <QMouseEvent>

#include <StormRefl/StormReflJson.h>
#include <StormData/StormDataJson.h>

#include "UIEditor.h"
#include "UIEditorOutputEquationList.h"

UIEditorOutputEquationList::UIEditorOutputEquationList(NotNullPtr<UIEditor> editor, UIDef & ui, Delegate<void> && size_change_cb, QWidget * parent) :
  QWidget(parent),
  m_Editor(editor),
  m_UI(ui),
  m_SizeChanged(std::move(size_change_cb)),
  m_ChildWatcher(editor),
  m_OutputWatcher(editor),
  m_IgnoreChanges(false)
{
  setFocusPolicy(Qt::ClickFocus);
}

void UIEditorOutputEquationList::ChangeSelection(const UIEditorNodeSelection & selection)
{
  ClearSelection();

  auto ui = UIEditor::GetUIForPath(m_UI, selection.m_NodePath.data());
  if (ui == nullptr)
  {
    return;
  }

  auto path = StormDataGetPath(ui->m_Children);
  m_ChildWatcher.SetPath(path.data(), true, true, [this]() { return m_Selection && UIEditor::GetUIForPath(m_UI, m_Selection->m_NodePath.data()); });
  m_ChildWatcher.SetAllUpdateCallbacks([this]() { if (m_IgnoreChanges == false) RefreshElements(); });

  path = StormDataGetPath(ui->m_Outputs);
  m_OutputWatcher.SetPath(path.data(), true, true, [this]() { return m_Selection && UIEditor::GetUIForPath(m_UI, m_Selection->m_NodePath.data()); });
  m_OutputWatcher.SetAllUpdateCallbacks([this]() { if(m_IgnoreChanges == false) RefreshElements(); });

  m_Selection = selection;
  RefreshElements();
}

void UIEditorOutputEquationList::ClearSelection()
{
  m_Editors.clear();
  m_Selection.Clear();

  SizeChanged();
}

void UIEditorOutputEquationList::RefreshElements()
{
  m_Editors.clear();

  auto ui = UIEditor::GetUIForPath(m_UI, m_Selection->m_NodePath.data());
  if (ui != nullptr)
  {
    uint32_t element_type = ui->m_InitData.GetTypeNameHash();
    auto variables = UIManager::GetVariablesForElementType(element_type);

    for (auto child : ui->m_Children)
    {
      for (auto var : child.second.m_UI.m_Inputs)
      {
        auto path = StormDataGetPath(ui->m_Outputs);
        auto data_ptr = [this]() -> NullOptPtr<RMergeList<UIDefOutputEquation>>
        {
          auto ui = UIEditor::GetUIForPath(m_UI, m_Selection->m_NodePath.data());
          return ui ? &ui->m_Outputs : nullptr;
        };

        m_Editors.emplace_back(std::make_unique<UIOutputEquationEditor>(m_Editor, this, child.first, child.second.m_Name.data(), 
          var.second.m_VariableName.data(), path.data(), std::move(data_ptr), this));
        m_Editors.back()->show();
      }
    }
  }

  SizeChanged();
}

void UIEditorOutputEquationList::RepositionChildren()
{
  int height = 0;
  int w = width() - 1;

  for (auto & elem : m_Editors)
  {
    elem->setGeometry(0, height, w, 20);
    height += 20;
  }

  setMinimumHeight(height);
}

void UIEditorOutputEquationList::SizeChanged()
{
  RepositionChildren();
  m_SizeChanged();
}

void UIEditorOutputEquationList::resizeEvent(QResizeEvent * ev)
{
  RepositionChildren();
}
