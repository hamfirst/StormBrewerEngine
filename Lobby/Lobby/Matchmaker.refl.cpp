
#include "HurricaneDDS/DDSDatabaseConnection.h"
#include "HurricaneDDS/DDSResponderCall.h"

#include "StormData/StormDataJson.h"

#include "LobbyShared/LobbyGameFuncs.h"

#include "Matchmaker.refl.meta.h"
#include "Game.refl.meta.h"
#include "User.refl.meta.h"
#include "LobbyLevelList.refl.h"


Matchmaker::Matchmaker(DDSObjectInterface & obj_interface) :
        m_Interface(obj_interface)
{
  m_CasualBuckets.resize(kNumProjectZones);
  m_CompetitiveBuckets.resize(kNumProjectZones);
  m_CasualRefillGames.resize(kNumProjectZones);
}

void Matchmaker::Initialize()
{
  ReadPlaylistFile("Config/casual_playlist.txt", m_CasualPlaylist, m_CasualBuckets);
  ReadPlaylistFile("Config/competitive_playlist.txt", m_CompetitivePlaylist, m_CompetitiveBuckets);
}

void Matchmaker::Update()
{
  for(int zone = 0; zone < kNumProjectZones; ++zone)
  {
    for (int playlist = 0; playlist < (int)m_CasualPlaylist.m_Elements.size(); ++playlist)
    {
      auto & bucket = m_CasualBuckets[zone].m_Buckets[playlist];

      for(auto & user : bucket.m_Users)
      {

      }
    }
  }

  bool found_match;

  do
  {
    found_match = false;

    for(int zone = 0; zone < kNumProjectZones; ++zone)
    {
      if(FindMatch(zone, m_CasualPlaylist, m_CasualBuckets, m_CasualRefillGames.data()))
      {
        found_match = true;
        break;
      }

      if(FindMatch(zone, m_CompetitivePlaylist, m_CompetitiveBuckets, nullptr))
      {
        found_match = true;
        break;
      }
    }
  }
  while(found_match);
}

void Matchmaker::AddCasualUser(const PlaylistBucketUserList & user, const UserZoneInfo & zone_info, uint32_t playlist_mask)
{
  AddUser(user, zone_info, playlist_mask, m_CasualPlaylist, m_CasualBuckets);
}

void Matchmaker::AddCompetitiveUser(const PlaylistBucketUserList & user, const UserZoneInfo & zone_info, uint32_t playlist_mask)
{
  AddUser(user, zone_info, playlist_mask, m_CompetitivePlaylist, m_CompetitiveBuckets);
}

void Matchmaker::RemoveCasualUser(DDSKey user)
{
  RemoveUser(user, m_CasualPlaylist, m_CasualBuckets);
}

void Matchmaker::RemoveCompetitiveUser(DDSKey user)
{
  RemoveUser(user, m_CompetitivePlaylist, m_CompetitiveBuckets);
}

void Matchmaker::NotifyPlayerLeftCasualGame(DDSKey game_id, int team, int zone)
{
  auto & refill_list = m_CasualRefillGames[zone].m_Games;
  for(auto itr = refill_list.begin(); itr != refill_list.end(); ++itr)
  {
    if(itr->m_GameId == game_id)
    {
      itr->m_PlayersLeft[team]++;

      bool has_players = false;

      for(int test_team = 0; test_team < kMaxTeams; ++test_team)
      {
        if (itr->m_PlayersAssigned[test_team] != itr->m_PlayersLeft[test_team])
        {
          has_players = true;
          break;
        }
      }

      if(has_players == false)
      {
        m_Interface.Call(&Game::Cleanup, game_id);
        refill_list.erase(itr);
      }
      return;
    }
  }
}

void Matchmaker::ReadPlaylistFile(czstr playlist_file, PlaylistDatabaseObj & playlist_data, std::vector<PlaylistBucketList> & bucket_list)
{
  auto fp = fopen(playlist_file, "rt");
  assert(fp != nullptr);

  fseek(fp, 0, SEEK_END);
  auto size = ftell(fp);
  fseek(fp, 0, SEEK_SET);

  auto buffer = std::make_unique<char[]>(size + 1);
  fread(buffer.get(), 1, size, fp);
  fclose(fp);

  buffer[size] = 0;

  StormReflParseJson(playlist_data, buffer.get());

  for(auto & elem : playlist_data.m_Elements)
  {
    for(int zone = 0; zone < kNumProjectZones; ++zone)
    {
      bucket_list[zone].m_Buckets.emplace_back();
    }

    assert(elem.m_GameModes.size() > 0);
    for(auto & game_mode : elem.m_GameModes)
    {
      assert(game_mode.m_StageIndex < g_LobbyLevelList.GetNumLevels());

      auto & map_info = g_LobbyLevelList.GetLevelInfo(game_mode.m_StageIndex);
      auto max_players = GetMaxPlayers(map_info, game_mode);

      int total_players = 0;
      for(int team = 0; team < kMaxTeams; ++team)
      {
        total_players += elem.m_TeamSizes[team];
        assert(elem.m_TeamSizes[team] <= GetMaxTeamSize(team, map_info, game_mode));
      }

      assert(total_players <= max_players);
      elem.m_TotalGameSize = total_players;
    }
  }
}

