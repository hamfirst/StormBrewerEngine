#include "DraggableList.h"
#include "VectorRearrange.h"

#include <QResizeEvent>
#include <QApplication>
#include <QGuiApplication>
#include <QStyleHints>
#include <QStyle>
#include <QTimer>
#include <QFrame>
#include <QPainter>

DraggableList::DraggableList(Qt::Orientation orientation, bool invert, QWidget *parent) : QWidget(parent)
{
  m_Orientation = orientation;
  m_Invert = invert;
  m_Scroll = new QScrollBar(orientation, this);
  m_IgnoreScrollEvents = false;
  m_ScaleToFit = false;

  m_Dragging = false;
  m_DraggingOriginalIndex = 0;
  m_DraggingTargetIndex = 0;
  m_DragTimerLastUpdate = 0;
  m_DragScrollError = 0;

  connect(m_Scroll, &QScrollBar::valueChanged, this, &DraggableList::scrollValueChanged);

  setMouseTracking(true);

  m_Frame = new QFrame(this);
  m_Frame->setFrameStyle(QFrame::Panel | QFrame::Sunken);
  m_Frame->setAttribute(Qt::WA_TransparentForMouseEvents);

  m_ScrollVal = std::make_unique<QtLerpVar>(false);

  QTimer * updater = new QTimer(this);
  connect(updater, &QTimer::timeout, this, &DraggableList::updateAnimations);
  updater->start(16);
}

void DraggableList::SetInitialWidgets(const std::vector<QWidget *> & widgets)
{
  m_Widgets = widgets;

  for (auto widget : m_Widgets)
  {
    widget->setParent(this);
    widget->show();

    m_WidgetPositions.emplace_back(std::make_unique<QtLerpVar>(false, 0.5f));
    m_IsSelected.emplace_back(false);
  }

  updateScrolls();
  updateContent();

  for (auto & pos : m_WidgetPositions)
  {
    pos->Complete();
  }

  finalizePositions(true);

  m_Frame->raise();
}

void DraggableList::AddWidget(QWidget * widget, int index)
{
  widget->setParent(this);
  widget->show();

  if(index < 0)
  {
    index = (int)m_Widgets.size();
  }

  m_Widgets.insert(m_Widgets.begin() + index, widget);
  m_WidgetPositions.emplace(m_WidgetPositions.begin() + index, std::make_unique<QtLerpVar>(false, 0.5f));
  m_IsSelected.emplace(m_IsSelected.begin() + index, false);

  updateScrolls();
  updateContent();

  m_WidgetPositions[index]->Complete();
  m_Frame->raise();
}

void DraggableList::RemoveWidget(QWidget * widget)
{
  for(int index = 0; index < (int)m_Widgets.size(); index++)
  {
    if(m_Widgets[index] == widget)
    {
      m_Widgets.erase(m_Widgets.begin() + index);
      m_WidgetPositions.erase(m_WidgetPositions.begin() + index);
      m_IsSelected.erase(m_IsSelected.begin() + index);
      break;
    }
  }

  updateScrolls();
  updateContent();
}


void DraggableList::RemoveAllWidgets()
{
  m_Widgets.clear();
  updateScrolls();
  updateContent();
}

void DraggableList::BringIntoView(int index)
{
  int pos = 0;
  int length = 0;

  if (m_Invert == false)
  {
    if (m_Orientation == Qt::Horizontal)
    {
      for (int widget_index = 0; widget_index < index; widget_index++)
      {
        auto widget = m_Widgets[widget_index];

        QSize size = widget->sizeHint();
        pos += size.width() - 1;
      }

      length = m_Widgets[index]->sizeHint().width();
    }
    else
    {
      for (int widget_index = 0; widget_index < index; widget_index++)
      {
        auto widget = m_Widgets[widget_index];

        QSize size = widget->sizeHint();
        pos += size.height() - 1;
      }

      length = m_Widgets[index]->sizeHint().height();
    }
  }
  else
  {
    if (m_Orientation == Qt::Horizontal)
    {
      for (int widget_index = (int)m_Widgets.size() - 1; widget_index > index; widget_index--)
      {
        auto widget = m_Widgets[widget_index];

        QSize size = widget->sizeHint();
        pos += size.width() - 1;
      }

      length = m_Widgets[index]->sizeHint().width();
    }
    else
    {
      for (int widget_index = (int)m_Widgets.size() - 1; widget_index > index; widget_index--)
      {
        auto widget = m_Widgets[widget_index];

        QSize size = widget->sizeHint();
        pos += size.height() - 1;
      }

      length = m_Widgets[index]->sizeHint().height();
    }
  }

  int new_value;
  if (m_Orientation == Qt::Horizontal)
  {
    if (width() < length)
    {
      new_value = pos;
    }
    else
    {
      int min_value = pos + length - width();
      int max_value = pos;

      new_value = std::min(std::max(m_Scroll->value(), min_value), max_value);
    }
  }
  else
  {
    if (height() < length)
    {
      new_value = pos;
    }
    else
    {
      int min_value = pos + length - height();
      int max_value = pos;

      new_value = std::min(std::max(m_Scroll->value(), min_value), max_value);
    }
  }

  if (new_value != m_Scroll->value())
  {
    m_ScrollVal->SetTarget(new_value);
  }
}

