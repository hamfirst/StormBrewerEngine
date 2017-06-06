#pragma once

#include "GameMode.h"

#include "Engine/Camera/Camera.h"

class GameModeTestSprite : public GameMode
{
public:
  GameModeTestSprite(GameContainer & container);

  virtual void Initialize(GameContainer & container) override;
  virtual void OnAssetsLoaded(GameContainer & container) override;

  virtual void Update(GameContainer & container) override;
  virtual void Render(GameContainer & container) override;

private:

  Camera m_Camera;
};
