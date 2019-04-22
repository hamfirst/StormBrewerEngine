
#include <StormData/StormDataChangePacket.h>
#include <StormData/StormDataListUtil.h>

#include <HurricaneDDS/DDSResponderCall.h>
#include <HurricaneDDS/DDSResponder.refl.meta.h>

#include <hash/Hash64.h>
#include <sb/vector.h>

#include "LobbyShared/LobbyGameFuncs.h"

#include "User.refl.meta.h"
#include "UserConnection.refl.meta.h"
#include "UserConnectionMessages.refl.meta.h"
#include "Channel.refl.meta.h"
#include "BanList.refl.meta.h"
#include "GameServerConnection.refl.meta.h"
#include "WelcomeInfo.refl.meta.h"
#include "Game.refl.meta.h"
#include "GameList.refl.meta.h"
#include "Bot.refl.meta.h"
#include "Rewards.refl.meta.h"
#include "LobbyLevelList.refl.h"

#include "CommandParse.h"
#include "LobbyConfig.h"

STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(UserPersistent);
STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(UserLocalData);

UserNameLookup::UserNameLookup(const char * user_name) : m_UserNameLower(user_name) { std::transform(m_UserNameLower.begin(), m_UserNameLower.end(), m_UserNameLower.begin(), tolower); }
UserNameLookup::UserNameLookup(std::string & user_name) : UserNameLookup(user_name.c_str()) {}

UserPlatformIdLookup::UserPlatformIdLookup(DDSKey platform_id) : m_PlatformId(platform_id) {}

User::User(DDSNodeInterface node_interface, UserDatabaseObject & db_object) : 
  m_Interface(node_interface), m_Data(db_object),
  m_LinesThrottle(5, 1),
  m_CharsThrottle(1000, 50),
  m_GameCreationThrottle(1, (1/10.0f)),
  m_SquadCreationThrottle(1, (1.0f / 30.0f)),
  m_ProfileThrottle(4, 2),
  m_GameThrottle(8, 2)
{ 
  m_UserInfo.m_Name = m_Data.m_UserName;

  m_UserInfo.m_PlatformId = m_Data.m_PlatformId;
  m_UserInfo.m_Platform = m_Data.m_Platform;
  m_UserInfo.m_AdminLevel = m_Data.m_AdminLevel;

  m_UserInfo.m_Icon = m_Data.m_Icon;

#ifdef ENABLE_CHANNELS
  m_UserInfo.m_VisibleFlags = m_Data.m_VisibilityFlags;
  m_LocalInfo.m_AutoJoinChannels = m_Data.m_AutoJoinChannels;
#endif

  m_LocalInfo.m_Name = m_Data.m_UserName;
  m_LocalInfo.m_AdminLevel = m_Data.m_AdminLevel;
  m_LocalInfo.m_Title = m_Data.m_Title;
  m_LocalInfo.m_TitleList = m_Data.m_TitleList;
  m_LocalInfo.m_Icon = m_Data.m_Icon;
  m_LocalInfo.m_IconList = m_Data.m_IconList;
  m_LocalInfo.m_Celebration = m_Data.m_Celebration;
  m_LocalInfo.m_CelebrationList = m_Data.m_CelebrationList;
  m_LocalInfo.m_UserKey = m_Interface.GetLocalKey();
  m_LocalInfo.m_PlatformId = m_Data.m_PlatformId;
  m_LocalInfo.m_Platform = m_Data.m_Platform;
  m_LocalInfo.m_Persistent = m_Data.m_Persistent;

#ifdef ENABLE_SQUADS
  m_LocalInfo.m_OwnerSquad = m_Data.m_OwnerSquad;
  m_LocalInfo.m_PrimarySquad = m_Data.m_PrimarySquad;
#endif
}

void User::AddEndpoint(DDSKey key, std::string remote_ip, std::string remote_host)
{
  bool found_ip = false;
  for (auto elem : m_Data.m_HistoryHosts)
  {
    if (elem.second == remote_host)
    {
      found_ip = true;
      break;
    }
  }

  if (found_ip == false)
  {
    m_Data.m_HistoryHosts.EmplaceBack(remote_host);
  }

  m_Endpoints.emplace(std::make_pair(key, std::make_pair(remote_ip, remote_host)));

  if (m_Endpoints.size() == 1)
  {
#ifdef ENABLE_CHANNELS
    JoinChannel(0, "General");

    if (m_LocalInfo.m_AdminLevel > 0)
    {
      JoinChannel(0, "Admin");
      JoinChannel(0, "Support");
      JoinChannel(0, "Newbies");
    }

    for (auto squad : m_LocalInfo.m_Squads)
    {
      JoinChannel(0, squad.second.m_Tag.ToString());
    }

    for (auto channel : m_LocalInfo.m_AutoJoinChannels)
    {
      JoinChannel(0, channel.second);
    }
#endif

#ifdef ENABLE_REWARDS
    GiveGifts();
#endif

#ifdef ENABLE_REWARDS
    SendXPGain(key);
    ApplyXPGain(true);
#endif
  }
}

void User::SendToAllEndpoints(std::string data)
{
  for (auto ep : m_Endpoints)
  {
    m_Interface.Call(&UserConnection::SendData, ep.first, data);
  }
}

void User::SendNotification(std::string data)
{
  for (auto ep : m_Endpoints)
  {
    m_Interface.Call(&UserConnection::SendNotification, ep.first, data);
  }
}

void User::SendToEndpoint(DDSKey endpoint_id, std::string data)
{
  for (auto ep : m_Endpoints)
  {
    if (ep.first == endpoint_id)
    {
      m_Interface.Call(&UserConnection::SendData, ep.first, data);
      return;
    }
  }
}

void User::RemoveEndpoint(DDSKey key)
{
  auto itr = m_Endpoints.find(key);
  if (itr != m_Endpoints.end())
  {
    m_Endpoints.erase(itr);
    if (m_Endpoints.size() == 0)
    {
#ifdef ENABLE_CHANNELS
      LeaveAllChannels();
#endif
    }

    if (m_InGame && key == m_GameEndpoint)
    {
      LeaveGame();
    }

    if(m_Endpoints.size() == 0 && m_Data.m_IsGuest)
    {
      m_Interface.DestroySelf();
    }
  }
}

void User::SetLocation(std::string country_code, std::string currency_code)
{
  m_CountryCode = country_code;
  m_CurrencyCode = currency_code;
}

void User::UpdateName(std::string name)
{
  if(m_UserInfo.m_Name.compare(name) == 0)
  {
    std::string user_name_lower = name;
    std::transform(user_name_lower.begin(), user_name_lower.end(), user_name_lower.begin(), tolower);

    m_Data.m_UserName = name;
    m_Data.m_UserNameLower = user_name_lower;
    m_LocalInfo.m_Name = name;
    m_UserInfo.m_Name = name;
  }
}

#ifdef ENABLE_REWARDS
void User::GiveGifts()
{
  m_Interface.QueryDatabaseByKey("Gifts", m_Interface.GetLocalKey(), &User::HandleGiftData, this);
}

void User::HandleGiftData(int ec, std::string data)
{
  auto responder = CreateEmptyResponder(m_Interface);

  UserRewards gifts;
  StormReflParseJson(gifts, data.c_str());

  for (auto & icon : gifts.m_Icons)
  {
    AddIcon(responder, icon, false, false);
  }

  for (auto & title : gifts.m_Titles)
  {
    AddTitle(responder, title, false);
  }

  if (
    m_CountryCode == "GR" ||
    m_CountryCode == "FI" ||
    m_CountryCode == "GE" ||
    m_CountryCode == "IS" ||
    m_CountryCode == "GB" ||
    m_CountryCode == "NO" ||
    m_CountryCode == "DK" ||
    m_CountryCode == "CH" ||
    m_CountryCode == "MT" ||
    m_CountryCode == "PL" ||
    m_CountryCode == "AT" ||
    m_CountryCode == "LU" ||
    m_CountryCode == "NL" ||
    m_CountryCode == "HR" ||
    m_CountryCode == "RS" ||
    m_CountryCode == "SK" ||
    m_CountryCode == "SI" ||
    m_CountryCode == "RU" ||
    m_CountryCode == "CZ" ||
    m_CountryCode == "FR" ||
    m_CountryCode == "RO" ||
    m_CountryCode == "MD" ||
    m_CountryCode == "BE" ||
    m_CountryCode == "DE" ||
    m_CountryCode == "AM" ||
    m_CountryCode == "AZ" ||
    m_CountryCode == "LT" ||
    m_CountryCode == "BG" ||
    m_CountryCode == "HU" ||
    m_CountryCode == "IE" ||
    m_CountryCode == "IT" ||
    m_CountryCode == "PT" ||
    m_CountryCode == "BY" ||
    m_CountryCode == "TR" ||
    m_CountryCode == "AL" ||
    m_CountryCode == "ME" ||
    m_CountryCode == "MK" ||
    m_CountryCode == "ES" ||
    m_CountryCode == "UA" ||
    m_CountryCode == "BA" ||
    m_CountryCode == "SE" ||
    m_CountryCode == "KZ" ||
    m_CountryCode == "EE" ||
    m_CountryCode == "IL" ||
    m_CountryCode == "CY")
  {
    AddAutoJoinChannel(responder, "Europe");
  }
 
  m_Interface.DeleteFromDatabase("Gifts", m_Interface.GetLocalKey());
}
#endif

#ifdef ENABLE_CHANNELS
bool User::IsInChannel(DDSKey key) const
{
  for (auto elem : m_LocalInfo.m_Channels)
  {
    if (elem.second->m_ChannelKey == key)
    {
      return true;
    }
  }

  return false;
}

void User::JoinChannel(DDSKey requesting_endpoint, std::string channel_name)
{
  DDSLog::LogVerbose("Joining User %s To Channel %s", m_LocalInfo.m_Name.c_str(), channel_name.c_str());
  DDSKey channel_key = Channel::GetChannelKeyFromName(channel_name.data());

  if (std::find(m_PendingChannelJoins.begin(), m_PendingChannelJoins.end(), channel_key) != m_PendingChannelJoins.end())
  {
    return;
  }

  m_PendingChannelJoins.push_back(channel_key);
  m_Interface.CallWithResponderReturnArg(&Channel::AddUser, channel_key, &User::HandleChannelJoinResponse, this, 
    std::make_pair(requesting_endpoint, channel_key), m_Interface.GetLocalKey(), m_UserInfo.m_AdminLevel, channel_name);
}

void User::LeaveChannel(DDSKey channel_key)
{
  auto sub_itr = m_ChannelSubscriptions.begin();
  while (sub_itr != m_ChannelSubscriptions.end())
  {
    if ((*sub_itr).second == channel_key)
    {
      break;
    }

    ++sub_itr;
  }

  if (sub_itr == m_ChannelSubscriptions.end())
  {
    return;
  }

  //m_Interface.DestroySubscription<Channel>(sub_itr->second, sub_itr->first);

  m_Interface.Call(&Channel::RemoveUser, channel_key, m_Interface.GetLocalKey());

  auto channel_itr = m_LocalInfo.m_Channels.begin();
  while (channel_itr != m_LocalInfo.m_Channels.end())
  {
    if ((*channel_itr).second->m_ChannelKey == channel_key)
    {
      break;
    }

    ++channel_itr;
  }

  if (channel_itr != m_LocalInfo.m_Channels.end())
  {
    m_LocalInfo.m_Channels.RemoveAt(channel_itr->first);
  }

  m_Interface.DestroySharedLocalCopy(sub_itr->first);
  m_ChannelSubscriptions.erase(sub_itr);
}

