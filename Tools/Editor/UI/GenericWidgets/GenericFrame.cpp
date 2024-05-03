

#include "GenericFrame.h"

GenericFrame::GenericFrame(czstr title, QWidget * parent) :
  QGroupBox(parent),
  m_ChildWidget(nullptr)
{
  setTitle(title);
}

void GenericFrame::SetChildWidget(std::unique_ptr<QWidget> && widget)
{
  m_ChildWidget = std::move(widget);

  if (m_ChildWidget)
  {
    m_ChildWidget->setParent(this);
    m_ChildWidget->show();
  }

  UpdatePosition();
}

void GenericFrame::UpdatePosition()
{
  if (m_ChildWidget)
  {
    m_ChildWidget->setGeometry(4, 22, width() - 9, height() - 26);
  }
}

void GenericFrame::resizeEvent(QResizeEvent * ev)
{
  UpdatePosition();
}
