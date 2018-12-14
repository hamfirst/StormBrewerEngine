#pragma once

#include "Foundation/Time/StopWatch.h"
#include "Foundation/Sequencer/Sequencer.h"

#include "GameClient/GameMode.h"

#include "Engine/UI/UIManager.h"

class GameModeJoinPrivateGame : public GameMode
{
public:
  explicit GameModeJoinPrivateGame(GameContainer & game);
  ~GameModeJoinPrivateGame() override;

  void Initialize() override;
  void OnAssetsLoaded() override;

  void Update() override;
  void Render() override;

protected:

  void Submit(czstr game_code);
  void Back();

private:

  Sequencer m_Sequencer;

};


