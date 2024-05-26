

#include "GenericListFrame.h"

GenericListFrame::GenericListFrame(czstr title, bool show_add_button, bool show_remove_button, QWidget * parent) :
  GenericFrame(title, parent)
{
  if (show_add_button)
  {
    m_AddButton = std::make_unique<QPushButton>("+", this);
    connect(m_AddButton.get(), &QPushButton::pressed, this, &GenericListFrame::handleAddButtonClick);
  }

  if (show_remove_button)
  {
    m_RemoveButton = std::make_unique<QPushButton>("-", this);
    connect(m_RemoveButton.get(), &QPushButton::pressed, this, &GenericListFrame::handleRemoveButtonClick);
  }

  RepositionElements();
}

void GenericListFrame::SetAddDelegate(Delegate<void> && callback)
{
  m_AddDelegate = std::move(callback);
}

void GenericListFrame::SetRemoveDelegate(Delegate<void> && callback)
{
  m_RemoveDelegate = std::move(callback);
}

void GenericListFrame::SetAddButtonEnabled(bool enable)
{
  if (m_AddButton)
  {
    m_AddButton->setEnabled(enable);
  }
}

void GenericListFrame::SetRemoveButtonEnabled(bool enable)
{
  if (m_RemoveButton)
  {
    m_RemoveButton->setEnabled(enable);
  }
}

void GenericListFrame::RepositionElements()
{
  auto title_width = fontMetrics().horizontalAdvance(title());

  int x = title_width + 20;
  if (m_AddButton)
  {
    m_AddButton->setGeometry(x, 0, 20, 15);
    x += 25;
  }

  if (m_RemoveButton)
  {
    m_RemoveButton->setGeometry(x, 0, 20, 15);
    x += 25;
  }
}

void GenericListFrame::resizeEvent(QResizeEvent * ev)
{
  GenericFrame::resizeEvent(ev);
  RepositionElements();
}

void GenericListFrame::handleAddButtonClick()
{
  m_AddDelegate();
}

void GenericListFrame::handleRemoveButtonClick()
{
  m_RemoveDelegate();
}
