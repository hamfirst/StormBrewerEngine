

#include "GameServer/GameInstanceStateLoading.h"
#include "GameServer/GameInstanceStateGameplay.h"
#include "GameServer/GameInstanceStateData.h"
#include "GameServer/GameClientConnection.h"

#include "Game/GameController.refl.h"
#include "ProjectSettings/ProjectNetworkSettings.h"

static const int kTimeToWaitForLoad = 10 * 60;
static const int kSendInterval = 2 * 60;

GameInstanceStateLoading::GameInstanceStateLoading(GameInstanceStateData & state_data) :
  GameInstanceStateBase(state_data),
  m_TimeToWaitForLoad(kTimeToWaitForLoad),
  m_SendTimer(0)
{

}

bool GameInstanceStateLoading::JoinPlayer(std::size_t client_index, const GameJoinInfo & join_game)
{
  if (m_State.m_Players.Size() >= kMaxPlayers)
  {
    return false;
  }

  AddPlayer(client_index, join_game.m_Team);
  return true;
}

void GameInstanceStateLoading::RemovePlayer(std::size_t client_index)
{
  printf("Removing player from loading state\n");
  m_State.m_Players.RemoveAt(client_index);
  m_LoadTokens.RemoveAt(client_index);
}

void GameInstanceStateLoading::Update()
{
  if (m_SendTimer == 0)
  {
    auto visitor = [&](auto client_index, auto & client_data)
    {
      client_data.m_Client->SyncLoadingState(m_State);
    };

    m_StateData.VisitPlayers(visitor);
    m_SendTimer = kSendInterval;
  }
  else
  {
    m_SendTimer--;
  }

  m_TimeToWaitForLoad--;
  if (m_TimeToWaitForLoad < 0)
  {
    for (auto elem : m_State.m_Players)
    {
      if (elem.second.m_Loaded == false)
      {
        auto player_info = m_StateData.GetClient(elem.first);
        player_info.m_Client->ForceDisconnect();
      }
    }
  }

  bool ready = CheckFinishedLoading();
  if (ready)
  {
    m_StateData.SwitchState(GameInstanceStateDef<GameInstanceStateGameplay>{}, m_State);
  }
}

void GameInstanceStateLoading::HandlePlayerLoaded(std::size_t client_index, const FinishLoadingMessage & msg)
{
  auto load_token = m_LoadTokens[client_index];
  if (load_token != msg.m_LoadToken)
  {
    return;
  }

  auto & player_data = m_State.m_Players[client_index];
  player_data.m_Loaded = true;
}

bool GameInstanceStateLoading::CheckFinishedLoading() const
{
  return m_TimeToWaitForLoad <= 0;
}

void GameInstanceStateLoading::AddPlayer(std::size_t client_index, int team)
{
  auto & client_data = m_StateData.GetClient(client_index);
  auto & player_data = m_State.m_Players.EmplaceAt(client_index);
  player_data.m_Team = team;
  player_data.m_UserName = client_data.m_UserName;

  auto load_token = GetRandomNumber64();
  m_LoadTokens.EmplaceAt(client_index, load_token);

  LoadLevelMessage msg;
  msg.m_LoadToken = load_token;
  msg.m_Settings = m_StateData.GetInitSettings();
  client_data.m_Client->SendLoadLevel(msg);

  m_TimeToWaitForLoad = kTimeToWaitForLoad;
}
