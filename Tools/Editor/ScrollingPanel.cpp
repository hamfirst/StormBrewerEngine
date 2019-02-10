
#include "ScrollingPanel.h"

#include <QWheelEvent>
#include <QPainter>

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
  if (child_height <= height() - 20)
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
    m_ScrollBar->setPageStep(height());
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

  int widget_height = std::max(m_Widget->minimumHeight(), height() - 3);

  if (m_ShowScrollbar)
  {
    int min_width = m_ScrollBar->sizeHint().width();
    int scroll_val = m_ScrollBar->value();
    m_Widget->setGeometry(0, -scroll_val, width() - min_width - 3, widget_height);
    m_ScrollBar->setGeometry(width() - min_width, 0, min_width - 2, height() - 1);
  }
  else
  {
    auto w = width();
    m_Widget->setGeometry(0, 0, w, widget_height);
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
    m_ScrollBar->setValue(m_ScrollBar->value() - 100);
  }
  else
  {
    m_ScrollBar->setValue(m_ScrollBar->value() + 100);
  }
}

void ScrollingPanel::paintEvent(QPaintEvent * ev)
{
  QPainter p(this);
  p.fillRect(0, 0, width(), height(), palette().color(QPalette::Window));
}
