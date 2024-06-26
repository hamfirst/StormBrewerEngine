
#pragma once

#include "Foundation/Common.h"
#include "Runtime/Map/MapEffectLayerDef.refl.h"
#include "Engine/Map/MapEffectLayerRenderer.h"
#include "Engine/Entity/EntityHandle.h"

struct CollisionDrawerInitData : public MapEffectLayerInitData
{
  STORM_DATA_DEFAULT_CONSTRUCTION(CollisionDrawerInitData);
};



class CollisionDrawer : public MapEffectLayerRenderer
{
public:

  CollisionDrawer(const CollisionDrawerInitData & init_data);
  virtual ~CollisionDrawer();

  virtual void Init(GameContainer & game_container) override;
  virtual void Update(GameContainer & game_container) override;
  virtual void Render(GameContainer & game_container, const Box & viewport_bounds, 
    const RenderVec2 & screen_center, const Vector2 & offset, RenderState & render_state) override;

protected:

  uint32_t GetCollisionMask(GameContainer & game_container);

private:

};
