#pragma once

#include "Foundation/Time/StopWatch.h"
#include "Foundation/Sequencer/Sequencer.h"

#include "GameClient/Modes/GameModeOnlineBase.h"

#include "Engine/UI/UIManager.h"

class GameModeJoinPrivateGame : public GameModeOnlineBase
{
public:
  explicit GameModeJoinPrivateGame(GameContainer & game);
  ~GameModeJoinPrivateGame() override;

  void Initialize() override;
  void Deinit() override;
  void OnAssetsLoaded() override;

  void Update() override;
  void Render() override;

protected:

  void Submit(std::string & game_code);
  bool CheckValidGameCode(std::string & user_name);
  bool CheckSubmitValidGameCode(std::string & user_name);
  void Back();

private:

  Sequencer m_Sequencer;

};


