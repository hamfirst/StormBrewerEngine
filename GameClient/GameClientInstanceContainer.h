#pragma once

#include "Game/GameProtocol.h"
#include "Game/GameStage.h"
#include "Game/GameController.refl.h"
#include "Game/GameFullState.refl.h"
#include "Game/GameNetworkSettings.h"
#include "Game/GameLogicContainer.h"
#include "Game/GameSharedGlobalResources.h"
#include "Game/GameSharedInstanceResources.h"
#include "Game/GameEventReconciler.h"

#include "GameClient/GameClientController.refl.h"
#include "GameClient/GameClientLevelLoader.h"
#include "GameClient/GameClientEntitySync.h"
#include "GameClient/GameClientEventSender.h"
#include "GameClient/GameClientInstanceResources.h"
#include "GameClient/GameClientInstanceData.h"
#include "GameClient/GameServerEventResponder.h"

extern int s_BogusSendTimer;

class GameClientInstanceContainer
{
public:

  GameClientInstanceContainer(GameContainer & game_container, int num_local_clients, bool authority, 
                              NullOptPtr<GameEventReconciler> reconciler, NullOptPtr<int> reconcile_frame);
  ~GameClientInstanceContainer();

  void Load(const GameInitSettings & init_settings, uint64_t load_token = 0);
  bool IsLoaded();

  void Update();

  GameClientInstanceData GetClientInstanceData(GameClientEventSender & event_sender);
  GameLogicContainer GetLogicContainer(bool authority = false, int & send_timer = s_BogusSendTimer);

  GameController & GetGameController();
  GameClientController & GetClientController();
  GameClientLevelLoader & GetLevelLoader();
  GameClientEntitySync & GetEntitySync();

  GameInitSettings & GetInitSettings();
  ClientLocalData & GetClientLocalData(std::size_t client_index);
  ClientAuthData & GetClientAuthData(std::size_t client_index);

  GameFullState & GetState();
  GameFullState & GetDefaultState();
  GameInstanceData & GetInstanceData();
  GameSharedInstanceResources & GetSharedResources();
  GameClientInstanceResources & GetClientResources();
  GameStage & GetStage();

private:
  GameContainer & m_GameContainer;
  GameController m_GameController;
  GameClientController m_ClientController;
  GameClientLevelLoader m_LevelLoader;
  GameClientEntitySync m_EntitySync;
  GameServerEventResponder m_ServerEventResponder;
  bool m_Loaded;
  bool m_Authority;
  int m_SendTimer;

  GameInitSettings m_InitSettings;
  std::vector<ClientLocalData> m_ClientData;
  std::vector<ClientAuthData> m_ClientAuthData;
  std::size_t m_NumLocalClients;

  Optional<GameFullState> m_Sim;
  Optional<GameFullState> m_DefaultSim;
  Optional<GameSharedInstanceResources> m_SharedResources;
  Optional<GameClientInstanceResources> m_ClientResources;
  std::unique_ptr<GameStage> m_Stage;

};

