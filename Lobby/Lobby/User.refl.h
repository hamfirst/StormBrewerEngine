#pragma once

#include <HurricaneDDS/DDSDataObject.h>
#include <HurricaneDDS/DDSThrottle.refl.h>

#include <StormRefl/StormReflJsonStd.h>

#include "Game/GameNetworkData.refl.h"

#include "Lobby/SharedTypes.refl.h"
#include "Lobby/GameData.refl.h"
#include "Lobby/LobbyConfig.h"

#include "ProjectSettings/ProjectZones.h"

struct UserPersistent
{
  STORM_DATA_DEFAULT_CONSTRUCTION(UserPersistent);

#ifdef ENABLE_CHANNELS
  RBool m_EnterExitMessages;
  RBool m_TwelveHourClock;
  RInt m_PlayerListSort;
#endif
};

struct UserLocalData
{
  STORM_DATA_DEFAULT_CONSTRUCTION(UserLocalData);

  RString m_Name;
  RKey m_UserKey;
  RKey m_PlatformId;

  RInt m_AdminLevel;

  UserPersistent m_Persistent;

  RInt m_Title;
  RMergeList<RString> m_TitleList;

  RInt m_Icon;

  RMergeList<RString> m_IconNames;
  RString m_IconURL;

  RInt m_Celebration;
  RMergeList<RString> m_CelebrationNames;

#ifdef ENABLE_CHANNELS
  RMergeList<RString> m_AutoJoinChannels;
  RMergeList<DDSSharedLocalCopyPtr<ChannelInfo>> m_Channels;
#endif

#ifdef ENABLE_SQUADS
  RKey m_PrimarySquad;
  RKey m_OwnerSquad;

  RMap<DDSKey, SquadInfo> m_Squads;
  RMergeList<UserApplication> m_Applications;
  RMergeList<UserApplication> m_Requests;
#endif
};

struct UserDatabaseObject
{
  DDS_DATABASE_OBJECT(User);

  RString m_UserName;
  RString m_UserNameLower;

  RString m_Platform;
  DDSKey m_PlatformId = 0;

  RBool m_IsGuest = false;
  RInt m_AdminLevel = 0;

#ifdef ENABLE_CHANNELS
  RInt m_VisibilityFlags = 0;
#endif

  RInt m_Created;

  RInt m_Title = -1;
  RMergeList<RString> m_TitleList;

  RInt m_Icon = -1;
  RMergeList<RString> m_IconNames;
  RMergeList<RString> m_IconURLs;

  RInt m_Celebration = -1;
  RMergeList<RString> m_CelebrationNames;
  RMergeList<RInt> m_CelebrationIDs;

  RInt m_LastGamePlayed;
  GameStatsData m_Stats;

#ifdef ENABLE_REWARDS
  RInt m_Level;
  RInt m_XP;
  RSparseList<UserXPGain> m_XPLog;
#endif

  UserPersistent m_Persistent;

#ifdef ENABLE_CHANNELS
  RMergeList<RString> m_AutoJoinChannels;
#endif

#ifdef ENABLE_SQUADS
  RKey m_PrimarySquad = 0;
  RKey m_OwnerSquad = 0;
  RMergeList<RKey> m_Squads;

  RMergeList<RKey> m_Applications;
  RMergeList<RKey> m_Requests;
#endif

  RMergeList<RString> m_HistoryHosts;
};

struct UserNameLookup
{
  STORM_REFL;
  STORM_REFL_NODEFAULT;

  using DatabaseType = UserDatabaseObject;

  UserNameLookup(const char * user_name);
  UserNameLookup(std::string & user_name);

  std::string m_UserNameLower;
};

struct UserPlatformIdLookup
{
  STORM_REFL;
  STORM_REFL_NODEFAULT;

  using DatabaseType = UserDatabaseObject;

  UserPlatformIdLookup(DDSKey platform_id);

