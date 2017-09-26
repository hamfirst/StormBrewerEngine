#pragma once

#include "Engine/EngineCommon.h"
#include "Engine/Rendering/RenderState.h"
#include "Engine/Rendering/RenderUtil.h"

class GameContainer;

class MapEffectLayerRenderer
{
public:
  MapEffectLayerRenderer();
  virtual ~MapEffectLayerRenderer();
  
  virtual void Init(GameContainer & game_container);
  virtual void Update(GameContainer & game_container);
  virtual void Render(GameContainer & game_container, const Box & viewport_bounds, const RenderVec2 & screen_center, RenderState & render_state, RenderUtil & render_util);
};
