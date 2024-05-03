#pragma once

#include "Foundation/Common.h"

#include "Runtime/Map/MapDef.refl.h"

#include "Engine/Asset/TextureAsset.h"
#include "Engine/Rendering/VertexBuffer.h"

#include "Tools/Editor/Utility/DocumentValueWatcher.h"

class MapEditor;

class MapEditorEffectLayer
{
public:
  MapEditorEffectLayer(NotNullPtr<MapEditor> editor, MapDef & map, int layer_index);

  void Draw(VertexBuffer & buffer, const Box & viewport_bounds, RenderVec2 & screen_center);

  void ToggleHidden();
  void SetHidden(bool hidden);
  bool IsHidden();

private:
  NotNullPtr<MapEditor> m_Editor;

  MapDef & m_Map;
  int m_LayerIndex;
  bool m_Hidden = false;
};
