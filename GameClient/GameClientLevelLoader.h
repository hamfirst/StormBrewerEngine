#pragma once

#include "Foundation/Common.h"

#include "Runtime/Map/MapResource.h"

#include "Game/GameNetworkData.refl.h"
#include "Game/GameNetworkEvents.refl.h"

class GameContainer;

using LevelLoadCallback = Delegate<void, uint64_t, const Map &>;

class GameClientLevelLoader
{
public:
  GameClientLevelLoader(GameContainer & game);
  ~GameClientLevelLoader();

  void LoadLevel(const GameInitSettings & init_settings, uint64_t load_token, LevelLoadCallback && load_complete);
  void FinalizeLevel();
  void CancelLoading();

protected:
  void HandleLevelLoadComplete();

private:
  GameContainer & m_GameContainer;

  Map m_PendingLoadLevel;
  MapLoadLink m_PendingLoadLink;
  LevelLoadCallback m_LoadCallback;
  uint64_t m_LoadToken;

  Optional<std::size_t> m_LoadedMapId;
};

