
#include <QTimer>
#include <QTemporaryFile>

#include <corecrt_stdio_config.h>

#include "GameServerWidget.h"

GameServerWidget::GameServerWidget(QWidget *parent) :
  m_FrameClock(1.0 / 60.0)
{
  m_TextEdit = std::make_unique<QTextEdit>(this);
  m_TextEdit->setEnabled(false);
  m_TextEdit->append(QString("Server starting..."));

  m_LevelList.PreloadAllLevels();

  m_FrameClock.Start();

  QTimer * timer = new QTimer(this);
  connect(timer, &QTimer::timeout, this, &GameServerWidget::tick);
  timer->start(10);
}

GameServerWidget::~GameServerWidget()
{

}

void GameServerWidget::resizeEvent(QResizeEvent * ev)
{
  m_TextEdit->setGeometry(0, 0, width() - 1, height() - 1);
}

void GameServerWidget::tick()
{
  if (m_GameServer)
  {
    m_GameServer->Update();

    if (m_FrameClock.ShouldStartFrame())
    {
      m_FrameClock.BeginFrame();
      m_GameServer->GetGameInstanceManager().Update();
    }
  }
  else
  {
    if (m_StageManager)
    {
      if (m_LevelList.IsPreloadComplete() && m_SharedGlobalResources.IsLoaded() && m_ServerGlobalResources.IsLoaded())
      {
        m_GameServer.Emplace(256, 47815, m_StageManager.Value(), m_SharedGlobalResources);

        m_TextEdit->append(QString("Server started!\n"));
      }
    }
    else
    {
      if (m_LevelList.IsLevelListLoaded())
      {
        m_StageManager.Emplace(m_LevelList);
      }
    }
  }
}
