

#include "GameServer/GameInstanceStateGameplay.h"
#include "GameServer/GameInstanceStateStaging.h"
#include "GameServer/GameInstanceStateData.h"
#include "GameServer/GameClientConnection.h"

#include "Game/GameController.refl.h"
#include "Game/GameNetworkSettings.h"

GameInstanceStateGameplay::GameInstanceStateGameplay(GameInstanceStateData & state_data, const GameStateLoading & loading_data, std::unique_ptr<GameSharedInstanceResources> && resources) :
  GameInstanceStateBase(state_data),
  m_Stage(state_data.GetStage()),
  m_InstanceResources(std::move(resources)),
  m_SendTimer(0),
  m_InitialState(m_Stage.CreateDefaultGameState())
{
  GameLogicContainer logic_container(m_Controller, m_InitialState.m_InstanceData, m_InitialState.m_ServerObjectManager, 
    *this, *this, m_StateData.GetSharedResources(), *m_InstanceResources.get(), m_Stage, true, m_SendTimer);

  for (auto elem : loading_data.m_Players)
  {
    auto & player_info = m_PlayerInfo.EmplaceAt(elem.first);
    player_info.m_Loaded = true;
    player_info.m_LoadToken = 0;
    player_info.m_ClientFrame = 0;

    if (elem.second.m_Team >= 0)
    {
      auto player_id = m_PlayerIdAllocator.Allocate();
      m_Controller.ConstructPlayer(player_id, logic_container, elem.second.m_UserName, elem.second.m_Team);

      player_info.m_PlayerIndex = (int)player_id;

#ifdef NET_ALLOW_OBSERVERS
      player_info.m_ObserverIndex = -1;
#endif
    }
    else
    {
      player_info.m_PlayerIndex = -1;

#ifdef NET_ALLOW_OBSERVERS
      auto player_id = m_ObserverIdAllocator.Allocate();

      m_Controller.ConstructObserver(player_id, logic_container, elem.second.m_UserName);
      auto & player_data = m_InitialState.m_InstanceData.m_Observers.EmplaceBack();
      player_data.m_UserName = elem.second.m_UserName;

      player_info.m_ObserverIndex = m_InitialState.m_InstanceData.m_Observers.HighestIndex();
#endif
    }

    ClientLocalData local_data;
    local_data.m_PlayerIndex = player_info.m_PlayerIndex;

#ifdef NET_ALLOW_OBSERVERS
    local_data.m_ObserverIndex = player_info.m_ObserverIndex;
#endif

    player_info.m_LocalDataHistory.Push(0, std::move(local_data));
  }

#ifdef NET_FILL_WITH_BOTS
  while (m_InitialState.m_InstanceData.m_Players.Size() != kMaxPlayers)
  {
    auto player_id = m_PlayerIdAllocator.Allocate();

    auto team_counts = m_Controller.GetTeamCounts(m_InitialState.m_InstanceData);
    auto team = GameController::GetRandomTeam(team_counts, GetRandomNumber());
    m_Controller.ConstructBot(player_id, logic_container, "AI", team);
  }
#endif

  m_Controller.StartGame(logic_container);

  m_CurrentState = std::make_shared<GameFullState>(m_InitialState);
  m_SimHistory.Push(std::shared_ptr<GameFullState>(m_CurrentState));
}

bool GameInstanceStateGameplay::JoinPlayer(std::size_t client_index, const JoinGameMessage & join_game)
{
#ifdef NET_ALLOW_LATE_JOIN

  auto & state = GetCurrentInstanceData();
  if (state.m_Players.Size() >= kMaxPlayers)
  {
    return false;
  }

  auto load_token = GetRandomNumber64();

  auto & client_data = m_StateData.GetClient(client_index);
  auto & player_info = m_PlayerInfo.EmplaceAt(client_index);
  player_info.m_Loaded = false;
  player_info.m_LoadToken = load_token;
  player_info.m_PlayerIndex = -1;

  LoadLevelMessage msg;
  msg.m_LoadToken = load_token;
  msg.m_Settings = m_StateData.GetInitSettings();
  client_data.m_Client->SendLoadLevel(msg);

  return true;
#else
  return false;
#endif
}

