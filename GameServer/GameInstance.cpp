

#include "GameServer/GameInstance.h"
#include "GameServer/GameClientConnection.h"
#include "GameServer.h"

#include "Game/GameMessages.refl.meta.h"
#include "Game/GameFullState.refl.meta.h"
#include "Game/GameStage.h"

#include <sb/vector.h>

#include <ctime>

static const int kTimeToWaitForPlayers = 5 * 60;
static const int kTimeToWaitForLoad = 10 * 60;

GameInstance::GameInstance(GameServer & server, uint64_t game_id, const GameInitSettings & settings, const GameStage & stage, GameSharedGlobalResources & global_resources) :
  m_Server(server),
  m_GameId(game_id),
  m_State(GameInstanceState::kWaitingForPlayers),
  m_SharedGlobalResources(global_resources),
  m_SharedInstanceResources(settings),
  m_InitSettings(settings),
  m_Stage(stage),
#if NET_MODE == NET_MODE_GGPO
  m_ReconcileFrame(0),
  m_EventReconciler(32, 4),
#else
  m_GameState(stage.CreateDefaultGameState()),
#endif
  m_PlayerIdAllocator(kMaxPlayers, false),
  m_SendTimer(8),
  m_LoadTimer(kTimeToWaitForPlayers)
{

#if NET_MODE == NET_MODE_GGPO
  m_SimHistory.Push(SimHistory{});
  auto sim_data = m_SimHistory.Get();

  sim_data->m_Sim.Init(m_Stage);
#endif

#ifdef NET_USE_RANDOM
  m_GameState.m_GlobalData.m_Random = NetRandom((uint32_t)time(nullptr));
  m_GameState.m_GlobalData.m_Random.GetRandom();
  m_GameState.m_GlobalData.m_Random.GetRandom();
  m_GameState.m_GlobalData.m_Random.GetRandom();
  m_GameState.m_GlobalData.m_Random.GetRandom();
#endif
}

void GameInstance::Update()
{
#if NET_MODE == NET_MODE_GGPO
  m_ReconcileFrame = 0;

  auto sim_data = m_SimHistory.Get();
  auto new_sim = *sim_data;
  if (new_sim.m_Sim.Step(m_Stage, sim_data->m_Input, this, true))
  {
    m_SendTimer = 0;
  }

  for (auto & elem : new_sim.m_Actions)
  {
    elem(new_sim.m_Sim, m_Stage);
  }

  new_sim.m_Actions.clear();
  m_EventReconciler.AdvanceFrame();

  for (auto & player : m_Players)
  {
    for(std::size_t index = 0, end = player.m_PendingInput.size(); index < end;)
    {
      auto & input = player.m_PendingInput[index];
      if (input.m_Frame <= new_sim.m_Sim.m_FrameCount)
      {
        new_sim.m_Input[player.m_PlayerIndex] = input.m_Input;
        vremove_index_quick(player.m_PendingInput, index);
        end--;
      }
      else
      {
        index++;
      }
    }
  }

  m_SimHistory.Push(std::move(new_sim));

  m_SendTimer--;
  if (m_SendTimer <= 0)
  {
    auto shared_sim = std::make_shared<GameSimulation>(m_SimHistory.Get()->m_Sim);
    for (auto & player : m_Players)
    {
      player.m_Client->SyncState(shared_sim);
    }

    m_SendTimer = 8;
  }
#elif NET_MODE == NET_MODE_TURN_BASED_DETERMINISTIC

  auto game = GetLogicContainer();

#ifdef NET_MODE_TURN_BASED_REGULAR_UPDATES
  m_SendTimer--;
#endif

  if (m_SendTimer <= 0)
  {
    for (auto & player : m_Players)
    {
      if (player.m_Loaded)
      {
        player.m_Client->SyncState(m_GameState);
      }
    }

    m_SendTimer = kServerUpdateRate;
  }

#ifdef NET_MODE_TURN_BASED_RUN


#ifdef NET_MODE_TURN_BASED_INPUT
  for (auto & player : m_Players)
  {
    m_Controller.ApplyInput(player.m_PlayerIndex, game, m_Input.m_PlayerInput[player.m_PlayerIndex]);
  }
#endif

  m_Controller.Update(game);
#endif

#elif NET_MODE == NET_MODE_SERVER_AUTH

  auto game = GetLogicContainer();

  if (m_State == GameInstanceState::kWaitingForPlayers)
  {
    if (m_LoadTimer > 0)
    {
      m_LoadTimer--;
    }
    else
    {
      FillGameWithBots(GetRandomNumber());
    }

    if (m_Controller.NeedsMorePlayersToStartGame(game) == false)
    {
      StartWaitForLoad();
    }
  }
  else if (m_State == GameInstanceState::kWaitingForLoad)
  {
    if (m_LoadTimer > 0)
    {
      m_LoadTimer--;
    }
    else
    {
      RemovePlayersWhoHaventLoaded();
      FillGameWithBots(GetRandomNumber());
    }

    if (m_Controller.IsReadyToStartGame(game))
    {
      m_Controller.StartGame(game);
      m_State = GameInstanceState::kPlaying;
    }
  }

  if (m_State != GameInstanceState::kPlaying && m_State == GameInstanceState::kVictory)
  {
    return;
  }

  m_SendTimer--;
  if (m_SendTimer <= 0)
  {
    for (auto & player : m_Players)
    {
      if (player.m_Loaded)
      {
        player.m_Client->SyncState(m_GameState);
      }
    }

    m_SendTimer = kServerUpdateRate;
  }

  for (auto & player : m_Players)
  {
    m_Controller.ApplyInput(player.m_PlayerIndex, game, m_Input.m_PlayerInput[player.m_PlayerIndex]);
  }

  m_Controller.Update(game);

#endif
}

