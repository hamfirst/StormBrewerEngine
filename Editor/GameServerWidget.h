#pragma once

#include <QWidget>
#include <QTextEdit>

#include "Foundation/Time/FrameClock.h"

#include "Game/GameLevelList.h"
#include "Game/GameSharedGlobalResources.h"
#include "Game/GameStageManager.h"

#include "GameServer/GameServer.h"
#include "GameServer/GameServerGlobalResources.h"


class GameServerWidget : public QWidget
{
  Q_OBJECT
public:

  GameServerWidget(QWidget *parent = Q_NULLPTR);
  ~GameServerWidget();

protected:

  void resizeEvent(QResizeEvent * ev);

public slots :

  void tick();

private:

  std::unique_ptr<QTextEdit> m_TextEdit;

  FrameClock m_FrameClock;

  GameLevelList m_LevelList;
  Optional<GameStageManager> m_StageManager;
  Optional<GameServer> m_GameServer;

  GameSharedGlobalResources m_SharedGlobalResources;
  GameServerGlobalResources m_ServerGlobalResources;
};
