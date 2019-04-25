#pragma once

#include "Foundation/Time/StopWatch.h"
#include "Foundation/Sequencer/Sequencer.h"

#include "GameClient/Modes/GameMode.h"

#include "Engine/UI/UIManager.h"

class GameModeOnlineStaging : public GameMode
{
public:
  GameModeOnlineStaging(GameContainer & game);

  ~GameModeOnlineStaging() override;

  void Initialize() override;

  void OnAssetsLoaded() override;

  void Update() override;

  void Render() override;

protected:

  void Ready();
  void KickPlayer();

  void Quit();

private:

  Sequencer m_Sequencer;

};