void DraggableList::StartDragging(int target_index)
{
  m_Dragging = true;
  m_DraggingOriginalIndex = target_index;
  m_DraggingTargetIndex = target_index;

  m_DragTimer.start();
  m_DragTimerLastUpdate = 0;
  m_DragScrollError = 0;

  grabMouse();
}

void DraggableList::Rearrange(int src_index, int target_index)
{
  RearrangeVector(m_Widgets, src_index, target_index);
  RearrangeVector(m_WidgetPositions, src_index, target_index);
  RearrangeVector(m_IsSelected, src_index, target_index);

  updateScrolls();
  updateContent();
}

void DraggableList::SetScaleToFit(bool enable)
{
  m_ScaleToFit = enable;
}

void DraggableList::SetSelection(int index, bool additive)
{
  if (!additive)
  {
    ResetSelection();
  }

  m_IsSelected[index] = true;
}

void DraggableList::ResetSelection()
{
  for (auto val : m_IsSelected)
  {
    val = false;
  }
}

void DraggableList::RemoveSelection(int index)
{
  m_IsSelected[index] = false;
}

bool DraggableList::IsSelected(int index)
{
  return m_IsSelected[index];
}

void DraggableList::resizeEvent(QResizeEvent *event)
{
  updateScrolls();

  int scroll_size = this->style()->pixelMetric(QStyle::PM_ScrollBarExtent);

  if(m_Orientation == Qt::Horizontal)
  {
    m_Scroll->setGeometry(QRect(1, event->size().height() - scroll_size - 2, event->size().width() - 2, scroll_size - 2));
  }
  else
  {
    m_Scroll->setGeometry(QRect(event->size().width() - scroll_size - 2, 1, scroll_size - 2, event->size().height() - 2));
  }

  m_Frame->setGeometry(QRect(0, 0, event->size().width(), event->size().height()));

  updateContent();
  finalizePositions(true);
}

void DraggableList::wheelEvent(QWheelEvent * event)
{
  const int scroll_amount = 40;
  if (event->delta() > 0)
  {
    m_ScrollVal->SetTarget(std::max(m_ScrollVal->GetTarget() - scroll_amount, 0.0f));
  }
  else
  {
    m_ScrollVal->SetTarget(std::min(m_ScrollVal->GetTarget() + scroll_amount, (float)m_Scroll->maximum()));
  }
}

void DraggableList::mouseReleaseEvent(QMouseEvent *)
{
  if (m_Dragging)
  {
    m_Dragging = false;
    releaseMouse();

    if (m_DraggingOriginalIndex != m_DraggingTargetIndex)
    {
      emit dragComplete(m_DraggingOriginalIndex, m_DraggingTargetIndex);
    }

    updateContent();
    finalizePositions(true);
  }
}


void DraggableList::updateScrolls()
{
  int content_size = calculateContentSize();

  if(m_Orientation == Qt::Horizontal)
  {
    if(content_size <= width())
    {
      m_Scroll->hide();
      m_Scroll->setRange(0, 0);
      m_ScrollVal->SetTarget(0);
    }
    else
    {
      int scroll_size = content_size - width();
      m_Scroll->setRange(0, scroll_size);
      m_Scroll->setPageStep(width());
      m_Scroll->show();
    }
  }
  else
  {
    if(content_size <= height())
    {
      m_Scroll->hide();
      m_Scroll->setRange(0, 0);
      m_ScrollVal->SetTarget(0);
    }
    else
    {
      int scroll_size = content_size - height();
      m_Scroll->setRange(0, scroll_size);
      m_Scroll->setPageStep(height());
      m_Scroll->show();
    }
  }

  float new_scroll_val = std::min(std::max(m_ScrollVal->GetTarget(), 0.0f), (float)m_Scroll->maximum());
  m_ScrollVal->SetTarget(new_scroll_val);
}