  DDSKey m_PlatformId;
};

struct UserGameJoinInfo
{
  STORM_REFL;

  DDSKey m_EndpointId;
  std::string m_Password;
  bool m_Observer;
  LobbyGameType m_IntendedType;

  UserZoneInfo m_ZoneInfo;
};

struct User
{
  DDS_DATA_OBJECT(DDSDataObjectPriority::kMedium);
  User(DDSNodeInterface node_interface, UserDatabaseObject & db_object);

  // Endpoint functions
  void STORM_REFL_FUNC AddEndpoint(DDSKey key, std::string remote_ip, std::string remote_host);
  void STORM_REFL_FUNC SendToAllEndpoints(std::string data);
  void STORM_REFL_FUNC SendNotification(std::string msg);
  void STORM_REFL_FUNC SendToEndpoint(DDSKey endpoint_id, std::string data);
  void STORM_REFL_FUNC RemoveEndpoint(DDSKey key);
  void STORM_REFL_FUNC SetLocation(std::string country_code, std::string currency_code);
  void STORM_REFL_FUNC UpdateName(std::string name);

#ifdef ENABLE_REWARDS
  void STORM_REFL_FUNC GiveGifts();
  void STORM_REFL_FUNC HandleGiftData(int ec, std::string data);
#endif

#ifdef ENABLE_CHANNELS
  // Channel Functions
  bool IsInChannel(DDSKey channel_key) const;
  void STORM_REFL_FUNC JoinChannel(DDSKey requesting_endpoint, std::string channel_name);
  void STORM_REFL_FUNC LeaveChannel(DDSKey channel_key);
  void STORM_REFL_FUNC LeaveAllChannels();
  void STORM_REFL_FUNC SendChatToChannel(DDSKey src_endpoint_id, DDSKey channel_key, std::string message);
  void STORM_REFL_FUNC HandleChannelJoinResponse(std::pair<DDSKey, DDSKey> join_info, ChannelJoinResult result);
  void STORM_REFL_FUNC HandleChannelUpdate(DDSKey channel_key, std::string data, int version);
#endif

  // Game Functions
  void STORM_REFL_FUNC CreatePrivateGame(DDSKey endpoint_id, GameInitSettings creation_data, std::string password, const UserZoneInfo & zone_info);
  void STORM_REFL_FUNC JoinGame(DDSKey game_id, const UserGameJoinInfo & join_info);
  void STORM_REFL_FUNC JoinGameByLookupTable(uint32_t join_code, const UserGameJoinInfo & join_info);
  void STORM_REFL_FUNC SetInGame(DDSKey game_id, DDSKey game_random_id, DDSKey endpoint_id);
  void STORM_REFL_FUNC DestroyGame(DDSKey endpoint_id, DDSKey game_id);
  void STORM_REFL_FUNC HandleGameJoinResponse(DDSKey game_id, DDSKey endpoint_id, DDSKey game_random_id, bool success);
  void STORM_REFL_FUNC HandleJoinCodeLookup(DDSKey game_id, const UserGameJoinInfo & join_info);
  void STORM_REFL_FUNC SendGameChat(DDSKey endpoint_id, std::string msg);
  void STORM_REFL_FUNC SwitchTeams(DDSKey target_user, int team, DDSKey endpoint_id);
  void STORM_REFL_FUNC StartGame();
  void STORM_REFL_FUNC LeaveGame();
  void STORM_REFL_FUNC NotifyLeftGame(DDSKey game_id, DDSKey game_random_id);
  void STORM_REFL_FUNC HandleGameChat(DDSKey game_id, DDSKey game_random_id, std::string name, std::string title, std::string msg);
  void STORM_REFL_FUNC HandleGameUpdate(std::tuple<DDSKey, DDSKey> game_info, std::string data);

