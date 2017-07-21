#pragma once

#include <map>

#include "Engine/EngineCommon.h"

class RenderState;
class RenderUtil;
class GameContainer;

using DrawListRenderCall = Delegate<void, GameContainer &, const Box &, const RenderVec2 &, RenderState &, RenderUtil &>;

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

  void PushDraw(int layer_order, DrawListRenderCall && cb);
  void Draw(GameContainer & game_container, const Box & viewport_bounds, const RenderVec2 & screen_center, RenderState & render_state, RenderUtil & render_util);

private:

  std::map<int, std::vector<DrawListRenderCall>> m_DrawCallbacks;
};

