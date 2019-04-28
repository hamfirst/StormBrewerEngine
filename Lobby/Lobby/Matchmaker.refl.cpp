
#include "HurricaneDDS/DDSDatabaseConnection.h"
#include "HurricaneDDS/DDSResponderCall.h"

#include "StormData/StormDataJson.h"

#include "Foundation/Document/Document.h"
#include "Foundation/Document/DocumentCompiler.h"
#include "Foundation/Document/DocumentDefaultLoader.h"

#include "LobbyShared/LobbyGameFuncs.h"

#include "Matchmaker.refl.meta.h"
#include "Game.refl.meta.h"
#include "User.refl.meta.h"
#include "LobbyLevelList.refl.h"
#include "ServerManager.refl.h"


Matchmaker::Matchmaker(DDSObjectInterface & obj_interface) :
        m_Interface(obj_interface)
{
  m_CasualBuckets.resize(kNumProjectZones);
  m_CompetitiveBuckets.resize(kNumProjectZones);
  m_CasualRefillGames.resize(kNumProjectZones);
}

void Matchmaker::Initialize()
{
  ReadPlaylistFile("./CasualPlaylist.txt", m_CasualPlaylist, m_CasualBuckets);
  ReadPlaylistFile("./CompetitivePlaylist.txt", m_CompetitivePlaylist, m_CompetitiveBuckets);
}

void Matchmaker::Update()
{
  RefillMatches();
  CreateNewMatches();
  CreatePartialMatchesIfWaitingTooLong();
}

void Matchmaker::AddCasualUser(const PlaylistBucketUserList & user, const UserZoneInfo & zone_info, uint32_t playlist_mask)
{
  DDSLog::LogInfo("Adding casual user %zu", user.m_PrimaryUser.m_UserKey);
  AddUser(user, zone_info, playlist_mask, m_CasualPlaylist, m_CasualBuckets);

}

void Matchmaker::AddCompetitiveUser(const PlaylistBucketUserList & user, const UserZoneInfo & zone_info, uint32_t playlist_mask)
{
  DDSLog::LogInfo("Adding competitive user %zu", user.m_PrimaryUser.m_UserKey);
  AddUser(user, zone_info, playlist_mask, m_CompetitivePlaylist, m_CompetitiveBuckets);
}

void Matchmaker::RemoveCasualUser(DDSKey user, DDSKey random_id)
{
  RemoveUser(user, random_id, m_CasualPlaylist, m_CasualBuckets);
}

void Matchmaker::RemoveCompetitiveUser(DDSKey user, DDSKey random_id)
{
  RemoveUser(user, random_id, m_CompetitivePlaylist, m_CompetitiveBuckets);
}

void Matchmaker::NotifyPlayerLeftCasualGame(DDSKey game_id, int team, int zone)
{
  DDSLog::LogInfo("Player left casual game");
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
        m_Interface.Call(&Game::MatchmakerDestroyGame, game_id);
        refill_list.erase(itr);
      }
      return;
    }
  }
}

void Matchmaker::STORM_REFL_FUNC NotifyGameAcceptingPlayers(DDSKey game_id, int zone, bool accepting_players)
{
  DDSLog::LogInfo("Player left casual game");
  auto & refill_list = m_CasualRefillGames[zone].m_Games;
  for(auto itr = refill_list.begin(); itr != refill_list.end(); ++itr)
  {
    if(itr->m_GameId == game_id)
    {
      itr->m_AllowRefill = accepting_players;
      return;
    }
  }
}

void Matchmaker::CancelMatchmakingForUser(DDSKey user, DDSKey random_id)
{
  DDSLog::LogInfo("Matchmaking cancelled");
  RemoveCasualUser(user, random_id);
  RemoveCompetitiveUser(user, random_id);
}