void DraggableList::updateContent()
{
  int pos = 0;

  if (m_Invert == false)
  {
    if (m_Orientation == Qt::Horizontal)
    {
      for(int index = 0; index < (int)m_Widgets.size(); index++)
      {
        auto & widget = m_Widgets[transformDragIndex(index)];

        QSize size = widget->sizeHint();
        m_WidgetPositions[transformDragIndex(index)]->SetTarget(pos);

        pos += size.width() - 1;
      }
    }
    else
    {
      for (int index = 0; index < (int)m_Widgets.size(); index++)
      {
        auto & widget = m_Widgets[transformDragIndex(index)];

        QSize size = widget->sizeHint();
        m_WidgetPositions[transformDragIndex(index)]->SetTarget(pos);

        pos += size.height() - 1;
      }
    }
  }
  else
  {
    if (m_Orientation == Qt::Horizontal)
    {
      for(int index = (int)m_Widgets.size() - 1; index >= 0; index--)
      {
        auto widget = m_Widgets[transformDragIndex(index)];

        QSize size = widget->sizeHint();
        m_WidgetPositions[transformDragIndex(index)]->SetTarget(pos);

        pos += size.width() - 1;
      }
    }
    else
    {
      for (int index = (int)m_Widgets.size() - 1; index >= 0; index--)
      {
        auto widget = m_Widgets[transformDragIndex(index)];

        QSize size = widget->sizeHint();
        m_WidgetPositions[transformDragIndex(index)]->SetTarget(pos);

        pos += size.height() - 1;
      }
    }
  }
}

int DraggableList::calculateContentSize() const
{
  int size = 3;
  if(m_Orientation == Qt::Horizontal)
  {
    for(auto widget : m_Widgets)
    {
      size += widget->sizeHint().width() - 1;
    }
  }
  else
  {
    for(auto widget : m_Widgets)
    {
      size += widget->sizeHint().height() - 1;
    }
  }

  return size;
}

void DraggableList::finalizePositions(bool force)
{
  int pos_offset = (int)-m_ScrollVal->Get() + 1;

  for (int index = 0; index < (int)m_Widgets.size(); index++)
  {
    auto & pos = m_WidgetPositions[index];
    auto & widget = m_Widgets[index];

    QSize size = widget->sizeHint();

    if (m_ScaleToFit)
    {
      if (m_Orientation == Qt::Horizontal)
      {
        size.setHeight(std::max(widget->minimumSizeHint().height(), height() - 1));
      }
      else
      {
        size.setWidth(std::max(widget->minimumSizeHint().width(), width() - 1));
      }
    }

    bool is_modified;
    float value = pos->Get(is_modified);

    if (is_modified || force)
    {
      int drag_offset = (m_Dragging && index == m_DraggingOriginalIndex ? 10 : 1);
      if (m_Orientation == Qt::Horizontal)
      {
        widget->setGeometry(QRect((int)value + pos_offset, drag_offset, size.width(), size.height()));
      }
      else
      {
        widget->setGeometry(QRect(drag_offset, (int)value + pos_offset, size.width(), size.height()));
      }
    }
  }
}

