#pragma once

#include "Foundation/SpatialDatabase/SpatialDatabase.h"

#include "Runtime/Map/MapDef.refl.h"
#include "Runtime/TileSheet/TileSheetResource.h"

#include "Engine/Asset/TextureAsset.h"
#include "Engine/Rendering/VertexBuffer.h"
#include "Engine/Rendering/RenderSettings.h"
#include "Engine/DrawList/DrawList.h"




class MapManualTileLayerInstance
{
public:

  MapManualTileLayerInstance(MapDef & map, std::size_t layer_index);

  void LoadTextures();
  void CreateVertexBuffers();

  void Update();
  void Draw(const Box & viewport_bounds, const RenderVec2 & screen_center);

#ifdef USE_Z_ORDERING
  void DrawDynamic(const Box & viewport_bounds, DrawList & draw_list);
#endif

  int GetLayerOrder() const;

private:

  struct GridDrawElement
  {
    AssetReference<TextureAsset> m_Texture;
    int m_StartIndex;
    int m_EndIndex;
  };

  struct TextureInfo
  {
    uint32_t m_TextureNameHash;
    int m_FrameWidth;
    int m_FrameHeight;
    TextureAsset::LoadCallbackLink m_Asset;
  };

#ifdef USE_Z_ORDERING
  struct GridDrawDynamicElement
  {
    AssetReference<TextureAsset> m_Texture;
    int m_LowerEdge;
    int m_StartIndex;
    int m_EndIndex;
  };
#endif

  bool m_Initializing = false;
  int m_LayerOrder;

  VertexBuffer m_VertexBuffer;

  SpatialDatabaseGrid<std::vector<GridDrawElement>> m_DrawInfo;

#ifdef USE_Z_ORDERING
  SpatialDatabaseGrid<std::vector<GridDrawDynamicElement>> m_DynamicDrawInfo;
#endif

  TileSheetLoadLink m_TileSheet;

  std::vector<MapTile> m_Tiles;
  std::vector<TextureInfo> m_Textures;
};
