#pragma once

#include "Foundation/SpatialDatabase/SpatialDatabase.h"

#include "Runtime/Map/MapDef.refl.h"

#include "Engine/Asset/TextureAsset.h"
#include "Engine/Rendering/VertexBuffer.h"
#include "Engine/Map/MapEffectLayerRenderer.h"

class MapEffectLayerInstance
{
public:

  MapEffectLayerInstance(MapDef & map, std::size_t layer_index);

  void Init(GameContainer & game_container);
  void Update(GameContainer & game_container);
  void Draw(GameContainer & game_container, const Box & viewport_bounds, const RenderVec2 & screen_center, RenderState & render_state, RenderUtil & render_util);

  int GetLayerOrder() const;

private:

  int m_LayerOrder;
  std::unique_ptr<MapEffectLayerRenderer> m_Renderer;
};