void User::LeaveAllChannels()
{
  for (auto & sub : m_ChannelSubscriptions)
  {
    m_Interface.DestroySharedLocalCopy(sub.first);
    m_Interface.Call(&Channel::RemoveUser, sub.second, m_Interface.GetLocalKey());
  }

  m_ChannelSubscriptions.clear();

  m_LocalInfo.m_Channels.Clear();
}

void User::SendChatToChannel(DDSKey src_endpoint_id, DDSKey channel_key, std::string message)
{
  bool in_channel = false;
  for (auto channel : m_LocalInfo.m_Channels)
  {
    if (channel.second->m_ChannelKey == channel_key)
    {
      in_channel = true;
      break;
    }
  }

  if (in_channel == false)
  {
    return;
  }

  if (m_LocalInfo.m_AdminLevel == 0)
  {
    auto cur_time = m_Interface.GetNetworkTime();
    if (m_LinesThrottle.HasCredits(cur_time, 1) == false)
    {
      m_Interface.Call(&UserConnection::SendNotification, src_endpoint_id, "Your last message was not sent due to spam");
      return;
    }

    if (m_CharsThrottle.HasCredits(cur_time, message.size()) == false)
    {
      m_Interface.Call(&UserConnection::SendNotification, src_endpoint_id, "Your last message was not sent due to spam");
      return;
    }

    m_LinesThrottle.SubCredits(1);
    m_LinesThrottle.SetReboundTime(cur_time, 1);
    m_CharsThrottle.SubCredits(message.size());
  }

  m_Interface.Call(&Channel::SendChatToChannel, channel_key,
      m_Interface.GetLocalKey(), src_endpoint_id, message, m_LocalInfo.m_Title);
}

void User::HandleChannelJoinResponse(std::pair<DDSKey, DDSKey> join_info, ChannelJoinResult result)
{
  auto endpoint_id = std::get<0>(join_info);
  auto channel_key = std::get<1>(join_info);

  auto itr = std::find(m_PendingChannelJoins.begin(), m_PendingChannelJoins.end(), channel_key);
  if (itr == m_PendingChannelJoins.end())
  {
    m_Interface.Call(&Channel::RemoveUser, channel_key, m_Interface.GetLocalKey());
    return;
  }

  m_PendingChannelJoins.erase(itr);

  if (result == ChannelJoinResult::kLocked)
  {
    if (endpoint_id != 0)
    {
      m_Interface.Call(&UserConnection::SendNotification, endpoint_id, "That channel is locked");
    }
    return;
  }
  else if (result == ChannelJoinResult::kAlreadyIn)
  {
    if (endpoint_id != 0)
    {
      m_Interface.Call(&UserConnection::SendNotification, endpoint_id, "You're already in that channel");
    }
    return;
  }

//  DDSKey sub_key =
//    m_Interface.CreateSubscription(DDSSubscriptionTarget<Channel>{}, channel_key, ".m_ChannelInfo", &User::HandleChannelUpdate, true, channel_key);

  auto sub_key = m_Interface.CreateSharedLocalCopy(
    DDSSubscriptionTarget<Channel>{}, DDSSubscriptionTarget<ChannelInfo>{}, channel_key, ".m_ChannelInfo", &User::HandleChannelUpdate, channel_key);

  m_ChannelSubscriptions.emplace_back(sub_key, channel_key);
}

void User::HandleChannelUpdate(DDSKey channel_key, std::string data, int version)
{
  DDSLog::LogVerbose("Got channel update:\n%s", data.data());

  auto channel_itr = m_LocalInfo.m_Channels.begin();
  while (channel_itr != m_LocalInfo.m_Channels.end())
  {
    if ((*channel_itr).second->m_ChannelKey == channel_key)
    {
      break;
    }

    ++channel_itr;
  }

  if (channel_itr == m_LocalInfo.m_Channels.end())
  {
    // Check to see if this is a channel we just subscribed to
    auto sub_itr = std::find_if(m_ChannelSubscriptions.begin(), m_ChannelSubscriptions.end(), [&](auto & sub_info) { return sub_info.second == channel_key; });
    if (sub_itr == m_ChannelSubscriptions.end())
    {
      return;
    }

    auto new_channel_info = m_Interface.GetSharedLocalCopyPtr<Channel, ChannelInfo>(channel_key, ".m_ChannelInfo", version);
    m_LocalInfo.m_Channels.EmplaceBack(std::move(new_channel_info));
    return;
  }

  DDSApplySharedLocalCopyChangePacket(channel_itr->second, data, version);
}

#endif

void User::CreatePrivateGame(DDSKey endpoint_id, GameInitSettings creation_data, std::string password, const UserZoneInfo & zone_info)
{
  if (m_GameCreationThrottle.GrabCredits(m_Interface.GetNetworkTime(), 1) == false)
  {
    m_Interface.Call(&UserConnection::SendRuntimeError, endpoint_id, "You must wait 10 seconds before you can create another game");
    return;
  }

  if (creation_data.m_StageIndex >= g_LobbyLevelList.GetNumLevels())
  {
    m_Interface.Call(&UserConnection::SendRuntimeError, endpoint_id, "Error creating game");
    return;
  }

  if (password.length() >= 20)
  {
    m_Interface.Call(&UserConnection::SendRuntimeError, endpoint_id, "You password is too long. It must be less than 30 characters");
    return;
  }

  auto & level_info = g_LobbyLevelList.GetLevelInfo(creation_data.m_StageIndex);

#ifdef NET_USE_PLAYER_LIMIT
  auto max_players = GetMaxPlayers(level_info, creation_data);
  if (creation_data.m_PlayerCount < 2 || creation_data.m_PlayerCount > max_players)
  {
    m_Interface.Call(&UserConnection::SendRuntimeError, endpoint_id, "Invalid player limit");
    return;
  }
#endif

#ifdef NET_USE_SCORE_LIMIT
  if (creation_data.m_ScoreLimit < 0 || (creation_data.m_ScoreLimit > level_info.m_ScoreLimit && level_info.m_ScoreLimit != 0))
  {
    m_Interface.Call(&UserConnection::SendRuntimeError, endpoint_id, "Invalid score limit");
    return;
  }
#endif

#ifdef NET_USE_TIME_LIMIT
  if (creation_data.m_TimeLimit < 0 || (creation_data.m_TimeLimit > level_info.m_TimeLimit && level_info.m_TimeLimit != 0))
  {
    m_Interface.Call(&UserConnection::SendRuntimeError, endpoint_id, "Invalid time limit");
    return;
  }
#endif

  auto game_id = DDSGetRandomNumber64();

  m_Interface.Call(&Game::InitPrivateGame, game_id, creation_data, password);

  UserGameJoinInfo join_info;
  join_info.m_EndpointId = endpoint_id;
  join_info.m_Password = password;
  join_info.m_Observer = false;
  join_info.m_ZoneInfo = zone_info;
  join_info.m_IntendedType = LobbyGameType::kPrivate;

  JoinGame(game_id, join_info);
}

void User::JoinGame(DDSKey game_id, const UserGameJoinInfo & join_info)
{
  GameUserJoinInfo game_info;
  game_info.m_UserKey = m_Interface.GetLocalKey();
  game_info.m_EndpointId = join_info.m_EndpointId;
  game_info.m_Name = m_Data.m_UserName;

#ifdef ENABLE_SQUADS
  game_info.m_SquadTag = m_UserInfo.m_SquadTag;
#endif

  game_info.m_AdminLevel = m_UserInfo.m_AdminLevel;
  game_info.m_Icon = m_Data.m_Icon;
  game_info.m_Title = m_Data.m_Title;
  game_info.m_Celebration = m_Data.m_Celebration;

  game_info.m_Password = join_info.m_Password;
  game_info.m_Observer = join_info.m_Observer;
  game_info.m_ZoneInfo = join_info.m_ZoneInfo;
  game_info.m_IntendedType = join_info.m_IntendedType;

  m_Interface.CallWithResponder(&Game::AddUser, game_id, &User::HandleGameJoinResponse, this, game_info);
}

void User::JoinGameByLookupTable(uint32_t join_code, const UserGameJoinInfo & join_info)
{
  m_Interface.CallSharedWithResponder(&GameList::LookupJoinCode, &User::HandleJoinCodeLookup, this, join_code, join_info);
}

void User::SetInGame(DDSKey game_id, DDSKey game_random_id, DDSKey endpoint_id)
{
  LeaveGame();

  if (m_Endpoints.find(endpoint_id) == m_Endpoints.end())
  {
    m_Interface.Call(&Game::RemoveUser, game_id, m_Interface.GetLocalKey());
    return;
  }

  m_InGame = true;
  m_SentInitialGameData = false;

  m_GameId = game_id;
  m_GameEndpoint = endpoint_id;
  m_GameRandomId = game_random_id;

  UserGameInfo user_game_info;
  user_game_info.m_GameId = game_id;
  m_UserInfo.m_Game = user_game_info;

  m_GameSubscriptionId = m_Interface.CreateSubscription(
    DDSSubscriptionTarget<Game>{}, game_id, ".m_GameInfo", &User::HandleGameUpdate, true, std::make_tuple(game_id, game_random_id));
}

void User::DestroyGame(DDSKey endpoint_id, DDSKey game_id)
{
  if (m_LocalInfo.m_AdminLevel == 0)
  {
    return;
  }

  m_Interface.Call(&Game::Destroy, game_id);
}

void User::HandleGameJoinResponse(DDSKey game_id, DDSKey endpoint_id, DDSKey game_random_id, bool success)
{
  if (success == false)
  {
    m_Interface.Call(&UserConnection::SendRuntimeError, endpoint_id, std::string("Could not connect to game"));
  }
  else
  {
    SetInGame(game_id, game_random_id, endpoint_id);
  }
}

void User::HandleJoinCodeLookup(DDSKey game_id, const UserGameJoinInfo & join_info)
{
  if(game_id == 0)
  {
    m_Interface.Call(&UserConnection::SendRuntimeError, join_info.m_EndpointId, std::string("Invalid join code"));
  }
  else
  {
    JoinGame(game_id, join_info);
  }
}

void User::SendGameChat(DDSKey endpoint_id, std::string msg)
{
  if (m_InGame == false || m_GameEndpoint != endpoint_id)
  {
    return;
  }

  m_Interface.Call(&Game::SendChat, m_GameId, m_Interface.GetLocalKey(), m_GameEndpoint, msg);
}

void User::SwitchTeams(DDSKey target_user, int team, DDSKey endpoint_id)
{
  if (m_InGame == false || m_GameEndpoint != endpoint_id)
  {
    return;
  }

  if (m_GameThrottle.GrabCredits(m_Interface.GetNetworkTime(), 1) == false)
  {
    return;
  }

  m_Interface.Call(&Game::RequestTeamSwitch, m_GameId, m_Interface.GetLocalKey(), target_user, team);
}

