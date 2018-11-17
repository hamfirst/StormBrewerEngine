
#include "Engine/EngineCommon.h"
#include "Engine/DrawList/DrawList.h"
#include "Engine/Rendering/RenderSettings.h"

DrawList::DrawList()
{

}

DrawList::~DrawList()
{

}

void DrawList::Clear()
{
  m_DrawCallbacks.clear();
}

void DrawList::PushDraw(int layer_order, int draw_key, DrawListRenderCall && cb)
{
  auto itr = m_DrawCallbacks.find(layer_order);
  if (itr == m_DrawCallbacks.end())
  {
    auto result = m_DrawCallbacks.emplace(std::make_pair(layer_order, std::vector<std::pair<int, DrawListRenderCall>>{}));
    itr = result.first;
  }

  itr->second.emplace_back(std::make_pair(draw_key, std::move(cb)));
}

void DrawList::Draw(GameContainer & game_container, const Box & viewport_bounds, const RenderVec2 & screen_center, RenderState & render_state, RenderUtil & render_util)
{
  for (auto & elem : m_DrawCallbacks)
  {
#ifdef USE_Z_ORDERING
    std::stable_sort(elem.second.begin(), elem.second.end(), [](const std::pair<int, DrawListRenderCall> & a, const std::pair<int, DrawListRenderCall> & b) { return a.first > b.first; });
#endif

    for (auto & draw_info : elem.second)
    {
      draw_info.second(game_container, viewport_bounds, screen_center, render_state, render_util);
    }
  }
}
