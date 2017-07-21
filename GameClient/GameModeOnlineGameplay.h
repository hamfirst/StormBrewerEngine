#pragma once

#include "GameClient/GameMode.h"
#include "GameClient/GameClientSystems.h"

#include "Engine/Camera/Camera.h"

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

  Optional<GameClientSystems> m_ClientSystems;
};


