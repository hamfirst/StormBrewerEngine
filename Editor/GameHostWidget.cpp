
#include "GameHostWidget.h"
#include "EditorContainer.h"

//#define HORIZONTAL_ORIENTATION

GameHostWidget::GameHostWidget(EditorContainer * editor, QWidget *parent) :
  QWidget(parent),
  m_Editor(editor)
{
  m_Layout = std::make_unique<QGridLayout>();

  m_Client1 = std::make_unique<GameClientWidget>(0, this);
  m_Client2 = std::make_unique<GameClientWidget>(1, this);
  m_Server = std::make_unique<GameServerWidget>(this);

#ifdef HORIZONTAL_ORIENTATION
  m_Layout->setColumnStretch(0, 2);
  m_Layout->setColumnStretch(1, 1);
  m_Layout->addWidget(m_Client1.get(), 0, 0);
  m_Layout->addWidget(m_Client2.get(), 1, 0);
  m_Layout->addWidget(m_Server.get(), 0, 1, 2, 1);
  setMinimumSize(800, 600);
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
