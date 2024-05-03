#pragma once

#include "Foundation/Common.h"
#include "Foundation/CircularBuffer/CircularBuffer.h"

#include "GameShared/GameLogicContainer.h"
#include "GameShared/GameEventReconciler.h"

#include "LobbyShared/SharedTypes.refl.h"

#include "ProjectSettings/ProjectNetworkSettings.h"


#include "Game/NetworkEvents/GameMessages.refl.h"
#include "Game/NetworkEvents/GameNetworkData.refl.h"
#include "Game/SimulationEvents/GameSimulationEventCallbacks.h"
#include "Game/State/GameFullState.refl.h"
#include "Game/GameController/GameController.refl.h"
#include "GameServer/GameInstanceStateData.h"

class GameClientConnection;
class GameServer;
class GameInstanceStateBase;

struct GameInfoTeamSizes;

using GameSimulationActionList = std::vector<Delegate<void, GameLogicContainer &>>;

enum class GameInstanceState
{
  kWaitingForPlayers,
  kWaitingForLoad,
  kPlaying,
  kVictory,
};

class GameInstance
{
public:

  GameInstance(GameServer & server, uint64_t game_id,
          const GameInitSettings & settings, const GameInfoTeamSizes & team_info, GameStageManager & stage_manager);

  ~GameInstance();

  void Update();

  bool JoinPlayer(GameClientConnection * client, const GameJoinInfo & join_game, bool game_leader);
  void RemovePlayer(GameClientConnection * client);

  void HandlePlayerLoaded(GameClientConnection * client, const FinishLoadingMessage & finish_loading);
  void HandleTextChat(GameClientConnection * client, const SendTextChatMessage & text_message);

#ifdef NET_USE_LOADOUT
  void HandleChangeLoadout(GameClientConnection * client, const ChangeLoadoutMessage & text_message);
#endif

#if NET_MODE == NET_MODE_GGPO

  void UpdatePlayer(GameClientConnection * client, GameGGPOClientUpdate & update_data);

#else

  void UpdatePlayer(GameClientConnection * client, const ClientAuthData & auth_data);
  void HandleClientEvent(GameClientConnection * client, std::size_t class_id, void * event_ptr);

#endif

  uint64_t GetGameId() const { return m_GameId; }

  std::size_t GetNumPlayers();
  std::vector<GameClientConnection *> GetConnectedPlayers() const;


protected:
  friend class GameInstanceStateData;

  std::size_t GetPlayerIndex(NotNullPtr<GameClientConnection> client);
  void SetNewState(std::unique_ptr<GameInstanceStateBase> && state);

private:

  GameServer & m_Server;
  uint64_t m_GameId;

  GameInstanceStateData m_StateData;
  std::unique_ptr<GameInstanceStateBase> m_State;
  std::unique_ptr<GameInstanceStateBase> m_NewState;

};


