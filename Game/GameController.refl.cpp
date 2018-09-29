#include "Game/GameCommon.h"
#include "Foundation/Pathfinding/Pathfinding.h"

#include "Game/GameController.refl.meta.h"
#include "Game/GameLogicContainer.h"
#include "Game/GameNetworkData.refl.meta.h"
#include "Game/GameNetworkEvents.refl.meta.h"
#include "Game/GameSimulationEventCallbacks.h"
#include "Game/GameServerEventSender.h"
#include "Game/GameStage.h"
#include "Game/AI/PlayerAI.h"
#include "Game/Configs/GameConfig.refl.meta.h"
#include "Game/ServerObjects/Player/PlayerServerObject.refl.meta.h"

#include "Runtime/ServerObject/ServerObjectManager.h"

#include "StormRefl/StormReflMetaCall.h"


GLOBAL_ASSET(ConfigPtr<GameConfig>, "./Configs/GameConfig.gameconfig", g_GameConfig);

struct GameControllerRegister
{
  template <typename ParamType>
  static void Register(
    GameController * ptr, 
    std::vector<Delegate<void, const void *, std::size_t, GameLogicContainer &>> & client_events,
    std::vector<Delegate<void, const void *, GameLogicContainer &>> & auth_events,
    void (GameController::*func_ptr)(const ParamType &, std::size_t, GameLogicContainer &))
  {
    static_assert(std::is_base_of<ClientNetworkEvent, ParamType>::value, "Client event handlers must have a parameter that inherits from ClientNetworkEvent");

    auto class_id = ClientNetworkEvent::__s_TypeDatabase.GetClassId<ParamType>();
    client_events[class_id] = Delegate<void, const void *, std::size_t, GameLogicContainer &>(
      [=](const void * ev, std::size_t player_index, GameLogicContainer & game) { (ptr->*func_ptr)(*(const ParamType *)ev, player_index, game); });
  }

  template <typename ParamType>
  static void Register(
    GameController * ptr,
    std::vector<Delegate<void, const void *, std::size_t, GameLogicContainer &>> & client_events,
    std::vector<Delegate<void, const void *, GameLogicContainer &>> & auth_events,
    void (GameController::*func_ptr)(const ParamType &, GameLogicContainer &))
  {
    static_assert(std::is_base_of<ServerAuthNetworkEvent, ParamType>::value, "Auth event handlers must have a parameter that inherits from ServerAuthNetworkEvent");

    auto class_id = ServerAuthNetworkEvent::__s_TypeDatabase.GetClassId<ParamType>();
    auth_events[class_id] = Delegate<void, const void *, GameLogicContainer &>(
      [=](const void * ev, GameLogicContainer & game) { (ptr->*func_ptr)(*(const ParamType *)ev, game); });
  }
};

GameController::GameController()
{
  auto num_client_types = ClientNetworkEvent::__s_TypeDatabase.GetNumTypes();
  m_ClientEventCallbacks.resize(num_client_types);

  auto num_auth_types = ServerAuthNetworkEvent::__s_TypeDatabase.GetNumTypes();
  m_AuthEventCallbacks.resize(num_auth_types);

  auto visitor = [&](auto f)
  {
    using FuncType = decltype(f);
    using ParamType = typename std::decay_t<typename FuncType::template param_info<0>::param_type>;

    auto func_ptr = FuncType::GetFunctionPtr();
    GameControllerRegister::Register(this, m_ClientEventCallbacks, m_AuthEventCallbacks, func_ptr);
  };

  StormReflVisitFuncs(*this, visitor);
}

void GameController::BootstrapGame(GameLogicContainer & game, uint32_t seed)
{
#ifdef NET_USE_RANDOM
  auto & sim_data = game.GetInstanceData();
  sim_data.m_Random = NetRandom(seed);
  sim_data.m_Random.GetRandom();
  sim_data.m_Random.GetRandom();
  sim_data.m_Random.GetRandom();
  sim_data.m_Random.GetRandom();
#endif
}

void GameController::ConstructPlayer(std::size_t player_index, GameLogicContainer & game, const std::string & name, int team)
{
  GamePlayer player;
  player.m_UserName = name;
  player.m_Team = team;

  auto & global_data = game.GetInstanceData();
  global_data.m_Players.EmplaceAt(player_index, std::move(player));
}

