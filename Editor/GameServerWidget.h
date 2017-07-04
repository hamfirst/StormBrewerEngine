#pragma once

#include <QWidget>

#include "Foundation/Time/FrameClock.h"

#include "Game/GameLevelList.h"
#include "Game/GameStageManager.h"

#include "GameServer/GameServer.h"


class GameServerWidget : public QWidget
{
  Q_OBJECT
public:

  GameServerWidget(QWidget *parent = Q_NULLPTR);
  ~GameServerWidget();

public slots :

  void tick();

private:

  FrameClock m_FrameClock;

  GameLevelList m_LevelList;
  Optional<GameStageManager> m_StageManager;
  Optional<GameServer> m_GameServer;

};
