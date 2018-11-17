
#include <QMenu>
#include <QKeyEvent>
#include <QPainter>
#include <QStyle>
#include <QStyleOptionFrame>
#include <QMouseEvent>

#include <StormRefl/StormReflJson.h>
#include <StormRefl/StormReflMetaEnum.h>
#include <StormData/StormDataJson.h>
#include <sb/vector.h>

#include "Runtime/UI/UIDef.refl.meta.h"
#include "Runtime/UI/UITypes.refl.meta.h"

#include "UIEditor.h"
#include "UIEditorNodeList.h"
#include "UIEditorViewer.h"


UIEditorNodeList::UIEditorNodeList(NotNullPtr<UIEditor> editor, UIDef & ui, QWidget * parent) :
  QWidget(parent),
  m_Editor(editor),
  m_UI(ui),
  m_Watcher(editor),
  m_ScrollBar(std::make_unique<QScrollBar>(this))
{
  setFocusPolicy(Qt::ClickFocus);
  setMaximumWidth(220);

  connect(m_ScrollBar.get(), &QScrollBar::valueChanged, this, &UIEditorNodeList::scrollChanged);

  m_Watcher.SetPath("", false, true, [] {return true; });
  m_Watcher.SetAllUpdateCallbacks([this] { UpdateScroll(); });
}

void UIEditorNodeList::ChangeSelection(const UIEditorNodeSelection & layer)
{
  m_Selection = layer;
  repaint();
}

void UIEditorNodeList::ClearSelection()
{
  m_Selection.Clear();
  repaint();
}

Vector2 UIEditorNodeList::VisitElements(Delegate<bool, const UIDef &, const UIEditorNodeSelection &, const std::string &, int, int> && visitor)
{
  int x = 3, y = 0;
  TraverseElement(m_UI, visitor, "", "Root", x, y);

  return Vector2(x, y);
}

bool UIEditorNodeList::TraverseElement(UIDef & ui, Delegate<bool, const UIDef &, const UIEditorNodeSelection &, const std::string &, int, int> & visitor, 
  const std::string & path, const std::string & name, int & x, int & y)
{
  UIEditorNodeSelection sel = { path };
  if (visitor(ui, sel, name, x, y) == false)
  {
    return false;
  }

  x += 10;
  y += 13;
  for (auto def : ui.m_Children)
  {
    auto child_path = path + "." + std::to_string(def.first);
    if (TraverseElement(def.second.m_UI, visitor, child_path, def.second.m_Name.ToString(), x, y) == false)
    {
      return false;
    }
  }

  x -= 10;
  return true;
}

Optional<UIEditorNodeSelection> UIEditorNodeList::GetNodeForPosition(int y)
{
  Optional<UIEditorNodeSelection> selection;
  VisitElements([this, &selection, y](const UIDef & ui, const UIEditorNodeSelection & layer, const std::string & name, int x_pos, int y_pos) -> bool
  {
    int layer_height = fontMetrics().height();

    y_pos -= m_ScrollBar->value();
    if (y < y_pos + layer_height)
    {
      selection = layer;
      return false;
    }
    else
    {
      return true;
    }
  });

  return selection;
}

void UIEditorNodeList::NodeRemoved(const UIEditorNodeSelection & node)
{
  if (m_Selection && node.m_NodePath == m_Selection->m_NodePath)
  {
    m_Editor->ClearSelection();
  }

  UpdateScroll();
}

void UIEditorNodeList::UpdateScroll()
{
  auto content_dims = VisitElements([](const UIDef & ui, const UIEditorNodeSelection &, const std::string &, int, int) { return true; });
  auto content_height = content_dims.y;

  if (height() >= content_height)
  {
    m_ScrollBar->hide();
    m_ScrollBar->setMaximum(0);
  }
  else
  {
    m_ScrollBar->show();
    m_ScrollBar->setMaximum(content_height - height());
    m_ScrollBar->setPageStep(height());
  }

  repaint();
}

void UIEditorNodeList::paintEvent(QPaintEvent * ev)
{
  QPainter p(this);

  p.fillRect(0, 0, width(), height(), Qt::white);

  QStyleOptionFrame frame_option;
  frame_option.rect = QRect(0, 0, width() - 1, height() - 1);

  style()->drawPrimitive(QStyle::PE_Frame, &frame_option, &p, this);

  int layer_height = fontMetrics().height();

  VisitElements([&](const UIDef & ui, const UIEditorNodeSelection & layer, const std::string & name, int x_pos, int y_pos)
  {
    y_pos -= m_ScrollBar->value();

    if (m_Selection && layer.m_NodePath == m_Selection->m_NodePath)
    {
      p.fillRect(0, y_pos, width() - 1, layer_height, Qt::darkBlue);
      p.setPen(Qt::white);
    }
    else
    {
      p.setPen(Qt::black);
    }

    p.drawText(x_pos, y_pos, width(), height(), 0, name.data());
    return true;
  });
}

