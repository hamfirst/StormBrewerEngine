
#include "Engine/EngineCommon.h"
#include "Engine/Engine.h"

#include <gl3w/gl3w.h>
#include <SDL/SDL.h>

#include <freetype/ft2build.h>
#include FT_FREETYPE_H

#include "Engine/Asset/AssetLoader.h"
#include "Engine/Audio/AudioManager.h"
#include "Engine/Text/TextManager.h"
#include "Engine/Rendering/RenderState.h"

static bool s_Quit = false;
static bool s_Focused = false;

FT_Library g_FreeType;

bool EngineInit()
{
  gl3wInit();

  BootstrapContext();

  if (FT_Init_FreeType(&g_FreeType))
  {
    fprintf(stderr, "Could not start FreeType");
    return false;
  }

  g_AssetLoader.Init();
  g_AudioManager.Init();

  g_TextManager.Init();

  return true;
}

void EngineUpdate()
{
  g_AssetLoader.ProcessResponses();

  SDL_Event e;
  while (SDL_PollEvent(&e))
  {
    if (e.type == SDL_KEYDOWN)
    {

    }
    else if (e.type == SDL_WINDOWEVENT)
    {
      if (e.window.event == SDL_WINDOWEVENT_FOCUS_GAINED)
      {
        s_Focused = true;
      }
      else if (e.window.event == SDL_WINDOWEVENT_FOCUS_LOST)
      {
        s_Focused = false;
      }
    }
    else if (e.type == SDL_QUIT)
    {
      s_Quit = true;
    }
  }
}

void EngineCleanup()
{
  g_AssetLoader.ShutDown();
  g_AudioManager.ShutDown();
  g_TextManager.ShutDown();
}

void EngineSetFocused()
{
  s_Focused = true;
}

void EngineSetUnfocused()
{
  s_Focused = false;
}

bool EngineWantsToQuit()
{
  return s_Quit;
}