void GameInstanceStateGameplay::RemovePlayer(std::size_t client_index)
{
  auto & player_info = m_PlayerInfo[client_index];
  if (player_info.m_PlayerIndex != -1)
  {
    PlayerLeaveEvent ev;
    ev.m_PlayerIndex = player_info.m_PlayerIndex;

    m_PendingExternals.emplace_back(std::move(ev));

    m_PlayerIdAllocator.Release(player_info.m_PlayerIndex);
  }
  
#ifdef NET_ALLOW_OBSERVERS
  if (player_info.m_ObserverIndex != -1)
  {
    ObserverLeaveEvent ev;
    ev.m_PlayerIndex = player_info.m_ObserverIndex;

    m_PendingExternals.emplace_back(std::move(ev));

    m_ObserverIdAllocator.Release(player_info.m_PlayerIndex);
  }
#endif

  m_PlayerInfo.RemoveAt(client_index);
}

void GameInstanceStateGameplay::Update()
{
  auto new_state = std::make_shared<GameFullState>(*m_CurrentState.get());
  auto frame = new_state->m_InstanceData.m_FrameCount;

  GameLogicContainer logic_container(m_Controller, new_state->m_InstanceData, new_state->m_ServerObjectManager,
    *this, *this, m_StateData.GetSharedResources(), *m_InstanceResources.get(), m_Stage, true, m_SendTimer);

  m_ReconcileFrame = 0;

  for (auto & elem : m_PendingExternals)
  {
    m_Controller.ProcessExternal(elem, logic_container);
    m_ExternalsHistory.Push(frame, std::move(elem));
  }

  auto input_iter = m_Inputistory.IterateElementsSince(frame);
  auto input_visitor = [&](HistoryInput & elem)
  {
    m_Controller.ApplyInput(elem.m_PlayerIndex, logic_container, elem.m_Input);
  };

  input_iter.VisitElementsForCurrentTime(input_visitor);
  input_iter.Advance();

  auto event_iter = m_EventHistory.IterateElementsSince(frame);
  auto event_visitor = [&](HistoryEvent & elem)
  {
    m_Controller.HandleClientEvent(elem.m_PlayerIndex, logic_container, elem.m_Event.GetClassId(), elem.m_Event.GetBase());
  };

  event_iter.VisitElementsForCurrentTime(event_visitor);
  event_iter.Advance();

  m_Controller.Update(logic_container);
  m_Reconciler.AdvanceFrame();

  m_SimHistory.Push(new_state);
  m_CurrentState = new_state;

  m_SendTimer--;
  if (m_SendTimer <= 0)
  {
    for (auto player_info : m_PlayerInfo)
    {
      SendPacketToPlayer(player_info.first, player_info.second);
    }
  
    m_SendTimer = kServerUpdateRate;
  }

  //
  //
  //
  //#if NET_MODE == NET_MODE_GGPO
  //
  //m_ReconcileFrame = 0;
  //
  //auto sim_data = m_SimHistory.Get();
  //auto new_sim = *sim_data;
  //
  //GameLogicContainer game(m_Controller, new_sim.m_Sim.m_InstanceData, new_sim.m_Sim.m_ServerObjectManager,
  //  *this, *this, m_SharedGlobalResources, m_SharedInstanceResources, m_Stage, true, m_SendTimer);
  //
  //for (auto & elem : new_sim.m_Actions)
  //{
  //  elem(game);
  //}
  //
  //new_sim.m_Actions.clear();
  //m_EventReconciler.AdvanceFrame();
  //
  //for (auto & player : m_Players)
  //{
  //  for (std::size_t index = 0, end = player.m_PendingInput.size(); index < end;)
  //  {
  //    auto & input = player.m_PendingInput[index];
  //    if (input.m_Frame <= new_sim.m_Sim.m_InstanceData.m_FrameCount)
  //    {
  //      new_sim.m_Input.m_PlayerInput[player.m_PlayerIndex] = input.m_Input;
  //
  //      m_Controller.ApplyInput(player.m_PlayerIndex, game, input.m_Input);
  //      vremove_index_quick(player.m_PendingInput, index);
  //      end--;
  //    }
  //    else
  //    {
  //      index++;
  //    }
  //  }
  //}
  //
  //m_Controller.Update(game);
  //
  //m_SimHistory.Push(std::move(new_sim));
  //
  //m_SendTimer--;
  //if (m_SendTimer <= 0)
  //{
  //  for (auto & player : m_Players)
  //  {
  //    player.m_Client->SyncState(player.m_LastInputFrame, m_SimHistory.Get(0)->m_Sim);
  //  }
  //
  //  m_SendTimer = kServerUpdateRate;
  //}
  //
  //#elif NET_MODE == NET_MODE_TURN_BASED_DETERMINISTIC
  //
  //auto game = GetLogicContainer();
  //
  //#ifdef NET_MODE_TURN_BASED_REGULAR_UPDATES
  //m_SendTimer--;
  //#endif
  //
  //if (m_SendTimer <= 0)
  //{
  //  for (auto & player : m_Players)
  //  {
  //    if (player.m_Loaded)
  //    {
  //      player.m_Client->SyncState(m_GameState);
  //    }
  //  }
  //
  //  m_SendTimer = kServerUpdateRate;
  //}
  //
  //#ifdef NET_MODE_TURN_BASED_RUN
  //
  //
  //#ifdef NET_MODE_TURN_BASED_INPUT
  //for (auto & player : m_Players)
  //{
  //  m_Controller.ApplyInput(player.m_PlayerIndex, game, m_Input.m_PlayerInput[player.m_PlayerIndex]);
  //}
  //#endif
  //
  //m_Controller.Update(game);
  //#endif
  //
  //#elif NET_MODE == NET_MODE_SERVER_AUTH
  //
  //auto game = GetLogicContainer();
  //
  //if (m_State == GameInstanceState::kWaitingForPlayers)
  //{
  //  if (m_LoadTimer > 0)
  //  {
  //    m_LoadTimer--;
  //  }
  //  else
  //  {
  //    FillGameWithBots(GetRandomNumber());
  //  }
  //
  //  if (m_Controller.NeedsMorePlayersToStartGame(game) == false)
  //  {
  //    StartWaitForLoad();
  //  }
  //}
  //else if (m_State == GameInstanceState::kWaitingForLoad)
  //{
  //  if (m_LoadTimer > 0)
  //  {
  //    m_LoadTimer--;
  //  }
  //  else
  //  {
  //    RemovePlayersWhoHaventLoaded();
  //    FillGameWithBots(GetRandomNumber());
  //  }
  //
  //  if (m_Controller.IsReadyToStartGame(game))
  //  {
  //    m_Controller.StartGame(game);
  //    m_State = GameInstanceState::kPlaying;
  //  }
  //}
  //
  //if (m_State != GameInstanceState::kPlaying && m_State == GameInstanceState::kVictory)
  //{
  //  return;
  //}
  //
  //m_SendTimer--;
  //if (m_SendTimer <= 0)
  //{
  //  for (auto & player : m_Players)
  //  {
  //    if (player.m_Loaded)
  //    {
  //      player.m_Client->SyncState(m_GameState);
  //    }
  //  }
  //
  //  m_SendTimer = kServerUpdateRate;
  //}
  //
  //for (auto & player : m_Players)
  //{
  //  m_Controller.ApplyInput(player.m_PlayerIndex, game, m_Input.m_PlayerInput[player.m_PlayerIndex]);
  //}
  //
  //m_Controller.Update(game);
  //
  //#endif
  //

}

