#pragma once

#include "Foundation/Common.h"
#include "Foundation/SparseList/SparseList.h"
#include "Foundation/SpatialDatabase/SpatialDatabase.h"
#include "Foundation/Allocator/IdAllocator.h"

#include "Runtime/Map/MapDef.refl.h"
#include "Runtime/ServerObject/ServerObjectResource.h"
#include "Runtime/Entity/EntityResource.h"

#include "Engine/Asset/TextureAsset.h"
#include "Engine/Rendering/VertexBuffer.h"

#include "Tools/Editor/Utility/DocumentSubValueListMirror.h"

class MapEditor;

struct MapEditorServerObjectManagerElement
{
  EntityResourcePtr m_Entity;
  Optional<Box> m_Frame;
};

class MapEditorServerObjectManager
{
public:
  MapEditorServerObjectManager(NotNullPtr<MapEditor> editor, MapDef & map, int layer_index);

  void AddServerObject(czstr ServerObject_file, const Vector2 & pos);
  void RemoveServerObject(std::size_t index);

  void SetPreviewServerObject(czstr ServerObject_file);
  void SetPreviewServerObjectPosition(const Vector2 & pos);
  void ClearPreviewServerObject();
  void CommitPreviewServerObject();

  void SelectServerObjects(const Box & box);
  Optional<std::string> FindServerObject(const Vector2 & pos);
  void DropSelection();
  void ClearSelection();
  void DeselectServerObjects();
  void DeleteSelectedServerObjects();
  void MoveSelection(const Vector2 & offset);
  bool IsOnSelectedServerObject(const Vector2 & pos);

  void SetSingleSelection(std::size_t ServerObject_index);
  Optional<std::size_t> GetSingleSelectionIndex();

  void Draw(const Box & viewport_bounds, const RenderVec2 & screen_center, RenderState & render_state);
  void DrawPreviewServerObject(const RenderVec2 & screen_center, RenderState & render_state);
  void DrawSelection(VertexBuffer & vertex_buffer, const Box & viewport_bounds, const RenderVec2 & screen_center, RenderState & render_state);

  void ToggleHidden();
  void SetHidden(bool hidden);
  bool IsHidden();

  void ToggleColapsed();
  bool IsCollapsed();

private:
  NotNullPtr<MapEditor> m_Editor;

  MapDef & m_Map;
  int m_LayerIndex;

  Optional<Vector2> m_PreviewServerObjectPosition;
  std::string m_PreviewServerObjectFile;
  ServerObjectLoadLink m_PreviewServerObject;
  EntityResourcePtr m_PreviewEntity;
  
  std::vector<std::size_t> m_SelectedServerObjects;
  Vector2 m_SelectedServerObjectOffset;
  
  DocumentSubValueListMirror m_SpriteMirror;
  Delegate<NullOptPtr<MapEditorServerObjectManagerElement>, std::size_t> m_GetSprite;

  bool m_Hidden;
  bool m_Collapsed;
};
