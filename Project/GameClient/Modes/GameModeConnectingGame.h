#pragma once

#include "Foundation/Time/StopWatch.h"
#include "Foundation/Time/FrameClock.h"
#include "Foundation/Variant/Variant.h"

#include "Game/GameNetworkData.refl.h"
#include "GameClient/Modes/GameModeOnlineBase.h"

#include "Engine/UI/UIManager.h"

class GameModeConnectingGame : public GameModeOnlineBase
{
public:
  GameModeConnectingGame(GameContainer & game);
  ~GameModeConnectingGame();

  void Initialize() override;
  void OnAssetsLoaded() override;

  void Update() override;
  void Render() override;

protected:

  void Back();

protected:


  bool m_ConnectFailed;

  double m_Start;
  double m_LastConnect;
  FrameClock m_FrameClock;
};


