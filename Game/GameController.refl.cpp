
#include "Game/GameController.refl.meta.h"
#include "Game/GameLogicContainer.h"
#include "Game/GameNetworkData.refl.meta.h"
#include "Game/GameNetworkEvents.refl.meta.h"
#include "Game/GameSimulationEventCallbacks.h"

#include "Server/ServerObject/ServerObjectManager.h"

#include "StormRefl/StormReflMetaCall.h"

GameController::GameController()
{
  auto num_types = ClientNetworkEvent::__s_TypeDatabase.GetNumTypes();
  m_EventCallbacks.resize(num_types);

  auto visitor = [&](auto f)
  {
    using FuncType = decltype(f);
    using ParamType = typename std::decay_t<FuncType::template param_info<0>::param_type>;

    static_assert(std::is_base_of<ClientNetworkEvent, ParamType>::value, "Client event handlers must have a parameter that inherits from ClientNetworkEvent");

    auto class_id = ClientNetworkEvent::__s_TypeDatabase.GetClassId<ParamType>();
    auto func_ptr = FuncType::GetFunctionPtr();

    m_EventCallbacks[class_id] = Delegate<void, void *, std::size_t, GameLogicContainer &>(
      [=](void * ev, std::size_t player_index, GameLogicContainer & game) { (this->*func_ptr)(*(const ParamType *)ev, player_index, game); });
  };

  StormReflVisitFuncs(*this, visitor);
}

void GameController::PlayerJoined(std::size_t player_index, GameLogicContainer & game)
{
  auto & global_data = game.GetGlobalData();
  if (global_data.m_Started == false)
  {
    if (DoAllTeamsHavePlayers(game))
    {
      global_data.m_Started = true;

#if NET_MODE == NET_MODE_TURN_BASED_DETERMINISTIC
      global_data.m_TimeExpiration = kTurnMaxTime;
      global_data.m_ActiveTurn = 0;
#endif
    }
  }
}

void GameController::PlayerLeft(std::size_t player_index, GameLogicContainer & game)
{
  auto & global_data = game.GetGlobalData();

  if (global_data.m_Players.HighestIndex() == -1)
  {
    game.GetSimEventCallbacks().HandleWinGame(-1);
    return;
  }

  if (kMaxTeams > 1 && global_data.m_Started == false)
  {
    auto winning_team = GetOnlyTeamWithPlayers(game);
    if (winning_team)
    {
      game.GetSimEventCallbacks().HandleWinGame(winning_team.Value());
      return;
    }
  }
}

bool GameController::DoAllTeamsHavePlayers(GameLogicContainer & game)
{
  for (int team = 0; team < kMaxTeams; ++team)
  {
    bool team_has_players = false;
    for (auto player : game.GetGlobalData().m_Players)
    {
      if (player.second.m_Team == team)
      {
        team_has_players = true;
        break;
      }
    }

    if (team_has_players == false)
    {
      return false;
    }
  }

  return true;
}

Optional<int> GameController::GetOnlyTeamWithPlayers(GameLogicContainer & game)
{
  Optional<int> team_with_players;
  for (auto player : game.GetGlobalData().m_Players)
  {
    if (team_with_players)
    {
      if (team_with_players.Value() != (int)player.second.m_Team)
      {
        return{};
      }
    }
    else
    {
      team_with_players = (int)player.second.m_Team;
    }
  }

  return team_with_players;
}

void GameController::HandleClientEvent(std::size_t player_index, GameLogicContainer & game, std::size_t event_class_id, void * event_ptr)
{
#if NET_MODE == NET_MODE_TURN_BASED_DETERMINISTIC
  if (!IsPlayerActive(player_index, game))
  {
    return;
  }
#endif

  m_EventCallbacks[event_class_id].Call(event_ptr, player_index, game);
}

void GameController::ApplyInput(std::size_t player_index, GameLogicContainer & game, ClientInput & input)
{

}

void GameController::Update(GameLogicContainer & game)
{
  if (game.GetGlobalData().m_Started == false)
  {
#ifdef NET_MODE_TURN_BASED_RUN
    game.GetGlobalData().m_Running = false;
#endif

    return;
  }

  auto obj_manager = game.GetObjectManager();

  ServerObjectUpdateList update_list;
  obj_manager.CreateUpdateList(update_list);
  
  if (update_list.HasUpdates() == false)
  {
    return;
  }

  update_list.CallFirst(game);
  update_list.CallMiddle(game);
  update_list.CallLast(game);

#ifdef NET_MODE_TURN_BASED_RUN
  game.GetGlobalData().m_Running = false;
#endif
}

void GameController::HandlePlaceholderEvent(const PlaceholderClientEvent & ev, std::size_t player_index, GameLogicContainer & game)
{

}

#if NET_MODE == NET_MODE_TURN_BASED_DETERMINISTIC
bool GameController::IsPlayerActive(std::size_t player_index, GameLogicContainer & game)
{
  auto & global_data = game.GetGlobalData();
  if (global_data.m_Players.HasAt(player_index) == false)
  {
    return false;
  }

  auto player_team = (int)global_data.m_Players[player_index].m_Team;

  return global_data.m_ActiveTurn == player_team;
}

void GameController::CheckEndTurnTimer(GameLogicContainer & game)
{
  auto & global_data = game.GetGlobalData();

  if (global_data.m_Started == false)
  {
    return;
  }

  auto time_left = global_data.m_TimeExpiration;
  if (time_left == 0)
  {
    game.GetSimEventCallbacks().HandleTimeExpired();
  }
  else
  {
    global_data.m_TimeExpiration = time_left - 1;
  }
}

void GameController::EndTurn(GameLogicContainer & game)
{
  auto & global_data = game.GetGlobalData();

#ifdef NET_MODE_TURN_BASED_RUN
  global_data.m_Running = true;
#endif

  auto active = (int)global_data.m_ActiveTurn;
  if (global_data.m_ActiveTurn + 1 >= kMaxTeams)
  {
    global_data.m_ActiveTurn = 0;
  }
  else
  {
    global_data.m_ActiveTurn = active + 1;
  }

  global_data.m_TimeExpiration = kTurnMaxTime;
  game.TriggerImmediateSend();
}

void GameController::HandleEndTurnEvent(const EndTurnEvent & ev, std::size_t player_index, GameLogicContainer & game)
{
  EndTurn(game);
}
#endif
