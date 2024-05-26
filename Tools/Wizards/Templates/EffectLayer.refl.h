#pragma once

#include ""GameClient/GameClientCommon.h""
#include ""Runtime/Map/MapEffectLayerDef.refl.h""
#include ""Engine/Map/MapEffectLayerRenderer.h""

struct {class_name}InitData : public MapEffectLayerInitData
{{
  STORM_DATA_DEFAULT_CONSTRUCTION_DERIVED({class_name}InitData);
}};

class {class_name} : public MapEffectLayerRenderer
{{
public:

  {class_name}({class_name}InitData && init_data);
  virtual ~{class_name}();

  virtual void Update(GameContainer & world) override;
  virtual void Render(GameContainer & world, const Box & viewport_bounds,
                                    const RenderVec2 & screen_center, const Vector2 & offset, RenderState & render_state) override;
}};
