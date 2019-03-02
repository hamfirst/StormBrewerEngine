
#include <HurricaneDDS/DDSDatabaseConnection.h>
#include <HurricaneDDS/DDSResponderCall.h>

#include <StormData/StormDataJson.h>

#include "BanList.refl.meta.h"

#ifdef ENABLE_BAN_LIST

STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(BanListElement);


bool MatchStr(const char *first, const char * second)
{
  if (*first == '\0' && *second == '\0')
  {
    return true;
  }

  if (*first == '*' && *(first + 1) != '\0' && *second == '\0')
  {
    return false;
  }

  if (*first == '?' || *first == *second)
  {
    return MatchStr(first + 1, second + 1);
  }

  if (*first == '*')
  {
    return MatchStr(first + 1, second) || MatchStr(first, second + 1);
  }

  return false;
}


BanList::BanList(DDSObjectInterface & obj_interface) :
  m_Interface(obj_interface)
{
  DDSDatabaseSettings settings;
  settings.DatabaseName = DATABASE_NAME;

  DDSDatabaseConnection connection(settings);
  auto result = connection.QueryDatabaseByKey(0, "bans");

  if (result.first == 0)
  {
    StormReflParseJson(m_List, result.second.data());
  }
}

void BanList::Ban(BanType type, std::string data, int duration, std::string message)
{
  if (duration == 0)
  {
    return;
  }

  BanListElement elem;
  elem.m_Type = type;
  elem.m_Data = data;
  elem.m_Expiration = (int)time(NULL) + duration;
  elem.m_Message = message;

  m_List.EmplaceBack(elem);

  SaveBanList();
}

void BanList::Unban(int ban_index)
{
  if (m_List.RemoveAt(ban_index))
  {
    SaveBanList();
  }
}

void BanList::UnbanMatch(std::string match_str)
{
  std::vector<std::size_t> dead_bans;

  for (auto elem : m_List)
  {
    if (MatchStr(elem.second.m_Data.c_str(), match_str.data()))
    {
      dead_bans.push_back(elem.first);
    }
  }

  if (dead_bans.size() > 0)
  {
    for (auto index : dead_bans)
    {
      m_List.RemoveAt(index);
    }

    SaveBanList();
  }
}

void BanList::GetInfo(DDSResponder & responder)
{
  CleanupExpiredBans();

  std::string data = "Ban List:\n";
  for (auto elem : m_List)
  {
    auto & ban = elem.second;

    time_t t = ban.m_Expiration;
    char time_str[128];
    strftime(time_str, sizeof(time_str), "%y-%m-%d %H:%M:%S", localtime(&t));
    data += time_str;
    data += ' ';
    data += ban.m_Type.ToString();
    data += ' ';
    data += ban.m_Data.ToString();
    data += ' ';
    data += ban.m_Message.ToString();

    data += '\n';
  }

  DDSResponderCall(responder, data);
}

bool BanList::CheckBanList(const char * remote_ip, const char * remote_host, uint64_t platform_id) const
{
  auto cur_time = time(NULL);

  std::string platform_id_str = std::to_string(platform_id);

  for (auto elem : m_List)
  {
    auto & ban = elem.second;

    if (ban.m_Expiration < (int)cur_time)
    {
      continue;
    }

    if (ban.m_Type == BanType::kRemoteIp)
    {
      if (MatchStr(ban.m_Data.data(), remote_ip))
      {
        return true;
      }
    }
    else if (ban.m_Type == BanType::kRemoteHost)
    {
      if (MatchStr(ban.m_Data.data(), remote_host))
      {
        return true;
      }
    }
    else if (ban.m_Type == BanType::kPlatformId)
    {
      if (MatchStr(ban.m_Data.data(), platform_id_str.data()))
      {
        return true;
      }
    }
  }

  return false;
}


void BanList::SaveBanList()
{
  DDSDatabaseSettings settings;
  settings.DatabaseName = DATABASE_NAME;

  DDSDatabaseConnection connection(settings);
  connection.QueryDatabaseUpsert(0, "bans", StormReflEncodeJson(m_List));
}

void BanList::CleanupExpiredBans()
{
  std::vector<std::size_t> dead_bans;

  auto cur_time = time(NULL);

  for (auto elem : m_List)
  {
    auto & ban = elem.second;

    if (ban.m_Expiration < (int)cur_time)
    {
      dead_bans.push_back(elem.first);
    }
  }

  if (dead_bans.size() > 0)
  {
    for (auto index : dead_bans)
    {
      m_List.RemoveAt(index);
    }

    SaveBanList();
  }
}

#endif