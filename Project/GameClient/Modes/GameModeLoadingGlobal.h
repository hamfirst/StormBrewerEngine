#pragma once

#include "Foundation/Time/StopWatch.h"

#include "GameClient/Modes/GameMode.h"

class GameModeLoadingGlobal : public GameMode
{
public:
  GameModeLoadingGlobal(GameContainer & game);
  ~GameModeLoadingGlobal();

  virtual void Initialize() override;
  virtual void OnAssetsLoaded() override;

  virtual void Update() override;
  virtual void Render() override;

protected:

  bool m_StartedPreload = false;
};


