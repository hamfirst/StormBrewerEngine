#pragma once

#include "GameClient/Modes/GameModeOnlineBase.h"

#include "Engine/UI/UIManager.h"

class GameModePlayOnline : public GameModeOnlineBase
{
public:
  GameModePlayOnline(GameContainer & game);
  ~GameModePlayOnline();

  void Initialize() override;
  void OnAssetsLoaded() override;

  void Update() override;
  void Render() override;
};
