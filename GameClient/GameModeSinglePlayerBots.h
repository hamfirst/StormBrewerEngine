#pragma once

#include "GameClient/GameMode.h"
#include "GameClient/GameClientSystems.h"
#include "GameClient/GameClientInstanceContainer.h"

#include "Engine/Camera/Camera.h"

class GameModeSinglePlayerBots : public GameMode, public GameClientEventSender
{
public:
  GameModeSinglePlayerBots(GameContainer & game, const std::string & player_name, const GameInitSettings game_settings);
  ~GameModeSinglePlayerBots();

  virtual void Initialize() override;
  virtual void OnAssetsLoaded() override;

  virtual void Update() override;
  virtual void Render() override;

  virtual bool IsLoaded() override;

protected:

  virtual void SendClientEvent(std::size_t class_id, const void * event_ptr);

private:
  std::unique_ptr<GameClientInstanceContainer> m_InstanceContainer;
  Optional<GameClientInstanceData> m_InstanceData;
  Optional<GameClientSystems> m_ClientSystems;

  std::string m_PlayerName;
};