void GameInstance::Reset()
{

}

bool GameInstance::JoinPlayer(GameClientConnection * client, const JoinGameMessage & join_game)
{
  auto player_id = m_PlayerIdAllocator.Allocate();
  if (player_id == IdAllocator::kInvalidId)
  {
    return false;
  }

#if NET_MODE == NET_MODE_GGPO
  auto sim_data = m_SimHistory.Get();

#ifndef NET_ALLOW_LATE_JOIN

  if (sim_data.m_Started)
  {
    return false;
  }
#endif

  auto team = GetRandomTeam();
  auto seed = GetRandomNumber();

  int player_index = (int)player_id;

  struct JoinInfo
  {
    std::string m_Name;
    int m_PlayerIndex;
    uint32_t m_Team;
    uint32_t m_Seed;
  };

  JoinInfo join_info;
  join_info.m_Name = join_game.m_Name;
  join_info.m_PlayerIndex = player_index;
  join_info.m_Team = team;
  join_info.m_Seed = seed;

  sim_data->m_Actions.emplace_back([info = std::make_shared<JoinInfo>(std::move(join_info))](GameSimulation & sim, GameStage & stage)
  { 
    sim.AddPlayer(stage, info->m_PlayerIndex, info->m_Name, info->m_Team, info->m_Seed);
  });

  sim_data->m_Input[player_index] = {};

  m_Players.emplace_back(GamePlayer{ client, player_index, sim_data->m_Sim.m_FrameCount });

  ClientLocalData client_data;
  client_data.m_PlayerIndex = (int)player_index;

  client->SyncState(std::make_shared<GameSimulation>(sim_data->m_Sim));
  client->SyncClientData(client_data);
  client->AddToSenderList(m_EventSenderList);

#else

#ifndef NET_ALLOW_LATE_JOIN

  if (m_GameState.m_GlobalData.m_Started)
  {
    return false;
  }

#endif

  auto game = GetLogicContainer();
  auto team = m_Controller.GetRandomTeam(game.GetGlobalData(), GetRandomNumber());
  m_Controller.ConstructPlayer(player_id, game, join_game.m_UserName, team);

  m_Input.m_PlayerInput[player_id] = {};

  auto load_token = GetRandomNumber64();

  int player_index = (int)player_id;
  m_Players.emplace_back(GamePlayer{ client, player_index, load_token });

  LoadLevelMessage load_msg;
  load_msg.m_LoadToken = load_token;
  load_msg.m_Settings = m_InitSettings;

  client->SendLoadLevel(load_msg);

#endif

  return true;
}

