#pragma once

#include "GameShared/GameSharedCommon.h"
#include "GameShared/GameWorld.h"
#include "Runtime/ServerObject/ServerObject.h"

class GameServerObjectBase;

class CVCPushSystem
{
public:

  void SetCharacterCVCPosition(const Box & box, NotNullPtr<GameServerObjectBase> obj);
  void ProcessCVC(GameWorld & world);

  void Clear();

private:

  struct CVCData
  {
    ServerObjectHandle m_Handle;
    Box m_Box;
  };

  std::vector<CVCData> m_Data;
};
