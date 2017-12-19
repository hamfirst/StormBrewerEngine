
#include "Runtime/RuntimeCommon.h"
#include "Runtime/ServerObject/ServerObjectOverlapSystem.h"
#include "Runtime/ServerObject/ServerObjectManager.h"
#include "Runtime/Sprite/SpriteResource.h"


ServerObjectOverlapSystem g_ServerObjectOverlapSystem;
PreMainCallList g_ServerObjectOverlapSystemRegister;
PreMainCallList g_ServerObjectOverlapSystemInteractionRegister;

void ServerObjectOverlapSystem::RegisterObjectType(std::size_t object_type, NotNullPtr<SpriteResource> sprite, uint32_t data_name_hash)
{
#ifdef _DEBUG
  ASSERT(m_ObjectInfo.HasAt(object_type) == false, "Registering overlap object twice");
#endif

  m_ObjectInfo.EmplaceAt(object_type, ObjectInfo{ sprite, data_name_hash });
}

void ServerObjectOverlapSystem::RegisterObjectInteraction(std::size_t src_object_type, std::size_t dst_object_type)
{
#ifdef _DEBUG
  ASSERT(m_ObjectInfo.HasAt(src_object_type), "Object must be registered first before interation");
  ASSERT(m_ObjectInfo.HasAt(dst_object_type), "Object must be registered first before interation");
#endif

  m_ObjectInfo[src_object_type].m_DstTypes.push_back(dst_object_type);
}

void ServerObjectOverlapSystem::CheckOverlaps(ServerObjectManager & obj_manager, GameLogicContainer & game_logic_containers)
{
  struct Object
  {
    NotNullPtr<ServerObject> m_ServerObject;
    int m_TypeIndex;
    Box m_Box;
  };

  std::vector<Object> objects;
  obj_manager.VisitObjects([&](std::size_t slot_index, ServerObject * obj)
  {
    auto pos = obj->GetPosition();
    auto type_index = obj->GetTypeIndex();

    auto obj_info = m_ObjectInfo[type_index];
    auto box = obj_info.m_Sprite->GetSingleBox(obj_info.m_DataNameHash);

    box.m_Start += pos;
    box.m_End += pos;

    objects.emplace_back(Object{ obj, type_index, box });
  });

  EventMetaData meta_data;
  meta_data.m_GameLogicContainer = &game_logic_containers;

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
        for (auto & elem : m_ObjectInfo[index1].m_DstTypes)
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
