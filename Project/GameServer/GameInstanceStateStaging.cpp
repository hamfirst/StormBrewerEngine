
#include "GameServer/GameInstanceStateStaging.h"
#include "GameServer/GameInstanceStateLoading.h"
#include "GameServer/GameInstanceStateData.h"
#include "GameServer/GameClientConnection.h"

#include "Game/GameController.refl.h"
#include "ProjectSettings/ProjectNetworkSettings.h"

static const int kTimeToWaitForPlayers = 5 * 60;
static const int kSendInterval = 2 * 60;

GameInstanceStateStaging::GameInstanceStateStaging(GameInstanceStateData & state_data) :
  GameInstanceStateBase(state_data),
  m_TimeToWaitForPlayers(kTimeToWaitForPlayers + 1),
  m_SendTimer(0)
{
  m_State.m_Settings = state_data.GetInitSettings();
  m_State.m_Countdown = 0;
  m_State.m_PrivateRoomId = 0;

  auto visitor = [this](auto client_index, auto & client_data)
  {
    AddPlayer(client_index);
  };

  m_StateData.VisitPlayers(visitor);
}

bool GameInstanceStateStaging::JoinPlayer(std::size_t client_index, const GameJoinInfo & join_game)
{
  if (m_State.m_Players.Size() >= kMaxPlayers)
  {
    return false;
  }

  AddPlayer(client_index);
  return true;
}

void GameInstanceStateStaging::RemovePlayer(std::size_t client_index)
{
  m_State.m_Players.RemoveAt(client_index);
}

void GameInstanceStateStaging::Update()
{
  m_State.m_WaitTimer = m_TimeToWaitForPlayers;

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

  m_TimeToWaitForPlayers--;
  bool ready = CheckGameReady() || m_TimeToWaitForPlayers <= 0;

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

void GameInstanceStateStaging::HandlePlayerReady(std::size_t client_index, const ReadyMessage & msg)
{
#if NET_USE_READY
  m_State.m_Players[client_index].m_Ready = msg.m_Ready;
#endif
}

void GameInstanceStateStaging::HandlePlayerLoaded(std::size_t client_index, const FinishLoadingMessage & msg)
{

}

void GameInstanceStateStaging::HandleTextChat(std::size_t client_index, const SendTextChatMessage & msg)
{
  GotTextChatMessage out_text;
  auto team = static_cast<int>(m_State.m_Players[client_index].m_Team);

  out_text.m_Message = msg.m_Message;
  out_text.m_UserName = m_State.m_Players[client_index].m_UserName;
  out_text.m_Team = m_State.m_Players[client_index].m_Team;

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

void GameInstanceStateStaging::HandleChangeLoadout(std::size_t client_index, const ChangeLoadoutMessage & msg)
{
  m_State.m_Players[client_index].m_Loadout = msg.m_Loadout;
}

void GameInstanceStateStaging::AddPlayer(std::size_t client_index)
{
  m_State.m_Players.EmplaceAt(client_index);

  auto & staging_player = m_State.m_Players.EmplaceAt(client_index);
  auto & player_data = m_StateData.GetClient(client_index);

  staging_player.m_UserName = player_data.m_UserName;

#ifdef NET_USE_RANDOM_TEAM
  auto team_counts = GameController::GetTeamCounts(m_State);
  auto team = GameController::GetRandomTeam(team_counts, player_data.m_RandomSeed);
#else
  auto team = (int)(client_index % kMaxTeams);
#endif

  staging_player.m_Team = team;
}

bool GameInstanceStateStaging::CheckGameReady()
{
  auto team_counts = GameController::GetTeamCounts(m_State);
  if(GameController::DoAllTeamsHavePlayers(team_counts) == false)
  {
    return false;
  }

#if defined(NET_USE_READY)
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
