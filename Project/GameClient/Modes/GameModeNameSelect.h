#pragma once

#include "Foundation/Time/StopWatch.h"
#include "Foundation/Sequencer/Sequencer.h"

#include "GameClient/Modes/GameModeOnlineBase.h"

#include "Engine/UI/UIManager.h"

class GameModeNameSelect : public GameModeOnlineBase
{
public:
  GameModeNameSelect(GameContainer & game, bool repick);
  ~GameModeNameSelect() override;

  void Initialize() override;
  void Deinit() override;
  void OnAssetsLoaded() override;

  void Update() override;
  void Render() override;

protected:

  bool Submit(std::string & user_name);
  bool CheckValidUserName(std::string & user_name);
  bool CheckSubmitValidUserName(std::string & user_name);
  void Back();

  void GoToNextMode();

private:
  bool m_Repick;
};


