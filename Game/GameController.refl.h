#pragma once

#include "Foundation/Common.h"

#include "Game/GameNetworkSettings.h"
#include "Game/GameNetworkData.refl.h"
#include "Game/GameNetworkEvents.refl.h"

class GameLogicContainer;

class GameController
{
public:
  STORM_REFL;
  STORM_REFL_FUNCS;
  STORM_REFL_NODEFAULT;

  GameController();

  void ConstructPlayer(std::size_t player_index, GameLogicContainer & game, const std::string & name, int team);
  void PlayerReady(std::size_t player_index, GameLogicContainer & game);
  void PlayerLeft(std::size_t player_index, GameLogicContainer & game);

  void InitPlayer(GameLogicContainer & game, std::size_t player_index, GamePlayer & player);
  void CleanupPlayer(GameLogicContainer & game, std::size_t player_index, GamePlayer & player);
  int AddAIPlayer(GameLogicContainer & game, uint32_t random_number);
  void FillWithBots(GameLogicContainer & game, uint32_t random_number);

  std::vector<int> GetTeamCounts(GameInstanceData & game_data);
  int GetRandomTeam(GameInstanceData & game_data, uint32_t random_number);
  bool DoAllTeamsHavePlayers(GameLogicContainer & game);
  Optional<int> GetOnlyTeamWithPlayers(GameLogicContainer & game);
  Optional<int> GetDefaultWinningTeam();

  void HandleClientEvent(std::size_t player_index, GameLogicContainer & game, std::size_t event_class_id, const void * event_ptr);

  void ApplyInput(std::size_t player_index, GameLogicContainer & game, ClientInput & input);
  void Update(GameLogicContainer & game);

  bool NeedsMorePlayersToStartGame(GameLogicContainer & game);
  bool IsReadyToStartGame(GameLogicContainer & game);
  void StartGame(GameLogicContainer & game);
  void EndGame(int winning_team, GameLogicContainer & game);


  void STORM_REFL_FUNC HandlePlaceholderEvent(const PlaceholderClientEvent & ev, std::size_t player_index, GameLogicContainer & game);

#if NET_MODE == NET_MODE_TURN_BASED_DETERMINISTIC
  bool IsPlayerActive(std::size_t player_index, GameLogicContainer & game);
  void CheckEndTurnTimer(GameLogicContainer & game);
  void EndTurn(GameLogicContainer & game);

  void STORM_REFL_FUNC HandleEndTurnEvent(const EndTurnEvent & ev, std::size_t player_index, GameLogicContainer & game);
#endif
private:

  std::vector<Delegate<void, const void *, std::size_t, GameLogicContainer &>> m_EventCallbacks;

  // There should be no state in this class since it's desinged to only respond to events using the GameLogicContainer
};

