
#include <QTimer>

#include "GameServerWidget.h"

GameServerWidget::GameServerWidget(QWidget *parent) :
  m_FrameClock(1.0 / 60.0)
{
  m_LevelList.PreloadAllLevels();

  m_FrameClock.Start();

  QTimer * timer = new QTimer(this);
  connect(timer, &QTimer::timeout, this, &GameServerWidget::tick);
  timer->start(10);
}

GameServerWidget::~GameServerWidget()
{

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
      if (m_LevelList.IsPreloadComplete())
      {
        m_GameServer.Emplace(256, 47815, m_StageManager.Value());
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
