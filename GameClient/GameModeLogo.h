#pragma once

#include "Foundation/Time/StopWatch.h"

#include "GameClient/GameMode.h"

class GameModeLogo : public GameMode
{
public:
  GameModeLogo(GameContainer & game);
  ~GameModeLogo();

  virtual void Initialize() override;
  virtual void OnAssetsLoaded() override;

  virtual void Update() override;
  virtual void Render() override;

protected:

private:

  StopWatch m_Timer;
};