void Matchmaker::ReadPlaylistFile(czstr playlist_file, PlaylistAsset & playlist_data, std::vector<PlaylistBucketList> & bucket_list)
{
  DocumentDefaultLoader loader;
  DocumentCompiler document_compiler(&loader);

  auto document = document_compiler.GetDocument(playlist_file);
  auto document_json = document->GetDocumentJson();

  StormReflParseJson(playlist_data, document_json.c_str());

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
                         PlaylistAsset & playlist_data, std::vector<PlaylistBucketList> & bucket_list)
{
  for(int zone = 0; zone < kNumProjectZones; ++zone)
  {
#ifdef ENABLE_GOOGLE_CLOUD
    if(zone_info.m_Latencies[zone] > kMaxLatency)
    {
      continue;
    }
#endif

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

void Matchmaker::RemoveUser(DDSKey user, DDSKey random_id, PlaylistAsset & playlist_data, std::vector<PlaylistBucketList> & bucket_list)
{
  for(int zone = 0; zone < kNumProjectZones; ++zone)
  {
    for (int playlist = 0; playlist < (int)playlist_data.m_Elements.size(); ++playlist)
    {
      auto & bucket = bucket_list[zone].m_Buckets[playlist];
      for(auto itr = bucket.m_Users.begin(); itr != bucket.m_Users.end(); ++itr)
      {
        if(itr->m_PrimaryUser.m_UserKey == user && itr->m_MatchmakerRandomId == random_id)
        {
          bucket.m_Users.erase(itr);
          break;
        }
      }
    }
  }
}

void Matchmaker::RefillMatches()
{
  for(int zone = 0; zone < kNumProjectZones; ++zone)
  {
    for (int playlist = 0; playlist < (int)m_CasualPlaylist.m_Elements.size(); ++playlist)
    {
      auto & bucket = m_CasualBuckets[zone].m_Buckets[playlist];
      for(auto & game : m_CasualRefillGames[zone].m_Games)
      {
        if(game.m_AllowRefill == false)
        {
          continue;
        }

        bool found_match;

        do
        {
          found_match = false;
          for (auto itr = bucket.m_Users.begin(), end = bucket.m_Users.end(); itr != end; ++itr)
          {
            auto & user = *itr;

            int players_in_bucket = (int)user.m_ExtraUsers.size() + 1;
            if (game.m_Playlist == playlist)
            {
              for (int team = 0; team < kMaxTeams; ++team)
              {
                auto players_on_team = game.m_PlayersAssigned[team] - game.m_PlayersLeft[team];
                auto spots_available = game.m_PlayersNeeded[team] - players_on_team;

                if (spots_available >= players_in_bucket)
                {
                  SendGameInfo(user.m_PrimaryUser.m_UserKey, user.m_PrimaryUser.m_EndpointId,
                               game.m_GameId, team, user.m_MatchmakerRandomId, LobbyGameType::kCasual);

                  for(auto & extra_user : user.m_ExtraUsers)
                  {
                    SendGameInfo(extra_user.m_UserKey, extra_user.m_EndpointId, game.m_GameId,
                                 team, user.m_MatchmakerRandomId, LobbyGameType::kCasual);
                  }

                  game.m_PlayersAssigned[team] += players_in_bucket;
                  bucket.m_Users.erase(itr);

                  found_match = true;

                  DDSLog::LogInfo("Found refill game!");
                  break;
                }
              }

              if(found_match)
              {
                break;
              }
            }
          }
        }
        while(found_match);
      }
    }
  }
}

void Matchmaker::CreateNewMatches()
{
  bool found_match;

  do
  {
    found_match = false;

    for(int zone = 0; zone < kNumProjectZones; ++zone)
    {
      if(FindMatch(zone, m_CasualPlaylist, m_CasualBuckets, m_CasualRefillGames.data(), LobbyGameType::kCasual))
      {
        found_match = true;
        break;
      }

      if(FindMatch(zone, m_CompetitivePlaylist, m_CompetitiveBuckets, nullptr, LobbyGameType::kCompetitive))
      {
        found_match = true;
        break;
      }
    }
  }
  while(found_match);
}

void Matchmaker::CreatePartialMatchesIfWaitingTooLong()
{
  bool found_match;
  auto threshold_time = m_Interface.GetNetworkTime() - kMaxTimeInMatchmaker;

  do
  {
    found_match = false;

    for(int zone = 0; zone < kNumProjectZones; ++zone)
    {
      for(auto & bucket : m_CasualBuckets[zone].m_Buckets)
      {
        for(auto & user : bucket.m_Users)
        {
          if(user.m_TimePutInMatchmaker < threshold_time)
          {
            if(CreatePartialMatch(user.m_PrimaryUser.m_UserKey))
            {
              found_match = true;
            }
          }
        }

        if(found_match)
        {
          break;
        }
      }

      if(found_match)
      {
        break;
      }
    }

  }
  while(found_match);
}

bool Matchmaker::FindMatch(int zone, PlaylistAsset & playlist_data,
        std::vector<PlaylistBucketList> & bucket_list, RefillGameList * refill_list, LobbyGameType type)
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
    std::vector<int> team_sizes;
    team_sizes.resize(kMaxTeams);

    for(int team = 0; team < kMaxTeams; ++team)
    {
      team_sizes[team] = playlist_data.m_Elements[playlist].m_TeamSizes[team];
    }

    if(BuildGameFromUsers(bucket, game, team_sizes))
    {
      DDSLog::LogInfo("Found match");

      FinalizeGame(game, zone, playlist, team_sizes, playlist_data, bucket_list, refill_list, type);
      return true;
    }
  }

  return false;
}

