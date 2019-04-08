#pragma once

#include "Foundation/Network/HttpRequest.h"

#include "ProjectSettings/ProjectZones.h"

#include <chrono>
#include <vector>

struct GameClientLatencyResults
{
  int m_Latency[kNumProjectZones] = { 0 };
};

class GameClientLatencyChecker
{
public:

  void Start();
  bool IsComplete() const;

  const GameClientLatencyResults & GetResults();

private:

  void HandleResponse(int index);

private:

  std::chrono::system_clock::time_point m_StartTime;
  std::vector<HttpRequest> m_Requests;

  GameClientLatencyResults m_LatencyResults;
};