void GameInstanceStateGameplay::HandlePlayerReady(std::size_t client_index, const ReadyMessage & msg)
{

}

void GameInstanceStateGameplay::HandlePlayerLoaded(std::size_t client_index, const FinishLoadingMessage & msg)
{
#ifdef NET_ALLOW_LATE_JOIN

#endif
  auto & client_info = m_StateData.GetClient(client_index);
  auto & player_info = m_PlayerInfo[client_index];

  if (player_info.m_LoadToken != msg.m_LoadToken)
  {
    return;
  }

  player_info.m_Loaded = true;
  player_info.m_ClientFrame = m_CurrentState->m_InstanceData.m_FrameCount;

  auto player_id = m_PlayerIdAllocator.Allocate();
  if (player_id >= kMaxPlayers)
  {

#ifdef NET_ALLOW_OBSERVERS
    player_info.m_PlayerIndex = -1;
    auto observer_id = m_ObserverIdAllocator.Allocate();
    if (observer_id < kMaxPlayers)
    {
      player_info.m_ObserverIndex = (int)observer_id;

      ObserverJoinedEvent ev;
      ev.m_PlayerIndex = (int)observer_id;
      ev.m_UserName = client_info.m_UserName;

      m_PendingExternals.emplace_back(std::move(ev));
    }
    else
#endif
    {
      client_info.m_Client->ForceDisconnect();
      return;
    }
  }
  else
  {
#ifdef NET_ALLOW_OBSERVERS
    player_info.m_ObserverIndex = -1;
#endif
    player_info.m_PlayerIndex = (int)player_id;

    PlayerJoinedEvent ev;
    ev.m_PlayerIndex = (int)player_id;
    ev.m_UserName = client_info.m_UserName;
    ev.m_RandomSeed = client_info.m_RandomSeed;

    m_PendingExternals.emplace_back(std::move(ev));
  }

  ClientLocalData local_data;
  local_data.m_PlayerIndex = player_info.m_PlayerIndex;

#ifdef NET_ALLOW_OBSERVERS
  local_data.m_ObserverIndex = player_info.m_ObserverIndex;
#endif

  player_info.m_LocalDataHistory.Push(player_info.m_ClientFrame, std::move(local_data));

  SendPacketToPlayer(client_index, player_info);

    //  auto player_id = m_StateData.m_IdAllocator.Allocate();
    //  if (player_id == IdAllocator::kInvalidId)
    //  {
    //    return false;
    //  }
    //
    //#if NET_MODE == NET_MODE_GGPO
    //  auto sim_data = m_SimHistory.Get();
    //
    //#ifndef NET_ALLOW_LATE_JOIN
    //
    //  if (sim_data->m_Sim.m_InstanceData.m_Started)
    //  {
    //    return false;
    //  }
    //#endif
    //
    //  auto r = GetRandomNumber();
    //
    //  if (sim_data->m_Sim.m_InstanceData.m_Started)
    //  {
    //    auto join_message_copy = std::make_unique<JoinGameMessage>(join_game);
    //    sim_data->m_Actions.emplace_back([this, r, player_id = (int)player_id, join_message = std::move(join_message_copy)](GameLogicContainer & game)
    //    {
    //      auto team = m_Controller.GetRandomTeam(game.GetInstanceData(), r);
    //      m_Controller.ConstructPlayer(player_id, game, join_message->m_UserName, team);
    //    });
    //  }
    //  else
    //  {
    //    auto game = GetLogicContainer();
    //    auto team = m_Controller.GetRandomTeam(game.GetInstanceData(), r);
    //    m_Controller.ConstructPlayer(player_id, game, join_game.m_UserName, team);
    //  }
    //
    //  sim_data->m_Input.m_PlayerInput[player_id] = {};
    //
    //  auto load_token = GetRandomNumber64();
    //
    //  int player_index = (int)player_id;
    //  m_Players.emplace_back(GamePlayer{ client, player_index, load_token, 0 });
    //
    //  LoadLevelMessage load_msg;
    //  load_msg.m_LoadToken = load_token;
    //  load_msg.m_Settings = m_InitSettings;
    //
    //  client->SendLoadLevel(load_msg);
    //
    //#else
    //
    //#ifndef NET_ALLOW_LATE_JOIN
    //
    //  if (m_GameState.m_InstanceData.m_Started)
    //  {
    //    return false;
    //  }
    //
    //#endif
    //
    //  auto game = GetLogicContainer();
    //  auto team = m_Controller.GetRandomTeam(game.GetInstanceData(), GetRandomNumber());
    //  m_Controller.ConstructPlayer(player_id, game, join_game.m_UserName, team);
    //
    //  m_Input.m_PlayerInput[player_id] = {};
    //
    //  auto load_token = GetRandomNumber64();
    //
    //  int player_index = (int)player_id;
    //  m_Players.emplace_back(GamePlayer{ client, player_index, load_token });
    //
    //  LoadLevelMessage load_msg;
    //  load_msg.m_LoadToken = load_token;
    //  load_msg.m_Settings = m_InitSettings;
    //
    //  client->SendLoadLevel(load_msg);
    //
    //#endif
    //
    //  return true;

    //  for (auto itr = m_Players.begin(), end = m_Players.end(); itr != end; ++itr)
    //  {
    //    if (itr->m_Client == client)
    //    {
    //      if (itr->m_Loaded || itr->m_LoadToken != finish_loading.m_LoadToken)
    //      {
    //        return;
    //      }
    //
    //      itr->m_Loaded = true;
    //
    //#if NET_MODE == NET_MODE_GGPO
    //      auto sim_data = m_SimHistory.Get();
    //      if (sim_data->m_Sim.m_InstanceData.m_Started)
    //      {
    //        sim_data->m_Actions.emplace_back([this, player_index = itr->m_PlayerIndex](GameLogicContainer & game)
    //        {
    //          m_Controller.PlayerReady(player_index, game);
    //        });
    //      }
    //      else
    //      {
    //        auto game = GetLogicContainer();
    //        m_Controller.PlayerReady(itr->m_PlayerIndex, game);
    //      }
    //
    //      ClientLocalData client_data;
    //      client_data.m_PlayerIndex = itr->m_PlayerIndex;
    //
    //      client->SyncClientData(client_data);
    //      client->SyncState(0, sim_data->m_Sim);
    //#else
    //
    //      auto game = GetLogicContainer();
    //      m_Controller.PlayerReady(itr->m_PlayerIndex, game);
    //
    //      ClientLocalData client_data;
    //      client_data.m_PlayerIndex = itr->m_PlayerIndex;
    //
    //      client->SyncClientData(client_data);
    //      client->SyncState(m_GameState);
    //#endif
    //      return;
    //    }
    //  }
}


