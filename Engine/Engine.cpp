
#include "Engine/EngineCommon.h"
#include "Engine/Engine.h"

#include "Foundation/Network/Network.h"

#include "Runtime/Runtime.h"

#include <gl3w/gl3w.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_revision.h>

#include <freetype2/ft2build.h>
#include FT_FREETYPE_H

#include "Engine/Asset/AssetLoader.h"
#include "Engine/Audio/AudioManager.h"
#include "Engine/Text/TextManager.h"
#include "Engine/Rendering/RenderState.h"
#include "Engine/Window/WindowManager.h"
#include "Engine/Shader/ShaderManager.h"
#include "Engine/Input/GamepadState.h"

static bool s_Quit = false;
static bool s_EGLMode = false;

FT_Library g_FreeType;

#ifdef _MSC_VER

#ifdef _WIN64
#pragma comment(lib, "../External/Windows/angle/x64/libEGL.lib")
#pragma comment(lib, "../External/Windows/angle/x64/libGLESv2.lib")
#else
#pragma comment(lib, "../External/Windows/angle/libEGL.lib")
#pragma comment(lib, "../External/Windows/angle/libGLESv2.lib")
#endif
#endif

bool EngineInit(bool egl_mode)
{
  NetworkInit();
  RuntimeInit();

  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMECONTROLLER) < 0)
  {
    fprintf(stderr, "Could not start SDL");
    return false;
  }

  s_EGLMode = egl_mode;
  if (s_EGLMode)
  {
#if SDL_REVISION_NUMBER >= 10864
    SDL_SetHint(SDL_HINT_OPENGL_ES_DRIVER, "true");
#endif
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
  }

  SDL_SetHintWithPriority(SDL_HINT_MOUSE_RELATIVE_MODE_WARP, "1", SDL_HINT_OVERRIDE);

  if (FT_Init_FreeType(&g_FreeType))
  {
    fprintf(stderr, "Could not start FreeType");
    return false;
  }

  g_AssetLoader.Init();
  g_AudioManager.Init();

  GamepadState::Init();

  return true;
}

bool EngineRenderInit()
{
  gl3wInit(s_EGLMode);
  g_TextManager.Init();
  g_ShaderManager.Init();


  BootstrapContext();

  return true;
}

void EngineUpdate()
{
  g_AssetLoader.ProcessResponses();
  g_WindowManager.UpdateInput();

  SDL_Event e;
  while (SDL_PollEvent(&e))
  {
    if (e.type == SDL_QUIT)
    {
      s_Quit = true;
    }
    else if (e.type == SDL_KEYDOWN)
    {
      g_WindowManager.HandleKeyPressMessage(e.key.windowID, e.key.keysym.sym, e.key.keysym.scancode, true);
    }
    else if (e.type == SDL_KEYUP)
    {
      g_WindowManager.HandleKeyPressMessage(e.key.windowID, e.key.keysym.sym, e.key.keysym.scancode, false);
    }
    else if (e.type == SDL_MOUSEBUTTONDOWN)
    {
      g_WindowManager.HandleMouseButtonPressMessage(e.button.windowID, e.button.button, true);
    }
    else if (e.type == SDL_MOUSEBUTTONUP)
    {
      g_WindowManager.HandleMouseButtonPressMessage(e.button.windowID, e.button.button, false);
    }
    else if (e.type == SDL_MOUSEMOTION)
    {
      if (SDL_GetRelativeMouseMode())
      {
        g_WindowManager.HandleMouseMotionMessage(e.motion.windowID, e.motion.x, e.motion.y);
      }
      else
      {
        g_WindowManager.HandleMouseMotionMessage(e.motion.windowID, e.motion.x, e.motion.y);
      }
    }
    else if (e.type == SDL_CONTROLLERDEVICEADDED)
    {
      GamepadState::GamepadConnected(e.cdevice.which);
    }
    else if (e.type == SDL_CONTROLLERDEVICEREMOVED)
    {
      GamepadState::GamepadDisonnected(e.cdevice.which);
    }
    else if (e.type == SDL_WINDOWEVENT)
    {
      if (e.window.event == SDL_WINDOWEVENT_FOCUS_GAINED)
      {
        g_WindowManager.SetWindowKeyboardFocused(e.window.windowID, true);
      }
      else if (e.window.event == SDL_WINDOWEVENT_FOCUS_LOST)
      {
        g_WindowManager.SetWindowKeyboardFocused(e.window.windowID, false);
      }
      if (e.window.event == SDL_WINDOWEVENT_ENTER)
      {
        g_WindowManager.SetWindowMouseFocused(e.window.windowID, true);
      }
      else if (e.window.event == SDL_WINDOWEVENT_LEAVE)
      {
        g_WindowManager.SetWindowMouseFocused(e.window.windowID, false);
      }
      else if (e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
      {
        g_WindowManager.SetWindowSize(e.window.windowID, Vector2(e.window.data1, e.window.data2));
      }
      else if (e.window.event == SDL_WINDOWEVENT_MOVED)
      {
        g_WindowManager.SetWindowPos(e.window.windowID, Vector2(e.window.data1, e.window.data2));
      }
    }
    else if (e.type == SDL_TEXTINPUT)
    {
      g_WindowManager.HandleTextInputCommit(e.text.windowID, e.text.text);
    }
    else if (e.type == SDL_TEXTEDITING)
    {
      g_WindowManager.HandleTextInputComposition(e.edit.windowID, e.edit.text);
    }
  }
}

void EngineCleanup()
{
  GamepadState::Cleanup();

  SDL_Quit();

  g_AssetLoader.ShutDown();
  g_AudioManager.ShutDown();
  g_TextManager.ShutDown();
  g_ShaderManager.Shutdown();

  RuntimeCleanup();
  NetworkShutdown();
}

bool EngineWantsToQuit()
{
  return s_Quit;
}
