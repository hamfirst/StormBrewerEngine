#pragma once

#include "Foundation/Common.h"

#include "Runtime/Map/MapResource.h"

#include "Game/GameNetworkData.refl.h"
#include "Game/GameNetworkEvents.refl.h"
#include "Game/GameSimulationEventCallbacks.h"
#include "Game/GameServerEventSender.h"

class GameContainer;

using LevelLoadCallback = Delegate<void, uint64_t, const Map &>;

class GameClientController : public StormRelfEmptyBase, public GameSimulationEventCallbacks, public GameServerEventSender
{
public:
  STORM_REFL;
  STORM_REFL_FUNCS;
  STORM_REFL_NODEFAULT;

  GameClientController(GameContainer & game);

  void Connected();
  void Disconnected();
  void PreloadLevel();
  void CatastrophicFailure();

  void HandleGlobalEvent(std::size_t event_class_id, void * event_ptr);

  void STORM_REFL_FUNC HandlePlaceholderEvent(const PlaceholderGlobalEvent & ev);

private:
  GameContainer & m_GameContainer;

  std::vector<Delegate<void, void *>> m_EventCallbacks;

};

