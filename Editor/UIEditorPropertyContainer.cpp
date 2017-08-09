
#include <QMenu>
#include <QKeyEvent>
#include <QPainter>
#include <QStyle>
#include <QStyleOptionFrame>
#include <QMouseEvent>

#include <StormRefl/StormReflJson.h>
#include <StormData/StormDataJson.h>

#include "UIEditor.h"
#include "UIEditorPropertyContainer.h"

UIEditorPropertyContainer::UIEditorPropertyContainer(NotNullPtr<UIEditor> editor, UIDef & ui, Delegate<void> && size_change_cb, QWidget * parent) :
  QWidget(parent),
  m_Editor(editor),
  m_UI(ui),
  m_SizeChanged(std::move(size_change_cb))
{
  setFocusPolicy(Qt::ClickFocus);
}

void UIEditorPropertyContainer::ChangeSelection(const UIEditorNodeSelection & selection)
{
  auto ui = UIEditor::GetUIForPath(m_UI, selection.m_NodePath.data());
  if (ui == nullptr)
  {
    ClearSelection();
    return;
  }

  auto & prop_db = m_Editor->GetPropertyFieldDatabase();
  auto prop_def = prop_db.FindStructData(crc32("UIDef"));

  if (prop_def == nullptr)
  {
    ClearSelection();
    return;
  }

  NullOptPtr<PropertyField> init_data_props;
  NullOptPtr<PropertyField> input_props;

  for (auto & elem : prop_def->m_Struct.m_StructData->m_Members)
  {
    if (elem.m_Name == "m_InitData")
    {
      init_data_props = elem.m_FieldData;
      continue;
    }

    if (elem.m_Name == "m_Inputs")
    {
      input_props = elem.m_FieldData;
    }
  }

  if (init_data_props == nullptr || input_props == nullptr)
  {
    ClearSelection();
    return;
  }

  std::unique_ptr<char[]> sel_path = std::make_unique<char[]>(selection.m_NodePath.size() + 1);
  memcpy(sel_path.get(), selection.m_NodePath.data(), selection.m_NodePath.size());
  sel_path.get()[selection.m_NodePath.size()] = 0;

  auto init_data_ptr = [this, path = std::move(sel_path)]() -> void *
  { 
    auto ui = UIEditor::GetUIForPath(m_UI, path.get());
    if (ui == nullptr)
    {
      return nullptr;
    }

    return &ui->m_InitData;
  };

  m_ElementName.reset();
  if (selection.m_NodePath.size() > 0)
  {
    auto prev_node = selection.m_NodePath.rfind('.');
    if (prev_node != std::string::npos)
    {
      auto parent_path = selection.m_NodePath.substr(0, prev_node);
      auto child_index = stoi(selection.m_NodePath.substr(prev_node + 1));

      auto parent = UIEditor::GetUIForPath(m_UI, parent_path.data());
      auto child = parent ? parent->m_Children.TryGet(child_index) : nullptr;

      if (child)
      {
        std::unique_ptr<char[]> sel_path = std::make_unique<char[]>(parent_path.size() + 1);
        memcpy(sel_path.get(), parent_path.data(), parent_path.size());
        sel_path.get()[parent_path.size()] = 0;

        auto parent_data_ptr = [this, path = std::move(sel_path), index = child_index]() -> void *
        {
          auto ui = UIEditor::GetUIForPath(m_UI, path.get());
          if (ui == nullptr)
          {
            return nullptr;
          }

          auto child = ui->m_Children.TryGet(index);
          if (child == nullptr)
          {
            return nullptr;
          }

          return &child->m_Name;
        };

        auto base_path = StormDataGetPath(child->m_Name);
        m_ElementName = PropertyEditorCreate(m_Editor, prop_db.GetBasicField(PropertyFieldType::kString), true, 
          std::move(parent_data_ptr), std::move(base_path), [this] { SizeChanged(); }, nullptr, this);
        m_ElementName->show();
      }
    }
  }

  auto base_path = StormDataGetPath(ui->m_InitData);
  m_InitDataProperties = PropertyEditorCreate(m_Editor, init_data_props, true, std::move(init_data_ptr), std::move(base_path), [this] { SizeChanged(); }, nullptr, this);
  m_InitDataProperties->show();

  sel_path = std::make_unique<char[]>(selection.m_NodePath.size() + 1);
  memcpy(sel_path.get(), selection.m_NodePath.data(), selection.m_NodePath.size());
  sel_path.get()[selection.m_NodePath.size()] = 0;

  auto input_data_ptr = [this, path = std::move(sel_path)]() -> void *
  {
    auto ui = UIEditor::GetUIForPath(m_UI, path.get());
    if (ui == nullptr)
    {
      return nullptr;
    }

    return &ui->m_Inputs;
  };

  base_path = StormDataGetPath(ui->m_Inputs);
  m_InputsList = PropertyEditorCreate(m_Editor, input_props, true, std::move(input_data_ptr), std::move(base_path), [this] { SizeChanged(); }, "Inputs", this);
  m_InputsList->show();

  m_Equations = std::make_unique<UIEditorEquationList>(m_Editor, m_UI, [this] { SizeChanged(); }, this);
  m_Equations->ChangeSelection(selection);
  m_Equations->show();

  m_OutputEquations = std::make_unique<UIEditorOutputEquationList>(m_Editor, m_UI, [this] { SizeChanged(); }, this);
  m_OutputEquations->ChangeSelection(selection);
  m_OutputEquations->show();

  SizeChanged();
}

void UIEditorPropertyContainer::ClearSelection()
{
  m_InitDataProperties.reset();
  m_ElementName.reset();
  m_InputsList.reset();

  SizeChanged();
}

void UIEditorPropertyContainer::RepositionChildren()
{
  int height = 0;
  int w = width() - 1;

  if (m_ElementName)
  {
    auto elem_height = m_ElementName->minimumHeight();
    m_ElementName->setGeometry(0, height, w, elem_height);
    height += elem_height + 10;
  }

  if (m_InitDataProperties)
  {
    auto elem_height = m_InitDataProperties->minimumHeight();
    m_InitDataProperties->setGeometry(0, height, w, elem_height);
    height += elem_height + 5;
  }

  if (m_InputsList)
  {
    auto elem_height = m_InputsList->minimumHeight();
    m_InputsList->setGeometry(0, height, w, elem_height);
    height += elem_height;
  }

  if (m_Equations)
  {
    auto elem_height = m_Equations->minimumHeight();
    m_Equations->setGeometry(0, height, w, elem_height);
    height += elem_height;
  }

  if (m_OutputEquations)
  {
    auto elem_height = m_OutputEquations->minimumHeight();
    m_OutputEquations->setGeometry(0, height, w, elem_height);
    height += elem_height;
  }

  setMinimumHeight(height);
}

void UIEditorPropertyContainer::SizeChanged()
{
  RepositionChildren();
  m_SizeChanged();
}

void UIEditorPropertyContainer::resizeEvent(QResizeEvent * ev)
{
  RepositionChildren();
}