void User::StartGame()
{
  if (m_InGame == false)
  {
    return;
  }

  m_Interface.Call(&Game::RequestStartGame, m_GameId, m_Interface.GetLocalKey());
}

void User::LeaveGame()
{
  if (m_InGame == false)
  {
    return;
  }

  m_Interface.Call(&Game::RemoveUser, m_GameId, m_Interface.GetLocalKey());
  m_Interface.DestroySubscription<Game>(m_GameId, m_GameSubscriptionId);

  SendToEndpoint(m_GameEndpoint, StormReflEncodeJson(UserMessageBase{"leave_game"}));

  m_InGame = false;
  m_GameId = 0;
  m_UserInfo.m_Game = UserGameInfo{};

#ifdef ENABLE_REWARDS
  SendXPGain(m_GameEndpoint);
  ApplyXPGain(true);
#endif
}

void User::ReconnectToGame(DDSKey endpoint_id)
{
  if (m_InGame == false)
  {
    return;
  }

  m_GameEndpoint = endpoint_id;
  m_Interface.Call(&Game::RequestReconnect, m_GameId, m_Interface.GetLocalKey(), endpoint_id);
}

void User::BanFromCompetitive()
{
  if(IsOnProbationFromCompetitive())
  {
    static const int kMaxBanDuration = 3000;
    static const int kMaxProbationDuration = 6000;

    m_Data.m_CompetitiveBanDuration = std::min((int)m_Data.m_CompetitiveBanDuration * 2, kMaxBanDuration);
    m_Data.m_CompetitiveBanProbation = std::min((int)m_Data.m_CompetitiveBanProbation * 2, kMaxProbationDuration);
  }
  else
  {
    static const int kDefaultBanDuration = 300;
    static const int kDefaultProbationDuration = 600;

    m_Data.m_CompetitiveBanStart = m_Interface.GetNetworkTime();
    m_Data.m_CompetitiveBanDuration = kDefaultBanDuration;
    m_Data.m_CompetitiveBanProbation = kDefaultProbationDuration;
  }
}

void User::NotifyLeftGame(DDSKey game_id, DDSKey game_random_id)
{

  if (m_InGame == false || m_GameId != game_id || m_GameRandomId != game_random_id)
  {
    return;
  }

  m_Interface.DestroySubscription<GameServerConnection>(m_GameId, m_GameSubscriptionId);

  m_InGame = false;
  m_GameId = 0;

  m_UserInfo.m_Game = UserGameInfo{};

#ifdef ENABLE_REWARDS
  SendXPGain(m_GameEndpoint);
  ApplyXPGain(true);
#endif
}

void User::NotifyLaunchGame(DDSKey game_id, DDSKey game_random_id, std::string server_ip, int server_port, DDSKey token)
{
  if (m_InGame == false || m_GameId != game_id || m_GameRandomId != game_random_id)
  {
    return;
  }

  UserLaunchGameMessage msg;
  msg.c = "launch_game";
  msg.server_ip = server_ip;
  msg.server_port = server_port;
  msg.token = token;
  SendToEndpoint(m_GameEndpoint, StormReflEncodeJson(msg));
}

void User::HandleGameChat(DDSKey game_id, DDSKey game_random_id, std::string name, int title, std::string msg)
{
  if (m_InGame == false || m_GameId != game_id || m_GameRandomId != game_random_id)
  {
    return;
  }

  UserChatMessageGame chat;
  chat.c = "game_chat";
  chat.user = name;
  chat.title = title;
  chat.msg = msg;
  SendToEndpoint(m_GameEndpoint, StormReflEncodeJson(chat));
}

void User::HandleGameUpdate(std::tuple<DDSKey, DDSKey> game_info, std::string data)
{
  if (m_InGame == false)
  {
    return;
  }

  auto game_id = std::get<0>(game_info);
  auto game_random_id = std::get<1>(game_info);

  if (game_random_id == m_GameRandomId)
  {
    UserGameInfoUpdate info;
    info.c = m_SentInitialGameData ? "game" : "join_game";
    info.data = data;
    info.game_id = game_id;

    m_Interface.Call(&UserConnection::SendData, m_GameEndpoint, StormReflEncodeJson(info));
    m_SentInitialGameData = true;
  }
}

#ifdef ENABLE_SQUADS
void User::CreateSquad(DDSKey creator_endpoint, std::string squad_name, std::string squad_tag)
{
  if(m_Data.m_IsGuest)
  {
    m_Interface.Call(&UserConnection::SendRuntimeError, creator_endpoint, "Guest users cannot create squads");
    return;
  }

  if (m_SquadCreationThrottle.HasCredits(m_Interface.GetNetworkTime(), 1) == false)
  {
    m_Interface.Call(&UserConnection::SendRuntimeError, creator_endpoint, "You must wait 30 seconds before you can create another squad");
    return;
  }

  if (m_CreatingSquad || m_Data.m_OwnerSquad != (DDSKey)0)
  {
    m_Interface.Call(&UserConnection::SendRuntimeError, creator_endpoint, "You can only create one squad");
    return;
  }

  if (User::ValidateUserName(squad_name, 3, 32, true) == false)
  {
    m_Interface.Call(&UserConnection::SendRuntimeError, creator_endpoint, "Invalid squad name");
    return;
  }

  if (User::ValidateUserName(squad_tag, 1, 8) == false)
  {
    m_Interface.Call(&UserConnection::SendRuntimeError, creator_endpoint, "Invalid squad tag");
    return;
  }

  m_CreatingSquad = true;

  auto channel_id = Channel::GetChannelKeyFromName(squad_tag.c_str());

  m_Interface.CallWithResponderReturnArgErrorBack(&BuiltInChannel::GetChannelName, channel_id,
    &User::HandleSquadCreateNameLookupFail, &User::HandleSquadCreateNameLookupSuccess, this,
    std::make_tuple(creator_endpoint, squad_name, squad_tag));
}

void User::DestroySquad(DDSKey destroyer_endpoint)
{
  if (m_Data.m_OwnerSquad == (DDSKey)0)
  {
    m_Interface.Call(&UserConnection::SendNotification, destroyer_endpoint, "You have not created a squad");
    return;
  }

  m_Interface.Call(&Squad::DestroySquad, m_Data.m_OwnerSquad);
  m_Data.m_OwnerSquad = 0;
  m_LocalInfo.m_OwnerSquad = 0;

  m_Interface.Call(&UserConnection::SendNotification, destroyer_endpoint, "Successfully disbanded squad");
}

void User::HandleSquadCreateNameLookupFail(std::tuple<DDSKey, std::string, std::string> squad_data, std::string channel_name)
{
  m_Interface.Call(&UserConnection::SendRuntimeError, std::get<0>(squad_data), std::string("Squad name conflicts with the built in channel ") + channel_name);
  m_CreatingSquad = false;
}

void User::HandleSquadCreateNameLookupSuccess(std::tuple<DDSKey, std::string, std::string> squad_data)
{
  auto creator_endpoint = std::get<0>(squad_data);
  auto squad_name = std::get<1>(squad_data);
  auto squad_tag = std::get<2>(squad_data);

  auto squad_key = Channel::GetChannelKeyFromName(squad_tag.data());

  SquadDatabaseObject squad_info;
  squad_info.m_SquadNameLower = squad_name;
  squad_info.m_SquadTagLower = squad_tag;
  squad_info.m_Creator = m_Interface.GetLocalKey();
  squad_info.m_DatabaseInfo.m_Name = squad_name;
  squad_info.m_DatabaseInfo.m_Tag = squad_tag;
  squad_info.m_DatabaseInfo.m_Motd = std::string("The ") + squad_name + " Channel";
  squad_info.m_DatabaseInfo.m_Locked = false;
  std::transform(squad_info.m_SquadNameLower.begin(), squad_info.m_SquadNameLower.end(), squad_info.m_SquadNameLower.begin(), tolower);
  std::transform(squad_info.m_SquadTagLower.begin(), squad_info.m_SquadTagLower.end(), squad_info.m_SquadTagLower.begin(), tolower);

  SquadDatabaseMemberInfo creator_info;
  creator_info.m_MembershipFlags = kSquadCreator;
  creator_info.m_UserKey = m_Interface.GetLocalKey();
  creator_info.m_Joined = (int)time(nullptr);
  squad_info.m_DatabaseInfo.m_Users.EmplaceBack(creator_info);

  m_Interface.InsertIntoDatabase(squad_info, squad_key, &User::HandleSquadCreate, this, std::make_tuple(squad_name, squad_tag, squad_key, creator_endpoint));

  JoinChannel(0, squad_tag);
}

void User::HandleSquadCreate(std::tuple<std::string, std::string, DDSKey, DDSKey> squad_info, int ec)
{
  m_CreatingSquad = false;

  auto endpoint = std::get<3>(squad_info);
  auto squad_id = std::get<2>(squad_info);

  if (ec)
  {
    m_Interface.Call(&UserConnection::SendRuntimeError, endpoint, "Either the squad name or tag is already taken");
  }
  else
  {
    m_Data.m_OwnerSquad = squad_id;
    m_Data.m_Squads.EmplaceBack(squad_id);

    m_LocalInfo.m_OwnerSquad = squad_id;

    LoadSquadInternal(squad_id);
    SetPrimarySquad(0, squad_id);

    m_Interface.Call(&UserConnection::SendNotification, endpoint, "Squad created successfully");

    m_SquadCreationThrottle.SubCredits(1);
  }
}

void User::HandleSquadOperationResponse(DDSKey endpoint_id, std::string response)
{
  m_Interface.Call(&UserConnection::SendNotification, endpoint_id, response);
}

void User::HandleSquadLookupFail(DDSKey endpoint_id)
{
  m_Interface.Call(&UserConnection::SendNotification, endpoint_id, "That squad does not exist");
}

void User::ApplyToSquad(DDSKey endpoint_id, std::string squad_name)
{
  if(m_Data.m_IsGuest)
  {
    m_Interface.Call(&UserConnection::SendNotification, endpoint_id, "Guest users cannot apply to squads");
    return;
  }

  auto squad_id = Channel::GetChannelKeyFromName(squad_name.c_str());
  m_Interface.CallWithResponderReturnArgErrorBack(&Squad::ApplyToSquad, squad_id, &User::HandleSquadOperationResponse, &User::HandleSquadLookupFail, this, endpoint_id,
    m_Interface.GetLocalKey(), m_UserInfo.m_Name.ToString());
}

void User::AcceptSquadApplication(DDSKey endpoint_id, DDSKey squad_id, DDSKey user_id)
{
  m_Interface.CallWithResponderReturnArgErrorBack(&Squad::AcceptApplicationToSquad, squad_id,
    &User::HandleSquadOperationResponse, &User::HandleSquadLookupFail, this, endpoint_id, m_Interface.GetLocalKey(), user_id);
}

