
#include <iostream>
#include <vector>
#include <functional>

#include <SDL2/SDL.h>

#include <gl3w/gl3w.h>

#undef max
#undef min

#include "Foundation/Common.h"
#include "Foundation/HistoryList/HistoryList.h"

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
#include "Engine/Profiler/Profiler.h"

#include "Runtime/Entity/EntityResource.h"
#include "Runtime/Sprite/SpriteResource.h"
#include "Runtime/Map/MapResource.h"

#include "GameClient/GameContainer.h"
#include "GameClient/GameCamera.h"

#include "Foundation/Pathfinding/Pathfinding.h"
#include "Foundation/Pathfinding/GraphPathfinding.h"
#include "Foundation/Pathfinding/GridPathfinding.h"

#ifdef _WEB
#include <emscripten.h>
#include <emscripten/html5.h>
#endif

#ifdef _MSC_VER
#include <io.h>
#include <fcntl.h>
#endif

#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "Imm32.lib")
#pragma comment(lib, "Version.lib")
#pragma comment(lib, "Opengl32.lib")

std::unique_ptr<GameContainer> s_GameContainer;

extern int g_LagSim;
extern czstr g_AccountName;

extern "C"
{
  void SetAccountName(czstr account_name)
  {
    g_AccountName = account_name;
  }
}

void StormWebrtcStaticInit();
void StormWebrtcStaticCleanup();

struct HistoryListData
{
  int m_List;
  int m_Frame;
  int m_Data;
};

int main(int argc, char *argv[])
{
#ifdef _MSC_VER
  AllocConsole();
  AttachConsole(GetCurrentProcessId());
  freopen("CON", "w", stdout);
#endif

#ifdef _DEBUG
  g_LagSim = 0;
#endif

#ifdef _WEB
  int multiplier = 1;

  EM_ASM(if (typeof window['EmscriptenLoadComplete'] === 'function') { EmscriptenLoadComplete() });
  SDL_SetHint(SDL_HINT_EMSCRIPTEN_KEYBOARD_ELEMENT, "#canvas");
#else

  int multiplier = 3;
#endif
  for (int index = 0; index < argc; index++)
  {
    if (!strcmp(argv[index], "-native"))
    {
      multiplier = 1;
    }
  }

#ifndef _WEB
  g_AssetLoader.DisableNetworkLoading();
#endif

  InitServerTypes();
  EngineInit(true);

#if defined(NET_USE_WEBRTC) && !defined(_WEB)
  StormWebrtcStaticInit();
#endif

  Vector2 resolution(kDefaultResolutionWidth, kDefaultResolutionHeight);
  resolution *= multiplier;

  auto window = g_WindowManager.CreateNewWindow("Game Title!", resolution.x, resolution.y);
  window.MakeCurrent();
  //window.SetVsyncEnabled(false);

  EngineRenderInit();

  g_TextManager.LoadFont("./Fonts/FFF.ttf", -1, 8);

  auto init_settings = std::make_unique<GameContainerInitSettings>();
  //init_settings->m_AutoBotGame = true;
  s_GameContainer = std::make_unique<GameContainer>(window, std::move(init_settings));

#ifdef _WEB

  emscripten_set_main_loop([]()
  {    
    ResetProfiler();

    {
      PROFILE_SCOPE("Engine update");
      EngineUpdate();
    }

    s_GameContainer->Update();
    s_GameContainer->Render();

  }, 0, false);

  emscripten_set_click_callback("canvas", s_GameContainer.get(), true, [](int type, const EmscriptenMouseEvent * ev, void * userdata) -> int
  {
    GameContainer * container = (GameContainer *)userdata;
    EngineUpdate();
    container->InputEvent();
    return 0;
  });

  emscripten_set_keypress_callback("canvas", s_GameContainer.get(), true, [](int type, const EmscriptenKeyboardEvent * ev, void * userdata) -> int
  {
    GameContainer * container = (GameContainer *)userdata;
    EngineUpdate();
    container->InputEvent();
    return 0;
  });

  emscripten_set_fullscreenchange_callback("canvas", s_GameContainer.get(), true, [](int type, const EmscriptenFullscreenChangeEvent * ev, void * userdata) -> int
  {
    printf("Got fullscreen event\n");
    GameContainer * container = (GameContainer *)userdata;
    auto & window = container->GetWindow();
    auto window_id = window.GetWindowId();

    g_WindowManager.HandleFullscreenChanged(window_id, ev->isFullscreen);
    return 0;
  });

  return 0;
#else

  while (EngineWantsToQuit() == false)
  {
    ResetProfiler();

    {
      PROFILE_SCOPE("Engine update");
      EngineUpdate();
    }

    s_GameContainer->Update();
    s_GameContainer->Render();
  }

  s_GameContainer.reset();
  EngineCleanup();

  SDL_Quit();

#if defined(NET_USE_WEBRTC) && !defined(_WEB)
  StormWebrtcStaticCleanup();
#endif

  return 0;

#endif
}
