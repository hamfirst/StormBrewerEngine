#pragma once

#include "Foundation/Common.h"
#include "Foundation/SparseList/SparseList.h"
#include "Foundation/SpatialDatabase/SpatialDatabase.h"
#include "Foundation/Allocator/IdAllocator.h"

#include "Runtime/Map/MapDef.refl.h"
#include "Runtime/TileSheet/TileSheetResource.h"
#include "Runtime/Animation/AnimationState.h"

#include "Engine/Asset/TextureAsset.h"
#include "Engine/Rendering/VertexBuffer.h"

#include "Tools/Editor/Utility/DocumentListValueWatcher.h"

class MapEditor;

class MapEditorTileManager
{
public:
  MapEditorTileManager(NotNullPtr<MapEditor> editor, MapDef & map, int layer_index);

  void Update();

  void SyncTiles(NotNullPtr<TileSheetResource> tile_sheet);
  void SyncTileSheet();

  void InsertTile(const MapTile & tile);
  void CommitPreviewTiles();
  void SelectTiles(const Box & box);
  void RemoveTiles(const std::vector<std::size_t> & tiles);
  Optional<MapTile> FindTile(const Vector2 & pos);

  void InsertAnimation(const MapAnimatedTile & anim);
  void CommitPreviewAnimations();
  void SelectAnimations(const Box & box);
  void RemoveAnimations(const std::vector<std::size_t> & anims);
  Optional<MapAnimatedTile> FindAnim(const Vector2 & pos);

  bool HasSelection();
  void ClearSelection();
  void DeleteSelection();
  void SetSelectionOffset(const Vector2 & offset);
  void CommitSelectedOffset();
  bool IsOnSelectedTile(const Vector2 & pos);
  bool IsOnPreviewTile(const Vector2 & pos);
  void DuplicateSelectedToPreview();

  void CopySelection();
  void PasteSelection(const Vector2 & screen_center);

  void Draw(const Box & viewport_bounds, const RenderVec2 & screen_center, RenderState & render_state);
  void DrawPreviewTiles(VertexBuffer & vertex_buffer, const RenderVec2 & screen_center, RenderState & render_state);
  void DrawSelectedTiles(VertexBuffer & vertex_buffer, const RenderVec2 & screen_center, RenderState & render_state);

  void SetPreviewTiles(const std::vector<MapTile> & tiles);
  void SetPreviewAnimations(const std::vector<MapAnimatedTile> & anims);
  void OffsetPreview(const Vector2 & offset);
  void ClearPreviewTiles();

  void ToggleHidden();
  void SetHidden(bool hidden);
  bool IsHidden();
protected:

  struct GridDrawElement
  {
    AssetReference<TextureAsset> m_Texture;
    int m_StartIndex;
    int m_EndIndex;
  };

  struct GridDrawList
  {
    VertexBuffer m_VertexBuffer;
    std::vector<GridDrawElement> m_DrawElems;
  };

  struct TextureInfo
  {
    uint32_t m_TextureNameHash;
    int m_FrameWidth;
    int m_FrameHeight;
    TextureAsset::LoadCallbackLink m_AssetLink;
  };

  struct AnimationInfo
  {
    Vector2 m_Position;
    AnimationState m_State;
    Box m_Bounds;
  };

  void HandleTileSheetReload(NotNullPtr<TileSheetResource> tile_sheet);
  void HandleTextureReload(NullOptPtr<TextureAsset> texture, int texture_index);

  void HandleTileListChange(const ReflectionChangeNotification & change);
  void HandleTileChildChange(const ReflectionChangeNotification & change, std::size_t index);

  void HandleAnimListChange(const ReflectionChangeNotification & change);
  void HandleAnimChildChange(const ReflectionChangeNotification & change, std::size_t index);

  void RefreshTile(std::size_t index);
  void RefreshTiles(uint32_t texture_hash);

  void RefreshAnimation(std::size_t index);

  Optional<Box> GetMultiTileBounds(const std::vector<std::size_t> & tiles);
  Optional<Box> GetMultiAnimBounds(const std::vector<std::size_t> & tiles);
  void AddToDirtyGridList(const Box & box);
  void AddToDirtyGridList(uint32_t grid_id);
  void AddAllToDirtyGridList();

  bool IsTileInPreview(const MapTile & tile);

  Box GetTileBounds(const MapTile & tile);
  Box GetTileBounds(const MapTile & tile, TextureInfo & tex);

  Box GetAnimBounds(const MapAnimatedTile & tile);

private:
  NotNullPtr<MapEditor> m_Editor;

  MapDef & m_Map;
  int m_LayerIndex;

  TileSheetLoadLink m_TileSheet;
  VertexBuffer m_DrawVertexBuffer;

  bool m_InitialSyncComplete;
  Optional<SpatialDatabase> m_TileSpatialDatabase;
  Optional<SparseList<Box>> m_TileLocations;
  Optional<IdAllocator> m_TileIdAllocator;

  Optional<SpatialDatabase> m_AnimSpatialDatabase;
  Optional<SparseList<AnimationInfo>> m_AnimInfo;
  Optional<IdAllocator> m_AnimIdAllocator;

  bool m_RecreateDrawInfo;
  Optional<std::vector<uint32_t>> m_DirtyGrids;
  Optional<SpatialDatabaseGrid<GridDrawList>> m_DrawInfo;

  bool m_IgnoreTextureReloads;
  std::vector<TextureInfo> m_Textures;

  bool m_LocalChange;
  DocumentListValueWatcher m_TileWatcher;
  DocumentListValueWatcher m_AnimWatcher;

  std::vector<MapTile> m_PreviewTiles;
  Optional<Box> m_PreviewTileBounds;

  std::vector<MapAnimatedTile> m_PreviewAnims;
  Optional<Box> m_PreviewAnimBounds;

  std::vector<std::size_t> m_SelectedTiles;
  std::vector<std::size_t> m_SelectedAnimations;
  Vector2 m_SelectedTileOffset;
  Vector2 m_SelectedAnimOffset;

  int m_NumFrames = 0;
  bool m_Hidden;
};