
#include "Engine/EngineCommon.h"
#include "Engine/Map/MapEffectLayerInstance.h"
#include "Engine/Map/MapEffectLayerRenderer.h"

#include "Runtime/Map/MapEffectLayerTypeDatabase.h"


MapEffectLayerInstance::MapEffectLayerInstance(MapDef & map, std::size_t layer_index)
{
  auto & layer_data = map.m_EffectLayers[(int)layer_index];
  m_LayerOrder = layer_data.m_LayerOrder;

  auto effect_type_info = layer_data.m_EffectLayerData.GetTypeInfo();
  if (effect_type_info)
  {
    m_Renderer = effect_type_info->m_CreateCodeObj(layer_data.m_EffectLayerData.GetValue());
  }
}

void MapEffectLayerInstance::Update(GameContainer & game_container)
{
  if (m_Renderer)
  {
    m_Renderer->Update(game_container);
  }
}

void MapEffectLayerInstance::Draw(GameContainer & game_container, const Box & viewport_bounds, const RenderVec2 & screen_center, RenderState & render_state, RenderUtil & render_util)
{
  if (m_Renderer)
  {
    m_Renderer->Render(game_container, viewport_bounds, screen_center, render_state, render_util);
  }
}

int MapEffectLayerInstance::GetLayerOrder() const
{
  return m_LayerOrder;
}

