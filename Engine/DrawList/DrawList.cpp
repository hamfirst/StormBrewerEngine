
#include "Engine/EngineCommon.h"
#include "Engine/DrawList/DrawList.h"

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

void DrawList::PushDraw(int layer_order, DrawListRenderCall && cb)
{
  auto itr = m_DrawCallbacks.find(layer_order);
  if (itr == m_DrawCallbacks.end())
  {
    auto result = m_DrawCallbacks.emplace(std::make_pair(layer_order, std::vector<DrawListRenderCall>{}));
    itr = result.first;
  }

  itr->second.emplace_back(std::move(cb));
}

void DrawList::Draw(GameContainer & game_container, const Box & viewport_bounds, const RenderVec2 & screen_center, RenderState & render_state, RenderUtil & render_util)
{
  for (auto & elem : m_DrawCallbacks)
  {
    for (auto & cb : elem.second)
    {
      cb(game_container, viewport_bounds, screen_center, render_state, render_util);
    }
  }
}
