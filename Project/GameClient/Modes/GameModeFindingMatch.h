#pragma once

#include "GameClient/Modes/GameModeOnlineBase.h"

#include "GameShared/GamePlayList.h"

#include "Engine/UI/UIManager.h"

enum class GameModeFindingMatchState
{
  kWaiting,
  kInGame,
  kCancelling,
  kCanceled,
  kFailed,
};

class GameModeFindingMatch : public GameModeOnlineBase
{
public:
  GameModeFindingMatch(GameContainer & game, bool ranked);
  ~GameModeFindingMatch();

  void Initialize() override;
  void Deinit() override;
  void OnAssetsLoaded() override;

  void Update() override;
  void Render() override;

protected:

  void Back();

private:
  GameModeFindingMatchState m_State = GameModeFindingMatchState::kWaiting;
  bool m_Ranked;
  double m_StartTime;
};
