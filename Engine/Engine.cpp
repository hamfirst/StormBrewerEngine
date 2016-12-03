
#include "Engine/EngineCommon.h"
#include "Engine/Engine.h"

#include "Foundation/Network/Network.h"

#include <gl3w/gl3w.h>
#include <SDL/SDL.h>

#include <freetype/ft2build.h>
#include FT_FREETYPE_H

#include "Engine/Asset/AssetLoader.h"
#include "Engine/Audio/AudioManager.h"
#include "Engine/Text/TextManager.h"
#include "Engine/Rendering/RenderState.h"
#include "Engine/Window/WindowManager.h"

static bool s_Quit = false;

FT_Library g_FreeType;

bool EngineInit()
{
  NetworkInit();

  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK) < 0)
  {
    fprintf(stderr, "Could not start SDL");
    return false;
  }

  if (FT_Init_FreeType(&g_FreeType))
  {
    fprintf(stderr, "Could not start FreeType");
    return false;
  }

  g_AssetLoader.Init();
  g_AudioManager.Init();

  return true;
}

bool EngineRenderInit()
{
  gl3wInit();
  g_TextManager.Init();

  return true;
}

void EngineUpdate()
{
  g_AssetLoader.ProcessResponses();

  SDL_Event e;
  while (SDL_PollEvent(&e))
  {
    if (e.type == SDL_QUIT)
    {
      s_Quit = true;
    }
    else if (e.type == SDL_KEYDOWN)
    {
      g_WindowManager.HandleKeypressMessage(e.key.windowID, e.key.keysym.scancode, true);
    }
    else if (e.type == SDL_KEYUP)
    {
      g_WindowManager.HandleKeypressMessage(e.key.windowID, e.key.keysym.scancode, false);
    }
    else if (e.type == SDL_WINDOWEVENT)
    {
      if (e.window.event == SDL_WINDOWEVENT_FOCUS_GAINED)
      {
        g_WindowManager.SetWindowFocused(e.window.windowID, true);
      }
      else if (e.window.event == SDL_WINDOWEVENT_FOCUS_LOST)
      {
        g_WindowManager.SetWindowFocused(e.window.windowID, true);
      }
    }
  }

  g_WindowManager.UpdateInput();
}

void EngineCleanup()
{
  g_AssetLoader.ShutDown();
  g_AudioManager.ShutDown();
  g_TextManager.ShutDown();

  NetworkShutdown();
}

bool EngineWantsToQuit()
{
  return s_Quit;
}
