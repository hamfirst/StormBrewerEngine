#pragma once

#include "Foundation/Time/StopWatch.h"
#include "Foundation/Sequencer/Sequencer.h"

#include "GameClient/GameMode.h"

#include "Engine/UI/UIManager.h"

class GameModeMainMenu : public GameMode
{
public:
  explicit GameModeMainMenu(GameContainer & game);
  ~GameModeMainMenu() override;

  void Initialize() override;
  void OnAssetsLoaded() override;

  void Update() override;
  void Render() override;
  void InputEvent() override;

protected:

  void PlayOnline();
  void PlayOffline();
  void Tutorial();
  void PlaySingleplayer();
  void CreatePrivateMatch();
  void JoinPrivateMatch();
  
  bool CanQuit();
  void Quit();

private:

  Sequencer m_Sequencer;

};