bool Matchmaker::CreatePartialMatch(DDSKey user_id)
{
  std::vector<std::pair<int, int>> potential_games;
  int best_user_count = 0;

  for(int zone = 0; zone < kNumProjectZones; ++zone)
  {
    for(int playlist = 0, end = m_CasualBuckets[zone].m_Buckets.size(); playlist < end; ++playlist)
    for (auto & bucket : m_CasualBuckets[zone].m_Buckets)
    {
      bool found_user = false;
      for (auto & user : bucket.m_Users)
      {
        if (user.m_PrimaryUser.m_UserKey == user_id)
        {
          found_user = true;
          break;
        }
      }

      if(found_user)
      {
        int num_users_in_bucket = 0;
        for (auto & user : bucket.m_Users)
        {
          num_users_in_bucket += 1 + user.m_ExtraUsers.size();
        }

        if(num_users_in_bucket > best_user_count)
        {
          potential_games.clear();
          best_user_count = num_users_in_bucket;
        }

        if(num_users_in_bucket >= best_user_count)
        {
          potential_games.emplace_back(std::make_pair(zone, playlist));
        }
      }
    }
  }

  if(potential_games.size() == 0)
  {
    return false;
  }

  auto & game_info = potential_games[DDSGetRandomNumber() % potential_games.size()];

  int zone = game_info.first;
  int playlist = game_info.second;

  auto & bucket = m_CasualBuckets[zone].m_Buckets[playlist];

  std::vector<int> team_sizes;
  team_sizes.resize(kMaxTeams);

  for(int team = 0; team < kMaxTeams; ++team)
  {
    team_sizes[team] = m_CasualPlaylist.m_Elements[playlist].m_TeamSizes[team];
  }

  GeneratedGame game;
  for(auto & user_info : bucket.m_Users)
  {
    int team_with_lowest_players = 0;
    int lowest_players = game.m_Users[0].size();

    for(int team = 1; team < kMaxTeams; ++team)
    {
      auto team_size = game.m_Users[team].size();
      if(team_size < lowest_players)
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
      user_data.m_MatchmakerRandomId = user_info.m_MatchmakerRandomId;

      game.m_Users[team_with_lowest_players].emplace_back(user_data);

      for(auto & extra_user : user_info.m_ExtraUsers)
      {
        user_data.m_UserId = extra_user.m_UserKey;
        user_data.m_EndpointId = extra_user.m_EndpointId;
        user_data.m_MatchmakerRandomId = user_info.m_MatchmakerRandomId;

        game.m_Users[team_with_lowest_players].emplace_back(user_data);
      }
    }

    bool all_teams_maxed = true;
    for(int team = 0; team < kMaxTeams; ++team)
    {
      auto team_size = game.m_Users[team].size();
      if(team_size < team_sizes[team])
      {
        all_teams_maxed = false;
        break;
      }
    }

    if(all_teams_maxed)
    {
      break;
    }
  }

  FinalizeGame(game, zone, playlist, team_sizes, m_CasualPlaylist, m_CasualBuckets, m_CasualRefillGames.data(), LobbyGameType::kCasual);
  return true;
}

