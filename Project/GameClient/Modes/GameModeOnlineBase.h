#pragma once

#include "GameClient/Modes/GameMode.h"

class GameModeOnlineBase : public GameMode
{
public:
  GameModeOnlineBase(GameContainer & game);
  ~GameModeOnlineBase();

  bool HandleDisconnect();

protected:

private:

  bool StillOnline();
};