#if NET_MODE == NET_MODE_GGPO

void GameInstanceStateGameplay::UpdatePlayer(std::size_t client_index, GameGGPOClientUpdate & update_data)
{
  auto & client_info = m_StateData.GetClient(client_index);
  auto & player_info = m_PlayerInfo[client_index];

  if (update_data.m_ClientFrame <= player_info.m_ClientFrame)
  {
    update_data.m_ClientFrame = player_info.m_ClientFrame + 1;
  }

  if (player_info.m_PlayerIndex == -1)
  {
    return;
  }

  int max_rewind_frame = m_CurrentState->m_InstanceData.m_FrameCount - kMaxRewindFrames;
  int rewind_frame = -1;

  if (update_data.m_Inputs)
  {
    auto & input_list = update_data.m_Inputs.Value();
    auto cur = input_list.begin();
    auto end = input_list.end();
    auto size = input_list.size();

    while (cur != end)
    {
      if (cur->m_Frame < player_info.m_ClientFrame || cur->m_Frame < max_rewind_frame)
      {
        ++cur;
        --size;
      }
      else
      {
        break;
      }
    }

    if (size > 0)
    {
      rewind_frame = cur->m_Frame;
      m_Inputistory.MergeList(cur, end, (int)size, [](ClientAuthData & v) { return v.m_Frame; }, 
        [&](ClientAuthData & v) { return HistoryInput{ player_info.m_PlayerIndex, v.m_Input}; });
    }
  }

  if (update_data.m_Events)
  {
    auto & events_list = update_data.m_Events.Value();
    auto cur = events_list.begin();
    auto end = events_list.end();
    auto size = events_list.size();

    while (cur != end)
    {
      if (cur->m_Frame < player_info.m_ClientFrame || cur->m_Frame < max_rewind_frame)
      {
        ++cur;
        --size;
      }
      else
      {
        break;
      }
    }

    if (size > 0)
    {
      rewind_frame = cur->m_Frame;
      m_EventHistory.MergeList(cur, end, (int)size, [](GameHistoryClientEvent & v) { return v.m_Frame; }, 
        [&](GameHistoryClientEvent & v) { return HistoryEvent{ player_info.m_PlayerIndex, v.m_Event }; });
    }
  }

  player_info.m_ClientFrame = update_data.m_ClientFrame;

  //if (update_data.m_Events)
  //{
  //  auto & event_list = update_data.m_Events.Value();
  //  auto cur = event_list.begin();
  //  auto end = event_list.end();
  //  auto size = event_list.size();

  //  while (cur != end)
  //  {
  //    if (cur->m_Frame < player_info.m_ClientFrame || cur->m_Frame < max_rewind_frame)
  //    {
  //      ++cur;
  //      --size;
  //    }
  //    else
  //    {
  //      break;
  //    }
  //  }

  //  if (size > 0)
  //  {
  //    rewind_frame = (rewind_frame == -1) ? cur->m_Frame : std::min(rewind_frame, cur->m_Frame);
  //    m_Inputistory.MergeList(cur, end, (int)size, [](auto & v) { return v.m_Frame; }, [](auto & v) { return v.m_Event; });
  //  }
  //}

  if (rewind_frame != -1)
  {
    auto frames_to_rewind = m_CurrentState->m_InstanceData.m_FrameCount - rewind_frame;

    if (frames_to_rewind > 0)
    {
      auto input_iter = m_Inputistory.IterateElementsSince(rewind_frame);
      auto event_iter = m_EventHistory.IterateElementsSince(rewind_frame);
      auto external_iter = m_ExternalsHistory.IterateElementsSince(rewind_frame);

      auto sim = *m_SimHistory.Get(frames_to_rewind);

      while (frames_to_rewind > 0)
      {
        m_ReconcileFrame = frames_to_rewind;

        auto new_state = std::make_shared<GameFullState>(*sim.get());

        int fake_send_timer = 0;
        GameLogicContainer logic_container(m_Controller, new_state->m_InstanceData, new_state->m_ServerObjectManager,
          *this, *this, m_StateData.GetSharedResources(), *m_InstanceResources.get(), m_Stage, true, fake_send_timer);

        auto input_visitor = [&](HistoryInput & elem)
        {
          m_Controller.ApplyInput(elem.m_PlayerIndex, logic_container, elem.m_Input);
        };

        input_iter.VisitElementsForCurrentTime(input_visitor);
        input_iter.Advance();

        auto event_visitor = [&](HistoryEvent & elem)
        {
          m_Controller.HandleClientEvent(elem.m_PlayerIndex, logic_container, elem.m_Event.GetClassId(), elem.m_Event.GetBase());
        };

        event_iter.VisitElementsForCurrentTime(event_visitor);
        event_iter.Advance();

        auto external_visitor = [&](NetPolymorphic<GameNetworkExternalEvent> & elem)
        {
          m_Controller.ProcessExternal(elem, logic_container);
        };

        external_iter.VisitElementsForCurrentTime(external_visitor);
        external_iter.Advance();

        m_Controller.Update(logic_container);
        --frames_to_rewind;

        m_SimHistory.SetAt(new_state, frames_to_rewind);

        if (frames_to_rewind == 0)
        {
          m_CurrentState = new_state;
        }

        sim = new_state;
      }
    }
  }

//  for (auto itr = m_Players.begin(), end = m_Players.end(); itr != end; ++itr)
//  {
//    if (itr->m_Client == client)
//    {
//      if (itr->m_Loaded == false)
//      {
//        return;
//      }
//
//      auto auth_data_copy = auth_data;
//      auto game = GetLogicContainer();
//      m_Controller.ValidateInput(itr->m_PlayerIndex, game, auth_data_copy.m_Input);
//
//#if NET_MODE == NET_MODE_GGPO
//      auto sim_data = m_SimHistory.Get();
//      if (auth_data_copy.m_Frame > sim_data->m_Sim.m_InstanceData.m_FrameCount)
//      {
//        itr->m_PendingInput.emplace_back(auth_data_copy);
//      }
//      else if (auth_data_copy.m_Frame == sim_data->m_Sim.m_InstanceData.m_FrameCount)
//      {
//        sim_data->m_Input.m_PlayerInput[itr->m_PlayerIndex] = auth_data_copy.m_Input;
//      }
//      else
//      {
//        Rewind(auth_data_copy, itr->m_PlayerIndex);
//      }
//
//      itr->m_LastInputFrame = auth_data_copy.m_Frame;
//#else
//      m_Input.m_PlayerInput[itr->m_PlayerIndex] = auth_data.m_Input;
//#endif
//      return;
//  }
}

