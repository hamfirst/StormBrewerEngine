#pragma once

#include "GameClient/Modes/GameModeOnlineBase.h"

#include "Engine/UI/UIManager.h"

class GameModePlaylistMenu : public GameModeOnlineBase
{
public:
  GameModePlaylistMenu(GameContainer & game, bool competitive);
  ~GameModePlaylistMenu();

  void Initialize() override;
  void OnAssetsLoaded() override;

  void Update() override;
  void Render() override;

private:
  bool m_Competitive;
};
