#pragma once

#include "Foundation/Common.h"
#include "Foundation/SparseList/SparseList.h"
#include "Foundation/SpatialDatabase/SpatialDatabase.h"
#include "Foundation/Allocator/IdAllocator.h"

#include "Runtime/Map/MapDef.refl.h"
#include "Runtime/TileSheet/TileSheetResource.h"

#include "Engine/Asset/TextureAsset.h"
#include "Engine/Rendering/VertexBuffer.h"

#include "DocumentListValueWatcher.h"

class MapEditor;
class RenderUtil;

class MapEditorTileManager
{
public:
  MapEditorTileManager(NotNullPtr<MapEditor> editor, MapDef & map, int layer_index);

  void SyncTiles();
  void SyncTileSheet();

  void InsertTile(const MapTile & tile);
  void CommitPreviewTiles();
  void SelectTiles(const Box & box);
  void ClearSelection();
  void DeleteSelectedTiles();
  void SetSelectedTileOffset(const Vector2 & offset);
  void CommitSelectedTileOffset();
  Optional<MapTile> FindTile(const Vector2 & pos);
  bool IsOnSelectedTile(const Vector2 & pos);

  void RemoveTiles(const std::vector<std::size_t> & tiles);

  void Draw(const Box & viewport_bounds, const RenderVec2 & screen_center);
  void DrawPreviewTiles(VertexBuffer & vertex_buffer, const RenderVec2 & screen_center);
  void DrawSelectedTiles(VertexBuffer & vertex_buffer, const RenderVec2 & screen_center, RenderUtil & render_util);

  void SetPreviewTiles(const std::vector<MapTile> & tiles);
  void ClearPreviewTiles();

  void ToggleHidden();
  void SetHidden(bool hidden);
  bool IsHidden();
protected:

  struct GridDrawElement
  {
    AssetReference<TextureAsset> m_Texture;
    VertexBuffer m_VertexBuffer;
  };

  struct TextureInfo
  {
    uint32_t m_TextureNameHash;
    int m_FrameWidth;
    int m_FrameHeight;
    TextureAsset::LoadCallbackLink m_AssetLink;
  };

  void HandleTileSheetReload(NotNullPtr<TileSheetResource> tile_sheet);
  void HandleTextureReload(NullOptPtr<TextureAsset> texture, int texture_index);

  void HandleListChange(const ReflectionChangeNotification & change);
  void HandleChildChange(const ReflectionChangeNotification & change, std::size_t index);

  void RefreshTile(std::size_t index);
  void RefreshTiles(uint32_t texture_hash);

  Optional<Box> GetTileBounds(const std::vector<std::size_t> & tiles);
  void AddToDirtyGridList(const Box & box);
  void AddToDirtyGridList(uint32_t grid_id);
  void AddAllToDirtyGridList();

  bool IsTileInPreview(const MapTile & tile);

  Box GetTileBounds(const MapTile & tile);
  Box GetTileBounds(const MapTile & tile, TextureInfo & tex);

private:
  NotNullPtr<MapEditor> m_Editor;

  MapDef & m_Map;
  int m_LayerIndex;

  TileSheetLoadLink m_TileSheet;

  bool m_InitialSyncComplete;
  Optional<SpatialDatabase> m_SpatialDatabase;
  Optional<SparseList<Box>> m_TileLocations;
  Optional<IdAllocator> m_IdAllocator;

  bool m_RecreateDrawInfo;
  Optional<std::vector<uint32_t>> m_DirtyGrids;
  Optional<SpatialDatabaseGrid<std::vector<GridDrawElement>>> m_DrawInfo;

  bool m_IgnoreTextureReloads;
  std::vector<TextureInfo> m_Textures;

  bool m_LocalChange;
  DocumentListValueWatcher m_Watcher;

  std::vector<MapTile> m_PreviewTiles;
  Optional<Box> m_PreviewTileBounds;

  std::vector<std::size_t> m_SelectedTiles;
  Vector2 m_SelectedTileOffset;

  bool m_Hidden;
};