
#include <QMenu>
#include <QKeyEvent>
#include <QPainter>
#include <QStyle>
#include <QStyleOptionFrame>
#include <QMouseEvent>

#include <StormRefl/StormReflJson.h>
#include <StormData/StormDataJson.h>

#include "UIEditor.h"
#include "UIEditorEquationList.h"

UIEditorEquationList::UIEditorEquationList(NotNullPtr<UIEditor> editor, UIDef & ui, Delegate<void> && size_change_cb, QWidget * parent) :
  QWidget(parent),
  m_Editor(editor),
  m_UI(ui),
  m_SizeChanged(std::move(size_change_cb)),
  m_Watcher(editor)
{
  setFocusPolicy(Qt::ClickFocus);
}

void UIEditorEquationList::ChangeSelection(const UIEditorNodeSelection & selection)
{
  ClearSelection();

  auto ui = UIEditor::GetUIForPath(m_UI, selection.m_NodePath.data());
  if (ui == nullptr)
  {
    return;
  }

  auto path = StormDataGetPath(ui->m_InitData) + ".T";
  m_Watcher.SetPath(path.data(), true, false, [this]() { return m_Selection && UIEditor::GetUIForPath(m_UI, m_Selection->m_NodePath.data()); });
  m_Watcher.SetAllUpdateCallbacks([this]() { RefreshElements(); });

  m_Selection = selection;
  RefreshElements();
}

void UIEditorEquationList::ClearSelection()
{
  m_Editors.clear();
  m_Selection.Clear();

  SizeChanged();
}

void UIEditorEquationList::RefreshElements()
{
  m_Editors.clear();

  auto ui = UIEditor::GetUIForPath(m_UI, m_Selection->m_NodePath.data());
  if (ui != nullptr)
  {
    uint32_t element_type = ui->m_InitData.GetTypeNameHash();
    auto variables = UIManager::GetVariablesForElementType(element_type);

    for (auto & var : variables)
    {
      auto path = StormDataGetPath(ui->m_Equations);
      auto data_ptr = [this]() -> NullOptPtr<RMergeList<UIDefEquation>>
      {
        auto ui = UIEditor::GetUIForPath(m_UI, m_Selection->m_NodePath.data());
        return ui ? &ui->m_Equations : nullptr;
      };

      m_Editors.emplace_back(std::make_unique<UIEquationEditor>(m_Editor, var.data(), path.data(), std::move(data_ptr), this));
      m_Editors.back()->show();
    }
  }

  SizeChanged();
}

void UIEditorEquationList::RepositionChildren()
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

void UIEditorEquationList::SizeChanged()
{
  RepositionChildren();
  m_SizeChanged();
}

void UIEditorEquationList::resizeEvent(QResizeEvent * ev)
{
  RepositionChildren();
}