void User::RescindSquadApplication(DDSKey endpoint_id, DDSKey squad_id)
{
  m_Interface.CallWithResponderReturnArgErrorBack(&Squad::RescindApplicationToSquad, squad_id, 
    &User::HandleSquadOperationResponse, &User::HandleSquadLookupFail, this, endpoint_id, m_Interface.GetLocalKey());
}

void User::DeclineSquadApplication(DDSKey endpoint_id, DDSKey squad_id, DDSKey user_id)
{
  m_Interface.CallWithResponderReturnArgErrorBack(&Squad::DeclineApplicationToSquad, squad_id,
    &User::HandleSquadOperationResponse, &User::HandleSquadLookupFail, this, endpoint_id, m_Interface.GetLocalKey(), user_id);
}

void User::RequestUserToJoinSquad(DDSKey endpoint_id, DDSKey squad_id, DDSKey platform_id)
{
  m_Interface.QueryDatabase(UserPlatformIdLookup{ platform_id }, &User::HandleSquadRequestUserLookup, this, std::make_tuple(endpoint_id, squad_id));
}

void User::HandleSquadRequestUserLookup(std::tuple<DDSKey, DDSKey> squad_data, int ec, std::string data)
{
  auto endpoint_id = std::get<0>(squad_data);
  auto squad_id = std::get<1>(squad_data);

  if (ec != 0)
  {
    m_Interface.Call(&UserConnection::SendNotification, endpoint_id, "That user does not exist");
  }
  else
  {
    UserDatabaseObject user_data;
    StormReflParseJson(user_data, data.data());

    if(user_data.m_IsGuest)
    {
      m_Interface.Call(&UserConnection::SendNotification, endpoint_id, "You can't invite guest users to squads");
    }
    else
    {
      auto user_id = GetUserIdForPlatformId(user_data.m_Platform, user_data.m_PlatformId);
      m_Interface.CallWithResponderReturnArg(&Squad::RequestUserToJoinSquad, squad_id, &User::HandleSquadOperationResponse, this, endpoint_id,
        m_Interface.GetLocalKey(), user_id, user_data.m_UserName.ToString());
    }
  }
}

void User::AcceptSquadRequest(DDSKey endpoint_id, DDSKey squad_id)
{
  m_Interface.CallWithResponderReturnArgErrorBack(&Squad::AcceptRequestToJoinSquad, squad_id,
    &User::HandleSquadOperationResponse, &User::HandleSquadLookupFail, this, endpoint_id, m_Interface.GetLocalKey());
}

void User::RescindSquadRequest(DDSKey endpoint_id, DDSKey squad_id, DDSKey user_id)
{
  m_Interface.CallWithResponderReturnArgErrorBack(&Squad::RescindRequestToJoinSquad, squad_id,
    &User::HandleSquadOperationResponse, &User::HandleSquadLookupFail, this, endpoint_id, m_Interface.GetLocalKey(), user_id);
}

void User::DeclineSquadRequest(DDSKey endpoint_id, DDSKey squad_id)
{
  m_Interface.CallWithResponderReturnArgErrorBack(&Squad::DeclineRequestToJoinSquad, squad_id,
    &User::HandleSquadOperationResponse, &User::HandleSquadLookupFail, this, endpoint_id, m_Interface.GetLocalKey());
}

void User::LeaveSquad(DDSKey endpoint_id, DDSKey squad_id)
{
  m_Interface.CallWithResponderReturnArgErrorBack(&Squad::LeaveSquad, squad_id,
    &User::HandleSquadOperationResponse, &User::HandleSquadLookupFail, this, endpoint_id, m_Interface.GetLocalKey());
}

void User::RemoveSquadMember(DDSKey endpoint_id, DDSKey squad_id, DDSKey user_id)
{
  m_Interface.CallWithResponderReturnArgErrorBack(&Squad::RemoveMember, squad_id,
    &User::HandleSquadOperationResponse, &User::HandleSquadLookupFail, this, endpoint_id, m_Interface.GetLocalKey(), user_id);
}

void User::EditSquadPermissions(DDSKey endpoint_id, DDSKey squad_id, DDSKey user_id, int permissions)
{
  m_Interface.CallWithResponderReturnArgErrorBack(&Squad::SetMemberPermissions, squad_id,
    &User::HandleSquadOperationResponse, &User::HandleSquadLookupFail, this, endpoint_id, m_Interface.GetLocalKey(), user_id, permissions);
}

void User::EditSquadMotd(DDSKey endpoint_id, DDSKey squad_id, std::string motd)
{
  m_Interface.CallWithResponderReturnArgErrorBack(&Squad::SetMotd, squad_id,
    &User::HandleSquadOperationResponse, &User::HandleSquadLookupFail, this, endpoint_id, m_Interface.GetLocalKey(), motd);
}

void User::LockSquadChannel(DDSKey endpoint_id, DDSKey squad_id, bool locked)
{
  m_Interface.CallWithResponderReturnArgErrorBack(&Squad::SetChannelLock, squad_id,
    &User::HandleSquadOperationResponse, &User::HandleSquadLookupFail, this, endpoint_id, m_Interface.GetLocalKey(), locked);
}

void User::SetPrimarySquad(DDSKey endpoint_id, DDSKey squad_id)
{
  if (endpoint_id != 0)
  {
    if (m_ProfileThrottle.GrabCredits(m_Interface.GetNetworkTime(), 1) == false)
    {
      return;
    }
  }

  if (squad_id == 0)
  {
    m_Data.m_PrimarySquad = squad_id;
    m_LocalInfo.m_PrimarySquad = squad_id;

    m_UserInfo.m_Squad = "";
    m_UserInfo.m_SquadTag = "";
    return;
  }

  auto squad_info = m_LocalInfo.m_Squads.TryGet(squad_id);
  if (squad_info == nullptr)
  {
    if (vfind(m_PendingSquadLoads, squad_id) == false)
    {
      return;
    }

    m_PendingPrimarySquad = squad_id;
    m_PendingPrimarySquadSettingEndpoint = endpoint_id;
    return;
  }

  bool found_member = true;
  for (auto member : squad_info->m_Users)
  {
    if (member.second.m_UserKey == m_Interface.GetLocalKey())
    {
      if (member.second.m_MembershipFlags <= kSquadHonoraryMember)
      {
        if (endpoint_id != 0)
        {
          m_Interface.Call(&UserConnection::SendNotification, endpoint_id,
            "You cannot use this squad tag when you are only an honorary member");
        }
        return;
      }

      found_member = true;
      break;
    }
  }

  if (found_member == false)
  {
    if (endpoint_id != 0)
    {
      m_Interface.Call(&UserConnection::SendNotification, endpoint_id, "You are not in this squad");
      return;
    }
  }

  m_Data.m_PrimarySquad = squad_id;
  m_LocalInfo.m_PrimarySquad = squad_id;

  if (squad_info)
  {
    m_UserInfo.m_Squad = squad_info->m_Name;
    m_UserInfo.m_SquadTag = squad_info->m_Tag;
  }
}

void User::AddSquadInternal(DDSKey squad_id)
{
  m_Data.m_Squads.EmplaceBack(squad_id);

  LoadSquadInternal(squad_id);

  if (m_Data.m_PrimarySquad == (DDSKey)0)
  {
    SetPrimarySquad(0, squad_id);
  }
}

void User::LoadSquadInternal(DDSKey squad_id)
{
  auto subscription_id = 
    m_Interface.CreateSubscription(DDSSubscriptionTarget<Squad>{}, squad_id, ".m_SquadInfo", 
      &User::HandleSquadUpdate, true, squad_id, &User::HandleSquadDeleted);

  m_SquadSubscriptionIds.emplace(std::make_pair(squad_id, subscription_id));
  m_PendingSquadLoads.push_back(squad_id);
}

void User::RemoveSquadInternal(DDSKey squad_id)
{
  bool found_squad = false;
  for (auto squad : m_Data.m_Squads)
  {
    if (squad.second == squad_id)
    {
      found_squad = true;
      m_Data.m_Squads.RemoveAt(squad.first);
    }
  }

  if (found_squad == false)
  {
    return;
  }

  auto sub_id = m_SquadSubscriptionIds.find(squad_id);
  if (sub_id != m_SquadSubscriptionIds.end())
  {
    m_Interface.DestroySubscription<Squad>(squad_id, sub_id->second);
    m_SquadSubscriptionIds.erase(sub_id);
  }

  if (squad_id == m_Data.m_OwnerSquad)
  {
    m_Data.m_OwnerSquad = 0;
    m_LocalInfo.m_OwnerSquad = 0;
  }

  if (m_LocalInfo.m_PrimarySquad == squad_id)
  {
    m_LocalInfo.m_PrimarySquad = 0;
    m_UserInfo.m_Squad = "";
    m_UserInfo.m_SquadTag = "";
  }

  m_LocalInfo.m_Squads.Remove(squad_id);

  for (auto itr = m_PendingSquadLoads.begin(), end = m_PendingSquadLoads.end(); itr != end; ++itr)
  {
    if (*itr == squad_id)
    {
      m_PendingSquadLoads.erase(itr);
      CheckCompleteLoad();
      break;
    }
  }
}

void User::AddApplicationInternal(DDSKey squad_id, std::string squad_name, std::string squad_tag)
{
  for (auto app : m_Data.m_Applications)
  {
    if (app.second == squad_id)
    {
      return;
    }
  }

  m_Data.m_Applications.EmplaceBack(squad_id);

  UserApplication app;
  app.m_SquadId = squad_id;
  app.m_SquadName = squad_name;
  app.m_SquadTag = squad_tag;
  m_LocalInfo.m_Applications.EmplaceBack(app);
}

void User::AddSquadRequestInternal(DDSKey squad_id, std::string squad_name, std::string squad_tag)
{
  for (auto app : m_Data.m_Requests)
  {
    if (app.second == squad_id)
    {
      return;
    }
  }

  m_Data.m_Requests.EmplaceBack(squad_id);

  UserApplication app;
  app.m_SquadId = squad_id;
  app.m_SquadName = squad_name;
  app.m_SquadTag = squad_tag;
  m_LocalInfo.m_Requests.EmplaceBack(app);
}

void User::LoadApplicationInternal(int index, DDSKey squad_id)
{
  m_PendingApplicationLoads.emplace_back(squad_id);
  m_Interface.CallWithResponderReturnArgErrorBack(&Squad::GetSquadName, squad_id, 
    &User::HandleSquadApplicationLoad, &User::HandleSquadApplicationLoadFailure, this, std::make_pair(index, squad_id));
}

void User::LoadSquadRequestInternal(int index, DDSKey squad_id)
{
  m_PendingRequestLoads.emplace_back(squad_id);
  m_Interface.CallWithResponderReturnArgErrorBack(&Squad::GetSquadName, squad_id, 
    &User::HandleSquadRequestLoad, &User::HandleSquadRequestLoadFailure, this, std::make_pair(index, squad_id));
}

void User::CancelApplicationInternal(DDSKey squad_id)
{
  for (auto app : m_LocalInfo.m_Applications)
  {
    if (app.second.m_SquadId == squad_id)
    {
      m_LocalInfo.m_Applications.RemoveAt(app.first);
      break;
    }
  }

  for (auto app : m_Data.m_Applications)
  {
    if (app.second == squad_id)
    {
      m_Data.m_Applications.RemoveAt(app.first);
      break;
    }
  }

  if (vremove_quick(m_PendingApplicationLoads, squad_id))
  {
    CheckCompleteLoad();
  }
}

