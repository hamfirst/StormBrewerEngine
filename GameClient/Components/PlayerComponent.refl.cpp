
#include "GameClient/GameClientCommon.h"

#include "Engine/Entity/Entity.h"
#include "Engine/Entity/EntitySystem.h"
#include "Engine/Audio/AudioManager.h"

#include "Game/ServerObjects/Player/PlayerServerObject.refl.meta.h"

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

  m_LastFrame = -1;
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
  auto info = GetServerObjectInfo();
  
  m_DeadReckonOffset = m_DeadReckonPos + m_DeadReckonOffset - info.m_HistoryPos;
  m_DeadReckonDec = m_DeadReckonOffset / (float)kServerUpdateRate / 2.0f;
  m_DeadReckonPos = info.m_HistoryPos;
}

void PlayerComponent::ServerDestroy()
{

}

void PlayerComponent::UpdateFirst()
{
  auto info = GetServerObjectInfo();

  if (info.m_IsLocal)
  {
    GetEntity()->SetPosition(info.m_CurrentPos);
  }
  else
  {
    GetEntity()->SetPosition(info.m_HistoryPos + m_DeadReckonOffset);
    m_DeadReckonPos = info.m_HistoryPos;
    m_DeadReckonOffset -= m_DeadReckonDec;
  }

  auto & sprite = GetEntity()->GetSprite();
  auto & render_state = GetEntity()->GetRenderState();

  auto event_visitor = [&](auto & event_info, auto box_start, auto box_end)
  {
    GetEntity()->TriggerEventHandler(event_info.GetTypeNameHash(), event_info.GetValue());
  };

  sprite->VisitEvents(event_visitor, render_state.m_AnimIndex, render_state.m_AnimFrame, render_state.m_AnimDelay);
} 

PlayerServerObjectInfo PlayerComponent::GetServerObjectInfo()
{
  PlayerServerObjectInfo info;
  info.m_CurrentObject = GetEntity()->GetServerObjectAs<PlayerServerObject>();
  info.m_HistoryObject = GetEntity()->GetServerObjectAs<PlayerServerObject>(7);
  info.m_CurrentPos = Vector2f(info.m_CurrentObject->m_Position.x, info.m_CurrentObject->m_Position.y);
  info.m_HistoryPos = Vector2f(info.m_HistoryObject->m_Position.x, info.m_HistoryObject->m_Position.y);

  auto instance_data = GetEntity()->GetGameContainer()->GetInstanceData();

  auto player = instance_data->GetGlobalInstanceData().m_Players.TryGet(info.m_CurrentObject->GetSlotIndex());
  info.m_IsLocal = player->m_AIPlayerInfo.IsValid();

  auto num_local = instance_data->GetNumLocalData();
  for (int index = 0; index < num_local; ++index)
  {
    if (instance_data->GetClientLocalData(index).m_PlayerIndex == info.m_CurrentObject->GetSlotIndex())
    {
      info.m_IsLocal = true;
      break;
    }
  }

  return info;
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
