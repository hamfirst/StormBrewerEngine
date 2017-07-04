#pragma once

#include "GameClient/GameMode.h"
#include "GameClient/GameCamera.h"

#include "Engine/Camera/Camera.h"

class GameModeOnlineGameplay : public GameMode
{
public:

  virtual void Initialize(GameContainer & container) override;
  virtual void OnAssetsLoaded(GameContainer & container) override;

  virtual void Update(GameContainer & container) override;
  virtual void Render(GameContainer & container) override;

protected:

private:

  GameCamera m_GameCamera;
  Camera m_EngineCamera;
};