void User::CancelSquadRequestInternal(DDSKey squad_id)
{
  for (auto app : m_LocalInfo.m_Requests)
  {
    if (app.second.m_SquadId == squad_id)
    {
      m_LocalInfo.m_Requests.RemoveAt(app.first);
      break;
    }
  }

  for (auto app : m_Data.m_Requests)
  {
    if (app.second == squad_id)
    {
      m_Data.m_Requests.RemoveAt(app.first);
      break;
    }
  }

  if (vremove_quick(m_PendingRequestLoads, squad_id))
  {
    CheckCompleteLoad();
  }
}

void User::HandleSquadUpdate(DDSKey squad_id, std::string data)
{
  auto squad_info = m_LocalInfo.m_Squads.TryGet(squad_id);
  if (squad_info == nullptr)
  {
    if (vremove_quick(m_PendingSquadLoads, squad_id) == false)
    {
      return;
    }

    SquadInfo new_squad_info;
    StormDataApplyChangePacket(new_squad_info, data.data());

    auto & new_squad_ref = m_LocalInfo.m_Squads.Emplace(squad_id, std::move(new_squad_info));
    squad_info = &new_squad_ref;
  }
  else
  {
    StormDataApplyChangePacket(*squad_info, data.data());
  }

  if (squad_id == m_PendingPrimarySquad)
  {
    SetPrimarySquad(m_PendingPrimarySquadSettingEndpoint, squad_id);
    m_PendingPrimarySquad = 0;
  }

  CheckCompleteLoad();

  if (squad_id == m_LocalInfo.m_PrimarySquad)
  {
    for (auto member : squad_info->m_Users)
    {
      if (member.second.m_UserKey == m_Interface.GetLocalKey())
      {
        if (member.second.m_MembershipFlags <= kSquadHonoraryMember)
        {
          SetPrimarySquad(0, 0);
          return;
        }
      }
    }

    m_UserInfo.m_Squad.SetIfDifferent(squad_info->m_Name);
    m_UserInfo.m_SquadTag.SetIfDifferent(squad_info->m_Tag);
  }
}

void User::HandleSquadDeleted(DDSKey squad_id)
{
  auto squad_info = m_LocalInfo.m_Squads.TryGet(squad_id);
  if (squad_info == nullptr)
  {
    if (vremove_quick(m_PendingSquadLoads, squad_id) == false)
    {
      return;
    }

    CheckCompleteLoad();
  }
}

void User::HandleSquadApplicationLoad(std::pair<int, DDSKey> squad_info, std::string name, std::string tag)
{
  UserApplication new_application;
  new_application.m_SquadId = squad_info.second;
  new_application.m_SquadName = name;
  new_application.m_SquadTag = tag;

  m_LocalInfo.m_Applications.EmplaceAt(squad_info.first, new_application);

  if (m_PendingApplicationLoads.size() > 0)
  {
    vremove_quick(m_PendingApplicationLoads, squad_info.second);
    CheckCompleteLoad();
  };
}

void User::HandleSquadApplicationLoadFailure(std::pair<int, DDSKey> squad_info)
{
  if (m_PendingApplicationLoads.size() > 0)
  {
    vremove_quick(m_PendingApplicationLoads, squad_info.second);
    CheckCompleteLoad();
  }
}

void User::HandleSquadRequestLoad(std::pair<int, DDSKey> squad_info, std::string name, std::string tag)
{
  UserApplication new_application;
  new_application.m_SquadId = squad_info.second;
  new_application.m_SquadName = name;
  new_application.m_SquadTag = tag;

  m_LocalInfo.m_Requests.EmplaceAt(squad_info.first, new_application);

  if (m_PendingRequestLoads.size() > 0)
  {
    vremove_quick(m_PendingRequestLoads, squad_info.second);
    CheckCompleteLoad();
  }
}

void User::HandleSquadRequestLoadFailure(std::pair<int, DDSKey> squad_info)
{
  if (m_PendingRequestLoads.size() > 0)
  {
    vremove_quick(m_PendingRequestLoads, squad_info.second);
    CheckCompleteLoad();
  }
}
#endif

void User::AddTitle(DDSResponder & responder, int title, bool quiet)
{
  for (auto user_title : m_LocalInfo.m_TitleList)
  {
    if (user_title.second == title)
    {
      DDSResponderCall(responder, "That user already has that title");
      return;
    }
  }

  if (quiet == false)
  {
    SendNotification("You have acquired a new title!");
  }

  m_LocalInfo.m_TitleList.EmplaceBack(title);
  m_Data.m_TitleList.EmplaceBack(title);
  DDSResponderCall(responder, "Title added successfully");
}

void User::SetTitle(int title)
{
  if (m_ProfileThrottle.GrabCredits(m_Interface.GetNetworkTime(), 1) == false)
  {
    return;
  }

  for(auto elem : m_LocalInfo.m_TitleList)
  {
    if(elem.second == title)
    {
      m_LocalInfo.m_Title = title;
      m_Data.m_Title = title;
    }
  }
}

void User::RemoveTitle(DDSResponder & responder, int title)
{
  for (auto user_title : m_LocalInfo.m_TitleList)
  {
    if (user_title.second == title)
    {
      if (m_LocalInfo.m_Title == (int)user_title.first)
      {
        SetTitle(-1);
      }

      m_LocalInfo.m_TitleList.RemoveAt(user_title.first);
      m_Data.m_TitleList.RemoveAt(user_title.first);

      DDSResponderCall(responder, "Title successfully removed");
      return;
    }
  }

  DDSResponderCall(responder, "Title not found");
}

void User::AddIcon(DDSResponder & responder, int icon, bool set, bool quiet)
{
  for (auto user_icon : m_LocalInfo.m_IconList)
  {
    if (user_icon.second == icon)
    {
      DDSResponderCall(responder, "That user already has the icon");
      return;
    }
  }

  if (quiet == false)
  {
    SendNotification("You have acquired a new icon!");
  }

  m_LocalInfo.m_IconList.EmplaceBack(icon);
  m_Data.m_IconList.EmplaceBack(icon);

  DDSResponderCall(responder, "Icon added successfully");

  if (set)
  {
    SetIcon(m_Data.m_IconList[m_Data.m_IconList.HighestIndex()]);
  }
}

void User::SetIcon(int icon)
{
  if (m_ProfileThrottle.GrabCredits(m_Interface.GetNetworkTime(), 1) == false)
  {
    return;
  }

  if (icon == -1)
  {
    m_UserInfo.m_Icon = -1;
    m_LocalInfo.m_Icon = -1;
    m_Data.m_Icon = -1;
    return;
  }

  for (auto user_icon : m_LocalInfo.m_IconList)
  {
    if (user_icon.second == icon)
    {
      m_LocalInfo.m_Icon = icon;
      m_Data.m_Icon = icon;
      m_UserInfo.m_Icon = icon;
      return;
    }
  }
}

void User::RemoveIcon(DDSResponder & responder, int icon)
{
  for (auto user_icon : m_LocalInfo.m_IconList)
  {
    if (user_icon.second == icon)
    {
      if (m_LocalInfo.m_Icon == (int)user_icon.first)
      {
        SetIcon(-1);
      }

      m_LocalInfo.m_IconList.RemoveAt(user_icon.first);
      m_Data.m_IconList.RemoveAt(user_icon.first);

      DDSResponderCall(responder, "Icon successfully removed");
      return;
    }
  }

  DDSResponderCall(responder, "Icon not found");
}

void User::AddCelebration(DDSResponder & responder, int celebration, bool set, bool quiet)
{
  for (auto user_celeb : m_LocalInfo.m_CelebrationList)
  {
    if (user_celeb.second == celebration)
    {
      DDSResponderCall(responder, "That user already has the celebration");
      return;
    }
  }

  if (quiet == false)
  {
    SendNotification("You have acquired a new celebration!");
  }

  m_Data.m_CelebrationList.EmplaceBack(celebration);
  m_LocalInfo.m_CelebrationList.EmplaceBack(celebration);

  DDSResponderCall(responder, "Celebration added successfully");

  if (set)
  {
    SetCelebration(m_Data.m_CelebrationList[m_Data.m_CelebrationList.HighestIndex()]);
  }
}

void User::SetCelebration(int celebration)
{
  if (m_ProfileThrottle.GrabCredits(m_Interface.GetNetworkTime(), 1) == false)
  {
    return;
  }

  if (celebration == -1)
  {
    m_LocalInfo.m_Celebration = -1;
    m_Data.m_Celebration = -1;
    return;
  }

  for (auto user_celeb : m_LocalInfo.m_CelebrationList)
  {
    if (user_celeb.second == celebration)
    {
      m_LocalInfo.m_Celebration = celebration;
      m_Data.m_Celebration = celebration;
      return;
    }
  }
}

void User::RemoveCelebration(DDSResponder & responder, int celebration)
{
  for (auto user_celeb : m_LocalInfo.m_CelebrationList)
  {
    if (user_celeb.second == celebration)
    {
      if (m_LocalInfo.m_Celebration == (int)user_celeb.first)
      {
        SetCelebration(-1);
      }

      m_LocalInfo.m_CelebrationList.RemoveAt(user_celeb.first);
      m_Data.m_CelebrationList.RemoveAt(user_celeb.first);

      DDSResponderCall(responder, "Celebration successfully removed");
      return;
    }
  }

  DDSResponderCall(responder, "Celebration not found");
}

void User::UpdateStats(GameStatsData stats, GameInitSettings instance_data)
{
  StormReflAggregate(m_Data.m_Stats, stats);
  m_Data.m_LastGamePlayed = (int)time(nullptr);

#ifdef ENABLE_REWARDS
  UserXPGain xp_log;

  xp_log.m_GamesPlayedCount = stats.m_GamesPlayed;
  xp_log.m_GamesWonCount = stats.m_GamesWon;
  xp_log.m_Gifted = 0;

  if (instance_data.m_TimeLimit > instance_data.m_ScoreLimit)
  {
    xp_log.m_GamesPlayed = stats.m_GamesPlayed * 20 * instance_data.m_TimeLimit;
    xp_log.m_GamesWon = stats.m_GamesWon * 100 * instance_data.m_TimeLimit;
  }
  else
  {
    xp_log.m_GamesPlayed = stats.m_GamesPlayed * 20 * instance_data.m_ScoreLimit;
    xp_log.m_GamesWon = stats.m_GamesWon * 100 * instance_data.m_ScoreLimit;
  }

  xp_log.m_XP = xp_log.m_GamesPlayed + xp_log.m_GamesWon;
  if (m_Data.m_XPLog.HighestIndex() == -1)
  {
    m_Data.m_XPLog.EmplaceBack(xp_log);
  }
  else
  {
    auto & elem = m_Data.m_XPLog.begin()->second;
    StormReflAggregate(elem, xp_log);
  }

  if (m_InGame == false)
  {
    for (auto ep : m_Endpoints)
    {
      SendXPGain(ep.first);
    }

    ApplyXPGain(true);
  }
#endif
}

