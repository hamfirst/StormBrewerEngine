#pragma once

#include "Foundation/Any/Any.h"

#include "Runtime/RuntimeCommon.h"
#include "Runtime/Map/MapDef.refl.h"

class RuntimeState;

class MapInstance
{
public:
  MapInstance(NotNullPtr<RuntimeState> runtime_state, MapDef & map_def, std::size_t map_id);
  void RemoveCollision(NotNullPtr<RuntimeState> runtime_state);

private:
  friend class MapRenderer;

  Any m_EngineData;
  std::size_t m_MapId;
};
