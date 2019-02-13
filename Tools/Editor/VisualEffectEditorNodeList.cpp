
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

#include "Runtime/VisualEffect/VisualEffectDef.refl.meta.h"

#include "VisualEffectEditor.h"
#include "VisualEffectEditorNodeList.h"
#include "VisualEffectEditorViewer.h"


VisualEffectEditorNodeList::VisualEffectEditorNodeList(NotNullPtr<VisualEffectEditor> editor, VisualEffectDef & ui, QWidget * parent) :
  QWidget(parent),
  m_Editor(editor),
  m_VisualEffect(ui),
  m_Watcher(editor),
  m_ScrollBar(std::make_unique<QScrollBar>(this))
{
  setFocusPolicy(Qt::ClickFocus);
  setMaximumWidth(220);

  connect(m_ScrollBar.get(), &QScrollBar::valueChanged, this, &VisualEffectEditorNodeList::scrollChanged);

  m_Watcher.SetPath("", false, true, [] {return true; });
  m_Watcher.SetAllUpdateCallbacks([this] { UpdateScroll(); });
}

void VisualEffectEditorNodeList::ChangeSelection(const VisualEffectEditorNodeSelection & layer)
{
  m_Selection = layer;
  repaint();
}

void VisualEffectEditorNodeList::ClearSelection()
{
  m_Selection.Clear();
  repaint();
}

Vector2 VisualEffectEditorNodeList::VisitElements(Delegate<bool, const VisualEffectEditorNodeSelection &, const std::string &, int, int> && visitor)
{
  int x = 10;
  int y = 0;

  for (auto def : m_VisualEffect.m_Emitters)
  {
    VisualEffectEditorNodeSelection sel;
    sel.m_Emitter = def.first;

    if (visitor(sel, def.second.m_Properties.m_Name.ToString(), x, y) == false)
    {
      return Vector2(x, y);
    }

    y += 13;
  }

  return Vector2(x, y);
}


Optional<VisualEffectEditorNodeSelection> VisualEffectEditorNodeList::GetNodeForPosition(int y)
{
  Optional<VisualEffectEditorNodeSelection> selection;
  VisitElements([this, &selection, y](const VisualEffectEditorNodeSelection & layer, const std::string & name, int x_pos, int y_pos) -> bool
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

void VisualEffectEditorNodeList::NodeRemoved(const VisualEffectEditorNodeSelection & node)
{
  if (m_Selection && node.m_Emitter == m_Selection->m_Emitter)
  {
    m_Editor->ClearSelection();
  }

  UpdateScroll();
}

void VisualEffectEditorNodeList::UpdateScroll()
{
  auto content_dims = VisitElements([](const VisualEffectEditorNodeSelection &, const std::string &, int, int) { return true; });
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

void VisualEffectEditorNodeList::paintEvent(QPaintEvent * ev)
{
  QPainter p(this);

  p.fillRect(0, 0, width(), height(), palette().color(QPalette::Window));
  int layer_height = fontMetrics().height();

  VisitElements([&](const VisualEffectEditorNodeSelection & layer, const std::string & name, int x_pos, int y_pos)
  {
    y_pos -= m_ScrollBar->value();

    if (m_Selection && layer.m_Emitter == m_Selection->m_Emitter)
    {
      p.fillRect(1, y_pos + 1, width() - 3, layer_height - 2, Qt::darkBlue);
      p.setPen(Qt::white);
    }
    else
    {
      p.setPen(palette().color(QPalette::Text));
    }

    p.drawText(x_pos, y_pos, width(), height(), 0, name.data());
    return true;
  });

  QStyleOptionFrame frame_option;
  frame_option.rect = QRect(0, 0, width() - 1, height() - 1);

  style()->drawPrimitive(QStyle::PE_Frame, &frame_option, &p, this);
}

void VisualEffectEditorNodeList::resizeEvent(QResizeEvent * ev)
{
  int scroll_width = m_ScrollBar->sizeHint().width();
  m_ScrollBar->setGeometry(width() - scroll_width - 2, 1, scroll_width, height() - 3);

  UpdateScroll();
}

void VisualEffectEditorNodeList::keyPressEvent(QKeyEvent * ev)
{

}

void VisualEffectEditorNodeList::mousePressEvent(QMouseEvent * ev)
{
  auto selection = GetNodeForPosition(ev->y());
  if (selection)
  {

    m_Editor->ChangeSelection(selection.Value());
  }

  if (ev->button() == Qt::RightButton)
  {
    QMenu menu(this);

    auto action = menu.addAction(QString("Add Emitter"));
    connect(action, &QAction::triggered, this, &VisualEffectEditorNodeList::addNewElement);

    menu.addSeparator();

    if (m_Selection)
    {
      auto del_action = menu.addAction("Delete");
      connect(del_action, &QAction::triggered, this, &VisualEffectEditorNodeList::deleteSelection);
    }

    menu.exec(mapToGlobal(ev->pos()));
  }
}

void VisualEffectEditorNodeList::wheelEvent(QWheelEvent * ev)
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

void VisualEffectEditorNodeList::scrollChanged()
{
  repaint();
}

void VisualEffectEditorNodeList::addNewElement()
{
  auto name = std::string("Emitter") + std::to_string(m_VisualEffect.m_Emitters.HighestIndex() + 2);

  VisualEffectDefEmitter new_element;
  new_element.m_Properties.m_Name = name;

  m_VisualEffect.m_Emitters.EmplaceBack(std::move(new_element));

  VisualEffectEditorNodeSelection new_selection;
  new_selection.m_Emitter = m_VisualEffect.m_Emitters.HighestIndex();
  m_Editor->ChangeSelection(new_selection);
}

void VisualEffectEditorNodeList::deleteSelection()
{
  if (m_Selection)
  {
    m_VisualEffect.m_Emitters.RemoveAt(m_Selection->m_Emitter);
  }
}