void User::FetchStats(DDSResponder & responder)
{
  UserStatsData stats;
  stats.c = "user_stats";
  stats.name = m_UserInfo.m_Name.ToString();
  stats.last_game_played = m_Data.m_LastGamePlayed;
  stats.stats = m_Data.m_Stats;

#ifdef ENABLE_REWARDS
  stats.rank = m_Data.m_Level;
  stats.xp = m_Data.m_XP;
#endif

  DDSResponderCall(responder, StormReflEncodeJson(stats));
}

#ifdef ENABLE_CHANNELS
void User::AddAutoJoinChannel(DDSResponder & responder, const std::string & channel_name)
{
  if (User::ValidateUserName(channel_name, 1, 16) == false)
  {
    DDSResponderCall(responder, "Invalid channel name");
    return;
  }

  if (m_LocalInfo.m_AutoJoinChannels.NumElements() >= 28)
  {
    DDSResponderCall(responder, "You have hit the limit on auto joins");
    return;
  }

  for (auto channel : m_LocalInfo.m_AutoJoinChannels)
  {
    if (channel.second.BasicCaseInsensitiveCompare(channel_name))
    {
      DDSResponderCall(responder, "That channel is already in the list of auto-joins");
      return;
    }
  }

  m_LocalInfo.m_AutoJoinChannels.EmplaceBack(channel_name);
  m_Data.m_AutoJoinChannels.EmplaceBack(channel_name);

  DDSResponderCall(responder, "Successfully added the channel to your list of auto-joins");
  JoinChannel(0, channel_name);
}

void User::RemoveAutoJoinChannel(DDSResponder & responder, const std::string & channel_name)
{
  for (auto channel : m_LocalInfo.m_AutoJoinChannels)
  {
    if (channel.second.BasicCaseInsensitiveCompare(channel_name))
    {
      m_LocalInfo.m_AutoJoinChannels.RemoveAt(channel.first);
      m_Data.m_AutoJoinChannels.RemoveAt(channel.first);

      DDSResponderCall(responder, "Successfully removed the channel to your list of auto-joins");
      return;
    }
  }
}

#endif

void User::ModifyPersistent(const std::string & change_packet)
{
  StormDataApplyChangePacket(m_Data.m_Persistent, change_packet.c_str());
  StormDataApplyChangePacket(m_LocalInfo.m_Persistent, change_packet.c_str());
}

#ifdef ENABLE_REWARDS
void User::GiveXP(DDSResponder & responder, int amount)
{
  UserXPGain xp_log = {};

  xp_log.m_Gifted = amount;
  xp_log.m_XP = amount;

  if (m_Data.m_XPLog.HighestIndex() == -1)
  {
    m_Data.m_XPLog.EmplaceBack(xp_log);
  }
  else
  {
    auto & elem = m_Data.m_XPLog.begin()->second;
    StormReflAggregate(elem, xp_log);
  }

  if (m_InGame == false)
  {
    for (auto ep : m_Endpoints)
    {
      SendXPGain(ep.first);
    }

    ApplyXPGain(true);
  }

  DDSResponderCall(responder, "Successfully gave user xp");
}

void User::SendXPGain(DDSKey endpoint_id)
{
  if (m_Data.m_XPLog.HighestIndex() == -1)
  {
    return;
  }

  auto itr = m_Data.m_XPLog.begin();
  auto & gain = itr->second;
  UserGotXP xp_msg;
  xp_msg.c = "xp";
  xp_msg.xp = m_Data.m_XP;
  xp_msg.level = m_Data.m_Level;
  xp_msg.xp_info = gain;

  ++itr;
  xp_msg.last = (itr == m_Data.m_XPLog.end());

  if (xp_msg.xp_info.m_XP > 0)
  {
    m_Interface.Call(&UserConnection::SendData, endpoint_id, StormReflEncodeJson(xp_msg));
  }
}

void User::ApplyXPGain(bool quiet)
{
  if (m_Data.m_XPLog.HighestIndex() == -1)
  {
    return;
  }

  auto itr = m_Data.m_XPLog.begin();
  auto & gain = itr->second;

  auto rewards = m_Interface.GetSharedObject<Rewards>();

  int xp = m_Data.m_XP;
  int level = m_Data.m_Level;
  std::vector<UserRewards> reward_list;

  auto responder = CreateEmptyResponder(m_Interface);

  rewards->UpdateRewards(gain.m_XP, xp, level, reward_list);
  for (auto & reward : reward_list)
  {
    for (auto & icon : reward.m_Icons)
    {
      AddIcon(responder, icon, false, quiet);
    }

    for (auto & title : reward.m_Titles)
    {
      AddTitle(responder, title, quiet);
    }

    for (auto & celeb : reward.m_Celebrations)
    {
      AddCelebration(responder, celeb, false, true);
    }
  }

  m_Data.m_XP = xp;
  m_Data.m_Level = level;

  m_Data.m_XPLog.Remove(itr);
}

void User::SkipXPGain()
{
  while (m_Data.m_XPLog.HighestIndex() != -1)
  {
    ApplyXPGain(false);
  }
}
#endif

