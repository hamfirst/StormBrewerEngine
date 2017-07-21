#pragma once

#include "Foundation/Time/StopWatch.h"

#include "GameClient/GameMode.h"

class GameModeConnecting : public GameMode
{
public:
  GameModeConnecting(GameContainer & game);
  ~GameModeConnecting();

  virtual void Initialize() override;
  virtual void OnAssetsLoaded() override;

  virtual void Update() override;
  virtual void Render() override;

protected:

};