void UIEditorNodeList::resizeEvent(QResizeEvent * ev)
{
  int scroll_width = m_ScrollBar->sizeHint().width();
  m_ScrollBar->setGeometry(width() - scroll_width - 2, 1, scroll_width, height() - 3);

  UpdateScroll();
}

void UIEditorNodeList::keyPressEvent(QKeyEvent * ev)
{

}

void UIEditorNodeList::mousePressEvent(QMouseEvent * ev)
{
  auto selection = GetNodeForPosition(ev->y());
  if (selection == false)
  {
    return;
  }

  m_Editor->ChangeSelection(selection.Value());

  if (ev->button() == Qt::RightButton)
  {
    QMenu menu(this);

    auto link_action = menu.addAction("Link File...");
    connect(link_action, &QAction::triggered, this, &UIEditorNodeList::linkElement);
    menu.addSeparator();

    auto visitor = [&](auto f)
    {
      auto action = menu.addAction(QString("Add ") + QString(f.GetName() + 1));
      action->setData(f.GetName());
      connect(action, &QAction::triggered, this, &UIEditorNodeList::addNewElement);
    };

    StormReflVisitEnumValues<UIElementType>::VisitEach(visitor);
    menu.addSeparator();

    if (m_Selection->m_NodePath.size() > 0)
    {
      auto del_action = menu.addAction("Delete");
      connect(del_action, &QAction::triggered, this, &UIEditorNodeList::deleteSelection);
    }

    menu.exec(mapToGlobal(ev->pos()));
  }
}

void UIEditorNodeList::wheelEvent(QWheelEvent * ev)
{
  if (ev->delta() > 0)
  {
    m_ScrollBar->setValue(m_ScrollBar->value() - 120);
  }
  else
  {
    m_ScrollBar->setValue(m_ScrollBar->value() + 120);
  }
}

void UIEditorNodeList::scrollChanged()
{
  repaint();
}

void UIEditorNodeList::linkElement()
{
  auto file_name = m_Editor->GetFileNameForAssetType("ui");

  if (file_name)
  {
    m_Editor->BeginTransaction();

    auto ui = UIEditor::GetUIForPath(m_UI, m_Selection->m_NodePath.data());
    if (ui != nullptr)
    {
      m_Editor->BeginTransaction();

      auto new_index = ui->m_Children.HighestIndex() + 1;
      auto name = std::string("New") + std::to_string(ui->m_Children.HighestIndex() + 2);

      UIDefChild & new_element = ui->m_Children.EmplaceBack();
      new_element.m_Name = name;

      auto link_path = StormDataGetPath(new_element.m_UI);

      m_Editor->CreateLink(file_name->data(), "", link_path.data());
      m_Editor->CommitChanges();

      auto new_selection = m_Selection.Value();
      new_selection.m_NodePath += "." + name;
      m_Editor->ChangeSelection(new_selection);
    }
  }
}

void UIEditorNodeList::addNewElement()
{
  QAction * action = qobject_cast<QAction *>(sender());
  if (action && m_Selection)
  {
    auto enum_name = action->data().toString().toStdString();
    auto enum_name_hash = crc32(enum_name);

    UIElementType type_enum = UIElementType::kContainer;
    StormReflGetEnumFromHash(type_enum, enum_name_hash);

    auto type_name_hash = UIManager::GetElementTypeNameHashForEnum(type_enum);

    auto ui = UIEditor::GetUIForPath(m_UI, m_Selection->m_NodePath.data());
    if (ui != nullptr)
    {
      auto name = std::string("New") + std::to_string(ui->m_Children.HighestIndex() + 2);

      UIDefChild new_element;
      new_element.m_UI.m_InitData.SetTypeFromNameHash(type_name_hash);
      new_element.m_Name = name;

      ui->m_Children.EmplaceBack(std::move(new_element));

      auto new_selection = m_Selection.Value();
      new_selection.m_NodePath += "." + name;
      m_Editor->ChangeSelection(new_selection);
    }
  }
}

void UIEditorNodeList::deleteSelection()
{
  if (m_Selection && m_Selection->m_NodePath.size() > 0)
  {
    auto prev_node = m_Selection->m_NodePath.rfind('.');
    if (prev_node != std::string::npos)
    {
      auto parent_path = m_Selection->m_NodePath.substr(0, prev_node);
      auto child_index = stoi(m_Selection->m_NodePath.substr(prev_node + 1));
      auto parent = UIEditor::GetUIForPath(m_UI, parent_path.data());

      if (parent)
      {
        parent->m_Children.RemoveAt(child_index);
      }
    }
  }
}