void User::ProcessSlashCommand(DDSKey endpoint_id, DDSKey channel_id, std::string msg)
{
  std::string cmd;
  const char * ptr = msg.data();

  while (*ptr != 0)
  {
    if (*ptr == ' ')
    {
      ptr++;
      break;
    }

    cmd += *ptr;
    ptr++;
  }

  DDSResponder user_lookup_responder = 
    m_Interface.CreateResponder(&User::HandleCommandResponderMessage, &User::HandleCommandUserLookupFail, this, endpoint_id);

  if (m_LocalInfo.m_AdminLevel > 0)
  {
    if (cmd == "/meminfo")
    {
      m_Interface.Call(&UserConnection::SendServerText, endpoint_id, m_Interface.GetNodeMemoryReport());
      return;
    }

    if (cmd == "/getinfo")
    {
      std::string user_name;

      if (ParseArgumentDefault(ptr, user_name))
      {
        CallUser(user_name.c_str(), &User::GetInfo, user_lookup_responder);
      }
      else
      {
        m_Interface.CallWithResponderReturnArg(&User::GetInfo, m_Interface.GetLocalKey(), &User::HandleCommandResponderMessage, this, endpoint_id);
      }
      return;
    }

#ifdef ENABLE_SQUADS
    if (cmd == "/squadinfo")
    {
      std::string squad_name;

      if (ParseArgumentDefault(ptr, squad_name))
      {
        auto squad_id = Channel::GetChannelKeyFromName(squad_name.c_str());
        m_Interface.CallWithResponderReturnArgErrorBack(&Squad::GetInfo, squad_id, 
          &User::HandleCommandResponderMessage, &User::HandleCommandSquadLookupFail, this, endpoint_id);
      }
      else
      {
        if (m_LocalInfo.m_OwnerSquad != (DDSKey)0)
        {
          m_Interface.CallWithResponderReturnArg(&Squad::GetInfo, m_LocalInfo.m_OwnerSquad, &User::HandleCommandResponderMessage, this, endpoint_id);
        }
        else if(m_LocalInfo.m_Squads.Size() != 0)
        {
          m_Interface.CallWithResponderReturnArg(&Squad::GetInfo, m_LocalInfo.m_Squads.begin()->first, &User::HandleCommandResponderMessage, this, endpoint_id);
        }
        else
        {
          User::HandleCommandResponderMessage(endpoint_id, "You are not in any squads");
        }
      }
      return;
    }

    if (cmd == "/killsquad")
    {
      std::string squad_name;

      if (ParseArgumentDefault(ptr, squad_name))
      {
        auto squad_id = Channel::GetChannelKeyFromName(squad_name.c_str());
        m_Interface.CallWithResponderReturnArgErrorBack(&Squad::KillSquad, squad_id,
          &User::HandleCommandResponderMessage, &User::HandleCommandSquadLookupFail, this, endpoint_id);
      }
      else
      {
        User::HandleCommandResponderMessage(endpoint_id, "Usage: /killsquad <squad>");
      }
      return;
    }
#endif

#ifdef ENABLE_CHANNELS
    if (cmd == "/channelinfo")
    {
      std::string channel_name;

      if (ParseArgumentDefault(ptr, channel_name))
      {
        channel_id = Channel::GetChannelKeyFromName(channel_name.c_str());
      }

      m_Interface.CallWithResponderReturnArgErrorBack(&Channel::GetInfo, channel_id,
        &User::HandleCommandResponderMessage, &User::HandleCommandSquadLookupFail, this, endpoint_id);
      return;
    }

    if (cmd == "/getchantext")
    {
      FetchChannelTextForEdit(endpoint_id, channel_id);
      return;
    }
#endif

#ifdef ENABLE_WELCOME_INFO
    if (cmd == "/lobbyinfo")
    {
      FetchWelcomeInfoForEdit(endpoint_id);
      return;
    }
#endif
    if (cmd == "/setadmin")
    {
      if (m_Data.m_AdminLevel == 9)
      {
        std::string user_name;
        std::string admin_level;

        if (ParseArgumentRemainder(ptr, user_name, admin_level))
        {
          CallUser(user_name.c_str(), &User::MakeAdmin, user_lookup_responder, atoi(admin_level.c_str()));
        }
        else
        {
          User::HandleCommandResponderMessage(endpoint_id, "Usage: /setadmin <user> <admin_level>");
        }

        return;
      }
    }

#ifdef ENABLE_REWARDS
    if (cmd == "/givexp")
    {
      if (m_Data.m_AdminLevel == 9)
      {
        std::string user_name;
        std::string xp;

        if (ParseArgumentRemainder(ptr, user_name, xp))
        {
          CallUser(user_name.c_str(), &User::GiveXP, user_lookup_responder, atoi(xp.c_str()));
        }
        else
        {
          User::HandleCommandResponderMessage(endpoint_id, "Usage: /givexp <user> <xp>");
        }

        return;
      }
    }
#endif

#ifdef ENABLE_BOTS
    if (cmd == "/createbot")
    {
      if (m_Data.m_AdminLevel == 9)
      {
        std::string channel_name;
        std::string bot_name;
        std::string password;

        if (ParseArgumentRemainder(ptr, channel_name, bot_name, password))
        {
          BotDatabaseObject initial_data;
          initial_data.m_UserName = bot_name;
          initial_data.m_UserNameLower = bot_name;
          initial_data.m_Password = password;
          initial_data.m_Channel = channel_name;
          std::transform(initial_data.m_UserNameLower.begin(), initial_data.m_UserNameLower.end(), initial_data.m_UserNameLower.begin(), tolower);

          DDSKey bot_key = crc64(initial_data.m_UserNameLower.ToString());
          m_Interface.InsertIntoDatabase(initial_data, bot_key, &User::HandleBotCreate, this, endpoint_id);
        }
        else
        {
          User::HandleCommandResponderMessage(endpoint_id, "Usage: /createbot <channel_name> <bot_name> <password>");
        }

        return;
      }
    }
#endif

#if defined(ENABLE_BOTS) && defined(ENABLE_WELCOME_INFO)
    if (cmd == "/setbotwelcomeinfo")
    {
      if (m_Data.m_AdminLevel == 9)
      {
        std::string bot_name;        
        std::string welcome_info_tab;

        if (ParseArgumentRemainder(ptr, bot_name, welcome_info_tab))
        {
          std::transform(bot_name.begin(), bot_name.end(), bot_name.begin(), tolower);

          DDSKey bot_key = crc64(bot_name);
          m_Interface.CallWithResponderReturnArgErrorBack(&Bot::SetWelcomeInfoTab, bot_key, 
            &User::HandleCommandResponderMessage, &User::HandleCommandUserLookupFail, this, endpoint_id, welcome_info_tab);
        }
        else
        {
          User::HandleCommandResponderMessage(endpoint_id, "Usage: /setbotwelcomeinfo <bot_name> <welcome_info_tab>");
        }

        return;
      }
    }
#endif

#ifdef ENABLE_WELCOME_INFO

    if (cmd == "/removewelcomeinfo")
    {
      if (m_Data.m_AdminLevel == 9)
      {
        std::string welcome_info_tab;

        if (ParseArgumentRemainder(ptr, welcome_info_tab))
        {
          m_Interface.CallSharedWithResponderReturnArg(&WelcomeInfo::RemoveTab, &User::HandleCommandResponderMessage, this, endpoint_id, welcome_info_tab);
        }
        else
        {
          User::HandleCommandResponderMessage(endpoint_id, "Usage: /removewelcomeinfo <welcome_info_tab>");
        }

        return;
      }
    }
#endif

#ifdef ENABLE_CHANNELS
    if (cmd == "/createbuiltin")
    {
      if (m_Data.m_AdminLevel == 9)
      {
        std::string channel_name;
        std::string channel_motd;

        if (ParseArgumentRemainder(ptr, channel_name, channel_motd))
        {
          BuiltInChannelDatabaseObject channel_data;
          channel_data.m_ChannelInfo.m_ChannelName = channel_name;
          channel_data.m_ChannelInfo.m_Motd = channel_motd;
          channel_data.m_ChannelInfo.m_RequiredAdminLevel = 0;

          std::transform(channel_name.begin(), channel_name.end(), channel_name.begin(), tolower);
          channel_data.m_ChannelNameLower = channel_name;
          m_Interface.InsertIntoDatabase(channel_data, Channel::GetChannelKeyFromName(channel_name.data()), 
            &User::HandleBuiltInChannelCreate, this, std::make_pair(endpoint_id, channel_name));
        }
        else
        {
          User::HandleCommandResponderMessage(endpoint_id, "Usage: /createbuiltin <channel_name> <channel_motd>");
        }

        return;
      }
    }
#endif

    if (cmd == "/rename")
    {
      std::string user_name;
      std::string new_user_name;

      if (ParseArgumentRemainder(ptr, user_name, new_user_name))
      {
        CallUser(user_name.c_str(), &User::Rename, user_lookup_responder, endpoint_id, new_user_name);
      }
      else
      {
        User::HandleCommandResponderMessage(endpoint_id, "Usage: /rename <user_name> <new_user_name>");
      }
      return;
    }

    if (cmd == "/addtitle")
    {
      if (m_Data.m_AdminLevel == 9)
      {
        std::string user_name;
        std::string title;

        if (ParseArgumentRemainder(ptr, user_name, title))
        {
          CallUser(user_name.c_str(), &User::AddTitle, user_lookup_responder, title);
        }
        else
        {
          User::HandleCommandResponderMessage(endpoint_id, "Usage: /addtitle <user> <title>");
        }
        return;
      }
    }

    if (cmd == "/removetitle")
    {
      if (m_Data.m_AdminLevel == 9)
      {
        std::string user_name;
        std::string title;

        if (ParseArgumentRemainder(ptr, user_name, title))
        {
          CallUser(user_name.c_str(), &User::RemoveTitle, user_lookup_responder, title);
        }
        else
        {
          User::HandleCommandResponderMessage(endpoint_id, "Usage: /removetitle <user> <title>");
        }

        return;
      }
    }

    if (cmd == "/addicon")
    {
      if (m_Data.m_AdminLevel == 9)
      {
        std::string user_name;
        std::string icon_url;
        std::string icon_name;

        if (ParseArgumentRemainder(ptr, user_name, icon_url, icon_name))
        {
          CallUser(user_name.c_str(), &User::AddIcon, user_lookup_responder, icon_url, icon_name, true);
        }
        else
        {
          User::HandleCommandResponderMessage(endpoint_id, "Usage: /addicon <user> <icon url> <icon name>");
        }

        return;
      }
    }

    if (cmd == "/removeicon")
    {
      if (m_Data.m_AdminLevel == 9)
      {
        std::string user_name;
        std::string icon;

        if (ParseArgumentRemainder(ptr, user_name, icon))
        {
          CallUser(user_name.c_str(), &User::RemoveIcon, user_lookup_responder, icon);
        }
        else
        {
          User::HandleCommandResponderMessage(endpoint_id, "Usage: /removeicon <user> <url or icon name>");
        }

        return;
      }
    }

    if (cmd == "/kick")
    {
      std::string user_name;

      if (ParseArgumentDefault(ptr, user_name))
      {
        CallUser(user_name.c_str(), &User::Kick, user_lookup_responder);
      }
      else
      {
        User::HandleCommandResponderMessage(endpoint_id, "Usage: /kick user");
      }
      return;
    }

#ifdef ENABLE_BAN_LIST
    if (cmd == "/banlist")
    {
      m_Interface.CallWithResponderReturnArgErrorBack(&BanList::GetInfo, 0,
        &User::HandleCommandResponderMessage, &User::HandleCommandSquadLookupFail, this, endpoint_id);
      return;
    }

    if (cmd == "/ban")
    {
      std::string user_name;
      std::string duration;
      std::string message;

      if (ParseArgumentRemainder(ptr, user_name, duration, message) == false)
      {
        User::HandleCommandResponderMessage(endpoint_id, "Usage: /ban <user> <duration> <message>");
        return;
      }

      int duration_secs;
      if ((duration_secs = ParseDuration(duration.c_str())) == 0)
      {
        User::HandleCommandResponderMessage(endpoint_id, "Invalid duration");
        return;
      }

      CallUser(user_name.c_str(), &User::BanSelf, user_lookup_responder, duration_secs, message + " (added with /ban " + user_name + ")");
      return;
    }

    if (cmd == "/banall")
    {
      std::string user_name;
      std::string duration;
      std::string message;

      if (ParseArgumentRemainder(ptr, user_name, duration, message) == false)
      {
        User::HandleCommandResponderMessage(endpoint_id, "Usage: /banall <user> <duration> <message>");
        return;
      }

      int duration_secs;
      if ((duration_secs = ParseDuration(duration.c_str())) == 0)
      {
        User::HandleCommandResponderMessage(endpoint_id, "Invalid duration");
        return;
      }

      CallUser(user_name.c_str(), &User::BanSelfAndConnections, user_lookup_responder, duration_secs, message + " (added with /banall " + user_name + ")");
      return;
    }

    if (cmd == "/banip")
    {
      std::string arg;
      std::string duration;
      std::string message;

      if (ParseArgumentRemainder(ptr, arg, duration, message) == false)
      {
        User::HandleCommandResponderMessage(endpoint_id, "Usage: /banip <ip> <duration> <message>");
        return;
      }

      int duration_secs;
      if ((duration_secs = ParseDuration(duration.c_str())) == 0)
      {
        User::HandleCommandResponderMessage(endpoint_id, "Invalid duration");
        return;
      }

      m_Interface.Call(&BanList::Ban, 0, BanType::kRemoteIp, arg, duration_secs, message);
      User::HandleCommandResponderMessage(endpoint_id, "Ban submitted");
      return;
    }

    if (cmd == "/banhost")
    {
      std::string arg;
      std::string duration;
      std::string message;

      if (ParseArgumentRemainder(ptr, arg, duration, message) == false)
      {
        User::HandleCommandResponderMessage(endpoint_id, "Usage: /banhost <ip> <duration> <message>");
        return;
      }

      int duration_secs;
      if ((duration_secs = ParseDuration(duration.c_str())) == 0)
      {
        User::HandleCommandResponderMessage(endpoint_id, "Invalid duration");
        return;
      }

      m_Interface.Call(&BanList::Ban, 0, BanType::kRemoteHost, arg, duration_secs, message);
      User::HandleCommandResponderMessage(endpoint_id, "Ban submitted");
      return;
    }
#endif
  }

#ifdef ENABLE_CHANNELS
  if (cmd == "/remove")
  {
    std::string user_name;

    if (ParseArgumentDefault(ptr, user_name))
    {
      CallUser(user_name.c_str(), &User::KickFromChannel, user_lookup_responder, 
        m_Interface.GetLocalKey(), endpoint_id, channel_id, (int)m_UserInfo.m_AdminLevel);
    }
    else
    {
      User::HandleCommandResponderMessage(endpoint_id, "Usage: /remove user");
    }
    return;
  }

  if (cmd == "/join")
  {
    std::string channel_name;
    ParseArgumentDefault(ptr, channel_name);

    if (User::ValidateUserName(channel_name, 1, 16) == false)
    {
      User::HandleCommandResponderMessage(endpoint_id, "Invalid channel name");
      return;
    }

    if (m_LocalInfo.m_Channels.NumElements() >= 30)
    {
      User::HandleCommandResponderMessage(endpoint_id, "You are in too many channels");
      return;
    }

    JoinChannel(endpoint_id, channel_name);
    return;
  }

  if (cmd == "/leave")
  {
    LeaveChannel(channel_id);
    return;
  }
#endif

  HandleCommandResponderMessage(endpoint_id, "Command not found: " + cmd);
}

void User::Rename(DDSResponder & responder, DDSKey src_endpoint_id, const std::string & new_name)
{
  std::string user_name_lower = new_name;
  std::transform(user_name_lower.begin(), user_name_lower.end(), user_name_lower.begin(), tolower);

  if (user_name_lower == m_Data.m_UserNameLower.ToString())
  {
    // Just set the name
    m_Data.m_UserName = new_name;
    m_LocalInfo.m_Name = new_name;
    m_UserInfo.m_Name = new_name;

    m_Interface.Call(&UserConnection::SendServerText, src_endpoint_id, "Successfully changed name");
  }
  else
  {
    auto data = m_Data;
    data.m_UserNameLower = user_name_lower;
    data.m_UserName = new_name;
    m_Interface.UpdateDatabase(data, &User::HandleRename, this, src_endpoint_id);
  }
}

void User::MakeAdmin(DDSResponder & responder, int admin_level)
{
  if (admin_level > 8)
  {
    admin_level = 8;
  }

  if (admin_level < 0)
  {
    admin_level = 0;
  }

  if (m_Data.m_AdminLevel == 9)
  {
    DDSResponderCall(responder, "You cannot change the admin level of root accounts ");
    return;
  }

  if (m_Data.m_AdminLevel == admin_level)
  {
    DDSResponderCall(responder, std::string("That user is already at admin level ") + std::to_string(admin_level));
    return;
  }

  m_Data.m_AdminLevel = admin_level;
  m_LocalInfo.m_AdminLevel = admin_level;
  m_UserInfo.m_AdminLevel = admin_level;

  if (admin_level > 0)
  {
    SendNotification(std::string("You are now an admin at level ") + std::to_string(admin_level));
    DDSResponderCall(responder, std::string("Successfully set user to admin level ") + std::to_string(admin_level));

#ifdef ENABLE_CHANNELS
    JoinChannel(0, "Admin");
    JoinChannel(0, "Support");
    JoinChannel(0, "Newbies");
#endif
  }
  else
  {
    SendNotification("You are no longer an admin");
    DDSResponderCall(responder, "Successfully set user to no admin level");
  }

}

