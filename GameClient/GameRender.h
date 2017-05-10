#pragma once

#include "Game/GameState.h"
#include "Game/GameSimulation.refl.h"

#include "Foundation/SparseList/SparseList.h"

#include "Engine/Camera/Camera.h"

class GameRender
{
public:
  void RenderGame(GameState & game_state, ClientLocalData & local_data, RenderState & render_state, Camera & camera);

private:

};
