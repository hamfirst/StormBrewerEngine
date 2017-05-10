#pragma once

#include "Foundation/SpatialDatabase/SpatialDatabase.h"

#include "Runtime/Map/MapDef.refl.h"

#include "Engine/Asset/TextureAsset.h"
#include "Engine/Rendering/VertexBuffer.h"

class MapManualTileLayerInstance
{
public:

  MapManualTileLayerInstance(MapDef & map, std::size_t layer_index);

  void Draw(const Box & viewport_bounds, const RenderVec2 & screen_center);

  int GetLayerOrder() const;

private:

  struct GridDrawElement
  {
    AssetReference<TextureAsset> m_Texture;
    VertexBuffer m_VertexBuffer;
  };

  int m_LayerOrder;
  SpatialDatabaseGrid<std::vector<GridDrawElement>> m_DrawInfo;
};