bool GameInstanceStateGameplay::ReconcileEvent(std::size_t event_type_name_hash, uint64_t event_id, const GameNetVec2 & pos)
{
  return m_Reconciler.PushEvent(event_type_name_hash, event_id, pos, m_ReconcileFrame);
}

#else

void GameInstanceStateGameplay::UpdatePlayer(std::size_t client_index, GameInstanceStateData & state_data, ClientAuthData & update_data)
{

}

void GameInstanceStateGameplay::HandleClientEvent(std::size_t client_index, GameInstanceStateData & state_data, , std::size_t class_id, void * event_ptr)
{
  //for (auto itr = m_Players.begin(), end = m_Players.end(); itr != end; ++itr)
  //{
  //  if (itr->m_Loaded == false)
  //  {
  //    return;
  //  }

  //  if (itr->m_Client == client)
  //  {
  //    auto game = GetLogicContainer();
  //    m_Controller.HandleClientEvent(itr->m_PlayerIndex, game, class_id, event_ptr);
  //    return;
  //  }
  //}
}



void GameInstanceStateGameplay::SendGlobalEvent(std::size_t class_id, const void * event_ptr)
{
  for (auto itr = m_Players.begin(), end = m_Players.end(); itr != end; ++itr)
  {
    itr->m_Client->SendGlobalEvent(class_id, event_ptr);
  }
}

