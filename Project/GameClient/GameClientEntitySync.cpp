#include "GameClient/GameClientCommon.h"

#include "Engine/Entity/Entity.h"
#include "Engine/EngineState.h"

#include "Runtime/Entity/EntityResource.h"
#include "Runtime/ServerObject/ServerObject.h"

#include "GameClient/GameClientEntitySync.h"
#include "GameClient/GameContainer.h"


GameClientEntitySync::GameClientEntitySync(GameContainer & game) :
  m_GameContainer(game)
{

}

GameClientEntitySync::~GameClientEntitySync()
{
  DestroyAll();
}

void GameClientEntitySync::ActivateEntities()
{
  for (auto ent : m_HistoryEntities)
  {
    auto entity = ent.second.Resolve();
    if (entity)
    {
      entity->Activate();
    }
  }

  for (auto ent : m_CurrentEntities)
  {
    auto entity = ent.second.Resolve();
    if (entity)
    {
      entity->Activate();
    }
  }

  m_ActivateEntities = true;
}

bool GameClientEntitySync::IsLocal(NotNullPtr<ServerObject> server_obj, GameLogicContainer & game_container)
{
  auto associated_player = server_obj->GetAssociatedPlayer(game_container);

  if (associated_player)
  {
    auto instance_data = m_GameContainer.GetInstanceData();
    if (instance_data)
    {
      auto num_local_clients = instance_data->GetNumLocalData();

      for (std::size_t index = 0; index < num_local_clients; ++index)
      {
        auto & local_data = instance_data->GetClientLocalData(index);
        if (local_data.m_PlayerIndex == associated_player.Value())
        {
          return true;
        }
      }
    }
  }

  return false;
}

void GameClientEntitySync::SyncEntityList(SparseList<EntityHandle> & entity_list,
        ServerObjectManager & obj_manager, GameLogicContainer & game_container, bool process_local, bool process_nonlocal)
{
  auto & engine_state = m_GameContainer.GetEngineState();

  std::size_t last_index = 0;
  auto visitor = [&] (std::size_t index, NotNullPtr<ServerObject> obj)
  {
    auto is_local = IsLocal(obj, game_container);
    if(is_local && !process_local)
    {
      return;
    }

    if(!is_local && !process_nonlocal)
    {
      return;
    }

    EntityHandle cur_handle;
    if (entity_list.HasAt(index))
    {
      cur_handle = entity_list[index];
    }

    while (index != last_index)
    {
      if (entity_list.HasAt(last_index))
      {
        auto entity = entity_list[last_index].Resolve();
        if (entity)
        {
          entity->ServerDestroy();
          entity->Destroy();
        }
      }

      last_index++;
    }

    last_index++;

    auto entity_asset = obj->GetEntityBinding();
    auto entity = cur_handle.Resolve();

    if (entity_asset)
    {
      if (entity)
      {
        auto asset_hash = crc32lowercase(entity_asset);
        if (asset_hash == entity->GetAssetNameHash())
        {
          entity->m_ServerObjectManager = &obj_manager;
          entity->ServerUpdate();
          return;
        }

        entity->ServerDestroy();
        entity->Destroy();
      }

      auto entity_resource = EntityResource::Load(entity_asset);
      if (entity_resource.GetResource()->IsLoaded() == false)
      {
        ASSERT(false, "Sync object bound asset must be preloaded");
        return;
      }

      auto new_entity = engine_state.CreateEntity(entity_resource.GetResource(), obj, &obj_manager, m_ActivateEntities);
      entity_list.InsertAt(index, new_entity->GetHandle());
      new_entity->ServerUpdate();
    }
    else
    {
      if (entity)
      {
        entity->ServerDestroy();
        entity->Destroy();
      }
    }
  };

  obj_manager.VisitObjects(visitor);

  while ((int)last_index <= entity_list.HighestIndex())
  {
    if (entity_list.HasAt(last_index))
    {
      auto entity = entity_list[last_index].Resolve();
      if (entity)
      {
        entity->ServerDestroy();
        entity->Destroy();
      }
    }

    last_index++;
  }
}

void GameClientEntitySync::Sync(GameClientInstanceContainer & instance_container)
{
#ifdef NET_SYNC_OLD_STATE

  auto history_container = instance_container.GetLogicContainer(NET_SYNC_HISTORY_FRAMES);
  auto current_container = instance_container.GetLogicContainer();

  SyncEntityList(m_HistoryEntities, history_container.GetObjectManager(), history_container, false, true);
  SyncEntityList(m_CurrentEntities, current_container.GetObjectManager(), current_container, true, false);
#else
  SyncEntityList(m_CurrentEntities, current_container.GetObjectManager(), current_container, true, true);
#endif
}

void GameClientEntitySync::DestroyAll()
{
  for (auto ent : m_HistoryEntities)
  {
    ent.second.Destroy();
  }

  for (auto ent : m_CurrentEntities)
  {
    ent.second.Destroy();
  }

  m_HistoryEntities.Clear();
  m_CurrentEntities.Clear();
}

void GameClientEntitySync::SendEntityEvent(int entity_index, uint32_t type_name_hash, const void * ev)
{
//  auto entity = m_Entities[entity_index].Resolve();
//
//  if (entity)
//  {
//    entity->TriggerEventHandler(type_name_hash, ev, EventMetaData(&m_GameContainer));
//  }
}

