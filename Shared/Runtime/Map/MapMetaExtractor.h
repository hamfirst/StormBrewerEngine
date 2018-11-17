#pragma once

#include "Runtime/RuntimeCommon.h"
#include "Runtime/Map/MapDef.refl.h"

struct MapComponentInitDataInfo
{
  Vector2 m_Position;
  int m_Layer;
};

template <typename Component, typename InitData>
void MapExtractComponentInitData(MapDef & map, std::vector<std::pair<MapComponentInitDataInfo, NotNullPtr<InitData>>> & outp_data)
{
  auto component_type_name = Component::TypeNameHash;
  for (auto & layer : map.m_EntityLayers)
  {
    for (auto & entity : layer.second.m_Entities)
    {
      for (auto & comp : entity.second.m_EntityDef.m_Components)
      {
        if (comp.second.GetTypeNameHash() == component_type_name)
        {
          MapComponentInitDataInfo init_data;
          init_data.m_Position = Vector2(entity.second.m_XPosition, entity.second.m_YPosition);
          init_data.m_Layer = layer.second.m_LayerOrder;

          outp_data.emplace_back(std::make_pair(init_data, static_cast<InitData *>(comp.second.GetValue())));
        }
      }
    }
  }
}

