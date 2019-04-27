#include "Game/GameCommon.h"
#include "Foundation/Pathfinding/Pathfinding.h"

#include "GameShared/Systems/GameLogicSystems.h"
#include "LobbyShared/LobbyGameFuncs.h"

#include "Game/GameController.refl.meta.h"
#include "GameShared/GameLogicContainer.h"
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

  auto & data = game.GetLowFrequencyInstanceDataForModify();
  data.m_Players.EmplaceAt(player_index, std::move(player));
}

void GameController::DestroyPlayer(std::size_t player_index, GameLogicContainer & game)
{
  CleanupPlayer(game, player_index);
}

bool GameController::AllowConversionToBot(std::size_t player_index, GameLogicContainer & game)
{
  auto & global_data = game.GetLowFrequencyInstanceData();
  auto player = global_data.m_Players.TryGet(player_index);

  if (player == nullptr)
  {
    return true;
  }

  auto game_data = game.GetInstanceData();
#ifdef NET_USE_SCORE
  auto max_score = GetScoreLimit(game);
  if (game_data.m_Score[(int)player->m_Team] > max_score / 2)
  {
    return false;
  }
#endif

  if(game_data.m_AIPlayerInfo.HasAt(player_index))
  {
    return false;
  }

  return true;
}

void GameController::ConvertBotToPlayer(std::size_t player_index, GameLogicContainer & game, const std::string & name)
{
  auto & global_data = game.GetLowFrequencyInstanceDataForModify();
  auto player = global_data.m_Players.TryGet(player_index);

  player->m_UserName = name;

  auto & game_data = game.GetInstanceData();
  game_data.m_AIPlayerInfo.RemoveAt(player_index);
}

void GameController::ConstructBot(std::size_t player_index, GameLogicContainer & game, const std::string & name, int team)
{
  GamePlayer player;
  player.m_UserName = name;
  player.m_Team = team;

  auto & global_data = game.GetLowFrequencyInstanceDataForModify();
  global_data.m_Players.EmplaceAt(player_index, std::move(player));

  auto & game_state = game.GetInstanceData();
  game_state.m_AIPlayerInfo.EmplaceAt(player_index);
}

void GameController::DestroyBot(std::size_t player_index, GameLogicContainer & game)
{
  auto & global_data = game.GetLowFrequencyInstanceDataForModify();
  global_data.m_Players.RemoveAt(player_index);

  auto & game_state = game.GetInstanceData();
  game_state.m_AIPlayerInfo.RemoveAt(player_index);
}

void GameController::ConvertPlayerToBot(std::size_t player_index, GameLogicContainer & game, const std::string & name)
{
  auto & global_data = game.GetLowFrequencyInstanceDataForModify();
  auto player = global_data.m_Players.TryGet(player_index);

  player->m_UserName = name;

  auto & game_state = game.GetInstanceData();
  game_state.m_AIPlayerInfo.EmplaceAt(player_index, AIPlayerInfo{});
}

#ifdef NET_ALLOW_OBSERVERS
void GameController::ConstructObserver(std::size_t observer_index, GameLogicContainer & game, const std::string & name)
{
  GameObserver player;
  player.m_UserName = name;

  auto & global_data = game.GetLowFrequencyInstanceDataForModify();
  global_data.m_Observers.EmplaceAt(observer_index, std::move(player));
}

void GameController::DestroyObserver(std::size_t observer_index, GameLogicContainer & game)
{
  auto & global_data = game.GetLowFrequencyInstanceDataForModify();
  global_data.m_Observers.RemoveAt(observer_index);
}


#ifdef NET_USE_LOADOUT
void GameController::ConvertObserverToPlayer(std::size_t observer_index, std::size_t player_index,
        GameLogicContainer & game, int team, uint32_t random_number, const GamePlayerLoadout & loadout)
#else
void GameController::ConvertObserverToPlayer(std::size_t observer_index, std::size_t player_index,
        GameLogicContainer & game, int team, uint32_t random_number)
