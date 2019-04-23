
#include <algorithm>
#include <random>

#include "HurricaneDDS/DDSRandom.h"
#include "HurricaneDDS/DDSChallenge.h"
#include "HurricaneDDS/DDSResponderCall.h"

#include "GameServerConnection.refl.meta.h"
#include "User.refl.meta.h"
#include "UserConnection.refl.meta.h"
#include "Game.refl.meta.h"
#include "GameList.refl.meta.h"
#include "Bot.refl.meta.h"

#include "GameServerMessages.refl.meta.h"
#include "UserConnectionMessages.refl.meta.h"


GameServerConnection::GameServerConnection(DDSNodeInterface node_interface) :
  m_State(GameServerConnectionState::kWaitingForConnection),
  m_Interface(node_interface),
  m_Error(false)
{

}

void GameServerConnection::GotMessage(GameServerMessageType cmd, std::string data)
{
  if (m_Error)
  {
    return;
  }

  switch (m_State)
  {
  case GameServerConnectionState::kWaitingForConnection:
    ForceDisconnect();
    break;
  case GameServerConnectionState::kAuthenticating:
    if (cmd == GameServerMessageType::kAuthResponse)
    {
      GameServerAuthenticateResponse resp;
      if (StormReflParseJson(resp, data.data()) == false)
      {
        ForceDisconnect();
        return;
      }
      
      if (resp.m_Challenge != m_ExpectedChallengeResponse)
      {
        ForceDisconnect();
        return;
      }

      m_ServerInfo = resp.m_ServerInfo;
      m_State = GameServerConnectionState::kConnected;
    }
    else
    {
      ForceDisconnect();
    }
    break;
  case GameServerConnectionState::kConnected:
    if (cmd == GameServerMessageType::kAuthUser)
    {
      GameServerAuthenticateUser msg;
      if (StormReflParseJson(msg, data.data()) == false)
      {
        ForceDisconnect();
        return;
      }

      m_Interface.Call(&Game::RedeemToken, msg.m_GameId, msg.m_UserId, msg.m_JoinToken, msg.m_ResponseId, m_Interface.GetLocalKey());
    }
    else if (cmd == GameServerMessageType::kRequestTeamSwitch)
    {

    }
    else if (cmd == GameServerMessageType::kRandomizeTeams)
    {

    }
    else if (cmd == GameServerMessageType::kUserDisconnected)
    {

    }
    else if (cmd == GameServerMessageType::kGameScore)
    {

    }
    else if (cmd == GameServerMessageType::kUserStats)
    {
      GameServerStats msg;
      if (StormReflParseJson(msg, data.data()) == false)
      {
        ForceDisconnect();
        return;
      }

      m_Interface.Call(&User::UpdateStats, msg.m_AccountId, msg.m_Stats, msg.m_Settings);
    }
    else if (cmd == GameServerMessageType::kGameResult)
    {
      GameServerGameResult msg;
      if (StormReflParseJson(msg, data.data()) == false)
      {
        ForceDisconnect();
        return;
      }
    }
    else
    {
      ForceDisconnect();
    }
  }
}

void GameServerConnection::CreateGame(const GameServerCreateGame & msg)
{
  m_ActiveGameIds.push_back(msg.m_GameId);
  SendPacket(msg);
}

void GameServerConnection::DestroyGame(const GameServerDestroyGame & msg)
{
  for(auto itr = m_ActiveGameIds.begin(), end = m_ActiveGameIds.end(); itr != end; ++itr)
  {
    if(*itr == msg.m_GameId)
    {
      m_ActiveGameIds.erase(itr);
      SendPacket(msg);
      break;
    }
  }
}

void GameServerConnection::RemoveUserFromGame(DDSKey game_id, DDSKey user_id)
{
  for(auto itr = m_ActiveGameIds.begin(), end = m_ActiveGameIds.end(); itr != end; ++itr)
  {
    if(*itr == game_id)
    {
      GameServerForceUserDisconnect msg;
      msg.m_GameId = game_id;
      msg.m_UserId = user_id;

      SendPacket(msg);
      return;
    }
  }
}

