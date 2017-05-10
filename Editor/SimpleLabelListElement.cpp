
#include <QPainter>

#include "SimpleLabelListElement.h"

SimpleLabelListElement::SimpleLabelListElement(QWidget * parent) :
  QWidget(parent),
  m_Selected(false)
{
  setMinimumHeight(fontMetrics().height() + 4);
}

void SimpleLabelListElement::SetText(czstr text)
{
  m_Text = text;
  update();
}

void SimpleLabelListElement::SetSelected(bool selected)
{
  m_Selected = selected;
  update();
}

void SimpleLabelListElement::SetClickedCallback(Delegate<void> && cb)
{
  m_ClickedDelegate = std::move(cb);
}

void SimpleLabelListElement::paintEvent(QPaintEvent * ev)
{
  QPainter painter(this);

  if (m_Selected)
  {
    painter.fillRect(0, 0, width(), height(), Qt::darkGray);
  }

  int font_height = fontMetrics().height();
  int y = height() / 2 + font_height / 2;

  painter.drawText(3, y - 2, m_Text);
}

void SimpleLabelListElement::mousePressEvent(QMouseEvent * ev)
{
  m_ClickedDelegate();
}
