#pragma once

#include "Engine/EngineCommon.h"
#include "Engine/Rendering/RenderState.h"

#include "Runtime/Map/MapEffectLayerDef.refl.h"

class GameContainer;

class MapEffectLayerRenderer : public MapEffectLayerLogicBase
{
public:
  MapEffectLayerRenderer();
  virtual ~MapEffectLayerRenderer();
  
  virtual void Init(GameContainer & world);
  virtual void Update(GameContainer & world);
  virtual void Render(GameContainer & world, const Box & viewport_bounds,
                      const RenderVec2 & screen_center, const Vector2 & offset, RenderState & render_state);
};
