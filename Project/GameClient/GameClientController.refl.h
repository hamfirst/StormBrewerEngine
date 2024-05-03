#pragma once

#include "Foundation/Common.h"

#include "Runtime/Map/MapResource.h"

#include "Game/NetworkEvents/GameNetworkData.refl.h"
#include "Game/NetworkEvents/GameNetworkEvents.refl.h"
#include "Game/NetworkEvents/GameServerEventSender.h"
#include "Game/SimulationEvents/GameSimulationEventCallbacks.h"

class GameContainer;

using LevelLoadCallback = Delegate<void, uint64_t, const Map &>;

class GameClientController : public StormRelfEmptyBase, public GameSimulationEventCallbacks
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

  void HandleGlobalEvent(std::size_t event_class_id, const void * event_ptr);
  void HandleAuthEvent(std::size_t event_class_id, const void * event_ptr);

  void STORM_REFL_FUNC HandleCreateEntityGlobalEvent(const CreateEntityGlobalEvent & ev);
  void STORM_REFL_FUNC HandleCameraShakeEvent(const CameraShakeEvent & ev);
  void STORM_REFL_FUNC HandlePlaySoundGlobalEvent(const PlaySoundGlobalEvent & ev);
  void STORM_REFL_FUNC HandlePlayVfxGlobalEvent(const PlayVfxGlobalEvent & ev);
  void STORM_REFL_FUNC HandlePlaceholderAuthEvent(const PlaceholderServerAuthEvent & ev);

private:
  GameContainer & m_GameContainer;

  std::vector<Delegate<void, const void *>> m_GlobalEventCallbacks;
  std::vector<Delegate<void, const void *>> m_AuthEventCallbacks;

};
