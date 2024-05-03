
#include <QTimer>
#include <QTemporaryFile>

#include "GameServerWidget.h"

#include "Runtime/Asset/Asset.h"
#include "Engine/Asset/ClientAssetLoader.h"

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

  g_GlobalAssetList.BeginAssetLoad(&g_EngineClientAssetLoader);
}

GameServerWidget::~GameServerWidget()
{
  g_GlobalAssetList.UnloadAllAssets();
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

    for (int index = 0; index < 3 && m_FrameClock.ShouldSkipFrameUpdate() == false; ++index)
    {
      m_FrameClock.BeginFrame();
      m_GameServer->GetGameInstanceManager().Update();

      m_FPSClock.Update();

      auto fps = m_FPSClock.GetFrameCount();
      if (fps != m_LastFPS)
      {
        m_TextEdit->setText(QString::number(fps));
        m_LastFPS = fps;
      }
    }

    m_FrameClock.RemoveExtra();
  }
  else
  {
    if (m_StageManager)
    {
      if (m_LevelList.IsPreloadComplete())
      {
        m_GameServer.Emplace(256, 47816, m_StageManager.Value(), nullptr);

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
