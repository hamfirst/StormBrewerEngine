#pragma once

#include "Game/GameProtocol.h"
#include "Game/GameStage.h"
#include "Game/GameController.refl.h"
#include "Game/GameFullState.refl.h"
#include "Game/GameNetworkSettings.h"
#include "Game/GameLogicContainer.h"
#include "Game/GameSharedGlobalResources.h"
#include "Game/GameSharedInstanceResources.h"

#include "GameClient/GameClientController.refl.h"
#include "GameClient/GameClientLevelLoader.h"
#include "GameClient/GameClientEntitySync.h"
#include "GameClient/GameClientEventSender.h"
#include "GameClient/GameClientInstanceResources.h"
#include "GameClient/GameClientInstanceData.h"

class GameClientInstanceContainer
{
public:

  GameClientInstanceContainer(GameContainer & game_container);
  ~GameClientInstanceContainer();

  void Load(const GameInitSettings & init_settings, uint64_t load_token = 0);
  bool IsLoaded();

  void Update();

  GameClientInstanceData GetInstanceData(GameClientEventSender & event_sender);
  GameLogicContainer GetLogicContainer(GameSharedGlobalResources & shared_resources, bool authority, int & send_timer);

  GameController & GetGameController();
  GameClientController & GetClientController();
  GameClientLevelLoader & GetLevelLoader();
  GameClientEntitySync & GetEntitySync();

  GameInitSettings & GetInitSettings();
  ClientLocalData & GetClientData();
  ClientAuthData & GetClientAuthData();

  GameFullState & GetSim();
  GameFullState & GetDefaultSim();
  GameSharedInstanceResources & GetSharedResources();
  GameClientInstanceResources & GetClientResources();
  GameStage & GetStage();

private:
  GameContainer & m_GameContainer;
  GameController m_GameController;
  GameClientController m_ClientController;
  GameClientLevelLoader m_LevelLoader;
  GameClientEntitySync m_EntitySync;
  bool m_Loaded;

  GameInitSettings m_InitSettings;
  ClientLocalData m_ClientData;
  ClientAuthData m_ClientAuthData;

  Optional<GameFullState> m_Sim;
  Optional<GameFullState> m_DefaultSim;
  Optional<GameSharedInstanceResources> m_SharedResources;
  Optional<GameClientInstanceResources> m_ClientResources;
  std::unique_ptr<GameStage> m_Stage;
};