void GameInstance::RemovePlayer(GameClientConnection * client)
{
  for (auto itr = m_Players.begin(), end = m_Players.end(); itr != end; ++itr)
  {
    if (itr->m_Client == client)
    {
#if NET_MODE == NET_MODE_GGPO
      auto sim_data = m_SimHistory.Get();
      sim_data->m_Actions.emplace_back([player_index = itr->m_PlayerIndex](GameSimulation & sim, GameStage & stage) { sim.RemovePlayer(player_index); });

      itr->m_Client->RemoveFromSenderList(m_EventSenderList);
#else

      if (itr->m_Loaded)
      {
        auto game = GetLogicContainer();
        m_Controller.PlayerLeft(itr->m_PlayerIndex, game);
      }

      m_GameState.m_GlobalData.m_Players.RemoveAt(itr->m_PlayerIndex);
#endif

      m_Players.erase(itr);
      return;
    }
  }
}

void GameInstance::HandlePlayerLoaded(GameClientConnection * client, const FinishLoadingMessage & finish_loading)
{
  for (auto itr = m_Players.begin(), end = m_Players.end(); itr != end; ++itr)
  {
    if (itr->m_Client == client)
    {
      if (itr->m_Loaded || itr->m_LoadToken != finish_loading.m_LoadToken)
      {
        return;
      }

      itr->m_Loaded = true;

      auto game = GetLogicContainer();
      m_Controller.PlayerReady(itr->m_PlayerIndex, game);

      ClientLocalData client_data;
      client_data.m_PlayerIndex = itr->m_PlayerIndex;

      client->SyncClientData(client_data);
      client->SyncState(m_GameState);
      return;
    }
  }
}

void GameInstance::FillGameWithBots(uint32_t random_number)
{
  auto game = GetLogicContainer();
  m_Controller.FillWithBots(game, random_number);
}

void GameInstance::StartWaitForLoad()
{
  m_State = GameInstanceState::kWaitingForLoad;
  m_LoadTimer = kTimeToWaitForLoad;
}

void GameInstance::RemovePlayersWhoHaventLoaded()
{
  for (int index = (int)m_Players.size() - 1; index >= 0; --index)
  {
    if (m_Players[index].m_Loaded == false)
    {
      m_Players[index].m_Client->ForceDisconnect();
    }
  }
}

void GameInstance::UpdatePlayer(GameClientConnection * client, const ClientAuthData & auth_data)
{
  for (auto itr = m_Players.begin(), end = m_Players.end(); itr != end; ++itr)
  {
    if (itr->m_Client == client)
    {
      if (itr->m_Loaded == false)
      {
        return;
      }

#if NET_MODE == NET_MODE_GGPO
      auto sim_data = m_SimHistory.Get();
      if (auth_data.m_Frame > sim_data->m_Sim.m_FrameCount)
      {
        itr->m_PendingInput.emplace_back(auth_data);
      }
      else if (auth_data.m_Frame == sim_data->m_Sim.m_FrameCount)
      {
        sim_data->m_Input[itr->m_PlayerIndex] = auth_data.m_Input;
      }
      else
      {
        Rewind(auth_data, itr->m_PlayerIndex);
      }

      itr->m_LastInputFrame = auth_data.m_Frame;
#else
      m_Input.m_PlayerInput[itr->m_PlayerIndex] = auth_data.m_Input;
#endif
      return;
    }
  }
}

void GameInstance::HandleClientEvent(GameClientConnection * client, std::size_t class_id, void * event_ptr)
{
  for (auto itr = m_Players.begin(), end = m_Players.end(); itr != end; ++itr)
  {
    if (itr->m_Loaded == false)
    {
      return;
    }

    if (itr->m_Client == client)
    {
      auto game = GetLogicContainer();
      m_Controller.HandleClientEvent(itr->m_PlayerIndex, game, class_id, event_ptr);
      return;
    }
  }
}

std::size_t GameInstance::GetNumPlayers()
{
  return m_Players.size();
}

