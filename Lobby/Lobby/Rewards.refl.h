#pragma once

#include <HurricaneDDS/DDSDataObject.h>

#include "GameData.refl.h"
<<<<<<< HEAD
=======
#include "LobbyConfig.h"

#ifdef ENABLE_REWARDS
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c

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
<<<<<<< HEAD
=======

#endif
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
