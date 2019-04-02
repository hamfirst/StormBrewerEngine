#pragma once

#include "Foundation/Common.h"

#include "Runtime/Map/MapDef.refl.h"
#include "Runtime/VisualEffect/VisualEffectResource.h"

#include "Engine/Asset/TextureAsset.h"
#include "Engine/Rendering/VertexBuffer.h"

#include "DocumentValueWatcher.h"
#include "DocumentSubValueListMirror.h"

class MapEditor;

using MapEditorParallaxObjectType = Variant<TextureAsset::LoadCallbackLink, SpriteLoadLink, VisualEffectLoadLink>;

struct MapEditorParallaxObjectManagerElement
{
  MapEditorParallaxObjectType m_Object;
  Optional<Box> m_Frame;
};

class MapEditorParallaxLayer
{
public:
  MapEditorParallaxLayer(NotNullPtr<MapEditor> editor, MapDef & map, int layer_index);

  void AddParallaxObject(const MapParallaxLayerObject & parallax_object_data);
  void RemoveParallaxObject(std::size_t index);

  void SetPreviewParallaxObjectPosition(const Vector2 & pos);
  void ClearPreviewParallaxObject();
  void CommitPreviewParallaxObject();

  void SelectParallaxObjects(const Box & box);
  Optional<MapParallaxLayerObject> FindParallaxObject(const Vector2 & pos);
  void DropSelection();
  void ClearSelection();
  void DeselectParallaxObjects();
  void DeleteSelectedParallaxObjects();
  void MoveSelection(const Vector2 & offset);
  bool IsOnSelectedParallaxObject(const Vector2 & pos);

  void SetSingleSelection(std::size_t parallax_object_index);
  Optional<std::size_t> GetSingleSelectionIndex();

  void Draw(VertexBuffer & buffer, const Box & viewport_bounds, const RenderVec2 & screen_center, RenderState & render_state);
  void DrawPreviewParallaxObject(VertexBuffer & buffer, const Box & viewport_bounds, const RenderVec2 & screen_center, RenderState & render_state);
  void DrawSelection(VertexBuffer & vertex_buffer, const Box & viewport_bounds, const RenderVec2 & screen_center, RenderState & render_state);

  Optional<Box> DrawObject(MapEditorParallaxObjectType & object, MapParallaxLayerObject & object_data,
    const Vector2 & pos, VertexBuffer & buffer, const Box & viewport_bounds, const RenderVec2 & screen_center, RenderState & render_state);

  void ToggleHidden();
  void SetHidden(bool hidden);
  bool IsHidden();

  void ToggleColapsed();
  bool IsCollapsed();

  static Optional<MapParallaxLayerObjectType> GetParallaxTypeForPath(czstr file_path);

  template <typename Updater>
  static MapEditorParallaxObjectType CreateObjectFromPath(czstr file_path, Updater && updater)
  {
    auto type = GetParallaxTypeForPath(file_path);

    if (type)
    {
      switch (type.Value())
      {
      case MapParallaxLayerObjectType::kSprite:
        return SpriteResource::LoadWithCallback(file_path, [updater](NullOptPtr<SpriteResource>) { updater(); });
      case MapParallaxLayerObjectType::kTexture:
        return TextureAsset::LoadWithCallback(file_path, [updater](NullOptPtr<TextureAsset>) { updater(); });
      case MapParallaxLayerObjectType::kVfx:
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

  std::vector<std::size_t> m_SelectedParallaxObjects;
  Vector2 m_SelectedParallaxObjectOffset;

  DocumentSubValueListMirror m_ObjectMirror;
  Delegate<NullOptPtr<MapEditorParallaxObjectManagerElement>, std::size_t> m_GetObject;

  bool m_Hidden = false;
  bool m_Collapsed = false;

  DocumentValueWatcher m_TextureWatcher;
  AssetReference<TextureAsset> m_TextureAsset;
};
