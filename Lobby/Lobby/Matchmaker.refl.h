#pragma once

#include <StormRefl/StormRefl.h>
#include <StormData/StormDataTypes.h>

#include <HurricaneDDS/DDSDataObject.h>

#include "LobbyConfig.h"

struct Matchmaker
{
public:
  DDS_SHARED_OBJECT;

  Matchmaker(DDSObjectInterface & iface);


public:


private:
  STORM_REFL_IGNORE DDSObjectInterface & m_Interface;
};

#endif