  // Squad Functions
#ifdef ENABLE_SQUADS
  void STORM_REFL_FUNC CreateSquad(DDSKey creator_endpoint, std::string squad_name, std::string squad_tag);
  void STORM_REFL_FUNC DestroySquad(DDSKey destroyer_endpoint);
  void STORM_REFL_FUNC HandleSquadCreateNameLookupFail(std::tuple<DDSKey, std::string, std::string> squad_data, std::string channel_name);
  void STORM_REFL_FUNC HandleSquadCreateNameLookupSuccess(std::tuple<DDSKey, std::string, std::string> squad_data);
  void STORM_REFL_FUNC HandleSquadCreate(std::tuple<std::string, std::string, DDSKey, DDSKey> squad_info, int ec);
  void STORM_REFL_FUNC HandleSquadOperationResponse(DDSKey endpoint_id, std::string response);
  void STORM_REFL_FUNC HandleSquadLookupFail(DDSKey endpoint_id);

  void STORM_REFL_FUNC ApplyToSquad(DDSKey endpoint_id, std::string squad_name);
  void STORM_REFL_FUNC AcceptSquadApplication(DDSKey endpoint_id, DDSKey squad_id, DDSKey user_id);
  void STORM_REFL_FUNC RescindSquadApplication(DDSKey endpoint_id, DDSKey squad_id);
  void STORM_REFL_FUNC DeclineSquadApplication(DDSKey endpoint_id, DDSKey squad_id, DDSKey user_id);

  void STORM_REFL_FUNC RequestUserToJoinSquad(DDSKey endpoint_id, DDSKey squad_id, DDSKey platform_id);
  void STORM_REFL_FUNC HandleSquadRequestUserLookup(std::tuple<DDSKey, DDSKey> squad_data, int ec, std::string data);
  void STORM_REFL_FUNC AcceptSquadRequest(DDSKey endpoint_id, DDSKey squad_id);
  void STORM_REFL_FUNC RescindSquadRequest(DDSKey endpoint_id, DDSKey squad_id, DDSKey user_id);
  void STORM_REFL_FUNC DeclineSquadRequest(DDSKey endpoint_id, DDSKey squad_id);

  void STORM_REFL_FUNC LeaveSquad(DDSKey endpoint_id, DDSKey squad_id);
  void STORM_REFL_FUNC RemoveSquadMember(DDSKey endpoint_id, DDSKey squad_id, DDSKey user_id);
  void STORM_REFL_FUNC EditSquadPermissions(DDSKey endpoint_id, DDSKey squad_id, DDSKey user_id, int permissions);
  void STORM_REFL_FUNC EditSquadMotd(DDSKey endpoint_id, DDSKey squad_id, std::string motd);
  void STORM_REFL_FUNC LockSquadChannel(DDSKey endpoint_id, DDSKey squad_id, bool locked);

  void STORM_REFL_FUNC SetPrimarySquad(DDSKey endpoint_id, DDSKey squad_id);

  void STORM_REFL_FUNC AddSquadInternal(DDSKey squad_id);
  void STORM_REFL_FUNC LoadSquadInternal(DDSKey squad_id);
  void STORM_REFL_FUNC RemoveSquadInternal(DDSKey squad_id);
  void STORM_REFL_FUNC AddApplicationInternal(DDSKey squad_id, std::string squad_name, std::string squad_tag);
  void STORM_REFL_FUNC AddSquadRequestInternal(DDSKey squad_id, std::string squad_name, std::string squad_tag);
  void STORM_REFL_FUNC LoadApplicationInternal(int index, DDSKey squad_id);
  void STORM_REFL_FUNC LoadSquadRequestInternal(int index, DDSKey squad_id);
  void STORM_REFL_FUNC CancelApplicationInternal(DDSKey squad_id);
  void STORM_REFL_FUNC CancelSquadRequestInternal(DDSKey squad_id);
  void STORM_REFL_FUNC HandleSquadUpdate(DDSKey squad_id, std::string data);
  void STORM_REFL_FUNC HandleSquadDeleted(DDSKey squad_id);
  void STORM_REFL_FUNC HandleSquadApplicationLoad(std::pair<int, DDSKey> squad_info, std::string name, std::string tag);
  void STORM_REFL_FUNC HandleSquadApplicationLoadFailure(std::pair<int, DDSKey> squad_info);
  void STORM_REFL_FUNC HandleSquadRequestLoad(std::pair<int, DDSKey> squad_info, std::string name, std::string tag);
  void STORM_REFL_FUNC HandleSquadRequestLoadFailure(std::pair<int, DDSKey> squad_info);
#endif

