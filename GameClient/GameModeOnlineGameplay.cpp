
#include "GameClient/GameModeConnecting.h"
#include "GameClient/GameModeOnlineGameplay.h"
#include "GameClient/GameContainer.h"
#include "GameClient/GameNetworkClient.h"

#include "Engine/Asset/TextureAsset.h"
#include "Engine/Text/TextManager.h"
#include "Engine/Entity/EntitySystem.h"
#include "Engine/Component/ComponentSystem.h"
#include "Engine/Component/ComponentUpdateBucketList.h"
#include "Engine/Map/MapSystem.h"
#include "Engine/DrawList/DrawList.h"
#include "Engine/EngineState.h"


void GameModeOnlineGameplay::Initialize(GameContainer & container)
{

}

void GameModeOnlineGameplay::OnAssetsLoaded(GameContainer & container)
{

}

void GameModeOnlineGameplay::Update(GameContainer & container)
{
  auto & client = container.GetClient();
  if (client.GetConnectionState() != ClientConnectionState::kConnected)
  {
    container.SwitchMode(GameModeDef<GameModeConnecting>{});
    return;
  }

  if (client.GetGlobalData()->m_Started == false)
  {
    container.SwitchMode(GameModeDef<GameModeConnecting>{});
    return;
  }

  client.Update();

  auto & engine_state = container.GetEngineState();
  auto comp_system = engine_state.GetComponentSystem();
  auto entity_system = engine_state.GetEntitySystem();

  ComponentUpdateBucketList update_list;
  comp_system->CreateUpdateBucketList(update_list);

  for (int index = 0, end = update_list.GetNumBuckets(); index < end; ++index)
  {
    update_list.CallFirst(index);
    entity_system->FinalizeEvents();

    update_list.CallMiddle(index);
    entity_system->FinalizeEvents();

    update_list.CallLast(index);
    entity_system->FinalizeEvents();
  }

  comp_system->FinalizeComponentDestroys();
}

void GameModeOnlineGameplay::Render(GameContainer & container)
{
  auto & render_state = container.GetRenderState();
  auto & render_util = container.GetRenderUtil();
  render_util.Clear();

  auto & engine_state = container.GetEngineState();
  auto entity_system = engine_state.GetEntitySystem();
  auto map_system = engine_state.GetMapSystem();

  auto screen_resolution = container.GetWindow().GetSize();
  m_GameCamera.Update(container, screen_resolution);

  m_EngineCamera.SetPosition(m_GameCamera.GetCameraPosition());
  m_EngineCamera.SetGameResolution(m_GameCamera.GetGameResolution());
  m_EngineCamera.SetScreenResolution(screen_resolution);

  auto viewport_bounds = Box::FromFrameCenterAndSize(m_GameCamera.GetCameraPosition(), m_GameCamera.GetGameResolution());

  m_EngineCamera.Draw(&engine_state, container.GetRenderState());
}

