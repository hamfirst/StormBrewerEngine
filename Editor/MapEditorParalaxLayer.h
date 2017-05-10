#pragma once

#include "Foundation/Common.h"

#include "Runtime/Map/MapDef.refl.h"

#include "Engine/Asset/TextureAsset.h"
#include "Engine/Rendering/VertexBuffer.h"

#include "DocumentValueWatcher.h"

class MapEditor;
class RenderUtil;

class MapEditorParalaxLayer
{
public:
  MapEditorParalaxLayer(NotNullPtr<MapEditor> editor, MapDef & map, int layer_index);

  void Draw(VertexBuffer & buffer, const Box & viewport_bounds, RenderVec2 & screen_center);

  void ToggleHidden();
  void SetHidden(bool hidden);
  bool IsHidden();

protected:

  void HandleTextureChanged();

private:
  NotNullPtr<MapEditor> m_Editor;

  MapDef & m_Map;
  int m_LayerIndex;
  bool m_Hidden = false;

  DocumentValueWatcher m_TextureWatcher;
  AssetReference<TextureAsset> m_TextureAsset;
};
