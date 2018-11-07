
#include "GameHostWidget.h"
#include "EditorContainer.h"



GameHostWidget::GameHostWidget(EditorContainer * editor, int number_of_clients, QWidget *parent) :
  QWidget(parent),
  m_Editor(editor)
{
  setAttribute(Qt::WA_X11NetWmWindowTypeDialog);

  m_Layout = new QGridLayout();

  for (int index = 0; index < number_of_clients; ++index)
  {
    m_Clients.emplace_back(new GameClientWidget(editor, index, false, this));
  }

  m_Server = new GameServerWidget(this);

  if (number_of_clients == 1)
  {
    m_Layout->setColumnStretch(0, 2);
    m_Layout->setColumnStretch(1, 1);

    m_Layout->addWidget(m_Clients[0], 0, 0);
    m_Layout->addWidget(m_Server, 0, 1);
  }
  else
  {
    int cols = (number_of_clients + 1) / 2;
    for (int index = 0; index < cols; ++index)
    {
      m_Layout->setColumnStretch(index, 2);
    }

    for (int index = 0; index < number_of_clients; ++index)
    {
      m_Layout->addWidget(m_Clients[index], index % 2, index / 2);
    }

    m_Layout->setColumnStretch(cols, 1);
    m_Layout->addWidget(m_Server, 0, cols, 1, 2);
  }

  setMinimumSize(1266, 800);
  setLayout(m_Layout);
}

void GameHostWidget::closeEvent(QCloseEvent * ev)
{
  m_Editor->NotifyClientWindowClosed(this);
}

void GameHostWidget::resizeEvent(QResizeEvent * ev)
{
  
}
