#pragma once

#include "Foundation/Time/StopWatch.h"
#include "Foundation/Time/FrameClock.h"
#include "Foundation/Variant/Variant.h"

#include "Game/GameNetworkData.refl.h"
#include "GameClient/Modes/GameMode.h"

#include "Engine/UI/UIManager.h"

enum class GameModeConnectingLobbyIntent
{
  kOnlineMenu,
  kCompetitive,
  kCasual,
  kHostPrivate,
  kJoinPrivate,
};

class GameModeConnectingLobby : public GameMode
{
public:
  GameModeConnectingLobby(GameContainer & game, GameModeConnectingLobbyIntent intent = GameModeConnectingLobbyIntent::kOnlineMenu);
  ~GameModeConnectingLobby();

  void Initialize() override;
  void Deinit() override;
  void OnAssetsLoaded() override;

  void Update() override;
  void Render() override;

protected:

  void Back();
  void ConnectComplete();

protected:
  GameModeConnectingLobbyIntent m_Intent;
  bool m_FinishedConnect;

  StopWatch m_StopWatch;
};


