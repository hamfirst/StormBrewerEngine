#pragma once

#include <StormNet/NetReflectionStruct.h>
#include <StormNet/NetReflectionTypeDatabase.h>

#include <StormNet/NetReflection.h>

#include "Game/GameNetworkData.refl.h"
#include "Server/ServerObject/ServerObjectManager.h"
#include "Server/ServerObject/ServerObjectSerialzie.h"

struct GameFullState
{
  NET_REFL;
  STORM_REFL_NODEFAULT;

  ServerObjectManager m_ServerObjectManager;
  GameInstanceData m_GlobalData;

};

