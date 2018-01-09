#include "GameClient/GameClientCommon.h"

#include "Engine/Entity/Entity.h"
#include "Engine/Entity/EntitySystem.h"
#include "Engine/EngineState.h"
#include "Engine/Audio/AudioManager.h"
#include "Engine/VisualEffect/VisualEffectManager.h"

#include "Runtime/Entity/EntityResource.h"

#include "GameClient/GameContainer.h"
#include "GameClient/GameClientUIManager.h"
#include "GameClient/GameClientController.refl.meta.h"

#include "StormRefl/StormReflMetaCall.h"

template <typename ParamType, bool IsGlobal, bool IsAuth>
struct GameClientControllerRegister
{
  static void Register(
    GameClientController * ptr,
    std::vector<Delegate<void, const void *>> & global_events,
    std::vector<Delegate<void, const void *>> & auth_events,
    void (GameClientController::*func_ptr)(const ParamType &))
  {

  }
};

template <typename ParamType>
struct GameClientControllerRegister<ParamType, true, false>
{
  static void Register(
    GameClientController * ptr, 
    std::vector<Delegate<void, const void *>> & global_events,
    std::vector<Delegate<void, const void *>> & auth_events,
    void (GameClientController::*func_ptr)(const ParamType &))
  {
    auto class_id = GlobalNetworkEvent::__s_TypeDatabase.GetClassId<ParamType>();
    global_events[class_id] = Delegate<void, const void *>([ptr, func_ptr](const void * ev) { (ptr->*func_ptr)(*(const ParamType *)ev); });
  }
};

template <typename ParamType>
struct GameClientControllerRegister<ParamType, false, true>
{
  static void Register(
    GameClientController * ptr,
    std::vector<Delegate<void, const void *>> & client_events,
    std::vector<Delegate<void, const void *>> & auth_events,
    void (GameClientController::*func_ptr)(const ParamType &))
  {
    auto class_id = ServerAuthNetworkEvent::__s_TypeDatabase.GetClassId<ParamType>();
    auth_events[class_id] = Delegate<void, const void *>([ptr, func_ptr](const void * ev) { (ptr->*func_ptr)(*(const ParamType *)ev); });
  }
};

GameClientController::GameClientController(GameContainer & game) :
  m_GameContainer(game)
{
  auto num_global_types = GlobalNetworkEvent::__s_TypeDatabase.GetNumTypes();
  m_GlobalEventCallbacks.resize(num_global_types);

  auto num_auth_types = ServerAuthNetworkEvent::__s_TypeDatabase.GetNumTypes();
  m_AuthEventCallbacks.resize(num_auth_types);

  auto visitor = [&](auto f)
  {
    using FuncType = decltype(f);
    using ParamType = typename std::decay_t<typename FuncType::template param_info<0>::param_type>;

    static_assert(std::is_base_of<GlobalNetworkEvent, ParamType>::value || std::is_base_of<ServerAuthNetworkEvent, ParamType>::value,
      "Event handler parameter must be either a child of GlobalNetworkEvent or ServerAuthNetworkEvent");

    auto func_ptr = FuncType::GetFunctionPtr();
    GameClientControllerRegister<ParamType,
      std::is_base_of<GlobalNetworkEvent, ParamType>::value,
      std::is_base_of<ServerAuthNetworkEvent, ParamType>::value>::Register(this, m_GlobalEventCallbacks, m_AuthEventCallbacks, func_ptr);
  };

  StormReflVisitFuncs(*this, visitor);
}

void GameClientController::Connected()
{

}

void GameClientController::Disconnected()
{

}

void GameClientController::PreloadLevel()
{
  m_GameContainer.GetEngineState().DestroyAllEntities();
}

void GameClientController::CatastrophicFailure()
{
  ASSERT(false, "Bad!");
}

void GameClientController::HandleGlobalEvent(std::size_t event_class_id, const void * event_ptr)
{
  m_GlobalEventCallbacks[event_class_id].Call(event_ptr);
}

void GameClientController::HandleAuthEvent(std::size_t event_class_id, const void * event_ptr)
{
  m_AuthEventCallbacks[event_class_id].Call(event_ptr);
}

void GameClientController::HandlePlaySoundGlobalEvent(const PlaySoundGlobalEvent & ev)
{
  auto audio_asset = AudioAsset::Find(ev.m_AssetHash);
  g_AudioManager.PlayAudio(audio_asset);
}

void GameClientController::HandlePlayVfxGlobalEvent(const PlayVfxGlobalEvent & ev)
{
  auto vfx_asset = VisualEffectResource::Find(ev.m_AssetHash);
  if (vfx_asset.IsLoaded())
  {
    m_GameContainer.GetEngineState().GetVisualEffectManager()->CreateVisualEffect(vfx_asset->GetData(), 0, Vector2(ev.m_PositionX, ev.m_PositionY));
  }
}

void GameClientController::HandlePlaceholderAuthEvent(const PlaceholderServerAuthEvent & ev)
{

}
