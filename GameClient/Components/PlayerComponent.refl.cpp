

#include "Foundation/Common.h"

#include "Engine/Entity/Entity.h"
#include "Engine/Entity/EntitySystem.h"
#include "Engine/Audio/AudioManager.h"

#include "Game/ServerObjects/PlayerServerObject.refl.meta.h"

#include "GameClient/GameContainer.h"
#include "GameClient/Components/PlayerComponent.refl.h"
#include "GameClient/Components/PlayerComponent.refl.meta.h"

#include "Engine/Rendering/GeometryVertexBufferBuilder.h"
#include "Engine/Shader/ShaderManager.h"

PlayerComponent::PlayerComponent(PlayerComponentInitData && init_data)
{
  m_DeadReckonOffset = {};
  m_DeadReckonDec = {};
  m_DeadReckonPos = {};
}

PlayerComponent::~PlayerComponent()
{

}

void PlayerComponent::OnActivate()
{
  auto server_obj = GetEntity()->GetServerObjectAs<PlayerServerObject>();
  m_DeadReckonPos = Vector2f(server_obj->m_Position.x, server_obj->m_Position.y);

  if (m_DeadReckonPos.x > 0)
  {
    GetEntity()->SetRotation(true, false);
  }
}

void PlayerComponent::OnDestroy()
{

}

void PlayerComponent::ServerUpdate()
{
  auto server_obj = GetEntity()->GetServerObjectAs<PlayerServerObject>();
  auto pos = Vector2f(server_obj->m_Position.x, server_obj->m_Position.y);
  m_DeadReckonOffset = m_DeadReckonPos + m_DeadReckonOffset - pos;
  m_DeadReckonDec = m_DeadReckonOffset / (float)kServerUpdateRate / 2.0f;
  m_DeadReckonPos = pos;
}

void PlayerComponent::ServerDestroy()
{

}

void PlayerComponent::UpdateFirst()
{
  auto server_obj = GetEntity()->GetServerObjectAs<PlayerServerObject>();
  auto pos = Vector2f(server_obj->m_Position.x, server_obj->m_Position.y);
  auto target_pos = pos;

  auto instance_data = GetEntity()->GetGameContainer()->GetInstanceData();

  auto player = instance_data->GetFullState().m_InstanceData.m_Players.TryGet(server_obj->GetSlotIndex());
  if (player && server_obj)
  {
    bool is_local = false;

    auto num_local = instance_data->GetLocalDataCount();
    for (int index = 0; index < num_local; ++index)
    {
      if (instance_data->GetLocalData(index).m_PlayerIndex == server_obj->GetSlotIndex())
      {
        is_local = true;
        break;
      }
    }

    if (is_local == false)
    {
      target_pos += m_DeadReckonOffset;
    }
  }

  GetEntity()->SetPosition(target_pos);
  m_DeadReckonOffset -= m_DeadReckonDec;

  m_DeadReckonPos = pos;

} 

Color PlayerComponent::GetTeamColor(int team)
{
  switch (team)
  {
  case 0:
  default:
    return Color(177, 37, 25);
  case 1:
    return Color(63, 70, 192);
  case 2:
    return Color(54, 191, 42);
  case 3:
    return Color(83, 93, 102);
  }
}
