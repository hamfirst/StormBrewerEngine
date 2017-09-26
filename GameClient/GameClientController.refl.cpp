
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


GameClientController::GameClientController(GameContainer & game) :
  m_GameContainer(game)
{
  auto num_types = GlobalNetworkEvent::__s_TypeDatabase.GetNumTypes();
  m_EventCallbacks.resize(num_types);

  auto visitor = [&](auto f)
  {
    using FuncType = decltype(f);
    using ParamType = typename std::decay_t<typename FuncType::template param_info<0>::param_type>;

    static_assert(std::is_base_of<GlobalNetworkEvent, ParamType>::value, "Global event handlers must have a parameter that inherits from GlobalNetworkEvent");

    auto class_id = GlobalNetworkEvent::__s_TypeDatabase.GetClassId<ParamType>();
    auto func_ptr = FuncType::GetFunctionPtr();

    m_EventCallbacks[class_id] = Delegate<void, const void *>([this, func_ptr](const void * ev) { (this->*func_ptr)(*(const ParamType *)ev); });
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
  m_EventCallbacks[event_class_id].Call(event_ptr);
}

void GameClientController::HandlePlaceholderEvent(const PlaceholderGlobalEvent & ev)
{

}
