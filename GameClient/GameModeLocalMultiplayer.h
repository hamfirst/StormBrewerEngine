#pragma once

#include "GameClient/GameMode.h"
#include "GameClient/GameClientSystems.h"
#include "GameClient/GameClientInstanceContainer.h"

#include "Engine/Camera/Camera.h"

#include "Foundation/Time/FrameClock.h"

class GameModeLocalMultiplayer : public GameMode, public GameClientEventSender
{
public:
  GameModeLocalMultiplayer(GameContainer & game, const std::vector<bool> & attached_players, const GameInitSettings game_settings);
  ~GameModeLocalMultiplayer();

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

  std::vector<bool> m_AttachedPlayers;

  FrameClock m_FrameClock;
};