#endif
{
  auto & game_data = game.GetLowFrequencyInstanceDataForModify();
  auto & user_name = game_data.m_Observers[observer_index].m_UserName;
  game_data.m_Observers.RemoveAt(observer_index);

  auto & stage = game.GetStage();
  auto & map_props = stage.GetMapProperties();

  GamePlayer player;
  player.m_UserName = user_name;

#ifdef NET_USE_LOADOUT
  player.m_Loadout = loadout;
#endif

  if(team < 0)
  {
    auto team_counts = GetTeamCounts(game_data);
    player.m_Team = GetRandomTeam(team_counts, random_number, map_props, game.GetGameInitSettings());
  }
  else
  {
    player.m_Team = team;
  }

  game_data.m_Players.EmplaceAt(player_index, std::move(player));
}

void GameController::ConvertPlayerToObserver(std::size_t observer_index, std::size_t player_index, GameLogicContainer & game)
{
  auto & game_data = game.GetLowFrequencyInstanceDataForModify();
  auto & user_name = game_data.m_Players[player_index].m_UserName;
  auto & team = game_data.m_Players[player_index].m_Team;
  game_data.m_Players.RemoveAt(player_index);

  GameObserver observer;
  observer.m_UserName = user_name;

  game_data.m_Observers.EmplaceAt(observer_index, std::move(observer));

#ifdef NET_FILL_WITH_BOTS
  ConstructBot(player_index, game, "AI", team);
#endif
}

#endif

void GameController::ProcessExternal(const NetPolymorphic<GameNetworkExternalEvent> & ext, GameLogicContainer & game)
{
  auto & stage = game.GetStage();
  auto & map_props = stage.GetMapProperties();
  auto & game_settings = game.GetGameInitSettings();

  if (ext.GetClassId() == GameNetworkExternalEvent::__s_TypeDatabase.GetClassId<PlayerJoinedEvent>())
  {
    auto ev = ext.Get<PlayerJoinedEvent>();
    ConstructPlayer(ev->m_PlayerIndex, game, ev->m_UserName, ev->m_Team);
  }
  else if (ext.GetClassId() == GameNetworkExternalEvent::__s_TypeDatabase.GetClassId<PlayerLeaveEvent>())
  {
    auto ev = ext.Get<PlayerLeaveEvent>();
    DestroyPlayer(ev->m_PlayerIndex, game);
  }
  else if (ext.GetClassId() == GameNetworkExternalEvent::__s_TypeDatabase.GetClassId<ChangePlayerNameEvent>())
  {
    auto ev = ext.Get<ChangePlayerNameEvent>();
    auto & game_state = game.GetLowFrequencyInstanceDataForModify();
    game_state.m_Players[ev->m_PlayerIndex].m_UserName = ev->m_Name;
  }
  else if (ext.GetClassId() == GameNetworkExternalEvent::__s_TypeDatabase.GetClassId<ChangePlayerTeam>())
  {
    auto ev = ext.Get<ChangePlayerTeam>();
    auto & game_state = game.GetLowFrequencyInstanceDataForModify();
    game_state.m_Players[ev->m_PlayerIndex].m_Team = ev->m_Team;
  }
#ifdef NET_USE_LOADOUT
  else if (ext.GetClassId() == GameNetworkExternalEvent::__s_TypeDatabase.GetClassId<ChangeLoadoutEvent>())
  {
    auto ev = ext.Get<ChangeLoadoutEvent>();
    auto & game_state = game.GetLowFrequencyInstanceDataForModify();
    game_state.m_Players[ev->m_PlayerIndex].m_Loadout = ev->m_Loadout;
  }
#endif
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
  else if (ext.GetClassId() == GameNetworkExternalEvent::__s_TypeDatabase.GetClassId<ChangeObserverNameEvent>())
  {
    auto ev = ext.Get<ChangeObserverNameEvent>();
    auto & game_state = game.GetLowFrequencyInstanceDataForModify();
    game_state.m_Observers[ev->m_ObserverIndex].m_UserName = ev->m_Name;
  }
  else if (ext.GetClassId() == GameNetworkExternalEvent::__s_TypeDatabase.GetClassId<ChangeObserverToPlayer>())
  {
    auto ev = ext.Get<ChangeObserverToPlayer>();

#ifdef NET_USE_LOADOUT
    ConvertObserverToPlayer(ev->m_ObserverIndex, ev->m_PlayerIndex, game, ev->m_Team, ev->m_RandomSeed, ev->m_Loadout);
#else
    ConvertObserverToPlayer(ev->m_ObserverIndex, ev->m_PlayerIndex, game, ev->m_Team, ev->m_RandomSeed);
#endif
  }
  else if (ext.GetClassId() == GameNetworkExternalEvent::__s_TypeDatabase.GetClassId<ChangePlayerToObserver>())
  {
    auto ev = ext.Get<ChangePlayerToObserver>();
    ConvertPlayerToObserver(ev->m_ObserverIndex, ev->m_PlayerIndex, game);
  }
#endif

}

