
#include <iostream>
#include <vector>
#include <functional>

#include <SDL2/SDL.h>

#include <gl3w/gl3w.h>

#undef main
#undef max
#undef min

#include "Foundation/Common.h"

#include <StormData/StormDataJson.h>

#include "Engine/Engine.h"
#include "Engine/Asset/AssetLoader.h"
#include "Engine/Text/TextManager.h"
#include "Engine/Rendering/Rendering.h"
#include "Engine/Rendering/RenderUtil.h"
#include "Engine/Window/WindowManager.h"
#include "Engine/Shader/ShaderManager.h"
#include "Engine/Camera/Camera.h"

#include "Runtime/RuntimeState.h"
#include "Runtime/Entity/Entity.h"
#include "Runtime/Entity/EntityResource.h"
#include "Runtime/Sprite/SpriteResource.h"
#include "Runtime/Map/MapResource.h"

#include "Shared/AssetBundle/AssetBundle.h"

#include "Game/GameState.h"
#include "GameClient/GameRender.h"


#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "Imm32.lib")
#pragma comment(lib, "Version.lib")
#pragma comment(lib, "Opengl32.lib")

int SDL_main(int argc, char *argv[])
{
  EngineInit(true);

  Vector2 resolution(320, 180);
  int multiplier = 3;

  for (int index = 0; index < argc; index++)
  {
    if (!strcmp(argv[index], "-native"))
    {
      multiplier = 1;
    }
  }

  auto window = g_WindowManager.CreateNewWindow("Game Title!", resolution.x * multiplier, resolution.y * multiplier);
  window.MakeCurrent();

  EngineRenderInit();

  RenderState render_state;
  render_state.InitRenderState(resolution.x, resolution.y);

  RenderUtil render_util;
  render_util.SetClearColor(Color(100, 149, 237, 255));
  render_util.LoadShaders();

  g_TextManager.LoadFont("Fonts/arial.ttf", -1, 15);

  g_AssetLoader.DisableNetworkLoading();

  GameState game_state;

  AssetBundle bundle;
  bundle.LoadAsset<MapResource>("./Maps/Test.map");
  bool loaded = false;

  Camera camera(resolution);

  while (EngineWantsToQuit() == false)
  {
    EngineUpdate();

    RenderUtil::Clear();

    if (loaded == false && bundle.AllLoadedSuccessfully())
    {
      auto map = MapResource::Load("./Maps/Test.map");
      game_state.LoadMap(map.GetResource());
      loaded = true;
    }

    if (loaded)
    {
      game_state.Update();
    }

    window.Swap();
  }

  EngineCleanup();

  SDL_Quit();
  return 0;
}
