#pragma once

#include "GameClient/Modes/GameMode.h"
#include "GameClient/GameClientSystems.h"
#include "GameClient/GameClientInstanceContainer.h"

#include "Engine/Camera/Camera.h"

#include "Foundation/Time/FrameClock.h"

class GameModeSinglePlayerBots : public GameMode, public GameClientEventSender
{
public:
  GameModeSinglePlayerBots(GameContainer & game, const GameInitSettings game_settings, bool show_tutorial);
  ~GameModeSinglePlayerBots();

  virtual void Initialize() override;
  virtual void OnAssetsLoaded() override;

  virtual void Update() override;
  virtual void Render() override;

  virtual bool IsLoaded() override;

protected:

  virtual void SendClientEvent(std::size_t class_id, const void * event_ptr, std::size_t client_index) override;

private:
  std::unique_ptr<GameClientInstanceContainer> m_InstanceContainer;
  std::unique_ptr<GameClientSystems> m_ClientSystems;

  Sequencer m_Sequencer;

  FrameClock m_FrameClock;
  bool m_ShowTutorial;

};


