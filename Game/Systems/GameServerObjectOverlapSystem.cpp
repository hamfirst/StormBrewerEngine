
#include "Game/GameCommon.h"
#include "Game/Systems/GameServerObjectOverlapSystem.h"
#include "Game/ServerObjects/GameServerObjectBase.refl.h"
#include "Runtime/ServerObject/ServerObjectManager.h"
#include "Runtime/Sprite/SpriteResource.h"


GameServerObjectOverlapSystem g_ServerObjectOverlapSystem;
PreMainCallList g_ServerObjectOverlapSystemRegister;
PreMainCallList g_ServerObjectOverlapSystemInteractionRegister;

void GameServerObjectOverlapSystem::RegisterObjectType(std::size_t object_type, NotNullPtr<SpritePtr> sprite, uint32_t data_name_hash)
{
#ifdef _DEBUG
  ASSERT(m_ObjectInfo.HasAt(object_type) == false, "Registering overlap object twice");
#endif

  ASSERT(sprite != nullptr, "Overlap system was not given proper sprite data");
  m_ObjectInfo.EmplaceAt(object_type, ObjectInfo{ sprite, data_name_hash });
}

void GameServerObjectOverlapSystem::RegisterObjectInteraction(std::size_t src_object_type, std::size_t dst_object_type)
{
#ifdef _DEBUG
  ASSERT(m_ObjectInfo.HasAt(src_object_type), "Object must be registered first before interation");
  ASSERT(m_ObjectInfo.HasAt(dst_object_type), "Object must be registered first before interation");
#endif

  m_ObjectInfo[src_object_type].m_DstTypes.push_back(dst_object_type);
}

void GameServerObjectOverlapSystem::CheckOverlaps(ServerObjectManager & obj_manager, GameLogicContainer & game_logic_container)
{
  struct Object
  {
    NotNullPtr<GameServerObjectBase> m_ServerObject;
    int m_TypeIndex;
    Box m_Box;
  };

  std::vector<Object> objects;
  obj_manager.VisitObjects([&](std::size_t slot_index, ServerObject * server_obj)
  {
    auto game_obj = server_obj->CastTo<GameServerObjectBase>();

    auto pos = static_cast<Vector2>(game_obj->GetPosition());
    auto type_index = game_obj->GetTypeIndex();

    if (m_ObjectInfo.HasAt(type_index) == false)
    {
      return;
    }

    auto obj_info = m_ObjectInfo[type_index];
    auto box = obj_info.m_Sprite->GetResource()->GetSingleBoxDefault(obj_info.m_DataNameHash);

    box.m_Start += pos;
    box.m_End += pos;

    objects.emplace_back(Object{ game_obj, type_index, box });
  });

  EventMetaData meta_data;
  meta_data.m_GameLogicContainer = &game_logic_container;

  auto num_objects = objects.size();
  for (std::size_t index1 = 0; index1 < num_objects; ++index1)
  {
    auto & object1 = objects[index1];
    for (std::size_t index2 = 0; index2 < num_objects; ++index2)
    {
      if (index1 == index2)
      {
        continue;
      }

      auto & object2 = objects[index2];
      if (BoxIntersect(object1.m_Box, object2.m_Box))
      {
        bool found_dest_id = false;
        for (auto & elem : m_ObjectInfo[object1.m_TypeIndex].m_DstTypes)
        {
          if (elem == object2.m_TypeIndex)
          {
            found_dest_id = true;
            break;
          }
        }

        if (found_dest_id)
        {
          object1.m_ServerObject->TriggerEventHandler(object2.m_ServerObject->GetTypeNameHash(), object2.m_ServerObject, meta_data);
        }
      }
    }
  }
}
