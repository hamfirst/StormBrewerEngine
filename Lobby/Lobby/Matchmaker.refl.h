#pragma once

#include "StormRefl/StormRefl.h"
#include "StormData/StormDataTypes.h"

#include "HurricaneDDS/DDSDataObject.h"

#include "Game/GameNetworkData.refl.h"

#include "SharedTypes.refl.h"
#include "LobbyConfig.h"

struct PlaylistDatabaseElement
{
  STORM_REFL;

  std::string m_Name;
  std::vector<GameInitSettings> m_GameModes;
  int m_TeamSizes[kMaxTeams] = {};
  bool m_AllowParties = false;
  int m_TotalGameSize = 0;
};

struct PlaylistDatabaseObj
{
  STORM_REFL;
  std::vector<PlaylistDatabaseElement> m_Elements;
};

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

  void STORM_REFL_FUNC RemoveCasualUser(DDSKey user);
  void STORM_REFL_FUNC RemoveCompetitiveUser(DDSKey user);

  void STORM_REFL_FUNC NotifyPlayerLeftCasualGame(DDSKey game_id, int team, int zone);

private:

  static void ReadPlaylistFile(czstr playlist_file, PlaylistDatabaseObj & playlist_data, std::vector<PlaylistBucketList> & bucket_list);

  static void AddUser(const PlaylistBucketUserList & user, const UserZoneInfo & zone_info, uint32_t playlist_mask,
               PlaylistDatabaseObj & playlist_data, std::vector<PlaylistBucketList> & bucket_list);
  static void RemoveUser(DDSKey user, PlaylistDatabaseObj & playlist_data, std::vector<PlaylistBucketList> & bucket_list);

  bool FindMatch(int zone, PlaylistDatabaseObj & playlist_data, std::vector<PlaylistBucketList> & bucket_list, RefillGameList * refill_list);
  static bool BuildGameFromUsers(const PlaylistBucket & bucket, GeneratedGame & out_game, int * team_sizes);

private:

  PlaylistDatabaseObj m_CasualPlaylist;
  PlaylistDatabaseObj m_CompetitivePlaylist;

  std::vector<PlaylistBucketList> m_CasualBuckets;
  std::vector<PlaylistBucketList> m_CompetitiveBuckets;

  std::vector<RefillGameList> m_CasualRefillGames;

private:
  STORM_REFL_IGNORE DDSObjectInterface & m_Interface;
};

