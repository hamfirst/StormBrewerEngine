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

  void PlayerJoined(std::size_t player_index, GameLogicContainer & game);
  void PlayerLeft(std::size_t player_index, GameLogicContainer & game);

  bool DoAllTeamsHavePlayers(GameLogicContainer & game);
  Optional<int> GetOnlyTeamWithPlayers(GameLogicContainer & game);

  void HandleClientEvent(std::size_t player_index, GameLogicContainer & game, std::size_t event_class_id, void * event_ptr);

  void ApplyInput(std::size_t player_index, GameLogicContainer & game, ClientInput & input);
  void Update(GameLogicContainer & game);

  void STORM_REFL_FUNC HandlePlaceholderEvent(const PlaceholderClientEvent & ev, std::size_t player_index, GameLogicContainer & game);

#if NET_MODE == NET_MODE_TURN_BASED_DETERMINISTIC
  bool IsPlayerActive(std::size_t player_index, GameLogicContainer & game);
  void CheckEndTurnTimer(GameLogicContainer & game);
  void EndTurn(GameLogicContainer & game);

  void STORM_REFL_FUNC HandleEndTurnEvent(const EndTurnEvent & ev, std::size_t player_index, GameLogicContainer & game);
#endif


private:

  std::vector<Delegate<void, void *, std::size_t, GameLogicContainer &>> m_EventCallbacks;

};

