
#include "StormData/StormDataJson.h"

#include "Foundation/BasicTypes/BasicTypeFuncs.h"

#include "Runtime/Map/MapTileJson.h"

#include "Engine/Rendering/VertexBufferBuilder.h"
#include "Engine/Rendering/VertexList.h"
#include "Engine/Shader/ShaderManager.h"

#include "MapEditorEffectLayer.h"
#include "MapEditor.h"


MapEditorEffectLayer::MapEditorEffectLayer(NotNullPtr<MapEditor> editor, MapDef & map, int layer_index) :
  m_Editor(editor),
  m_Map(map),
  m_LayerIndex(layer_index)
{

}

void MapEditorEffectLayer::Draw(VertexBuffer & buffer, const Box & viewport_bounds, RenderVec2 & screen_center)
{

}

void MapEditorEffectLayer::ToggleHidden()
{
  m_Hidden = !m_Hidden;
}

void MapEditorEffectLayer::SetHidden(bool hidden)
{
  m_Hidden = hidden;
}

bool MapEditorEffectLayer::IsHidden()
{
  return m_Hidden;
}