void GameController::InitPlayer(GameLogicContainer & game, std::size_t player_index, const GamePlayer & player)
{
  auto & obj_manager = game.GetObjectManager();

  auto player_obj = obj_manager.CreateDynamicObject<PlayerServerObject>(player_index, game);
  StormReflSefDefault(*player_obj);

  SetPlayerToSpawn(game, player_index);

  auto & game_state = game.GetInstanceData();
  if (game_state.m_AIPlayerInfo.HasAt(player_index))
  {
    PlayerAI::InitAI(game, player_index);
  }
}

void GameController::SetPlayerToSpawn(GameLogicContainer & game, std::size_t player_index)
{
  auto & stage = game.GetStage();
  auto & spawns = stage.GetPlayerSpawns();

  auto & player = game.GetLowFrequencyInstanceData().m_Players[player_index];
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
  auto & global_data = game.GetLowFrequencyInstanceDataForModify();
  global_data.m_Players.RemoveAt(player_index);

  if (global_data.m_Players.HighestIndex() == -1)
  {
    EndGame(-1, game);
    return;
  }

//  auto & game_data = game.GetInstanceData();
//  if (kMaxTeams > 1 && game_data.m_WiningTeam)
//  {
//    auto winning_team = GetOnlyTeamWithPlayers(game);
//    if (winning_team)
//    {
//      EndGame(-1, game);
//      return;
//    }
//  }

  auto & obj_manager = game.GetObjectManager();
  auto player_obj = obj_manager.GetReservedSlotObject(player_index);

  if (player_obj)
  {
    player_obj->Destroy(obj_manager);
  }
}

int GameController::AddAIPlayer(GameLogicContainer & game, uint32_t random_number)
{
  auto & game_data = game.GetLowFrequencyInstanceData();
  for (int index = 0; index < kMaxPlayers; index++)
  {
    if (game_data.m_Players.HasAt(index) == false)
    {
      auto team_counts = GetTeamCounts(game.GetLowFrequencyInstanceData());

      auto & stage = game.GetStage();
      auto & map_props = stage.GetMapProperties();
      auto & game_settings = game.GetGameInitSettings();

      ConstructPlayer(index, game, "AI", GetRandomTeam(team_counts, random_number, map_props, game_settings));

      auto & instance_data = game.GetInstanceData();
      instance_data.m_AIPlayerInfo.EmplaceAt(index);
      return index;
    }
  }

  return -1;
}

void GameController::FillWithBots(GameLogicContainer & game, uint32_t random_number)
{
  while (true)
  {
    auto team_counts = GetTeamCounts(game.GetLowFrequencyInstanceData());
    if (DoAllTeamsHavePlayers(team_counts, game.GetStage().GetMapProperties(), game.GetGameInitSettings()))
    {
      break;
    }

    int slot = -1;
    for (int index = 0; index < kMaxPlayers; ++index)
    {
      if (game.GetLowFrequencyInstanceData().m_Players.HasAt(index) == false)
      {
        slot = index;
        break;
      }
    }

    auto & stage = game.GetStage();
    auto & map_props = stage.GetMapProperties();
    auto & game_settings = game.GetGameInitSettings();

    auto team = GetRandomTeam(team_counts, random_number, map_props, game_settings);
    ConstructBot(slot, game, "AI", team);
  }
}

int GameController::GetMaxPlayerCount(GameLogicContainer & game) const
{
#ifdef NET_USE_PLAYER_LIMIT
  return game.GetLowFrequencyInstanceData().m_Settings.m_PlayerCount;
#else
  return kMaxPlayers;
#endif
}

#ifdef NET_USE_SCORE
int GameController::GetScoreLimit(GameLogicContainer & game) const
{
#ifdef NET_USE_SCORE_LIMIT
  return game.GetLowFrequencyInstanceData().m_Settings.m_ScoreLimit;
#else
  return kMaxScore;
#endif
}
#endif

