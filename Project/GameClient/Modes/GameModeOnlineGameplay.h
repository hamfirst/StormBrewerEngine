#pragma once

#include "GameClient/Modes/GameMode.h"
#include "GameClient/GameClientSystems.h"

#include "Engine/Camera/Camera.h"

#include "Foundation/Time/FrameClock.h"
#include "Foundation/Time/FPSClock.h"

class GameModeOnlineGameplay : public GameMode
{
public:
  GameModeOnlineGameplay(GameContainer & game);
  ~GameModeOnlineGameplay();

  virtual void Initialize() override;
  virtual void OnAssetsLoaded() override;

  virtual void Update() override;
  virtual void Render() override;

protected:

private:

  std::unique_ptr<GameClientSystems> m_ClientSystems;

  FrameClock m_FrameClock;
  FPSClock m_FPSClock;
};


