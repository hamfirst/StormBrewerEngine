#pragma once

#include "Foundation/Common.h"

#include "Runtime/Map/MapDef.refl.h"
#include "Runtime/VisualEffect/VisualEffectResource.h"

#include "Engine/Asset/TextureAsset.h"
#include "Engine/Rendering/VertexBuffer.h"

#include "DocumentValueWatcher.h"
#include "DocumentSubValueListMirror.h"

class MapEditor;
class RenderUtil;

using MapEditorParalaxObjectType = Variant<TextureAsset::LoadCallbackLink, SpriteLoadLink, VisualEffectLoadLink>;

struct MapEditorParalaxObjectManagerElement
{
  MapEditorParalaxObjectType m_Object;
  Optional<Box> m_Frame;
};

class MapEditorParalaxLayer
{
public:
  MapEditorParalaxLayer(NotNullPtr<MapEditor> editor, MapDef & map, int layer_index);

  void AddParalaxObject(const MapParalaxLayerObject & paralax_object_data);
  void RemoveParalaxObject(std::size_t index);

  void SetPreviewParalaxObjectPosition(const Vector2 & pos);
  void ClearPreviewParalaxObject();
  void CommitPreviewParalaxObject();

  void SelectParalaxObjects(const Box & box);
  Optional<MapParalaxLayerObject> FindParalaxObject(const Vector2 & pos);
  void DropSelection();
  void ClearSelection();
  void DeselectParalaxObjects();
  void DeleteSelectedParalaxObjects();
  void MoveSelection(const Vector2 & offset);
  bool IsOnSelectedParalaxObject(const Vector2 & pos);

  void SetSingleSelection(std::size_t paralax_object_index);
  Optional<std::size_t> GetSingleSelectionIndex();

  void Draw(VertexBuffer & buffer, const Box & viewport_bounds, const RenderVec2 & screen_center, RenderState & render_state, RenderUtil & render_util);
  void DrawPreviewParalaxObject(VertexBuffer & buffer, const Box & viewport_bounds, const RenderVec2 & screen_center, RenderState & render_state, RenderUtil & render_util);
  void DrawSelection(VertexBuffer & vertex_buffer, const Box & viewport_bounds, const RenderVec2 & screen_center, RenderState & render_state, RenderUtil & render_util);

  Optional<Box> DrawObject(MapEditorParalaxObjectType & object, MapParalaxLayerObject & object_data, 
    const Vector2 & pos, VertexBuffer & buffer, const Box & viewport_bounds, const RenderVec2 & screen_center, RenderState & render_state, RenderUtil & render_util);

  void ToggleHidden();
  void SetHidden(bool hidden);
  bool IsHidden();

  void ToggleColapsed();
  bool IsCollapsed();

  static Optional<MapParalaxLayerObjectType> GetParalaxTypeForPath(czstr file_path);

  template <typename Updater>
  static MapEditorParalaxObjectType CreateObjectFromPath(czstr file_path, Updater && updater)
  {
    auto type = GetParalaxTypeForPath(file_path);

    if (type)
    {
      switch (type.Value())
      {
      case MapParalaxLayerObjectType::kSprite:
        return SpriteResource::LoadWithCallback(file_path, [updater](NullOptPtr<SpriteResource>) { updater(); });
      case MapParalaxLayerObjectType::kTexture:
        return TextureAsset::LoadWithCallback(file_path, [updater](NullOptPtr<TextureAsset>) { updater(); });
      case MapParalaxLayerObjectType::kVfx:
        return VisualEffectResource::LoadWithCallback(file_path, [updater](NullOptPtr<VisualEffectResource>) { updater(); });
      }
    }

    return {};
  }

protected:

  void HandleTextureChanged();

private:
  NotNullPtr<MapEditor> m_Editor;

  MapDef & m_Map;
  int m_LayerIndex;

  Optional<Vector2> m_PreviewPosition;

  std::vector<std::size_t> m_SelectedParalaxObjects;
  Vector2 m_SelectedParalaxObjectOffset;

  DocumentSubValueListMirror m_ObjectMirror;
  Delegate<NullOptPtr<MapEditorParalaxObjectManagerElement>, std::size_t> m_GetObject;

  bool m_Hidden = false;
  bool m_Collapsed = false;

  DocumentValueWatcher m_TextureWatcher;
  AssetReference<TextureAsset> m_TextureAsset;
};
