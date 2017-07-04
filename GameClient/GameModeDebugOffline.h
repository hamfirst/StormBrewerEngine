#pragma once

#include "Game/GameProtocol.h"
#include "Game/GameController.refl.h"
#include "Game/GameFullState.refl.h"
#include "Game/GameNetworkSettings.h"
#include "Game/GameStage.h"
#include "Game/GameSimulationEventCallbacks.h"
#include "Game/GameServerEventSender.h"

#include "GameClient/GameMode.h"
#include "GameClient/GameCamera.h"
#include "GameClient/GameClientEntitySync.h"
#include "GameClient/GameClientController.refl.h"


#include "Engine/Camera/Camera.h"

struct GameInitSettings;

class GameModeDebugOffline : public GameMode, public GameSimulationEventCallbacks, public GameServerEventSender
{
public:

  static const int kNumPlayers = 2;

  GameModeDebugOffline(const Map & map, const GameInitSettings & init_settings, GameContainer & game);

  virtual void Initialize(GameContainer & container) override;
  virtual void OnAssetsLoaded(GameContainer & container) override;

  virtual void Update(GameContainer & container) override;
  virtual void Render(GameContainer & container) override;

protected:

  virtual void SendGlobalEvent(std::size_t class_id, void * event_ptr) override;
  virtual void SendGlobalEvent(std::size_t class_id, void * event_ptr, std::size_t connection_id) override;
  virtual void SendEntityEvent(std::size_t class_id, void * event_ptr, ServerObjectHandle object_handle) override;
  virtual void SendEntityEvent(std::size_t class_id, void * event_ptr, std::size_t connection_id, ServerObjectHandle object_handle) override;

protected:

  GameStage m_Stage;

  GameInitSettings m_InitSettings;
  GameController m_Controller;
  GameFullState m_GameState;
  GameInput m_Input;

  GameClientEntitySync m_EntitySync;
  GameClientController m_ClientController;

  GameCamera m_GameCamera;
  Camera m_EngineCamera;
};


