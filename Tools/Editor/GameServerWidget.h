#pragma once

#include <QWidget>
#include <QTextEdit>

#include "Foundation/Time/FrameClock.h"
#include "Foundation/Time/FPSClock.h"

#include "GameShared/GameLevelList.h"
#include "GameShared/GameStageManager.h"

#include "GameServer/GameServer.h"

#include "LobbyServerConnection/LobbyServerConnection.h"


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
  FPSClock m_FPSClock;
  int m_LastFPS = 0;

  GameLevelList m_LevelList;
  Optional<GameStageManager> m_StageManager;
  Optional<GameServer> m_GameServer;
};
