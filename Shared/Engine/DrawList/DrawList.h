#pragma once

#include <map>

#include "Engine/EngineCommon.h"

class RenderState;
class GameContainer;

using DrawListRenderCall = Delegate<void, GameContainer &, const Box &, const RenderVec2 &, RenderState &>;

class DrawList
{
public:
  DrawList();
  ~DrawList();

  DrawList(const DrawList & rhs) = delete;
  DrawList(DrawList && rhs) = delete;

  DrawList & operator = (const DrawList & rhs) = delete;
  DrawList & operator = (DrawList && rhs) = delete;
 
  void Clear();

  void PushDraw(int layer_order, int draw_key, DrawListRenderCall && cb);
  void Draw(GameContainer & world, const Box & viewport_bounds, const RenderVec2 & screen_center, RenderState & render_state);

private:

  std::map<int, std::vector<std::pair<int, DrawListRenderCall>>> m_DrawCallbacks;
};

