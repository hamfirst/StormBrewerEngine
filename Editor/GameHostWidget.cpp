
#include "GameHostWidget.h"
#include "EditorContainer.h"



GameHostWidget::GameHostWidget(EditorContainer * editor, bool exclude_one, QWidget *parent) :
  QWidget(parent),
  m_Editor(editor)
{
  m_Layout = std::make_unique<QGridLayout>();

  if (exclude_one == false)
  {
    m_Client1 = std::make_unique<GameClientWidget>(editor, 0, false, this);
  }

  m_Client2 = std::make_unique<GameClientWidget>(editor, 1, false, this);
  m_Server = std::make_unique<GameServerWidget>(this);

#if WIDGET_MODE == WIDGET_MODE_HORIZONTAL
  m_Layout->setColumnStretch(0, 2);
  m_Layout->setColumnStretch(1, 1);
  m_Layout->addWidget(m_Client1.get(), 0, 0);
  m_Layout->addWidget(m_Client2.get(), 1, 0);
  m_Layout->addWidget(m_Server.get(), 0, 1, 2, 1);
  setMinimumSize(800, 600);

#elif WIDGET_MODE == WIDGET_MODE_4X4

  m_Client3 = std::make_unique<GameClientWidget>(editor, 2, false, this);
  m_Client4 = std::make_unique<GameClientWidget>(editor, 3, false, this);


  m_Layout->setColumnStretch(0, 2);
  m_Layout->setColumnStretch(1, 2);
  m_Layout->setColumnStretch(2, 1);

  m_Layout->addWidget(m_Client1.get(), 0, 0);
  m_Layout->addWidget(m_Client2.get(), 1, 0);
  m_Layout->addWidget(m_Client3.get(), 0, 1);
  m_Layout->addWidget(m_Client4.get(), 1, 1);
  m_Layout->addWidget(m_Server.get(), 0, 2, 2, 1);
  setMinimumSize(1680, 800);
#else
  m_Layout->addWidget(m_Client1.get(), 0, 0);
  m_Layout->addWidget(m_Client2.get(), 0, 1);
  m_Layout->addWidget(m_Server.get(), 0, 2);
  setMinimumSize(1066, 600);
#endif

  setLayout(m_Layout.get());

}

void GameHostWidget::closeEvent(QCloseEvent * ev)
{
  m_Editor->NotifyClientWindowClosed(this);
}

void GameHostWidget::resizeEvent(QResizeEvent * ev)
{
  
}
