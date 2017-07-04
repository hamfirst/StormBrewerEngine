
#include "Game/GameFullState.refl.h"
#include "Game/GameLogicContainer.h"

#include "GameClient/GameModeConnecting.h"
#include "GameClient/GameModeDebugOffline.h"
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

GameModeDebugOffline::GameModeDebugOffline(const Map & map, const GameInitSettings & init_settings, GameContainer & game) :
  m_Stage(map),
  m_InitSettings(init_settings),
  m_GameState(m_Stage.CreateDefaultGameState()),
  m_EntitySync(game),
  m_ClientController(game)
{
  for (int index = 0; index < kNumPlayers; ++index)
  {
    ::GamePlayer player;
    player.m_Name = std::to_string(index);
    player.m_Team = index % kMaxTeams;

    m_Input.m_PlayerInput[index] = {};
    m_GameState.m_GlobalData.m_Players.EmplaceAt(index, std::move(player));
  }
}

void GameModeDebugOffline::Initialize(GameContainer & container)
{

}

void GameModeDebugOffline::OnAssetsLoaded(GameContainer & container)
{

}

void GameModeDebugOffline::Update(GameContainer & container)
{
  int send_timer = 0;
  GameLogicContainer game(m_GameState.m_GlobalData, m_GameState.m_ServerObjectManager, *this, *this, m_Stage, true, send_timer);
  m_Controller.CheckEndTurnTimer(game);

  for (int index = 0; index < kNumPlayers; ++index)
  {
    m_Controller.ApplyInput(index, game, m_Input.m_PlayerInput[index]);
  }

  if (m_GameState.m_GlobalData.m_Running)
  {
    m_Controller.Update(game);
  }

  m_EntitySync.Sync(m_GameState.m_ServerObjectManager);

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

void GameModeDebugOffline::Render(GameContainer & container)
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

void GameModeDebugOffline::SendGlobalEvent(std::size_t class_id, void * event_ptr)
{
  m_ClientController.HandleGlobalEvent(class_id, event_ptr);
}

void GameModeDebugOffline::SendGlobalEvent(std::size_t class_id, void * event_ptr, std::size_t connection_id)
{
  m_ClientController.HandleGlobalEvent(class_id, event_ptr);
}

void GameModeDebugOffline::SendEntityEvent(std::size_t class_id, void * event_ptr, ServerObjectHandle object_handle)
{
  m_EntitySync.SendEntityEvent((std::size_t)object_handle.GetRawSlotIndex(), (uint32_t)class_id, event_ptr);
}

void GameModeDebugOffline::SendEntityEvent(std::size_t class_id, void * event_ptr, std::size_t connection_id, ServerObjectHandle object_handle)
{
  m_EntitySync.SendEntityEvent((std::size_t)object_handle.GetRawSlotIndex(), (uint32_t)class_id, event_ptr);
}

