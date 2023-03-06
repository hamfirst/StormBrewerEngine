#include "ExpandableList.h"

#include <QTimer>
#include <QStyle>
#include <QResizeEvent>
#include <QWheelEvent>

ExpandableList::ExpandableList(Qt::Orientation orientation, QWidget *parent) : QWidget(parent)
{
  m_Orientation = orientation;
  m_SelectedItem = 0;
  m_Scroll = new QScrollBar(orientation, this);
  m_IgnoreScrollEvents = false;

  connect(m_Scroll, &QScrollBar::valueChanged, this, &ExpandableList::scrollValueChanged);

  setMouseTracking(true);

  m_Frame = new QFrame(this);
  m_Frame->setFrameStyle(QFrame::Panel | QFrame::Sunken);
  m_Frame->setAttribute(Qt::WA_TransparentForMouseEvents);

  m_ScrollVal = std::make_unique<QtLerpVar>(false);

  QTimer * updater = new QTimer(this);
  connect(updater, &QTimer::timeout, this, &ExpandableList::updateAnimations);
  updater->start(16);
}


void ExpandableList::SetInitialWidgets(std::vector<QWidget *> && widgets)
{
  m_Widgets = std::move(widgets);

  for (int index = 0; index < (int)m_Widgets.size(); index++)
  {
    m_WidgetPositions.emplace(m_WidgetPositions.begin() + index, std::make_unique<QtLerpVar>(false, 0.5f));
    m_WidgetSizes.emplace(m_WidgetSizes.begin() + index, std::make_unique<QtLerpVar>(false, 0.5f));
  }

  updateContent();

  for (int index = 0; index < (int)m_Widgets.size(); index++)
  {
    m_WidgetPositions[index]->Complete();
    m_WidgetSizes[index]->Complete();
  }

  m_Frame->raise();
  finalizePositions(true);
}

void ExpandableList::AddWidget(int index, QWidget * widget)
{
  if(index < 0)
  {
    index = (int)m_Widgets.size();
  }

  m_Widgets.insert(m_Widgets.begin() + index, widget);
  m_WidgetPositions.emplace(m_WidgetPositions.begin() + index, std::make_unique<QtLerpVar>(false, 0.5f));
  m_WidgetSizes.emplace(m_WidgetSizes.begin() + index, std::make_unique<QtLerpVar>(false, 0.5f));
  updateContent();

  m_WidgetPositions[index]->Complete();
  m_WidgetSizes[index]->Complete();

  widget->setFocus();
  widget->show();

  m_SelectedItem = index;

  updateScrolls();
  updateContent();
  finalizePositions(true);

  m_Frame->raise();
}

void ExpandableList::RemoveWidget(QWidget * widget)
{
  for(std::size_t index = 0; index < m_Widgets.size(); index++)
  {
    if(m_Widgets[index] == widget)
    {
      m_Widgets.erase(m_Widgets.begin() + index);
      m_WidgetPositions.erase(m_WidgetPositions.begin() + index);
      m_WidgetSizes.erase(m_WidgetSizes.begin() + index);
      break;
    }
  }

  if (m_SelectedItem >= (int)m_Widgets.size())
  {
    m_SelectedItem = (int)m_Widgets.size() - 1;
  }

  updateScrolls();
  updateContent();
}

void ExpandableList::RemoveAllWidgets()
{
  m_Widgets.clear();

  m_SelectedItem = -1;

  updateScrolls();
  updateContent();
}

void ExpandableList::SelectItem(QWidget * widget)
{
  for (std::size_t index = 0; index < m_Widgets.size(); index++)
  {
    if (m_Widgets[index] == widget)
    {
      if(m_SelectedItem != (int)index)
      {
        m_SelectedItem = (int)index;
        updateContent();
      }
      return;
    }
  }

  if (m_SelectedItem != -1)
  {
    m_SelectedItem = -1;
    updateContent();
  }
}

void ExpandableList::resizeEvent(QResizeEvent *event)
{
  updateScrolls();
  updateContent();
  finalizePositions(true);

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
  finalizePositions(true);
}

