
#include "GameClient/GameClientLatencyChecker.h"

#include <cstdio>

void GameClientLatencyChecker::Start()
{
  m_StartTime = std::chrono::system_clock::now();

  m_Requests.clear();
  for(int index = 0; index < kNumProjectZones; ++index)
  {
    m_LatencyResults.m_Latency[index] = 0;

    m_Requests.emplace_back(g_ProjectZoneUrls[index]);
    m_Requests.back().SetCallback([this, index](const HttpRequest &){ HandleResponse(index); });
  }
}

bool GameClientLatencyChecker::IsComplete() const
{
  for(int index = 0; index < kNumProjectZones; ++index)
  {
    if(m_LatencyResults.m_Latency[index] == 0)
    {
      return false;
    }
  }

  return true;
}

const GameClientLatencyResults & GameClientLatencyChecker::GetResults()
{
  return m_LatencyResults;
}

void GameClientLatencyChecker::HandleResponse(int index)
{
  auto time_since_start = std::chrono::system_clock::now() - m_StartTime;
  m_LatencyResults.m_Latency[index] = std::chrono::duration_cast<std::chrono::milliseconds>(time_since_start).count() / 2;

  if(IsComplete())
  {
    m_Requests.clear();
  }
}