void GameServerConnection::ChangeUserLoadout(DDSKey game_id, DDSKey user_id, const GamePlayerLoadout & loadout)
{
  for(auto itr = m_ActiveGameIds.begin(), end = m_ActiveGameIds.end(); itr != end; ++itr)
  {
    if(*itr == game_id)
    {
      GameServerForceUserDisconnect msg;
      msg.m_GameId = game_id;
      msg.m_UserId = user_id;

      SendPacket(msg);
      return;
    }
  }
}

void GameServerConnection::NotifyUserQuitGame(DDSKey game_id, DDSKey user_key, bool ban)
{
  for(auto itr = m_ActiveGameIds.begin(), end = m_ActiveGameIds.end(); itr != end; ++itr)
  {
    if(*itr == game_id)
    {
      m_Interface.Call(&Game::HandleUserQuitGame, game_id, user_key, ban);
      return;
    }
  }
}

void GameServerConnection::NotifyGameEnded(DDSKey game_id)
{
  for(auto itr = m_ActiveGameIds.begin(), end = m_ActiveGameIds.end(); itr != end; ++itr)
  {
    if(*itr == game_id)
    {
      m_Interface.Call(&Game::HandleGameComplete, game_id);
      return;
    }
  }
}

void GameServerConnection::NotifyTokenRedeemedSuccess(DDSKey game_id, const GameServerAuthenticateUserSuccess & msg)
{
  SendPacket(msg);
}

void GameServerConnection::NotifyTokenRedeemedFailure(DDSKey game_id, const GameServerAuthenticateUserFailure & msg)
{
  SendPacket(msg);
}

void GameServerConnection::ConnectToEndpoint(DDSConnectionId connection_id)
{
  m_ConnectionId = connection_id;

  if (m_State == GameServerConnectionState::kWaitingForConnection)
  {
    m_State = GameServerConnectionState::kAuthenticating;

    uint64_t challenge = DDSGetRandomNumber64();
    m_ExpectedChallengeResponse = DDSCalculateChallengeResponse(challenge) ^ kGameServerChallengePad;

    GameServerAuthenticateRequest req;
    req.m_Challenge = challenge;
    SendPacket(req);
  }

  for (auto & data : m_PendingMessages)
  {
    m_Interface.SendDataToLocalConnection(*m_ConnectionId, data);
  }

  m_PendingMessages.clear();
}

void GameServerConnection::PreDestroy()
{
  if (m_State == GameServerConnectionState::kConnected)
  {

  }
}

void GameServerConnection::PreMoveObject()
{
  DDSLog::LogVerbose("Moving server connection to new server %llu", m_Interface.GetLocalKey());

  auto node_info = m_Interface.GetNodeInfo(m_Interface.GetLocalKey());
  if (node_info)
  {
    std::string ip_addr = GetNodeAddrAsString(node_info->get().m_Addr);
    GameServerRelocate relocate{ ip_addr, node_info->get().m_EndpointPorts[1], m_Interface.GetLocalKey() };
    SendPacket(relocate);
    m_Relocating = true;
  }
  else
  {
    ForceDisconnect();
  }

  m_ConnectionId = {};
}

template <typename T>
void GameServerConnection::SendPacket(const T & t)
{
  if (m_Error)
  {
    return;
  }

  std::string packet_data = StormReflGetEnumAsString(T::Type);
  packet_data += ' ';
  StormReflEncodeJson(t, packet_data);

  if (m_ConnectionId)
  {
    m_Interface.SendDataToLocalConnection(*m_ConnectionId, packet_data);
  }
  else
  {
    m_PendingMessages.emplace_back(packet_data);
  }
}

void GameServerConnection::ForceDisconnect()
{
  if (m_ConnectionId)
  {
    m_Interface.DisconnectLocalConnection(*m_ConnectionId);
  }

  m_Error = true;
}
