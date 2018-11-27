#pragma once

#include "Foundation/Time/StopWatch.h"
#include "Foundation/Sequencer/Sequencer.h"
#include "Foundation/Time/FrameClock.h"

#include "Engine/UI/UIManager.h"

#include "GameClient/GameMode.h"
#include "GameClient/GameClientInstanceContainer.h"
#include "GameClient/GameClientSystems.h"

enum EndGamePlayAgainMode
{
  kOnlineGameplay,
  kOfflineMultiplayer,
  kOfflineSingleplayer
};

class GameModeEndGame : public GameMode
{
public:
  GameModeEndGame(GameContainer & game, std::unique_ptr<GameClientInstanceContainer> && instance_container, 
                                        std::unique_ptr<GameClientSystems> && client_systems, EndGamePlayAgainMode mode);
  virtual ~GameModeEndGame();

  void Initialize() override;
  void OnAssetsLoaded() override;

  void Update() override;
  void Render() override;

protected:

  void PlayAgain();
  void Quit();

private:

  bool m_Victory;
  std::unique_ptr<GameClientInstanceContainer> m_InstanceContainer;
  std::unique_ptr<GameClientSystems> m_ClientSystems;
  EndGamePlayAgainMode m_Mode;
  GameClientEventSender m_DefaultSender;

  StopWatch m_StopWatch;
  UIManager m_UIManager;
  FrameClock m_FrameClock;
};