void DraggableList::updateDrag()
{
  auto global_pos = QCursor::pos();
  auto local_pos = mapFromGlobal(global_pos);

  int original_target = m_DraggingTargetIndex;
  if (m_Orientation == Qt::Horizontal)
  {
    float scroll_pos = local_pos.x() + (int)m_ScrollVal->Get();

    if (m_Invert == false)
    {
      m_DraggingTargetIndex = (int)m_Widgets.size() - 1;
      for (int index = 0; index < (int)m_Widgets.size(); index++)
      {
        auto & widget = m_Widgets[index];
        auto size = widget->sizeHint();

        if (scroll_pos < size.width())
        {
          m_DraggingTargetIndex = index;
          break;
        }

        scroll_pos -= size.width();
      }
    }
    else
    {
      m_DraggingTargetIndex = 0;
      for (int index = (int)m_Widgets.size() - 1; index >= 0; index--)
      {
        auto & widget = m_Widgets[index];
        auto size = widget->sizeHint();

        if (scroll_pos < size.width())
        {
          m_DraggingTargetIndex = index;
          break;
        }

        scroll_pos -= size.width();
      }
    }
  }
  else
  {
    float scroll_pos = local_pos.y() + (int)m_ScrollVal->Get();

    if (m_Invert == false)
    {
      m_DraggingTargetIndex = (int)m_Widgets.size() - 1;
      for (int index = 0; index < (int)m_Widgets.size(); index++)
      {
        auto & widget = m_Widgets[index];
        auto size = widget->sizeHint();

        if (scroll_pos < size.height())
        {
          m_DraggingTargetIndex = index;
          break;
        }

        scroll_pos -= size.height();
      }
    }
    else
    {
      m_DraggingTargetIndex = 0;
      for (int index = (int)m_Widgets.size() - 1; index >= 0; index--)
      {
        auto & widget = m_Widgets[index];
        auto size = widget->sizeHint();

        if (scroll_pos < size.height())
        {
          m_DraggingTargetIndex = index;
          break;
        }

        scroll_pos -= size.height();
      }
    }
  }

  if (original_target != m_DraggingTargetIndex)
  {
    updateContent();
  }

  int update_secs = m_DragTimer.elapsed();
  float elapsed = (float)(update_secs - m_DragTimerLastUpdate) / 1000.0f;
  float movement = elapsed * 200;

  m_DragTimerLastUpdate = update_secs;

  if (m_Orientation == Qt::Horizontal)
  {
    if (local_pos.x() < 0)
    {
      m_DragScrollError -= movement;
    }
    else if (local_pos.x() > width())
    {
      m_DragScrollError += movement;
    }
    else
    {
      m_DragScrollError = 0;
    }
  }
  else
  {
    if (local_pos.y() < 0)
    {
      m_DragScrollError -= movement;
    }
    else if (local_pos.y() > height())
    {
      m_DragScrollError += movement;
    }
    else
    {
      m_DragScrollError = 0;
    }
  }

  int error = (int)m_DragScrollError;
  float ferror = (float)error;
  m_DragScrollError -= ferror;

  if (m_Orientation == Qt::Horizontal)
  {
    global_pos.setX(global_pos.x() - error);
  }
  else
  {
    global_pos.setY(global_pos.y() - error);
  }

  float new_scroll_target = std::max(std::min(m_ScrollVal->GetTarget() + ferror, (float)m_Scroll->maximum()), 0.0f);
  if (new_scroll_target != m_ScrollVal->GetTarget())
  {
    QCursor::setPos(global_pos);
    m_ScrollVal->SetTarget(new_scroll_target);
    float new_scroll_val = std::max(std::min(m_ScrollVal->Get() + ferror, (float)m_Scroll->maximum()), 0.0f);
    m_ScrollVal->SetValue(new_scroll_val);

    m_IgnoreScrollEvents = true;
    m_Scroll->setValue((int)new_scroll_val);
    m_IgnoreScrollEvents = false;
  }
}

int DraggableList::transformDragIndex(int index)
{
  if (m_Dragging == false)
  {
    return index;
  }

  if (index == m_DraggingTargetIndex)
  {
    return m_DraggingOriginalIndex;
  }

  int target_index = index;
  if (index == m_DraggingOriginalIndex && m_DraggingTargetIndex > m_DraggingOriginalIndex)
  {
    target_index++;
  }

  if (index > m_DraggingOriginalIndex)
  {
    target_index++;
  }

  if (index > m_DraggingTargetIndex)
  {
    target_index--;
  }

  return target_index;
}

void DraggableList::scrollValueChanged(int value)
{
  if (m_IgnoreScrollEvents == false)
  {
    m_ScrollVal->Set(value);
    finalizePositions(true);
  }
}

void DraggableList::updateAnimations()
{
  bool changed = false;
  for (auto & pos : m_WidgetPositions)
  {
    changed |= pos->update();
  }

  if (m_ScrollVal->update())
  {
    m_IgnoreScrollEvents = true;
    m_Scroll->setValue((int)m_ScrollVal->Get());
    m_IgnoreScrollEvents = false;

    changed = true;
  }

  if (m_Dragging)
  {
    updateDrag();
  }

  finalizePositions(changed || m_Dragging);
}
