
#include "GameServer/GameInstanceStatePrivateGameStaging.h"
#include "GameServer/GameInstanceStateLoading.h"
#include "GameServer/GameInstanceStateData.h"
#include "GameServer/GameClientConnection.h"

#include "Game/GameController.refl.h"
#include "Game/GameNetworkSettings.h"

static const int kSendInterval = 10 * 60;

GameInstanceStatePrivateGameStaging::GameInstanceStatePrivateGameStaging(GameInstanceStateData & state_data) :
        GameInstanceStateBase(state_data),
        m_SendTimer(0)
{
  m_State.m_Settings = state_data.GetInitSettings();
  m_State.m_Countdown = 0;
  m_State.m_PrivateRoomId = state_data.GetPrivateRoomId();

  auto visitor = [this](auto client_index, auto & client_data)
  {
    AddPlayer(client_index);
  };

  m_StateData.VisitPlayers(visitor);
}

bool GameInstanceStatePrivateGameStaging::JoinPlayer(std::size_t client_index, const GameJoinInfo & join_game)
{
  if (m_State.m_Players.Size() >= kMaxPlayers)
  {
    return false;
  }

  AddPlayer(client_index);
  return true;
}

void GameInstanceStatePrivateGameStaging::RemovePlayer(std::size_t client_index)
{
  auto & player_data = m_StateData.GetClient(client_index);
  if(player_data.m_GameLeader)
  {
    Optional<std::size_t> new_leader_index;
    auto visitor = [&](auto test_client_index, auto & client_data)
    {
      if(new_leader_index.IsValid() == false && test_client_index != client_index)
      {
        new_leader_index = test_client_index;
      }
    };

    m_StateData.VisitPlayers(visitor);

    if(new_leader_index)
    {
      auto & new_leader_player_data = m_StateData.GetClient(new_leader_index.Value());
      new_leader_player_data.m_GameLeader = true;
      m_State.m_Players[client_index].m_GameLeader = true;
    }
  }

  m_State.m_Players.RemoveAt(client_index);
  m_SendTimer = 0;
}

void GameInstanceStatePrivateGameStaging::Update()
{
  if (m_SendTimer == 0)
  {
    auto visitor = [&](auto client_index, auto & client_data)
    {
      client_data.m_Client->SyncStagingState(m_State);
    };

    m_StateData.VisitPlayers(visitor);
    m_SendTimer = kSendInterval;
  }
  else
  {
    m_SendTimer--;
  }

  bool ready = CheckGameReady();

  if (m_State.m_Countdown == 0)
  {
    if (ready)
    {
      m_State.m_Countdown = 10;
    }
  }
  else
  {
    if (ready == false)
    {
      m_State.m_Countdown = 0;
    }
    else
    {
      m_State.m_Countdown -= 1;
      if (m_State.m_Countdown <= 0)
      {
        m_StateData.SwitchState(GameInstanceStateDef<GameInstanceStateLoading>{}, m_State);
      }
    }
  }
}

void GameInstanceStatePrivateGameStaging::HandlePlayerReady(std::size_t client_index, const ReadyMessage & msg)
{
#if defined(NET_USE_READY) || defined(NET_USE_READY_PRIVATE_GAME)
  m_State.m_Players[client_index].m_Ready = msg.m_Ready;
#endif
}

void GameInstanceStatePrivateGameStaging::HandlePlayerLoaded(std::size_t client_index, const FinishLoadingMessage & msg)
{

}

void GameInstanceStatePrivateGameStaging::HandlePlayerKick(std::size_t client_index, const KickPlayerMessage & msg)
{
  auto & player_data = m_StateData.GetClient(client_index);
  if(player_data.m_GameLeader == false)
  {
    return;
  }

  player_data.m_Client->ForceDisconnect();
}

void GameInstanceStatePrivateGameStaging::HandleTextChat(std::size_t client_index, const SendTextChatMessage & msg)
{
  GotTextChatMessage out_text;
  auto team = static_cast<int>(m_State.m_Players[client_index].m_Team);

  out_text.m_Message = msg.m_Message;
  out_text.m_UserName = m_State.m_Players[client_index].m_UserName;

  if(msg.m_TeamOnly)
  {
    auto visitor = [&](auto client_index, auto & client_data)
    {
      if(m_State.m_Players[client_index].m_Team == team)
      {
        client_data.m_Client->SendTextChat(out_text);
      }
    };

    m_StateData.VisitPlayers(visitor);
  }
  else
  {
    auto visitor = [&](auto client_index, auto & client_data)
    {
      client_data.m_Client->SendTextChat(out_text);
    };

    m_StateData.VisitPlayers(visitor);
  }
}

void GameInstanceStatePrivateGameStaging::AddPlayer(std::size_t client_index)
{
  m_State.m_Players.EmplaceAt(client_index);

  auto & staging_player = m_State.m_Players.EmplaceAt(client_index);
  auto & player_data = m_StateData.GetClient(client_index);

  staging_player.m_UserName = player_data.m_UserName;
  staging_player.m_GameLeader = player_data.m_GameLeader;

#ifdef NET_USE_RANDOM_TEAM
  auto team_counts = GameController::GetTeamCounts(m_State);
  auto team = GameController::GetRandomTeam(team_counts, player_data.m_RandomSeed);
#else
  auto team = (int)(client_index % kMaxTeams);
#endif

  staging_player.m_Team = team;
}

bool GameInstanceStatePrivateGameStaging::CheckGameReady()
{
  auto team_counts = GameController::GetTeamCounts(m_State);
  if(GameController::DoAllTeamsHavePlayers(team_counts) == false)
  {
    return false;
  }

#if defined(NET_USE_READY) || defined(NET_USE_READY_PRIVATE_GAME)
  bool ready = true;
  auto visitor = [&](auto client_index, auto & client_data)
  {
    if(m_State.m_Players[client_index].m_Ready == false)
    {
      ready = false;
    }
  };

  m_StateData.VisitPlayers(visitor);

  if(ready == false)
  {
    return false;
  }
#endif

  return true;
}
