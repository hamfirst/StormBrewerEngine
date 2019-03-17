#pragma once

#include <HurricaneDDS/DDSDataObject.h>

#include "GameData.refl.h"
#include "LobbyConfig.h"

#ifdef ENABLE_REWARDS

struct RewardsRank
{
  STORM_REFL;

  int m_XP;
  UserRewards m_Rewards;
};

struct RewardsDatabaseObj
{
  STORM_REFL;

  std::vector<RewardsRank> m_Ranks;
};

struct Rewards
{
public:
  DDS_SHARED_OBJECT;

  Rewards(DDSObjectInterface & obj_interface);

  void Initialize();

  void STORM_REFL_FUNC FetchRewards(DDSResponder & responder);

public:

  void Update(int input_xp, int & xp, int & level, std::vector<UserRewards> & outp_rewards) const;

  RewardsDatabaseObj m_Info;

private:
  STORM_REFL_IGNORE DDSObjectInterface & m_Interface;
};

#endif