void GameController::DestroyPlayer(std::size_t player_index, GameLogicContainer & game)
{
  CleanupPlayer(game, player_index);
}

bool GameController::AllowConversionToBot(std::size_t player_index, GameLogicContainer & game)
{
  auto & global_data = game.GetInstanceData();
  auto player = global_data.m_Players.TryGet(player_index);

  if (player == nullptr)
  {
    return true;
  }

  if (global_data.m_Score[(int)player->m_Team] > kMaxScore / 2)
  {
    return false;
  }

  return true;
}

void GameController::ConvertBotToPlayer(std::size_t player_index, GameLogicContainer & game, const std::string & name)
{
  auto & global_data = game.GetInstanceData();
  auto player = global_data.m_Players.TryGet(player_index);

  player->m_UserName = name;
  player->m_AIPlayerInfo.Clear();
}

void GameController::ConstructBot(std::size_t player_index, GameLogicContainer & game, const std::string & name, int team)
{
  GamePlayer player;
  player.m_UserName = name;
  player.m_Team = team;
  player.m_AIPlayerInfo.Emplace();

  auto & global_data = game.GetInstanceData();
  global_data.m_Players.EmplaceAt(player_index, std::move(player));
}

void GameController::DestroyBot(std::size_t player_index, GameLogicContainer & game)
{
  auto & global_data = game.GetInstanceData();
  global_data.m_Players.RemoveAt(player_index);
}

void GameController::ConvertPlayerToBot(std::size_t player_index, GameLogicContainer & game, const std::string & name)
{
  auto & global_data = game.GetInstanceData();
  auto player = global_data.m_Players.TryGet(player_index);

  player->m_UserName = name;
  player->m_AIPlayerInfo.Emplace();
}

#ifdef NET_ALLOW_OBSERVERS
void GameController::ConstructObserver(std::size_t player_index, GameLogicContainer & game, const std::string & name)
{
  GameObserver player;
  player.m_UserName = name;

  auto & global_data = game.GetInstanceData();
  global_data.m_Observers.EmplaceAt(player_index, std::move(player));
}

void GameController::DestroyObserver(std::size_t player_index, GameLogicContainer & game)
{
  auto & global_data = game.GetInstanceData();
  global_data.m_Observers.RemoveAt(player_index);
}
#endif

void GameController::ProcessExternal(const NetPolymorphic<GameNetworkExternalEvent> & ext, GameLogicContainer & game)
{
  if (ext.GetClassId() == GameNetworkExternalEvent::__s_TypeDatabase.GetClassId<PlayerJoinedEvent>())
  {
    auto ev = ext.Get<PlayerJoinedEvent>();

    auto team_counts = GetTeamCounts(game.GetInstanceData());
    auto team = GetRandomTeam(team_counts, ev->m_RandomSeed);
    ConstructPlayer(ev->m_PlayerIndex, game, ev->m_UserName, team);
  }
  else if (ext.GetClassId() == GameNetworkExternalEvent::__s_TypeDatabase.GetClassId<PlayerLeaveEvent>())
  {
    auto ev = ext.Get<PlayerLeaveEvent>();
    DestroyPlayer(ev->m_PlayerIndex, game);
  }
#ifdef NET_ALLOW_OBSERVERS
  else if (ext.GetClassId() == GameNetworkExternalEvent::__s_TypeDatabase.GetClassId<ObserverJoinedEvent>())
  {
    auto ev = ext.Get<ObserverJoinedEvent>();
    ConstructObserver(ev->m_PlayerIndex, game, ev->m_UserName);
  }
  else if (ext.GetClassId() == GameNetworkExternalEvent::__s_TypeDatabase.GetClassId<ObserverLeaveEvent>())
  {
    auto ev = ext.Get<ObserverLeaveEvent>();
    DestroyObserver(ev->m_PlayerIndex, game);
  }
#endif
}

void GameController::InitPlayer(GameLogicContainer & game, std::size_t player_index, GamePlayer & player)
{
  auto & obj_manager = game.GetObjectManager();

  auto player_obj = obj_manager.CreateDynamicObject<PlayerServerObject>(player_index, game);
  StormReflSefDefault(*player_obj);

  SetPlayerToSpawn(game, player_index);

  if (player.m_AIPlayerInfo)
  {
    PlayerAI::InitAI(game, player_index);
  }
}

