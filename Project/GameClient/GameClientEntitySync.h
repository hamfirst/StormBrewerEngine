#pragma once

#include "Foundation/Common.h"

#include "Engine/Entity/EntityHandle.h"

#include "Runtime/ServerObject/ServerObjectManager.h"

class GameContainer;
class GameClientInstanceContainer;

class GameClientEntitySync
{
public:
  GameClientEntitySync(GameContainer & game);
  ~GameClientEntitySync();

  void ActivateEntities();
  void Sync(GameClientInstanceContainer & instance_container);
  void DestroyAll();

  void SendEntityEvent(int entity_index, uint32_t type_name_hash, const void * ev);

private:

  bool IsLocal(NotNullPtr<ServerObject> server_obj, GameWorld & world);
  void SyncEntityList(SparseList<EntityHandle> & entity_list, ServerObjectManager & obj_manager,
                      GameWorld & world, bool process_local, bool process_nonlocal);

private:
  GameContainer & m_GameContainer;
  SparseList<EntityHandle> m_HistoryEntities;
  SparseList<EntityHandle> m_CurrentEntities;

  bool m_ActivateEntities = false;
};

