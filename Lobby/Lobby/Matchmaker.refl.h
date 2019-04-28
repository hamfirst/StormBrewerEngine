#pragma once

#include "StormRefl/StormRefl.h"
#include "StormData/StormDataTypes.h"

#include "HurricaneDDS/DDSDataObject.h"

#include "Game/GameNetworkData.refl.h"
#include "GameShared/GamePlayListAsset.refl.h"

#include "LobbyShared/SharedTypes.refl.h"

#include "LobbyConfig.h"


struct PlaylistBucketUser
{
  STORM_REFL;
  DDSKey m_UserKey;
  DDSKey m_EndpointId;
};

struct PlaylistBucketUserList
{
  STORM_REFL;

  PlaylistBucketUser m_PrimaryUser;
  std::vector<PlaylistBucketUser> m_ExtraUsers;
  time_t m_TimePutInMatchmaker;
  DDSKey m_MatchmakerRandomId;
};

struct PlaylistBucket
{
  STORM_REFL;
  std::vector<PlaylistBucketUserList> m_Users;
};

struct PlaylistBucketList
{
  STORM_REFL;
  std::vector<PlaylistBucket> m_Buckets;
};

struct RefillGame
{
  STORM_REFL;

  DDSKey m_GameId;
  int m_Playlist = 0;
  int m_PlayersNeeded[kMaxTeams] = {0};
  int m_PlayersAssigned[kMaxTeams] = {0};
  int m_PlayersLeft[kMaxTeams] = {0};
  bool m_AllowRefill = true;
};

struct RefillGameList
{
  STORM_REFL;
  std::vector<RefillGame> m_Games;
};

struct GeneratedGame;

struct Matchmaker
{
public:
  DDS_SHARED_OBJECT;

  explicit Matchmaker(DDSObjectInterface & obj_interface);
  void Initialize();
  void Update();

  void STORM_REFL_FUNC AddCasualUser(const PlaylistBucketUserList & user, const UserZoneInfo & zone_info, uint32_t playlist_mask);
  void STORM_REFL_FUNC AddCompetitiveUser(const PlaylistBucketUserList & user, const UserZoneInfo & zone_info, uint32_t playlist_mask);

  void STORM_REFL_FUNC RemoveCasualUser(DDSKey user, DDSKey random_id);
  void STORM_REFL_FUNC RemoveCompetitiveUser(DDSKey user, DDSKey random_id);

  void STORM_REFL_FUNC NotifyPlayerLeftCasualGame(DDSKey game_id, int team, int zone);
  void STORM_REFL_FUNC NotifyGameAcceptingPlayers(DDSKey game_id, int zone, bool accepting_players);

  void STORM_REFL_FUNC CancelMatchmakingForUser(DDSKey user, DDSKey random_id);

private:

  static void ReadPlaylistFile(czstr playlist_file, PlaylistAsset & playlist_data, std::vector<PlaylistBucketList> & bucket_list);

  static void AddUser(const PlaylistBucketUserList & user, const UserZoneInfo & zone_info, uint32_t playlist_mask,
                      PlaylistAsset & playlist_data, std::vector<PlaylistBucketList> & bucket_list);
  static void RemoveUser(DDSKey user, DDSKey random_id, PlaylistAsset & playlist_data, std::vector<PlaylistBucketList> & bucket_list);

  void RefillMatches();
  void CreateNewMatches();
  void CreatePartialMatchesIfWaitingTooLong();

  bool FindMatch(int zone, PlaylistAsset & playlist_data,
          std::vector<PlaylistBucketList> & bucket_list, RefillGameList * refill_list, LobbyGameType type);

  bool CreatePartialMatch(DDSKey user_id);
  void FinalizeGame(GeneratedGame & game, int zone, int playlist, const std::vector<int> & team_sizes, PlaylistAsset & playlist_data,
                    std::vector<PlaylistBucketList> & bucket_list, RefillGameList * refill_list, LobbyGameType type);

  void SendGameInfo(DDSKey user_id, DDSKey endpoint_id, DDSKey game_id,
          int team, DDSKey matchmaker_random_id, LobbyGameType game_type);

  static bool BuildGameFromUsers(const PlaylistBucket & bucket, GeneratedGame & out_game, const std::vector<int> & team_sizes);


private:

  PlaylistAsset m_CasualPlaylist;
  PlaylistAsset m_CompetitivePlaylist;

  std::vector<PlaylistBucketList> m_CasualBuckets;
  std::vector<PlaylistBucketList> m_CompetitiveBuckets;

  std::vector<RefillGameList> m_CasualRefillGames;

private:
  STORM_REFL_IGNORE DDSObjectInterface & m_Interface;
};

