#pragma once

#include "Foundation/Common.h"

#include "Game/GameNetworkSettings.h"
#include "Game/GameNetworkData.refl.h"
#include "Game/GameNetworkEvents.refl.h"
#include "Game/GameNetworkExternals.refl.h"
#include "Game/GameFullState.refl.h"

class GameLogicContainer;

class GameController
{
public:
  STORM_REFL;
  STORM_REFL_FUNCS;
  STORM_REFL_NODEFAULT;

  GameController();

  void BootstrapGame(GameLogicContainer & game, uint32_t seed);

  void ConstructPlayer(std::size_t player_index, GameLogicContainer & game, const std::string & name, int team);
  void DestroyPlayer(std::size_t player_index, GameLogicContainer & game);
  bool AllowConversionToBot(std::size_t player_index, GameLogicContainer & game);
  void ConvertBotToPlayer(std::size_t player_index, GameLogicContainer & game, const std::string & name);

  void ConstructBot(std::size_t player_index, GameLogicContainer & game, const std::string & name, int team);
  void DestroyBot(std::size_t player_index, GameLogicContainer & game);
  void ConvertPlayerToBot(std::size_t player_index, GameLogicContainer & game, const std::string & name);

#ifdef NET_ALLOW_OBSERVERS
  void ConstructObserver(std::size_t player_index, GameLogicContainer & game, const std::string & name);
  void DestroyObserver(std::size_t player_index, GameLogicContainer & game);
#endif

  void ProcessExternal(const NetPolymorphic<GameNetworkExternalEvent> & ext, GameLogicContainer & game);

  void InitPlayer(GameLogicContainer & game, std::size_t player_index, GamePlayer & player);
  void CleanupPlayer(GameLogicContainer & game, std::size_t player_index);
  int AddAIPlayer(GameLogicContainer & game, uint32_t random_number);
  void FillWithBots(GameLogicContainer & game, uint32_t random_number);

  static std::vector<int> GetTeamCounts(GameInstanceData & game_data);
  static std::vector<int> GetTeamCounts(GameStateStaging & game_data);
  static std::vector<int> GetTeamCounts(GameStateLoading & game_data);
  static int GetRandomTeam(const std::vector<int> & team_counts, uint32_t random_number);
  static bool DoAllTeamsHavePlayers(const std::vector<int> & team_counts);
  Optional<int> GetOnlyTeamWithPlayers(GameLogicContainer & game);
  Optional<int> GetDefaultWinningTeam();

  void HandleClientEvent(std::size_t player_index, GameLogicContainer & game, std::size_t event_class_id, const void * event_ptr);
  void HandleAuthEvent(GameLogicContainer & game, std::size_t event_class_id, const void * event_ptr);

  bool ValidateInput(std::size_t player_index, GameLogicContainer & game, ClientInput & input);
  void ApplyInput(std::size_t player_index, GameLogicContainer & game, const ClientInput & input);
  void Update(GameLogicContainer & game);

  void StartGame(GameLogicContainer & game);
  void EndGame(int winning_team, GameLogicContainer & game);

  void AddScore(int team, GameLogicContainer & game, GameNetVec2 & pos);

  void STORM_REFL_FUNC HandlePlaceholderEvent(const PlaceholderClientEvent & ev, std::size_t player_index, GameLogicContainer & game);
  void STORM_REFL_FUNC HandleJumpEvent(const JumpEvent & ev, std::size_t player_index, GameLogicContainer & game);

  void STORM_REFL_FUNC HandlePlaceholderAuthEvent(const PlaceholderServerAuthEvent & ev, GameLogicContainer & game);


#if NET_MODE == NET_MODE_TURN_BASED_DETERMINISTIC
  bool IsPlayerActive(std::size_t player_index, GameLogicContainer & game);
  void CheckEndTurnTimer(GameLogicContainer & game);
  void EndTurn(GameLogicContainer & game);

  void STORM_REFL_FUNC HandleEndTurnEvent(const EndTurnEvent & ev, std::size_t player_index, GameLogicContainer & game);
#endif
private:

  std::vector<Delegate<void, const void *, std::size_t, GameLogicContainer &>> m_ClientEventCallbacks;
  std::vector<Delegate<void, const void *, GameLogicContainer &>> m_AuthEventCallbacks;

  // There should be no state in this class since it's desinged to only respond to events using the GameLogicContainer
};