#ifdef ENABLE_BAN_LIST
void User::BanSelf(DDSResponder & responder, int duration, std::string message)
{
  m_Interface.Call(&BanList::Ban, 0, BanType::kPlatformId, std::to_string(m_LocalInfo.m_PlatformId), duration, message);

  DDSResponderCall(responder, std::string("Banned user ") + m_UserInfo.m_Name.ToString());
}

void User::BanSelfAndConnections(DDSResponder & responder, int duration, std::string message)
{
  m_Interface.Call(&BanList::Ban, 0, BanType::kPlatformId, std::to_string(m_LocalInfo.m_PlatformId), duration, message);

  for (auto & elem : m_Endpoints)
  {
    m_Interface.Call(&BanList::Ban, 0, BanType::kRemoteIp, elem.second.first, duration, message);
    m_Interface.Call(&BanList::Ban, 0, BanType::kRemoteHost, elem.second.second, duration, message);
  }

  DDSResponderCall(responder, std::string("Banned user ") + m_UserInfo.m_Name.ToString() + " and all related connections");
}
#endif

void User::Kick(DDSResponder & responder)
{
  for (auto & ep : m_Endpoints)
  {
    m_Interface.Call(&UserConnection::SendConnectionError, ep.first, "You have been kicked");
  }

  DDSResponderCall(responder, std::string("Kicked user ") + m_UserInfo.m_Name.ToString());
}

void User::HandleRename(DDSKey return_ep, bool success)
{
  if (success)
  {
    m_UserInfo.m_Name = m_Data.m_UserName;
    m_LocalInfo.m_Name = m_Data.m_UserName;

    m_Interface.Call(&UserConnection::SendServerText, return_ep, "Successfully changed name");
  }
  else
  {
    m_Interface.Call(&UserConnection::SendServerText, return_ep, "Failed to change name");
  }
}

#ifdef ENABLE_WELCOME_INFO

void User::FetchWelcomeInfoForEdit(DDSKey endpoint_id)
{
  m_Interface.CallSharedWithResponderReturnArg(&WelcomeInfo::FetchWelcomeInfo, &User::HandleWelcomeInfoEdit, this, endpoint_id);
}

void User::HandleWelcomeInfoEdit(DDSKey endpoint_id, std::string info)
{
  UserLocalInfoUpdate msg;
  msg.c = "edit_lobby_info";
  msg.data = info;

  m_Interface.Call(&UserConnection::SendData, endpoint_id, StormReflEncodeJson(msg));
}

void User::UpdateWelcomeInfo(DDSKey endpoint_id, std::string info)
{
  if (m_LocalInfo.m_AdminLevel == 0)
  {
    return;
  }

  m_Interface.CallWithResponderReturnArg(&WelcomeInfo::UpdateInfo, 0, &User::HandleCommandResponderMessage, this, endpoint_id, "Welcome", info);
}
#endif

#ifdef ENABLE_CHANNELS
void User::KickFromChannel(DDSResponder & responder, DDSKey src_user_id, DDSKey src_user_endpoint, DDSKey channel_id, int src_admin_level)
{
  m_Interface.Call(&Channel::KickUser, channel_id, src_user_endpoint, m_Interface.GetLocalKey(), src_user_id, src_admin_level);
}

void User::FetchChannelTextForEdit(DDSKey endpoint_id, DDSKey channel_id)
{
  m_Interface.CallWithResponderReturnArg(&Channel::FetchChannelMotd, channel_id, &User::HandleChannelTextEdit, this, std::make_pair(endpoint_id, channel_id));
}

void User::HandleChannelTextEdit(std::pair<DDSKey, DDSKey> edit_info, std::string channel_text)
{
  UserChannelInfoUpdate msg;
  msg.c = "edit_channel_info";
  msg.data = channel_text;
  msg.channel_id = std::get<1>(edit_info);

  m_Interface.Call(&UserConnection::SendData, std::get<0>(edit_info), StormReflEncodeJson(msg));
}

void User::UpdateChannelText(DDSKey endpoint_id, DDSKey channel_id, std::string channel_text)
{
  if (m_LocalInfo.m_AdminLevel == 0)
  {
    return;
  }

  m_Interface.CallWithResponderReturnArg(&Channel::UpdateChannelMotd, channel_id, &User::HandleCommandResponderMessage, this, endpoint_id, channel_text);
}

void User::HandleBuiltInChannelCreate(std::pair<DDSKey, std::string> return_info, int ec)
{
  if (ec == 0)
  {
    m_Interface.Call(&UserConnection::SendServerText, return_info.first, "Successfully created built in channel");
    JoinChannel(0, return_info.second);
  }
  else
  {
    m_Interface.Call(&UserConnection::SendServerText, return_info.first, "Failed to create built in channel");
  }
}


#endif

void User::HandleCommandResponderMessage(DDSKey endpoint_id, std::string msg)
{
  if (m_UserInfo.m_AdminLevel == 0)
  {
    m_Interface.Call(&UserConnection::SendNotification, endpoint_id, msg);
  }
  else
  {
    m_Interface.Call(&UserConnection::SendServerText, endpoint_id, msg);
  }
}

void User::HandleCommandUserLookupFail(DDSKey endpoint_id)
{
  if (m_UserInfo.m_AdminLevel == 0)
  {
    m_Interface.Call(&UserConnection::SendNotification, endpoint_id, "User not found");
  }
  else
  {
    m_Interface.Call(&UserConnection::SendServerText, endpoint_id, "User not found");
  }
}

void User::HandleCommandSquadLookupFail(DDSKey endpoint_id)
{
  if (m_UserInfo.m_AdminLevel == 0)
  {
    m_Interface.Call(&UserConnection::SendNotification, endpoint_id, "Squad not found");
  }
  else
  {
    m_Interface.Call(&UserConnection::SendServerText, endpoint_id, "Squad not found");
  }
}

#ifdef ENABLE_BOTS
void User::HandleBotCreate(DDSKey endpoint_id, int ec)
{
  if (ec == 0)
  {
    m_Interface.Call(&UserConnection::SendServerText, endpoint_id, "Successfully created bot");
  }
  else
  {
    m_Interface.Call(&UserConnection::SendServerText, endpoint_id, "Invalid bot name");
  }
}
#endif

void User::GetInfo(DDSResponder & responder)
{
  std::string data = "User info for " + m_UserInfo.m_Name.ToString() + "\n";
  StormReflEncodePrettyJson(m_UserInfo, data);
  data += "\nLocal Info\n";
  StormReflEncodePrettyJson(m_LocalInfo, data);
  data += "\nDatabase Info\n";
  StormReflEncodePrettyJson(m_Data, data);
  
  if (m_Endpoints.size() > 0)
  {
    data += "\nCurrent Connections:\n";

    for (auto & elem : m_Endpoints)
    {
      data += "Remote Ip: ";
      data += elem.second.first;
      data += " Remote Host: ";
      data += elem.second.second;
      data += "\n";
    }
  }

  DDSResponderCall(responder, data);
}

bool User::IsValidEndpoint(DDSKey endpoint_id) const
{
  for(auto & endp : m_Endpoints)
  {
    if(endp.first == endpoint_id)
    {
      return true;
    }
  }

  return false;
}

bool User::IsBannedFromCompetitive() const
{
  return m_Data.m_CompetitiveBanStart + m_Data.m_CompetitiveBanDuration > m_Interface.GetNetworkTime();
}

bool User::IsOnProbationFromCompetitive() const
{
  return m_Data.m_CompetitiveBanStart + m_Data.m_CompetitiveBanProbation > m_Interface.GetNetworkTime();
}

void User::BeginLoad()
{
#ifdef ENABLE_SQUADS

  MergeListRemoveDuplicates(m_Data.m_Squads);
  MergeListRemoveDuplicates(m_Data.m_Applications);
  MergeListRemoveDuplicates(m_Data.m_Requests);

  for (auto squad : m_Data.m_Squads)
  {
    LoadSquadInternal(squad.second);
  }

  for (auto squad : m_Data.m_Applications)
  {
    LoadApplicationInternal(squad.first, squad.second);
  }

  for (auto squad : m_Data.m_Requests)
  {
    LoadSquadRequestInternal(squad.first, squad.second);
  }
#endif

  CheckCompleteLoad();
}

void User::CheckCompleteLoad()
{
#ifdef ENABLE_SQUADS

  if (m_PendingSquadLoads.size() != 0)
  {
    return;
  }

  if (m_PendingApplicationLoads.size() != 0)
  {
    return;
  }

  if (m_PendingRequestLoads.size() != 0)
  {
    return;
  }
#endif

  m_Interface.FinalizeObjectLoad();
}

bool User::ValidateUserName(const std::string & name, int min_characters, int max_characters, bool allow_space)
{
  if ((int)name.size() < min_characters || (int)name.size() > max_characters)
  {
    return false;
  }

  for (auto c : name)
  {
    bool is_alpha = (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
    bool is_num = (c >= '0' && c <= '9');
    bool is_special = (c == '-' || c == '.' || c == '_');
    bool is_space = (c == ' ' && allow_space);

    if (!is_alpha && !is_num && !is_special && !is_space)
    {
      return false;
    }
  }

  return true;
}

DDSKey User::GetUserIdForPlatformId(const std::string & platform, uint64_t platform_id)
{
  std::string steam_id_str = platform + std::to_string(platform_id);
  return crc64(steam_id_str);
}

void User::HandleUserNameLookupForCall(std::tuple<int, std::string, DDSResponderData> call_data, int ec, std::string data)
{
  auto method_id = std::get<0>(call_data);
  auto call_args = std::get<1>(call_data);
  auto responder_data = std::get<2>(call_data);

  DDSResponder responder{ m_Interface, responder_data };

  const char * id = StormDataFindJsonStartByPath(".m_PlatformId", data.c_str());
  const char * platform = StormDataFindJsonStartByPath(".m_Platform", data.c_str());

  if (id == nullptr)
  {
    DDSResponderCallError(responder);
  }
  else
  {
    std::string platform_parsed;
    if (StormReflParseJson(platform_parsed, id) == false)
    {
      DDSResponderCallError(responder);
      return;
    }

    uint64_t id_parsed;
    if (StormReflParseJson(id_parsed, id) == false)
    {
      DDSResponderCallError(responder);
      return;
    }

    auto user_key = User::GetUserIdForPlatformId(platform_parsed, id_parsed);
    m_Interface.CallWithForwardedResponderRaw(StormReflTypeInfo<User>::GetNameHash(), method_id, user_key, responder_data, std::move(call_args));
  }
}