  // Profile Functions
  void STORM_REFL_FUNC AddTitle(DDSResponder & responder, std::string title, bool quiet);
  void STORM_REFL_FUNC SetTitle(int title_index);
  void STORM_REFL_FUNC RemoveTitle(DDSResponder & responder, std::string title);

  void STORM_REFL_FUNC AddIcon(DDSResponder & responder, std::string icon_url, std::string icon_name, bool set, bool quiet);
  void STORM_REFL_FUNC SetIcon(int icon_index);
  void STORM_REFL_FUNC RemoveIcon(DDSResponder & responder, std::string icon);

  void STORM_REFL_FUNC AddCelebration(DDSResponder & responder, int celebration_id, std::string celebration_name, bool set, bool quiet);
  void STORM_REFL_FUNC SetCelebration(int celebration_index);
  void STORM_REFL_FUNC RemoveCelebration(DDSResponder & responder, std::string celebration);

  void STORM_REFL_FUNC UpdateStats(GameStatsData stats, GameInitSettings instance_data);
  void STORM_REFL_FUNC FetchStats(DDSResponder & responder);

#ifdef ENABLE_CHANNELS
  void STORM_REFL_FUNC AddAutoJoinChannel(DDSResponder & responder, const std::string & channel_name);
  void STORM_REFL_FUNC RemoveAutoJoinChannel(DDSResponder & responder, const std::string & channel_name);
#endif

  void STORM_REFL_FUNC ModifyPersistent(const std::string & change_packet);

#ifdef ENABLE_REWARDS
  void STORM_REFL_FUNC GiveXP(DDSResponder & responder, int amount);
  void STORM_REFL_FUNC SendXPGain(DDSKey endpoint_id);
  void STORM_REFL_FUNC ApplyXPGain(bool quiet);
  void STORM_REFL_FUNC SkipXPGain();
#endif

  // Admin Functions
  void STORM_REFL_FUNC ProcessSlashCommand(DDSKey endpoint_id, DDSKey channel_id, std::string msg);
  void STORM_REFL_FUNC Rename(DDSResponder & responder, DDSKey src_endpoint_id, const std::string & new_name);
  void STORM_REFL_FUNC MakeAdmin(DDSResponder & responder, int admin_level);

#ifdef ENABLE_BAN_LIST
  void STORM_REFL_FUNC BanSelf(DDSResponder & responder, int duration, std::string message);
  void STORM_REFL_FUNC BanSelfAndConnections(DDSResponder & responder, int duration, std::string message);
#endif

  void STORM_REFL_FUNC Kick(DDSResponder & responder);
  void STORM_REFL_FUNC HandleRename(DDSKey return_ep, bool success);

#ifdef ENABLE_WELCOME_INFO
  void STORM_REFL_FUNC FetchWelcomeInfoForEdit(DDSKey endpoint_id);
  void STORM_REFL_FUNC HandleWelcomeInfoEdit(DDSKey endpoint_id, std::string info);
  void STORM_REFL_FUNC UpdateWelcomeInfo(DDSKey endpoint_id, std::string info);
  void STORM_REFL_FUNC FetchChannelTextForEdit(DDSKey endpoint_id, DDSKey channel_id);
#endif

#ifdef ENABLE_CHANNELS
  void STORM_REFL_FUNC KickFromChannel(DDSResponder & responder, DDSKey src_user_id, DDSKey src_user_endpoint, DDSKey channel_id, int src_admin_level);
  void STORM_REFL_FUNC HandleChannelTextEdit(std::pair<DDSKey, DDSKey> edit_info, std::string channel_text);
  void STORM_REFL_FUNC UpdateChannelText(DDSKey endpoint_id, DDSKey channel_id, std::string channel_text);
  void STORM_REFL_FUNC HandleBuiltInChannelCreate(std::pair<DDSKey, std::string> return_info, int ec);
#endif