void GameController::SetPlayerToSpawn(GameLogicContainer & game, std::size_t player_index)
{
  auto & stage = game.GetStage();
  auto & spawns = stage.GetPlayerSpawns();

  auto & player = game.GetInstanceData().m_Players[player_index];
  auto player_obj = game.GetObjectManager().GetReservedSlotObjectAs<PlayerServerObject>(player_index);

  if (spawns[(int)player.m_Team].size() == 0)
  {
    player_obj->m_Position = {};
  }
  else
  {
    auto & spawn = spawns[(int)player.m_Team][0];
    player_obj->m_Position = GameNetVec2(spawn.x, spawn.y);
  }
}

void GameController::CleanupPlayer(GameLogicContainer & game, std::size_t player_index)
{
  auto & global_data = game.GetInstanceData();
  global_data.m_Players.RemoveAt(player_index);

  if (global_data.m_Players.HighestIndex() == -1)
  {
    EndGame(-1, game);
    return;
  }

  if (kMaxTeams > 1 && global_data.m_WiningTeam)
  {
    auto winning_team = GetOnlyTeamWithPlayers(game);
    if (winning_team)
    {
      EndGame(-1, game);
      return;
    }
  }

  auto & obj_manager = game.GetObjectManager();
  auto player_obj = obj_manager.GetReservedSlotObject(player_index);

  if (player_obj)
  {
    player_obj->Destroy(obj_manager);
  }
}

int GameController::AddAIPlayer(GameLogicContainer & game, uint32_t random_number)
{
  auto & game_data = game.GetInstanceData();
  for (int index = 0; index < kMaxPlayers; index++)
  {
    if (game_data.m_Players.HasAt(index) == false)
    {
      auto team_counts = GetTeamCounts(game.GetInstanceData());
      ConstructPlayer(index, game, "AI", GetRandomTeam(team_counts, random_number));

      auto & player = game_data.m_Players[index];
      player.m_AIPlayerInfo.Emplace();
      return index;
    }
  }

  return -1;
}

void GameController::FillWithBots(GameLogicContainer & game, uint32_t random_number)
{
  while (true)
  {
    auto team_counts = GetTeamCounts(game.GetInstanceData());
    if (DoAllTeamsHavePlayers(team_counts))
    {
      break;
    }

    int slot = -1;
    for (int index = 0; index < kMaxPlayers; ++index)
    {
      if (game.GetInstanceData().m_Players.HasAt(index) == false)
      {
        slot = index;
        break;
      }
    }

    auto team = GetRandomTeam(team_counts, random_number);
    ConstructBot(slot, game, "AI", team);
  }
}

std::vector<int> GameController::GetTeamCounts(GameInstanceData & game_data)
{
  std::vector<int> teams(kMaxTeams);
  for (auto hero : game_data.m_Players)
  {
    teams[(int)hero.second.m_Team]++;
  }

  return teams;
}

std::vector<int> GameController::GetTeamCounts(GameStateStaging & game_data)
{
  std::vector<int> teams(kMaxTeams);
  for (auto hero : game_data.m_Players)
  {
    if (hero.second.m_Team >= 0)
    {
      teams[(int)hero.second.m_Team]++;
    }
  }

  return teams;
}

std::vector<int> GameController::GetTeamCounts(GameStateLoading & game_data)
{
  std::vector<int> teams(kMaxTeams);
  for (auto hero : game_data.m_Players)
  {
    if (hero.second.m_Team >= 0)
    {
      teams[(int)hero.second.m_Team]++;
    }
  }

  return teams;
}

