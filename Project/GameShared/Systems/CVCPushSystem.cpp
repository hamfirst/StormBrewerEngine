
#include "GameShared/GameSharedCommon.h"
#include "GameShared/Systems/CVCPushSystem.h"
#include "Game/ServerObjects/GameServerObjectBase.refl.h"


void CVCPushSystem::SetCharacterCVCPosition(const Box & box, NotNullPtr<GameServerObjectBase> obj)
{
  m_Data.push_back(CVCData{ obj->GetObjectHandle(), box });
}

void CVCPushSystem::ProcessCVC(GameWorld & world)
{
  for (std::size_t index1 = 0, end = m_Data.size(); index1 < end; ++index1)
  {
    auto obj1 = m_Data[index1].m_Handle.ResolveTo<GameServerObjectBase>(world.GetObjectManager());
    if (obj1 == nullptr)
    {
      continue;
    }

    auto box1 = m_Data[index1].m_Box;
    auto box1_size = GameNetVal(box1.Size().x) / GameNetVal(2);

    for (std::size_t index2 = index1 + 1; index2 < end; ++index2)
    {
      auto obj2 = m_Data[index2].m_Handle.ResolveTo<GameServerObjectBase>(world.GetObjectManager());
      if (obj2 == nullptr)
      {
        continue;
      }

      auto box2 = m_Data[index2].m_Box;
      auto box2_size = GameNetVal(box2.Size().x) / GameNetVal(2);

      if (BoxIntersect(box1, box2))
      {
        auto pos1 = obj1->GetPosition();
        auto pos2 = obj2->GetPosition();

        GameNetVal diff_x;

        if (pos1.x > pos2.x || (pos1.x == pos2.x && obj1->GetSlotIndex() < obj2->GetSlotIndex()))
        {
          diff_x = (pos2.x + box2_size) - (pos1.x - box1_size);
        }
        else
        {
          diff_x = (pos2.x - box2_size) - (pos1.x + box1_size);
        }

        auto half_diff_x = diff_x / GameNetVal(2);
        auto movement = GameNetVec2(half_diff_x, GameNetVal(0));

        auto move1_result = obj1->MoveCheckCollisionDatabase(world, movement);
        if (move1_result.m_HitLeft || move1_result.m_HitRight)
        {
          movement = GameNetVec2(-diff_x, GameNetVal(0));
        }
        else
        {
          movement = GameNetVec2(-half_diff_x, GameNetVal(0));
        }

        auto move2_result = obj2->MoveCheckCollisionDatabase(world, movement);
        if (move2_result.m_HitLeft || move2_result.m_HitRight)
        {
          movement = GameNetVec2(half_diff_x, GameNetVal(0));
          obj1->MoveCheckCollisionDatabase(world, movement);
        }
      }
    }
  }
}

void CVCPushSystem::Clear()
{
  m_Data.clear();
}
