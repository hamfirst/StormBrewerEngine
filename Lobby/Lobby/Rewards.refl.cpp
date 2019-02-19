

#include <HurricaneDDS/DDSDatabaseConnection.h>
#include <HurricaneDDS/DDSResponderCall.h>

#include <StormData/StormDataJson.h>

#include "Rewards.refl.meta.h"
#include "ProjectSettings.h"

bool g_LoadRewards = false;

Rewards::Rewards(DDSObjectInterface & obj_interface) :
  m_Interface(obj_interface)
{
  DDSDatabaseSettings settings;
  settings.DatabaseName = kDatabaseName;

  if (g_LoadRewards)
  {
    FILE * fp = fopen("rewards.txt", "rt");
    if (fp != nullptr)
    {
      fseek(fp, 0, SEEK_END);
      auto size = ftell(fp);
      fseek(fp, 0, SEEK_SET);

      auto buffer = std::make_unique<char[]>(size + 1);
      fread(buffer.get(), 1, size, fp);
      fclose(fp);

      buffer[size] = 0;

      StormReflParseJson(m_Info, buffer.get());
    }
  }
  else
  {
    DDSDatabaseConnection connection(settings);
    auto result = connection.QueryDatabaseByKey(0, "rewards");

    if (result.first == 0)
    {
      RewardsDatabaseObj db_info;
      StormReflParseJson(db_info, result.second.data());

      m_Info = db_info;
    }
  }
}

void Rewards::Update(int input_xp, int & xp, int & level, std::vector<UserRewards> & outp_rewards) const
{
  while (true)
  {
    if (level >= (int)m_Info.m_Ranks.size())
    {
      xp += input_xp;
      return;
    }

    if (xp + input_xp >= m_Info.m_Ranks[level].m_XP)
    {
      outp_rewards.push_back(m_Info.m_Ranks[level].m_Rewards);

      input_xp -= m_Info.m_Ranks[level].m_XP - xp;
      xp = 0;
      level++;
    }
    else
    {
      xp += input_xp;
      return;
    }
  }
}

void Rewards::FetchRewards(DDSResponder & responder)
{
  DDSResponderCall(responder, StormReflEncodeJson(m_Info));
}
