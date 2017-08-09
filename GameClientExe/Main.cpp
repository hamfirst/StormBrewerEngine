
#include <iostream>
#include <vector>
#include <functional>

#include <SDL2/SDL.h>

#include <gl3w/gl3w.h>

#undef max
#undef min

#include "Foundation/Common.h"

#include "StormData/StormDataJson.h"

#include "Engine/Engine.h"
#include "Engine/Asset/AssetLoader.h"
#include "Engine/Asset/AssetBundle.h"
#include "Engine/Text/TextManager.h"
#include "Engine/Rendering/Rendering.h"
#include "Engine/Rendering/RenderUtil.h"
#include "Engine/Window/WindowManager.h"
#include "Engine/Shader/ShaderManager.h"
#include "Engine/Camera/Camera.h"
#include "Engine/Entity/Entity.h"
#include "Engine/EngineState.h"

#include "Runtime/Entity/EntityResource.h"
#include "Runtime/Sprite/SpriteResource.h"
#include "Runtime/Map/MapResource.h"

#include "GameClient/GameContainer.h"
#include "GameClient/GameCamera.h"

#include "Foundation/Pathfinding/GridPathfinding.h"





#ifdef _WEB
#include <emscripten.h>
#include <emscripten/html5.h>
#endif


#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "Imm32.lib")
#pragma comment(lib, "Version.lib")
#pragma comment(lib, "Opengl32.lib")

std::unique_ptr<GameContainer> s_GameContainer;


void StormWebrtcStaticInit();
void StormWebrtcStaticCleanup();

int main(int argc, char *argv[])
{
  int multiplier = 2;
  for (int index = 0; index < argc; index++)
  {
    if (!strcmp(argv[index], "-native"))
    {
      multiplier = 1;
    }
  }

  PathfindingBasicTraversalGrid<> grid(Vector2(3, 3));
  grid.SetGridData(1, 1, true);

  auto result = Pathfinding<PathfindingBasicTraversalGrid<>>::FindPath(0, 8, grid);

  //g_AssetLoader.DisableNetworkLoading();
  EngineInit(true);

#ifdef NET_USE_WEBRTC
  StormWebrtcStaticInit();
#endif

  Vector2 resolution(kDefaultResolutionWidth, kDefaultResolutionHeight);
  resolution *= multiplier;

  auto window = g_WindowManager.CreateNewWindow("Game Title!", resolution.x, resolution.y);
  window.MakeCurrent();

  EngineRenderInit();

  g_TextManager.LoadFont("./Fonts/FFF.ttf", -1, 8);
  g_TextManager.LoadFont("./Fonts/Arial.ttf", -2, 25);
  s_GameContainer = std::make_unique<GameContainer>(window);

#ifdef _WEB

  emscripten_set_main_loop([]()
  {
    EngineUpdate();
    s_GameContainer->Update();
    s_GameContainer->Render();

  }, 0, false);

  return 0;
#else

  while (EngineWantsToQuit() == false)
  {
    EngineUpdate();
    s_GameContainer->Update();
    s_GameContainer->Render();
  }

  s_GameContainer.reset();
  EngineCleanup();

  SDL_Quit();

#ifdef NET_USE_WEBRTC
  StormWebrtcStaticCleanup();
#endif
  return 0;

#endif
}