#if NET_MODE == NET_MODE_GGPO
void GameInstance::Rewind(const ClientAuthData & auth_data, int player_index)
{
  auto sim_data = m_SimHistory.Get();
  int rewind_frames = sim_data->m_Sim.m_FrameCount - auth_data.m_Frame;
  if (rewind_frames >= kMaxRewindFrames - 1)
  {
    rewind_frames = kMaxRewindFrames - 1;
  }

  NullOptPtr<SimHistory> sim_history = m_SimHistory.Get(rewind_frames);
  if (sim_history == nullptr)
  {
    return;
  }

  sim_history->m_Input[player_index] = auth_data.m_Input;

  SimHistory cur_sim = *sim_history;
  while (rewind_frames > 0)
  {
    m_ReconcileFrame = rewind_frames;

    cur_sim.m_Sim.Step(m_Stage, cur_sim.m_Input, nullptr, true);

    for (auto & elem : cur_sim.m_Actions)
    {
      elem(cur_sim.m_Sim, m_Stage);
    }

    rewind_frames--;

    cur_sim.m_Actions = m_SimHistory.Get(rewind_frames)->m_Actions;

    auto * old_input = m_SimHistory.Get(rewind_frames)->m_Input;
    for (int index = 0; index < kMaxPlayers; index++)
    {
      if (index != player_index)
      {
        cur_sim.m_Input[index] = old_input[index];
      }
    }

    m_SimHistory.SetAt(cur_sim, rewind_frames);
  }

  m_SimHistory.SetAt(cur_sim, 0);
}
#endif

#if NET_MODE == NET_MODE_TURN_BASED_DETERMINISTIC
void GameInstance::HandleTimeExpired()
{
  GameLogicContainer game(m_Controller, m_GameState.m_GlobalData, m_GameState.m_ServerObjectManager, *this, *this, m_SharedGlobalResources, m_SharedInstanceResources, m_Stage, true, m_SendTimer);
  m_Controller.EndTurn(game);
}
#endif

std::vector<GameClientConnection *> GameInstance::GetConnectedPlayers() const
{
  std::vector<GameClientConnection *> list;
  for (auto itr = m_Players.begin(), end = m_Players.end(); itr != end; ++itr)
  {
    list.emplace_back(itr->m_Client);
  }

  return list;
}

GameLogicContainer GameInstance::GetLogicContainer()
{
  return GameLogicContainer(m_Controller, m_GameState.m_GlobalData, m_GameState.m_ServerObjectManager, *this, *this, m_SharedGlobalResources, m_SharedInstanceResources, m_Stage, true, m_SendTimer);
}


void GameInstance::SendGlobalEvent(std::size_t class_id, void * event_ptr)
{
  for (auto itr = m_Players.begin(), end = m_Players.end(); itr != end; ++itr)
  {
    itr->m_Client->SendGlobalEvent(class_id, event_ptr);
  }
}

void GameInstance::SendGlobalEvent(std::size_t class_id, void * event_ptr, std::size_t connection_id)
{
  for (auto itr = m_Players.begin(), end = m_Players.end(); itr != end; ++itr)
  {
    if (itr->m_PlayerIndex == connection_id)
    {
      itr->m_Client->SendGlobalEvent(class_id, event_ptr);
      return;
    }
  }
}

void GameInstance::SendEntityEvent(std::size_t class_id, void * event_ptr, ServerObjectHandle object_handle)
{
  auto slot_id = object_handle.GetRawSlotIndex();
  if (slot_id < 0)
  {
    return;
  }

  TargetNetworkEvent * event = (TargetNetworkEvent *)event_ptr;
  event->m_Target = slot_id;

  for (auto itr = m_Players.begin(), end = m_Players.end(); itr != end; ++itr)
  {
    itr->m_Client->SendEntityEvent(class_id, event);
  }
}

void GameInstance::SendEntityEvent(std::size_t class_id, void * event_ptr, std::size_t connection_id, ServerObjectHandle object_handle)
{
  auto slot_id = object_handle.GetRawSlotIndex();
  if (slot_id < 0)
  {
    return;
  }

  TargetNetworkEvent * event = (TargetNetworkEvent *)event_ptr;
  event->m_Target = slot_id;

  for (auto itr = m_Players.begin(), end = m_Players.end(); itr != end; ++itr)
  {
    if (itr->m_PlayerIndex == connection_id)
    {
      itr->m_Client->SendEntityEvent(class_id, event);
      return;
    }
  }
}