void GameInstanceStateGameplay::SendGlobalEvent(std::size_t class_id, const void * event_ptr, std::size_t connection_id)
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

void GameInstanceStateGameplay::SendEntityEvent(std::size_t class_id, const void * event_ptr, ServerObjectHandle object_handle)
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

void GameInstanceStateGameplay::SendEntityEvent(std::size_t class_id, const void * event_ptr, std::size_t connection_id, ServerObjectHandle object_handle)
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

#endif

GameLogicContainer GameInstanceStateGameplay::GetLogicContainer(int history_index)
{
  return GameLogicContainer(m_Controller, m_CurrentState->m_InstanceData, m_CurrentState->m_ServerObjectManager,
    *this, *this, m_StateData.GetSharedResources(), *m_InstanceResources.get(), m_Stage, true, m_SendTimer);
}

void GameInstanceStateGameplay::SendPacketToPlayer(std::size_t client_id, GameInstanceStateGameplayPlayer & player)
{
  auto & client_info = m_StateData.GetClient(client_id);
  if (player.m_Loaded == false)
  {
    GameStateLoading loading_state;

    for (auto elem : m_CurrentState->m_InstanceData.m_Players)
    {
      GameStateLoadingPlayer player;
      player.m_Loaded = true;
      player.m_UserName = elem.second.m_UserName;
      player.m_Team = (int)elem.second.m_Team;
      loading_state.m_Players.EmplaceBack(std::move(player));
    }

#ifdef NET_ALLOW_OBSERVERS
    for (auto elem : m_CurrentState->m_InstanceData.m_Observers)
    {
      GameStateLoadingPlayer player;
      player.m_Loaded = true;
      player.m_UserName = elem.second.m_UserName;
      player.m_Team = -1;
      loading_state.m_Players.EmplaceBack(std::move(player));
    }
#endif

    for (auto elem : m_PlayerInfo)
    {
      if (elem.second.m_Loaded == false)
      {
        auto & client_data = m_StateData.GetClient(elem.first);

        GameStateLoadingPlayer player;
        player.m_Loaded = true;
        player.m_UserName = client_data.m_UserName;
        player.m_Team = -1;
        loading_state.m_Players.EmplaceBack(std::move(player));
      }
    }

    client_info.m_Client->SyncLoadingState(loading_state);
    return;
  }

  GameGGPOServerGameState packet;
  packet.m_AckFrame = player.m_ClientFrame;
  packet.m_ServerFrame = m_CurrentState->m_InstanceData.m_FrameCount;

  if (player.m_ClientFrame >= m_CurrentState->m_InstanceData.m_FrameCount)
  {
    packet.m_State = m_CurrentState;
  }
  else
  {
    auto ack_history = m_CurrentState->m_InstanceData.m_FrameCount - player.m_ClientFrame;
    if (ack_history >= kMaxHistoryFrames)
    {
      ack_history = kMaxHistoryFrames - 1;
    }

    packet.m_State = *m_SimHistory.Get(ack_history);
  }
;
  auto packet_frame = packet.m_State->m_InstanceData.m_FrameCount;

  auto input_visitor = [&](int time, HistoryInput & inp)
  {
    if (inp.m_PlayerIndex == player.m_PlayerIndex)
    {
      return;
    }

    if (packet.m_Inputs == false)
    {
      packet.m_Inputs.Emplace();
    }

    packet.m_Inputs->EmplaceBack(GameHistoryInput{ inp.m_PlayerIndex, time, inp.m_Input });
  };
  m_Inputistory.VisitElementsSince(packet_frame, input_visitor);

  auto event_visitor = [&](int time, HistoryEvent & inp)
  {
    if (inp.m_PlayerIndex == player.m_PlayerIndex)
    {
      return;
    }

    if (packet.m_Events == false)
    {
      packet.m_Events.Emplace();
    }

    packet.m_Events->EmplaceBack(GameHistoryEvent{ inp.m_PlayerIndex, time, inp.m_Event });
  };
  m_EventHistory.VisitElementsSince(packet_frame, event_visitor);

  auto external_visitor = [&](int time, NetPolymorphic<GameNetworkExternalEvent> & inp)
  {
    if (packet.m_Externals == false)
    {
      packet.m_Externals.Emplace();
    }

    packet.m_Externals->EmplaceBack(GameHistoryExternal{ time, inp });
  };
  m_ExternalsHistory.VisitElementsSince(packet_frame, external_visitor);

  auto auth_visitor = [&](int time, NetPolymorphic<ServerAuthNetworkEvent> & inp)
  {
    if (packet.m_ServerAuthEvents == false)
    {
      packet.m_ServerAuthEvents.Emplace();
    }

    packet.m_ServerAuthEvents->EmplaceBack(GameHistoryAuthEvent{ time, inp });
  };
  m_AuthEventHistory.VisitElementsSince(packet_frame, auth_visitor);

  auto local_data_visitor = [&](int time, ClientLocalData & inp)
  {
    if (packet.m_LocalData == false)
    {
      packet.m_LocalData.Emplace();
    }

    packet.m_LocalData->EmplaceBack(GameHistoryClientLocal{ time, inp });
  };
  player.m_LocalDataHistory.VisitElementsSince(player.m_ClientFrame, local_data_visitor);

  client_info.m_Client->SyncGameState(packet);
}
