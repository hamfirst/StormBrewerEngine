#pragma once

#include "Foundation/Time/StopWatch.h"
#include "Foundation/Sequencer/Sequencer.h"

#include "GameClient/Modes/GameMode.h"
#include "Game/NetworkEvents/GameNetworkData.refl.h"

#include "Engine/UI/UIManager.h"

class GameModeOfflineStaging : public GameMode
{
public:
  GameModeOfflineStaging(GameContainer & game, GameInitSettings & settings);
  ~GameModeOfflineStaging() override;

  void Initialize() override;
  void OnAssetsLoaded() override;

  void Update() override;
  void Render() override;

protected:

  void Start();
  void Back();

private:

  Sequencer m_Sequencer;


  bool m_Attached[kMaxPlayers];
};