  void STORM_REFL_FUNC HandleCommandResponderMessage(DDSKey endpoint_id, std::string msg);
  void STORM_REFL_FUNC HandleCommandUserLookupFail(DDSKey endpoint_id);
  void STORM_REFL_FUNC HandleCommandSquadLookupFail(DDSKey endpoint_id);

#ifdef ENABLE_BOTS
  void STORM_REFL_FUNC HandleBotCreate(DDSKey endpoint_id, int ec);
#endif

  // Inspection functions
  void STORM_REFL_FUNC GetInfo(DDSResponder & responder);

public:

  void BeginLoad();
  void CheckCompleteLoad();  

  static bool ValidateUserName(const std::string & name, int min_characters = 3, int max_characters = 32, bool allow_space = false);

  static DDSKey GetUserIdForPlatformId(const std::string & platform, uint64_t platform_id);
  static std::string GetDefaultIcon();

public:

  template <typename ... Args, typename ... CallArgs>
  void CallUser(const char * user_name, void (User::*func)(DDSResponder &, Args ...), DDSResponder & responder, CallArgs && ... args)
  {
    std::tuple<int, std::string, DDSResponderData> return_data = 
      std::make_tuple(StormReflGetMemberFunctionIndex(func), DDSSerializeCallData(std::forward<CallArgs>(args)...), responder.m_Data);

    responder.m_Interface.QueryDatabase(UserNameLookup{ user_name }, &User::HandleUserNameLookupForCall, this, std::move(return_data));
  }

  void STORM_REFL_FUNC HandleUserNameLookupForCall(std::tuple<int, std::string, DDSResponderData> call_data, int ec, std::string data);

public:

  UserInfo m_UserInfo;
  UserLocalData m_LocalInfo;

  DDSThrottle m_CharsThrottle;
  DDSThrottle m_LinesThrottle;
  DDSThrottle m_GameCreationThrottle;
  DDSThrottle m_SquadCreationThrottle;
  DDSThrottle m_ProfileThrottle;
  DDSThrottle m_GameThrottle;

  std::vector<DDSKey> m_PendingSquadLoads;
  std::vector<DDSKey> m_PendingApplicationLoads;
  std::vector<DDSKey> m_PendingRequestLoads;
  bool m_CreatingSquad = false;

  DDSKey m_PendingPrimarySquad = 0;
  DDSKey m_PendingPrimarySquadSettingEndpoint = 0;

  std::map<DDSKey, DDSKey> m_SquadSubscriptionIds;

  std::vector<std::pair<std::pair<DDSKey, DDSKey>, DDSKey>> m_ChannelSubscriptions;
  std::map<DDSKey, std::pair<std::string, std::string>> m_Endpoints;

  std::vector<DDSKey> m_PendingChannelJoins;

  bool m_InGame = false;
  bool m_SentInitialGameData = false;
  DDSKey m_GameId = 0;
  DDSKey m_GameRandomId = 0;

  DDSKey m_GameEndpoint = 0;
  DDSKey m_GameSubscriptionId = 0;

  std::string m_CountryCode;
  std::string m_CurrencyCode;

private:

  STORM_REFL_IGNORE DDSNodeInterface m_Interface;
  STORM_REFL_IGNORE UserDatabaseObject & m_Data;
};