void ExpandableList::wheelEvent(QWheelEvent * event)
{
  const int scroll_amount = 40;
  if (event->angleDelta().y() > 0)
  {
    m_ScrollVal->SetTarget(std::max(m_ScrollVal->GetTarget() - scroll_amount, 0.0f));
  }
  else
  {
    m_ScrollVal->SetTarget(std::min(m_ScrollVal->GetTarget() + scroll_amount, (float)m_Scroll->maximum()));
  }
}

void ExpandableList::updateScrolls()
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

void ExpandableList::updateContent()
{
  float pos = 0;
  if(m_Orientation == Qt::Horizontal)
  {
    for(std::size_t index = 0; index < m_Widgets.size(); index++)
    {
      auto & widget = m_Widgets[index];
      QSize widget_size = (m_SelectedItem == (int)index ? widget->sizeHint() : widget->minimumSizeHint());

      m_WidgetPositions[index]->SetTarget(pos);
      m_WidgetSizes[index]->SetTarget(widget_size.width());

      pos += widget_size.width();
    }
  }
  else
  {
    for(std::size_t index = 0; index < m_Widgets.size(); index++)
    {
      auto & widget = m_Widgets[index];
      QSize widget_size = (m_SelectedItem == (int)index ? widget->sizeHint() : widget->minimumSizeHint());

      m_WidgetPositions[index]->SetTarget(pos);
      m_WidgetSizes[index]->SetTarget(widget_size.height());

      pos += widget_size.height();
    }
  }
}

int ExpandableList::calculateContentSize() const
{
  int size = 0;
  if(m_Orientation == Qt::Horizontal)
  {
    for(std::size_t index = 0; index < m_Widgets.size(); index++)
    {
      auto & widget = m_Widgets[index];
      QSize widget_size = (m_SelectedItem == (int)index ? widget->sizeHint() : widget->minimumSizeHint());
      size += widget_size.width();
    }
  }
  else
  {
    for(std::size_t index = 0; index < m_Widgets.size(); index++)
    {
      auto & widget = m_Widgets[index];
      QSize widget_size = (m_SelectedItem == (int)index ? widget->sizeHint() : widget->minimumSizeHint());
      size += widget_size.height();
    }
  }

  return size;
}

void ExpandableList::finalizePositions(bool force)
{
  int pos_offset = (int)-m_ScrollVal->Get() + 1;

  int scroll_size = m_Scroll->isVisible() ? this->style()->pixelMetric(QStyle::PM_ScrollBarExtent) : 0;

  for (int index = 0; index < (int)m_Widgets.size(); index++)
  {
    auto & pos = m_WidgetPositions[index];
    auto & size = m_WidgetSizes[index];
    auto & widget = m_Widgets[index];

    bool pos_is_modified, size_is_modified;
    float pos_value = pos->Get(pos_is_modified);
    float size_value = size->Get(size_is_modified);

    if (size_is_modified || pos_is_modified || force)
    {
      if (m_Orientation == Qt::Horizontal)
      {
        widget->setGeometry(QRect((int)pos_value + pos_offset, 0, (int)size_value, height() - scroll_size - 1));
      }
      else
      {
        widget->setGeometry(QRect(0, (int)pos_value + pos_offset, width() - scroll_size - 1, (int)size_value));
      }
    }
  }
}

void ExpandableList::scrollValueChanged(int value)
{
  if (m_IgnoreScrollEvents == false)
  {
    m_ScrollVal->Set(value);
    finalizePositions(true);
  }
}

void ExpandableList::updateAnimations()
{
  bool changed = false;
  for (auto & pos : m_WidgetPositions)
  {
    changed |= pos->update();
  }

  for(auto & size : m_WidgetSizes)
  {
    changed |= size->update();
  }

  if (m_ScrollVal->update())
  {
    m_IgnoreScrollEvents = true;
    m_Scroll->setValue((int)m_ScrollVal->Get());
    m_IgnoreScrollEvents = false;

    changed = true;
  }

  if(changed)
  {
    finalizePositions(true);
  }
}