void Matchmaker::FinalizeGame(GeneratedGame & game, int zone, int playlist, const std::vector<int> & team_sizes, PlaylistAsset & playlist_data,
                              std::vector<PlaylistBucketList> & bucket_list, RefillGameList * refill_list, LobbyGameType type)
{
  int mode_index = DDSGetRandomNumber() % playlist_data.m_Elements[playlist].m_GameModes.size();
  auto & game_mode = playlist_data.m_Elements[playlist].m_GameModes[mode_index];

  DDSKey game_id = DDSGetRandomNumber64();

  if(type == LobbyGameType::kCompetitive)
  {
    m_Interface.Call(&Game::InitCompetitiveGame, game_id, game_mode, game, zone, team_sizes);
  }
  else
  {
    m_Interface.Call(&Game::InitCasualGame, game_id, game_mode, game, zone, team_sizes);
  }

  for(int team = 0; team < kMaxTeams; ++team)
  {
    for(auto & user : game.m_Users[team])
    {
      SendGameInfo(user.m_UserId, user.m_EndpointId, game_id, team, user.m_MatchmakerRandomId, type);

      RemoveCompetitiveUser(user.m_UserId, user.m_MatchmakerRandomId);
      RemoveCasualUser(user.m_UserId, user.m_MatchmakerRandomId);
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
      refill_game.m_PlayersNeeded[team] = team_sizes[team];
    }

    refill_list[zone].m_Games.emplace_back(refill_game);
  }
}

void Matchmaker::SendGameInfo(DDSKey user_id, DDSKey endpoint_id, DDSKey game_id,
        int team, DDSKey matchmaker_random_id, LobbyGameType game_type)
{
  DDSLog::LogInfo("Sending match info to %zu", user_id);
  UserGameJoinInfo join_info;
  join_info.m_EndpointId = endpoint_id;
  join_info.m_Observer = false;
  join_info.m_IntendedType = game_type;
  join_info.m_AssignedTeam = team;
  join_info.m_MatchmakerRandomId = matchmaker_random_id;

  m_Interface.Call(&User::JoinGameByMatchmaker, user_id, game_id, matchmaker_random_id, join_info);
}

bool Matchmaker::BuildGameFromUsers(const PlaylistBucket & bucket, GeneratedGame & out_game, const std::vector<int> & team_sizes)
{
  for(auto & user_info : bucket.m_Users)
  {
    int team_with_lowest_players = 0;
    int lowest_players = out_game.m_Users[0].size();

    for(int team = 1; team < kMaxTeams; ++team)
    {
      auto team_size = out_game.m_Users[team].size();
      if(team_size < lowest_players)
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
      user_data.m_MatchmakerRandomId = user_info.m_MatchmakerRandomId;

      out_game.m_Users[team_with_lowest_players].emplace_back(user_data);

      for(auto & extra_user : user_info.m_ExtraUsers)
      {
        user_data.m_UserId = extra_user.m_UserKey;
        user_data.m_EndpointId = extra_user.m_EndpointId;
        user_data.m_MatchmakerRandomId = user_info.m_MatchmakerRandomId;

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