int GameController::GetRandomTeam(const std::vector<int> & team_counts, uint32_t random_number)
{
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

bool GameController::DoAllTeamsHavePlayers(const std::vector<int> & team_counts)
{
  for (int team = 0; team < kMaxTeams; ++team)
  {
    if (team_counts[team] == 0)
    {
      return false;
    }
  }

  return true;
}

Optional<int> GameController::GetOnlyTeamWithPlayers(GameLogicContainer & game)
{
  Optional<int> team_with_players;
  for (auto player : game.GetInstanceData().m_Players)
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

  m_ClientEventCallbacks[event_class_id].Call(event_ptr, player_index, game);
}

void GameController::HandleAuthEvent(GameLogicContainer & game, std::size_t event_class_id, const void * event_ptr)
{
  m_AuthEventCallbacks[event_class_id].Call(event_ptr, game);
}

bool GameController::ValidateInput(std::size_t player_index, GameLogicContainer & game, ClientInput & input)
{
#ifndef PLATFORMER_MOVEMENT
  input.m_InputStr.Clamp(0, 1);
#else
  input.m_XInput.Clamp(-1, 1);
  input.m_YInput.Clamp(-1, 1);
#endif
  return true;
}

void GameController::ApplyInput(std::size_t player_index, GameLogicContainer & game, const ClientInput & input)
{
  auto server_obj = game.GetObjectManager().GetReservedSlotObjectAs<PlayerServerObject>(player_index);
  auto player_obj = game.GetInstanceData().m_Players.TryGet(player_index);

  if (player_obj && player_obj->m_AIPlayerInfo)
  {
    return;
  }

  if (server_obj)
  {
    server_obj->m_Input = input;
  }
}

void GameController::Update(GameLogicContainer & game)
{
  auto & game_data = game.GetInstanceData();
  if (game_data.m_WiningTeam)
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
  obj_manager.IncrementTimeAlive();
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

  auto & event_system = game.GetServerObjectEventSystem();

  update_list.CallFirst(game);
  event_system.FinalizeEvents(game.GetObjectManager());
  update_list.CallMiddle(game);
  event_system.FinalizeEvents(game.GetObjectManager());
  update_list.CallLast(game);
  event_system.FinalizeEvents(game.GetObjectManager());

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

#if NET_MODE == NET_MODE_GGPO
  game_data.m_FrameCount++;
#endif
}

void GameController::StartGame(GameLogicContainer & game)
{
  auto & global_data = game.GetInstanceData();

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

  auto & stage = game.GetStage();
  auto slot = kMaxPlayers;

  game.TriggerImmediateSend();
}

void GameController::EndGame(int winning_team, GameLogicContainer & game)
{
  game.GetInstanceData().m_WiningTeam.Emplace(winning_team);

  auto & sim_events = game.GetSimEventCallbacks();
  sim_events.HandleWinGame(winning_team);
}

void GameController::AddScore(int team, GameLogicContainer & game, GameNetVec2 & pos)
{
  auto & game_data = game.GetInstanceData();

  if (game.IsAuthority())
  {
    ++game_data.m_Score[team];

    if (game_data.m_Score[team] >= kMaxScore)
    {
      for (auto player : game_data.m_Players)
      {
        if (player.second.m_Team == team)
        {
          auto player_obj = game.GetObjectManager().GetReservedSlotObjectAs<PlayerServerObject>(player.first);
          if (player_obj)
          {
            player_obj->Destroy(game.GetObjectManager());
          }
        }
      }
    }

    auto winning_team = -1;
    for (auto team = 0; team < kMaxTeams; ++team)
    {
      if (game_data.m_Score[team] < kMaxScore)
      {
        if (winning_team == -1)
        {
          winning_team = team;
        }
        else
        {
          winning_team = -1;
          break;
        }
      }
    }

    if (winning_team != -1)
    {
      EndGame(winning_team, game);
    }
  }
}

void GameController::HandlePlaceholderEvent(const PlaceholderClientEvent & ev, std::size_t player_index, GameLogicContainer & game)
{
  auto & global_data = game.GetInstanceData();
}

void GameController::HandleJumpEvent(const JumpEvent & ev, std::size_t player_index, GameLogicContainer & game)
{
  auto server_obj = game.GetObjectManager().GetReservedSlotObjectAs<PlayerServerObject>(player_index);
  if (server_obj)
  {
#ifdef PLATFORMER_MOVEMENT
    server_obj->Jump(game);
#endif
  }
}

void GameController::HandlePlaceholderAuthEvent(const PlaceholderServerAuthEvent & ev, GameLogicContainer & game)
{

}

#if NET_MODE == NET_MODE_TURN_BASED_DETERMINISTIC
bool GameController::IsPlayerActive(std::size_t player_index, GameLogicContainer & game)
{
  auto & global_data = game.GetInstanceData();
  if (global_data.m_Players.HasAt(player_index) == false)
  {
    return false;
  }

  auto player_team = (int)global_data.m_Players[player_index].m_Team;
  return global_data.m_ActiveTurn == player_team;
}

void GameController::CheckEndTurnTimer(GameLogicContainer & game)
{
  auto & global_data = game.GetInstanceData();

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
  auto & global_data = game.GetInstanceData();

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