void Matchmaker::AddUser(const PlaylistBucketUserList & user, const UserZoneInfo & zone_info, uint32_t playlist_mask,
                         PlaylistDatabaseObj & playlist_data, std::vector<PlaylistBucketList> & bucket_list)
{
  for(int zone = 0; zone < kNumProjectZones; ++zone)
  {
    if(zone_info.m_Latencies[zone] > kMaxLatency)
    {
      continue;
    }

    for(int playlist = 0; playlist < (int)playlist_data.m_Elements.size(); ++playlist)
    {
      if(playlist_data.m_Elements[playlist].m_AllowParties == false && user.m_ExtraUsers.size() > 0)
      {
        continue;
      }

      if((playlist_mask & (1U << playlist)) != 0)
      {
        bucket_list[zone].m_Buckets[playlist].m_Users.emplace_back(user);
      }
    }
  }
}

void Matchmaker::RemoveUser(DDSKey user, PlaylistDatabaseObj & playlist_data, std::vector<PlaylistBucketList> & bucket_list)
{
  for(int zone = 0; zone < kNumProjectZones; ++zone)
  {
    for (int playlist = 0; playlist < (int)playlist_data.m_Elements.size(); ++playlist)
    {
      auto & bucket = bucket_list[zone].m_Buckets[playlist];
      for(auto itr = bucket.m_Users.begin(); itr != bucket.m_Users.end(); ++itr)
      {
        if(itr->m_PrimaryUser.m_UserKey == user)
        {
          bucket.m_Users.erase(itr);
          break;
        }
      }
    }
  }
}

bool Matchmaker::FindMatch(int zone, PlaylistDatabaseObj & playlist_data, std::vector<PlaylistBucketList> & bucket_list, RefillGameList * refill_list)
{
  for (int playlist = 0; playlist < (int)playlist_data.m_Elements.size(); ++playlist)
  {
    auto & bucket = bucket_list[zone].m_Buckets[playlist];
    int users_in_bucket = 0;

    for (auto & user_list : bucket.m_Users)
    {
      users_in_bucket += 1 + user_list.m_ExtraUsers.size();
    }

    if(users_in_bucket < playlist_data.m_Elements[playlist].m_TotalGameSize)
    {
      continue;
    }

    GeneratedGame game;
    if(BuildGameFromUsers(bucket, game, playlist_data.m_Elements[playlist].m_TeamSizes))
    {
      int mode_index = DDSGetRandomNumber() % playlist_data.m_Elements[playlist].m_GameModes.size();
      auto & game_mode = playlist_data.m_Elements[playlist].m_GameModes[mode_index];

      DDSKey game_id = DDSGetRandomNumber64();
      m_Interface.Call(&Game::InitCompetitiveGame, game_id, game_mode, game, zone);

      for(int team = 0; team < kMaxTeams; ++team)
      {
        for(auto & user : game.m_Users[team])
        {
          UserGameJoinInfo join_info;
          join_info.m_EndpointId = user.m_EndpointId;
          join_info.m_Observer = false;
          join_info.m_IntendedType = LobbyGameType::kCompetitive;

          m_Interface.Call(&User::JoinGame, user.m_UserId, game_id, join_info);

          RemoveCompetitiveUser(user.m_UserId);
          RemoveCasualUser(user.m_UserId);
        }
      }

      if(refill_list)
      {
        RefillGame refill_game;
        refill_game.m_GameId = game_id;
        refill_game.m_Playlist = playlist;

        for(int team = 0; team < kMaxTeams; ++team)
        {
          refill_game.m_PlayersLeft[team] = 0;
          refill_game.m_PlayersAssigned[team] = game.m_Users[team].size();
          refill_game.m_PlayersNeeded[team] = game.m_Users[team].size();
        }

        refill_list[zone].m_Games.emplace_back(refill_game);
      }

      return true;
    }
  }

  return false;
}

bool Matchmaker::BuildGameFromUsers(const PlaylistBucket & bucket, GeneratedGame & out_game, int * team_sizes)
{
  for(auto & user_info : bucket.m_Users)
  {
    int team_with_lowest_players = 0;
    int lowest_players = 0;

    for(int team = 1; team < kMaxTeams; ++team)
    {
      auto team_size = out_game.m_Users[team].size();
      if(lowest_players < team_size)
      {
        team_with_lowest_players = team;
        lowest_players = team_size;
      }
    }

    if(lowest_players + user_info.m_ExtraUsers.size() + 1 <= team_sizes[team_with_lowest_players])
    {
      GeneratedGameUser user_data;
      user_data.m_UserId = user_info.m_PrimaryUser.m_UserKey;
      user_data.m_EndpointId = user_info.m_PrimaryUser.m_EndpointId;

      out_game.m_Users[team_with_lowest_players].emplace_back(user_data);

      for(auto & extra_user : user_info.m_ExtraUsers)
      {
        user_data.m_UserId = extra_user.m_UserKey;
        user_data.m_EndpointId = extra_user.m_EndpointId;

        out_game.m_Users[team_with_lowest_players].emplace_back(user_data);
      }
    }

    bool all_teams_maxed = true;
    for(int team = 0; team < kMaxTeams; ++team)
    {
      auto team_size = out_game.m_Users[team].size();
      if(team_size < team_sizes[team])
      {
        all_teams_maxed = false;
        break;
      }
    }

    if(all_teams_maxed)
    {
      return true;
    }
  }

  return false;
}
