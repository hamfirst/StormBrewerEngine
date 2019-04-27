#pragma once

#include "Foundation/Time/StopWatch.h"
#include "Foundation/Sequencer/Sequencer.h"

#include "GameClient/Modes/GameMode.h"

#include "Engine/UI/UIManager.h"

class GameModeMainMenu : public GameMode
{
public:
  explicit GameModeMainMenu(GameContainer & game, const std::string_view & error_msg = "");
  ~GameModeMainMenu() override;

  void Initialize() override;
  void Deinit() override;
  void OnAssetsLoaded() override;

  void Update() override;
  void Render() override;
  void InputEvent() override;

protected:

  void PlayOnline();
  void PlayOffline();
  void Tutorial();
  void PlaySingleplayer();

  void Quit();

private:

  std::string m_ErrorMessage;
};


