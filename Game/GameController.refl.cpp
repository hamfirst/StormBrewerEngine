
#include "Foundation/Pathfinding/Pathfinding.h"

#include "Game/GameController.refl.meta.h"
#include "Game/GameLogicContainer.h"
#include "Game/GameNetworkData.refl.meta.h"
#include "Game/GameNetworkEvents.refl.meta.h"
#include "Game/GameSimulationEventCallbacks.h"
#include "Game/GameStage.h"
#include "Game/AI/PlayerAI.h"

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

    m_EventCallbacks[class_id] = Delegate<void, const void *, std::size_t, GameLogicContainer &>(
      [=](const void * ev, std::size_t player_index, GameLogicContainer & game) { (this->*func_ptr)(*(const ParamType *)ev, player_index, game); });
  };

  StormReflVisitFuncs(*this, visitor);
}

void GameController::ConstructPlayer(std::size_t player_index, GameLogicContainer & game, const std::string & name, int team)
{
  GamePlayer player;
  player.m_UserName = name;
  player.m_Team = team;
  player.m_Ready = false;

  auto & global_data = game.GetGlobalData();
  global_data.m_Players.EmplaceAt(player_index, std::move(player));
}

void GameController::PlayerReady(std::size_t player_index, GameLogicContainer & game)
{
  auto & global_data = game.GetGlobalData();
  global_data.m_Players[player_index].m_Ready = true;
}

void GameController::PlayerLeft(std::size_t player_index, GameLogicContainer & game)
{
  auto & global_data = game.GetGlobalData();

  if (global_data.m_Started)
  {
    CleanupPlayer(game, player_index, global_data.m_Players[player_index]);
  }

  if (global_data.m_Players.HighestIndex() == -1)
  {
    EndGame(-1, game);
    return;
  }

  if (kMaxTeams > 1 && global_data.m_Started == false)
  {
    auto winning_team = GetOnlyTeamWithPlayers(game);
    if (winning_team)
    {
      EndGame(-1, game);
      return;
    }
  }
}


void GameController::InitPlayer(GameLogicContainer & game, std::size_t player_index, GamePlayer & player)
{
  auto & obj_manager = game.GetObjectManager();

  auto & stage = game.GetStage();
  //auto spawn_id = stage.GetSpawn(player.m_Team);

  //auto player_obj = obj_manager.CreateDynamicObject<TruckServerObject>(player_index);
  //StormReflSefDefault(*player_obj);
  //player_obj->m_CurrentTown = spawn_id;

  //player.m_Cash = 200;
  //player.m_Deliveries.clear();
  //player.m_Capacity = 3;
}

void GameController::CleanupPlayer(GameLogicContainer & game, std::size_t player_index, GamePlayer & player)
{
  auto & obj_manager = game.GetObjectManager();
  auto player_obj = obj_manager.GetReservedSlotObject(player_index);

  if (player_obj)
  {
    player_obj->Destroy(obj_manager);
  }
}

int GameController::AddAIPlayer(GameLogicContainer & game, uint32_t random_number)
{
  auto & game_data = game.GetGlobalData();
  for (int index = 0; index < kMaxPlayers; index++)
  {
    if (game_data.m_Players.HasAt(index) == false)
    {
      ConstructPlayer(index, game, "AI", GetRandomTeam(game.GetGlobalData(), random_number));

      game_data.m_Players[index].m_AIPlayerInfo.Emplace();
      game_data.m_Players[index].m_Ready = true;
      return index;
    }
  }

  return -1;
}

void GameController::FillWithBots(GameLogicContainer & game, uint32_t random_number)
{
  NetRandom r(random_number);
  while (NeedsMorePlayersToStartGame(game))
  {
    AddAIPlayer(game, r.GetRandom());
  }
}

std::vector<int> GameController::GetTeamCounts(GameInstanceData & game_data)
{
  std::vector<int> teams(kMaxTeams);

#if NET_MODE == NET_MODE_GGPO
  auto sim_data = m_SimHistory.Get();
  for (auto & hero : sim_data->m_Sim.m_Players)
  {
    teams[(int)hero.second.m_Team]++;
  }
#else
  for (auto & hero : game_data.m_Players)
  {
    teams[(int)hero.second.m_Team]++;
  }
#endif

  return teams;
}

