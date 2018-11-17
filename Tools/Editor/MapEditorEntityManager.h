#pragma once

#include "Foundation/Common.h"
#include "Foundation/SparseList/SparseList.h"
#include "Foundation/SpatialDatabase/SpatialDatabase.h"
#include "Foundation/Allocator/IdAllocator.h"

#include "Runtime/Map/MapDef.refl.h"
#include "Runtime/Entity/EntityResource.h"
#include "Runtime/Sprite/SpriteResource.h"

#include "Engine/Asset/TextureAsset.h"
#include "Engine/Rendering/VertexBuffer.h"

#include "DocumentSubValueListMirror.h"

class MapEditor;
class RenderUtil;

struct MapEditorEntityManagerElement
{
  SpritePtr m_Sprite;
  Optional<Box> m_Frame;
};

class MapEditorEntityManager
{
public:
  MapEditorEntityManager(NotNullPtr<MapEditor> editor, MapDef & map, int layer_index);

  void AddEntity(czstr entity_file, const Vector2 & pos);
  void RemoveEntity(std::size_t index);

  void SetPreviewEntity(czstr entity_file);
  void SetPreviewEntityPosition(const Vector2 & pos);
  void ClearPreviewEntity();
  void CommitPreviewEntity();

  void SelectEntities(const Box & box);
  Optional<std::string> FindEntity(const Vector2 & pos);
  void DropSelection();
  void ClearSelection();
  void DeselectEntities();
  void DeleteSelectedEntities();
  void MoveSelection(const Vector2 & offset);
  bool IsOnSelectedEntity(const Vector2 & pos);

  void SetSingleSelection(std::size_t entity_index);
  Optional<std::size_t> GetSingleSelectionIndex();

  void Draw(const Box & viewport_bounds, const RenderVec2 & screen_center, RenderState & render_state, RenderUtil & render_util);
  void DrawPreviewEntity(const RenderVec2 & screen_center, RenderState & render_state, RenderUtil & render_util);
  void DrawSelection(VertexBuffer & vertex_buffer, const Box & viewport_bounds, const RenderVec2 & screen_center, RenderState & render_state, RenderUtil & render_util);

  void ToggleHidden();
  void SetHidden(bool hidden);
  bool IsHidden();

  void ToggleColapsed();
  bool IsCollapsed();

private:
  NotNullPtr<MapEditor> m_Editor;

  MapDef & m_Map;
  int m_LayerIndex;

  Optional<Vector2> m_PreviewEntityPosition;
  std::string m_PreviewEntityFile;
  EntityResourcePtr m_PreviewEntity;
  
  std::vector<std::size_t> m_SelectedEntities;
  Vector2 m_SelectedEntityOffset;
  
  DocumentSubValueListMirror m_SpriteMirror;
  Delegate<NullOptPtr<MapEditorEntityManagerElement>, std::size_t> m_GetSprite;

  bool m_Hidden;
  bool m_Collapsed;
};