#ifdef NET_USE_ROUND_TIMER
void GameController::RoundStarted(GameLogicContainer & game) const
{

}

void GameController::RoundEnded(GameLogicContainer & game) const
{

}

void GameController::RoundReset(GameLogicContainer & game) const
{

}

int GameController::GetTimeLimit(GameLogicContainer & game) const
{
#ifdef NET_USE_TIME_LIMIT
  if(game.GetLowFrequencyInstanceData().m_Settings.m_TimeLimit != 0)
  {
    game.GetLowFrequencyInstanceData().m_Settings.m_TimeLimit * 60 * 60;
  }
#endif

  return kMaxRoundTimer;
}
#endif

std::vector<int> GameController::GetTeamCounts(const GameInstanceLowFrequencyData & game_data)
{
  std::vector<int> teams(kMaxTeams);
  for (auto hero : game_data.m_Players)
  {
    teams[(int)hero.second.m_Team]++;
  }

  return teams;
}

std::vector<int> GameController::GetTeamCounts(const GameStateLoading & game_data)
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

Optional<int> GameController::GetOnlyTeamWithPlayers(GameLogicContainer & game)
{
  Optional<int> team_with_players;
  for (auto player : game.GetLowFrequencyInstanceData().m_Players)
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
  auto player_obj = game.GetLowFrequencyInstanceData().m_Players.TryGet(player_index);

  if (player_obj && game.GetInstanceData().m_AIPlayerInfo.HasAt(player_index))
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
  auto & collision = game.GetSystems().GetCollisionDatabase();
  auto & cvc = game.GetSystems().GetCVCPushSystem();

  collision.ResetDynamicCollision();
  cvc.Clear();

  update_list.CallFirst(game);
  event_system.FinalizeEvents(game.GetObjectManager());
  update_list.CallMiddle(game);
  event_system.FinalizeEvents(game.GetObjectManager());
  update_list.CallLast(game);
  event_system.FinalizeEvents(game.GetObjectManager());

  cvc.ProcessCVC(game);

  for (auto player : game.GetInstanceData().m_AIPlayerInfo)
  {
    PlayerAI::UpdateAI(game, player.first);
  }

#ifdef NET_USE_ROUND_TIMER

  if (game_data.m_RoundTimer > 0)
  {
    --game_data.m_RoundTimer;
  }
  else
  {
    if(game_data.m_RoundState == RoundState::kPreRound)
    {
      game_data.m_RoundState = RoundState::kRound;
      game_data.m_RoundTimer = GetTimeLimit(game);

      RoundStarted(game);
    }
    else if(game_data.m_RoundState == RoundState::kRound)
    {
      game_data.m_RoundState = RoundState::kPostRound;
      game_data.m_RoundTimer = kPostRoundTimer;

      RoundEnded(game);
    }
    else if(game_data.m_RoundState == RoundState::kPostRound)
    {
      game_data.m_RoundState = RoundState::kPreRound;
      game_data.m_RoundTimer = kPostRoundTimer;

      RoundReset(game);
    }
  }


#endif

#if NET_MODE == NET_MODE_GGPO
  game.GetInstanceData().m_FrameCount++;
#endif
}

void GameController::StartGame(GameLogicContainer & game)
{
  auto & global_data = game.GetInstanceData();

#ifdef NET_USE_ROUND_TIMER
  global_data.m_RoundState = RoundState::kPreRound;
  global_data.m_RoundTimer = kPostRoundTimer;
#endif

#if NET_MODE == NET_MODE_TURN_BASED_DETERMINISTIC
  global_data.m_TimeExpiration = kTurnMaxTime;
  global_data.m_ActiveTurn = 0;
#endif
  for (auto player : game.GetLowFrequencyInstanceData().m_Players)
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

#ifdef NET_USE_SCORE
void GameController::AddScore(int team, GameLogicContainer & game, GameNetVec2 & pos)
{
  if (game.IsAuthority())
  {
    auto & game_data = game.GetInstanceData();
    ++game_data.m_Score[team];

    auto max_score = GetScoreLimit(game);

    auto winning_team = -1;
    for (auto team = 0; team < kMaxTeams; ++team)
    {
      if (game_data.m_Score[team] > max_score)
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
#endif

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