int GameController::GetRandomTeam(GameInstanceData & game_data, uint32_t random_number)
{
  auto team_counts = GetTeamCounts(game_data);

  std::vector<int> best_teams;
  int best_team_count = 100000;

  for (std::size_t index = 0, end = team_counts.size(); index < end; ++index)
  {
    if (team_counts[index] < best_team_count)
    {
      best_teams.clear();
      best_teams.push_back((int)index);
      best_team_count = team_counts[index];
    }
    else if (team_counts[index] == best_team_count)
    {
      best_teams.push_back((int)index);
    }
  }

  return best_teams[random_number % best_teams.size()];
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

Optional<int> GameController::GetDefaultWinningTeam()
{
  return{};
}

void GameController::HandleClientEvent(std::size_t player_index, GameLogicContainer & game, std::size_t event_class_id, const void * event_ptr)
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
  auto & game_data = game.GetGlobalData();
  if (game_data.m_Started == false)
  {

#ifdef NET_MODE_TURN_BASED_RUN
    game_data.m_Running = false;
#endif

    return;
  }

  if (game_data.m_WiningTeam != -1)
  {
    return;
  }

#ifdef NET_USE_COUNTDOWN

  if (game_data.m_Countdown > 0)
  {
    --game_data.m_Countdown;
    return;
  }

#endif

  auto & obj_manager = game.GetObjectManager();

  ServerObjectUpdateList update_list;
  obj_manager.CreateUpdateList(update_list);

#ifdef NET_MODE_TURN_BASED_RUN
  CheckEndTurnTimer(game);

  if (game_data.m_Running == false)
  {
    return;
  }

  auto time_left = game_data.m_TimeExpiration;
  if (time_left == 0)
  {
    game_data.m_Running = false;
    game_data.m_TimeExpiration = kTurnMaxTime;
    return;
  }

  game_data.m_TimeExpiration = time_left - 1;

#endif

  update_list.CallFirst(game);
  update_list.CallMiddle(game);
  update_list.CallLast(game);

  for (auto player : game_data.m_Players)
  {
    if (player.second.m_AIPlayerInfo)
    {
      PlayerAI::UpdateAI(game, player.first);
    }
  }

#ifdef NET_USE_ROUND_TIMER

  if (game_data.m_RoundTimer > 0)
  {
    --game_data.m_RoundTimer;
    return;
  }
  else
  {
    auto winning_team = GetDefaultWinningTeam();
    EndGame(winning_team ? winning_team.Value() : kMaxTeams, game);
  }

#endif
}

bool GameController::NeedsMorePlayersToStartGame(GameLogicContainer & game)
{
  return DoAllTeamsHavePlayers(game) == false;
}

bool GameController::IsReadyToStartGame(GameLogicContainer & game)
{
  if (NeedsMorePlayersToStartGame(game))
  {
    return false;
  }

  auto & global_data = game.GetGlobalData();
  for (auto && player : global_data.m_Players)
  {
    if (player.second.m_Ready == false)
    {
      return false;
    }
  }

  return true;
}

void GameController::StartGame(GameLogicContainer & game)
{
  auto & global_data = game.GetGlobalData();
  global_data.m_Started = true;

#ifdef NET_USE_COUNTDOWN
  global_data.m_Countdown = kMaxCountdown;
#endif
#ifdef NET_USE_ROUND_TIMER
  global_data.m_RoundTimer = kMaxRoundTimer;
#endif

#if NET_MODE == NET_MODE_TURN_BASED_DETERMINISTIC
  global_data.m_TimeExpiration = kTurnMaxTime;
  global_data.m_ActiveTurn = 0;
#endif
  for (auto player : global_data.m_Players)
  {
    InitPlayer(game, player.first, player.second);
  }

  game.TriggerImmediateSend();
}

void GameController::EndGame(int winning_team, GameLogicContainer & game)
{
  game.GetGlobalData().m_WiningTeam = winning_team;

  auto & sim_events = game.GetSimEventCallbacks();
  sim_events.HandleWinGame(winning_team);
}

void GameController::HandlePlaceholderEvent(const PlaceholderClientEvent & ev, std::size_t player_index, GameLogicContainer & game)
{
  auto & global_data = game.GetGlobalData();
  if (!global_data.m_Started)
  {
    return;
  }
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

#ifdef NET_MODE_TURN_BASED_RUN
  if (global_data.m_Running)
  {
    return;
  }
#endif

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

  if (global_data.m_Running)
  {
    return;
  }

#ifdef NET_MODE_TURN_BASED_RUN
  global_data.m_Running = true;
  global_data.m_TimeExpiration = kTurnUpdateTime;
#else
  global_data.m_TimeExpiration = kTurnMaxTime;
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

  game.TriggerImmediateSend();
}

void GameController::HandleEndTurnEvent(const EndTurnEvent & ev, std::size_t player_index, GameLogicContainer & game)
{
  EndTurn(game);
}

#endif
