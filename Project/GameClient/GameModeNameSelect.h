#pragma once

#include "Foundation/Time/StopWatch.h"
#include "Foundation/Sequencer/Sequencer.h"

#include "GameClient/GameMode.h"

#include "Engine/UI/UIManager.h"

enum class GameModeNameSelectNextScreen
{
  kJoinOnline,
  kCreatePrivate,
  kJoinPrivate,
};

class GameModeNameSelect : public GameMode
{
public:
  GameModeNameSelect(GameContainer & game, GameModeNameSelectNextScreen next_screen);
  ~GameModeNameSelect() override;

  void Initialize() override;
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

  GameModeNameSelectNextScreen m_NextMode;

  Sequencer m_Sequencer;
};


