#pragma once

#include "Foundation/Common.h"

#include "ProjectSettings/ProjectNetworkSettings.h"

#include "Game/NetworkEvents/GameNetworkData.refl.h"
#include "Game/NetworkEvents/GameNetworkEvents.refl.h"
#include "Game/NetworkEvents/GameNetworkExternals.refl.h"
#include "Game/State/GameFullState.refl.h"

class GameWorld;

class GameController
{
public:
  STORM_REFL;
  STORM_REFL_FUNCS;
  STORM_REFL_NODEFAULT;

  GameController();

  void BootstrapGame(GameWorld & game, uint32_t seed);

  void ConstructPlayer(std::size_t player_index, GameWorld & game, const std::string & name, int team);
  void DestroyPlayer(std::size_t player_index, GameWorld & game);
  bool AllowConversionToBot(std::size_t player_index, GameWorld & game);
  void ConvertBotToPlayer(std::size_t player_index, GameWorld & game, const std::string & name);

  void ConstructBot(std::size_t player_index, GameWorld & game, const std::string & name, int team);
  void DestroyBot(std::size_t player_index, GameWorld & game);
  void ConvertPlayerToBot(std::size_t player_index, GameWorld & game, const std::string & name);

#ifdef NET_ALLOW_OBSERVERS
  void ConstructObserver(std::size_t observer_index, GameWorld & game, const std::string & name);
  void DestroyObserver(std::size_t observer_index, GameWorld & game);

#ifdef NET_USE_LOADOUT
  void ConvertObserverToPlayer(std::size_t observer_index, std::size_t player_index, GameWorld & game, int team,
          uint32_t random_number, const GamePlayerLoadout & loadout);
#else
  void ConvertObserverToPlayer(std::size_t observer_index, std::size_t player_index,
                               GameWorld & game, int team, uint32_t random_number);
#endif

  void ConvertPlayerToObserver(std::size_t observer_index, std::size_t player_index, GameWorld & game);
#endif

  void ProcessExternal(const NetPolymorphic<GameNetworkExternalEvent> & ext, GameWorld & game);

  void InitPlayer(GameWorld & game, std::size_t player_index, const GamePlayer & player);
  void SetPlayerToSpawn(GameWorld & game, std::size_t player_index);
  void CleanupPlayer(GameWorld & game, std::size_t player_index);
  int AddAIPlayer(GameWorld & game, uint32_t random_number);
  void FillWithBots(GameWorld & game, uint32_t random_number);

  int GetMaxPlayerCount(GameWorld & game) const;

#ifdef NET_USE_SCORE
  int GetScoreLimit(GameWorld & game) const;
#endif

#ifdef NET_USE_ROUND_TIMER

  void RoundStarted(GameWorld & game) const;
  void RoundEnded(GameWorld & game) const;
  void RoundReset(GameWorld & game) const;
  int GetTimeLimit(GameWorld & game) const;
#endif

  static std::vector<int> GetTeamCounts(const GameInstanceLowFrequencyData & game_data);
  static std::vector<int> GetTeamCounts(const GameStateLoading & game_data);
  Optional<int> GetOnlyTeamWithPlayers(GameWorld & game);
  Optional<int> GetDefaultWinningTeam();

  void HandleClientEvent(std::size_t player_index, GameWorld & game, std::size_t event_class_id, const void * event_ptr);
  void HandleAuthEvent(GameWorld & game, std::size_t event_class_id, const void * event_ptr);

  bool ValidateInput(std::size_t player_index, GameWorld & game, ClientInput & input);
  void ApplyInput(std::size_t player_index, GameWorld & game, const ClientInput & input);
  void Update(GameWorld & game);

  void StartGame(GameWorld & game);
  void EndGame(int winning_team, GameWorld & game);

#ifdef NET_USE_SCORE
  void AddScore(int team, GameWorld & game, GameNetVec2 & pos);
#endif

  void STORM_REFL_FUNC HandlePlaceholderEvent(const PlaceholderClientEvent & ev, std::size_t player_index, GameWorld & game);
  void STORM_REFL_FUNC HandleJumpEvent(const JumpEvent & ev, std::size_t player_index, GameWorld & game);

  void STORM_REFL_FUNC HandlePlaceholderAuthEvent(const PlaceholderServerAuthEvent & ev, GameWorld & game);


#if NET_MODE == NET_MODE_TURN_BASED_DETERMINISTIC
  bool IsPlayerActive(std::size_t player_index, GameWorld & game);
  void CheckEndTurnTimer(GameWorld & game);
  void EndTurn(GameWorld & game);

  void STORM_REFL_FUNC HandleEndTurnEvent(const EndTurnEvent & ev, std::size_t player_index, GameWorld & game);
#endif
private:

  std::vector<Delegate<void, const void *, std::size_t, GameWorld &>> m_ClientEventCallbacks;
  std::vector<Delegate<void, const void *, GameWorld &>> m_AuthEventCallbacks;

  // There should be no state in this class since it's designed to only respond to events using the GameWorld
};

