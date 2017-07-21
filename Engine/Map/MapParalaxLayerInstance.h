#pragma once

#include "Foundation/SpatialDatabase/SpatialDatabase.h"

#include "Runtime/Map/MapDef.refl.h"

#include "Engine/Asset/TextureAsset.h"
#include "Engine/Rendering/VertexBuffer.h"

class RenderState;
class RenderUtil;

class MapParalaxLayerInstance
{
public:

  MapParalaxLayerInstance(MapDef & map, std::size_t layer_index);

  void Update();
  void Draw(const Box & viewport_bounds, const RenderVec2 & screen_center, RenderState & render_state, RenderUtil & render_util);

  int GetLayerOrder() const;

private:

  AssetReference<TextureAsset> m_Texture;
  int m_LayerOrder;

  bool m_RepeatX;
  bool m_RepeatY;

  float m_ParalaxX;
  float m_ParalaxY;
};
