
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
#include "GameClient/GameContainer.h"
#include "GameClient/GameRender.h"

#ifdef _WEB
#include <emscripten.h>
#include <emscripten/html5.h>
#endif


#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "Imm32.lib")
#pragma comment(lib, "Version.lib")
#pragma comment(lib, "Opengl32.lib")


std::unique_ptr<GameContainer> s_GameContainer;

int main(int argc, char *argv[])
{
  int multiplier = 3;
  for (int index = 0; index < argc; index++)
  {
    if (!strcmp(argv[index], "-native"))
    {
      multiplier = 1;
    }
  }

  //g_AssetLoader.DisableNetworkLoading();
  EngineInit(true);

  Vector2 resolution(320, 180);
  resolution *= multiplier;

  auto window = g_WindowManager.CreateNewWindow("Game Title!", resolution.x, resolution.y);
  window.MakeCurrent();

  EngineRenderInit();

  g_TextManager.LoadFont("./Fonts/arial.ttf", -1, 12);
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
  return 0;

#endif
}
