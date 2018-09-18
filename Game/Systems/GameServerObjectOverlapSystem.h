#pragma once

#include "Game/GameCommon.h"
#include "Runtime/Sprite/SpriteResource.h"

#include "Foundation/SparseList/SparseList.h"
#include "Foundation/CallList/CallList.h"

class ServerObjectManager;
class GameLogicContainer;

class GameServerObjectOverlapSystem
{
public:
  void RegisterObjectType(std::size_t object_type, NotNullPtr<SpritePtr> sprite, uint32_t data_name_hash);
  void RegisterObjectInteraction(std::size_t src_object_type, std::size_t dst_object_type);
  void CheckOverlaps(ServerObjectManager & obj_manager, GameLogicContainer & game_logic_container);

private:
  struct ObjectInfo
  {
    NotNullPtr<SpritePtr> m_Sprite;
    uint32_t m_DataNameHash;
    std::vector<std::size_t> m_DstTypes;
  };

  SparseList<ObjectInfo> m_ObjectInfo;
};

extern GameServerObjectOverlapSystem g_ServerObjectOverlapSystem;
extern PreMainCallList g_ServerObjectOverlapSystemRegister;
extern PreMainCallList g_ServerObjectOverlapSystemInteractionRegister;