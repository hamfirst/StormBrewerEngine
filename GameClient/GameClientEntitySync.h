#pragma once

#include "Foundation/Common.h"

#include "Engine/Entity/EntityHandle.h"

#include "Server/ServerObject/ServerObjectManager.h"

class GameContainer;

class GameClientEntitySync
{
public:
  GameClientEntitySync(GameContainer & game);
  ~GameClientEntitySync();

  void Sync(ServerObjectManager & obj_manager);
  void DestroyAll();

  void SendEntityEvent(int entity_index, uint32_t type_name_hash, void * ev);

private:
  GameContainer & m_GameContainer;
  SparseList<EntityHandle> m_Entities;
};

