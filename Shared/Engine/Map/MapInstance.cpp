
#include "Engine/EngineCommon.h"

#include "Runtime/TileSheet/TileSheetResource.h"

#include "Engine/EngineState.h"
#include "Engine/Map/MapInstance.h"
#include "Engine/Entity/Entity.h"
#include "Engine/Entity/EntityHandle.h"
#include "Engine/Entity/EntitySystem.h"
#include "Engine/Rendering/RenderSettings.h"

MapInstance::MapInstance(NotNullPtr<EngineState> engine_state, MapDef & map_def, std::size_t map_id, const Vector2 & offset) :
  m_MapId(map_id),
  m_Offset(offset)
{
  for (auto elem : map_def.m_ManualTileLayers)
  {
    m_ManualTileLayers.emplace_back(map_def, elem.first, offset);
  }

  for (auto elem : map_def.m_EffectLayers)
  {
    m_EffectLayers.emplace_back(map_def, elem.first);
  }

  for (auto elem : map_def.m_ParalaxLayers)
  {
    m_ParalaxLayers.emplace_back(map_def, elem.first, engine_state->GetVisualEffectManager());
  }

  std::vector<Entity *> entities;
  for (auto elem : map_def.m_EntityLayers)
  {
    for (auto entity : elem.second.m_Entities)
    {
      auto new_entity = engine_state->m_EntitySystem->CreateEntity(&entity.second.m_EntityDef, false);
      new_entity->GetPosition() = Vector2(entity.second.m_XPosition, entity.second.m_YPosition);
      new_entity->GetLayer() = elem.second.m_LayerOrder;
      entities.push_back(new_entity);
    }
  }

  for (auto entity : entities)
  {
    m_MapEntities.push_back(entity->GetHandle());
  }
}

void MapInstance::Init(GameContainer & game_container)
{
  for (auto & layer : m_EffectLayers)
  {
    layer.Init(game_container);
  }

  for (auto & elem : m_MapEntities)
  {
    auto entity = elem.Resolve();
    if (entity)
    {
      entity->Activate();
    }
  }
}

void MapInstance::Update(GameContainer & game_container)
{
  for (auto & layer : m_ManualTileLayers)
  {
    layer.Update();
  }

  for (auto & layer : m_ParalaxLayers)
  {
    layer.Update();
  }

  for (auto & layer : m_EffectLayers)
  {
    layer.Update(game_container);
  }
}

void MapInstance::Draw(const Box & viewport_bounds, DrawList & draw_list)
{
  for (auto & layer : m_ParalaxLayers)
  {
    draw_list.PushDraw(layer.GetLayerOrder(), INT_MAX, [&](GameContainer & game_container, const Box & viewport_bounds, const RenderVec2 & screen_center, RenderState & render_state)
    {
      layer.Draw(viewport_bounds, screen_center, m_Offset, render_state);
    });
  }

  for (auto & layer : m_ManualTileLayers)
  {
    draw_list.PushDraw(layer.GetLayerOrder(), INT_MAX, [&](GameContainer & game_container, const Box & viewport_bounds, const RenderVec2 & screen_center, RenderState & render_state)
    {
      layer.Draw(viewport_bounds, screen_center, render_state);
    });

#ifdef USE_Z_ORDERING
    layer.DrawDynamic(viewport_bounds, draw_list);
#endif
  }

  for (auto & layer : m_EffectLayers)
  {
    draw_list.PushDraw(layer.GetLayerOrder(), INT_MAX, [&](GameContainer & game_container, const Box & viewport_bounds, const RenderVec2 & screen_center, RenderState & render_state)
    {
      layer.Draw(game_container, viewport_bounds, screen_center, m_Offset, render_state);
    });
  }
}
