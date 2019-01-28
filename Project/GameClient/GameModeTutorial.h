#pragma once

#include "GameClient/GameMode.h"
#include "GameClient/GameClientSystems.h"
#include "GameClient/GameClientInstanceContainer.h"

#include "Engine/Camera/Camera.h"

#include "Foundation/Time/FrameClock.h"
#include "Foundation/Sequencer/Sequencer.h"

class GameModeTutorial : public GameMode, public GameClientEventSender
{
public:
  GameModeTutorial(GameContainer & game);
  ~GameModeTutorial() override;

  void Initialize() override;
  void OnAssetsLoaded() override;

  void Update() override;
  void Render() override;

  bool IsLoaded() override;

protected:

  void SendClientEvent(std::size_t class_id, const void * event_ptr, std::size_t client_index) override;

  void Pause();
  void Resume();

private:
  std::unique_ptr<GameClientInstanceContainer> m_InstanceContainer;
  std::unique_ptr<GameClientSystems> m_ClientSystems;

  Sequencer m_Sequencer;

  FrameClock m_FrameClock;
  bool m_Paused = false;
};


