
#include "ScrollingPanel.h"

#include <QWheelEvent>

ScrollingPanel::ScrollingPanel(QWidget * parent) :
  QWidget(parent),
  m_Widget(nullptr),
  m_ShowScrollbar(false),
  m_ScrollBar(std::make_unique<QScrollBar>(this))
{
  m_ScrollBar->hide();
  m_ScrollBar->setMinimum(0);
  m_ScrollBar->setEnabled(true);

  recalculate();
  scrollChanged();

  connect(m_ScrollBar.get(), &QScrollBar::valueChanged, this, &ScrollingPanel::scrollChanged);
}

void ScrollingPanel::SetChildWidget(std::unique_ptr<QWidget> && widget)
{
  m_Widget = std::move(widget);

  if (m_Widget)
  {
    m_Widget->setParent(this);
    m_Widget->show();
  }

  recalculate();
  scrollChanged();
}

void ScrollingPanel::recalculate()
{
  if (m_Widget == nullptr)
  {
    m_ScrollBar->hide();
    m_ShowScrollbar = false;
    return;
  }

  bool prev_scroll = m_ShowScrollbar;

  int child_height = m_Widget->minimumHeight();
  if (child_height <= height())
  {
    if (m_ShowScrollbar)
    {
      m_ScrollBar->setValue(0);
      m_ScrollBar->hide();

      m_ShowScrollbar = false;
    }
  }
  else
  {
    if (m_ShowScrollbar == false)
    {
      m_ScrollBar->show();
      m_ShowScrollbar = true;
    }

    m_ScrollBar->setMaximum(child_height - height());
  }

  if (prev_scroll != m_ShowScrollbar)
  {
    scrollChanged();
  }
}

void ScrollingPanel::scrollChanged()
{
  if (m_Widget == nullptr)
  {
    return;
  }

  int widget_height = m_Widget->minimumHeight();

  if (m_ShowScrollbar)
  {
    int min_width = m_ScrollBar->sizeHint().width();
    int scroll_val = m_ScrollBar->value();
    m_Widget->setGeometry(0, -scroll_val, width() - min_width, widget_height);
    m_ScrollBar->setGeometry(width() - min_width - 2, 0, min_width - 2, height() - 1);
  }
  else
  {
    m_Widget->setGeometry(0, 0, width(), widget_height);
  }
}

void ScrollingPanel::resizeEvent(QResizeEvent * ev)
{
  recalculate();
  scrollChanged();
}

void ScrollingPanel::wheelEvent(QWheelEvent * ev)
{
  if (m_ShowScrollbar == false)
  {
    return;
  }

  auto delta = ev->delta();
  if (delta > 0)
  {
    m_ScrollBar->setValue(m_ScrollBar->value() - 20);
  }
  else
  {
    m_ScrollBar->setValue(m_ScrollBar->value() + 20);
  }
}

