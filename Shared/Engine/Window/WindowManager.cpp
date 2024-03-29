
#include "Engine/EngineCommon.h"
#include "Engine/Window/WindowManager.h"
#include "Engine/Window/FakeWindow.h"
#include "Engine/Input/InputState.h"
#include "Engine/Input/TextInputContext.h"

#include <SDL2/SDL.h>

#include "External/gl3w/gl3w.h"

#ifdef _WEB
#include <emscripten.h>
#include <emscripten/html5.h>
#endif

WindowManager g_WindowManager;
static std::unordered_map<uint32_t, std::unique_ptr<WindowState>> s_Windows;

struct ENGINE_EXPORT  WindowState
{
  SDL_Window * m_SDLWindow;
  SDL_GLContext m_Context;

  FakeWindow * m_FakeWindow;

  int m_RefCount;
  bool m_KeyboardFocus;
  bool m_MouseFocus;

  bool m_FullScreen;

  Box m_WindowGeo;

  std::unique_ptr<InputState> m_InputState;
  std::shared_ptr<TextInputContext> m_TextInputContext;
};


Window WindowManager::CreateNewWindow(czstr title, int width, int height, bool fullscreen)
{
  auto flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;
  if (fullscreen)
  {
    flags |= SDL_WINDOW_FULLSCREEN;
  }

  auto sdl_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
  if (sdl_window == nullptr)
  {
    return{};
  }

  auto context = SDL_GL_CreateContext(sdl_window);
  if(context == nullptr)
  {
    printf("Could not create context: %s\n", SDL_GetError());
  }

  uint32_t id = SDL_GetWindowID(sdl_window);

  auto result = s_Windows.emplace(std::make_pair(id, std::unique_ptr<WindowState>(new WindowState{ sdl_window, context, nullptr, 1, false, false })));
  WindowState & window = *result.first->second;

  int x, y;
  SDL_GetWindowPosition(sdl_window, &x, &y);
  window.m_WindowGeo.m_Start = Vector2(x, y);
  SDL_GetWindowSize(sdl_window, &x, &y);
  window.m_WindowGeo.m_End = window.m_WindowGeo.m_Start + Vector2(x, y);

  window.m_InputState = std::make_unique<InputState>();
  window.m_FullScreen = fullscreen;

  return Window(id);
}

Window WindowManager::CreateFakeWindow(FakeWindow * window, const Box & window_geo)
{
  uint32_t id = m_NextFakeWindowId;
  m_NextFakeWindowId++;

  auto result = s_Windows.emplace(std::make_pair(id, std::unique_ptr<WindowState>(new WindowState{ nullptr, nullptr, window, 1, false, false, false, window_geo, std::make_unique<InputState>() })));
  return Window(id);
}

void WindowManager::HandleKeyPressMessage(uint32_t window_id, int key_code, int scan_code, bool pressed)
{
  auto itr = s_Windows.find(window_id);
  if (itr == s_Windows.end()) return;
  WindowState & window = *itr->second;

  window.m_InputState->HandleKeyPressMessage(scan_code, pressed, (bool)window.m_TextInputContext);

  if (window.m_TextInputContext && pressed)
  {
    window.m_TextInputContext->HandleKeyPressEvent(key_code);
  }
}

void WindowManager::HandleMouseButtonPressMessage(uint32_t window_id, int button, bool pressed)
{
  auto itr = s_Windows.find(window_id);
  if (itr == s_Windows.end()) return;
  WindowState & window = *itr->second;

  window.m_InputState->HandleMouseButtonPressMessage(button, pressed, window.m_MouseFocus);
}

void WindowManager::HandleMouseMotionMessage(uint32_t window_id, int x, int y)
{
  auto itr = s_Windows.find(window_id);
  if (itr == s_Windows.end()) return;
  WindowState & window = *itr->second;

  window.m_InputState->HandleMouseMoveMessage(x, y, window.m_WindowGeo, window.m_MouseFocus);
}

void WindowManager::HandleMouseWheelMessage(uint32_t window_id, int dv)
{
  auto itr = s_Windows.find(window_id);
  if (itr == s_Windows.end()) return;
  WindowState & window = *itr->second;

  window.m_InputState->HandleMouseWheelMessage(dv);
}

void WindowManager::HandleTextInputCommit(uint32_t window_id, czstr character)
{
  auto itr = s_Windows.find(window_id);
  if (itr == s_Windows.end()) return;
  WindowState & window = *itr->second;

  if (window.m_TextInputContext)
  {
    window.m_TextInputContext->CommitInput(character);
  }
}

void WindowManager::HandleTextInputComposition(uint32_t window_id, czstr composition)
{
  auto itr = s_Windows.find(window_id);
  if (itr == s_Windows.end()) return;
  WindowState & window = *itr->second;

  if (window.m_TextInputContext)
  {
    window.m_TextInputContext->SetComposition(composition);
  }
}

void WindowManager::HandleFullscreenChanged(uint32_t window_id, bool enabled)
{
  auto itr = s_Windows.find(window_id);
  if (itr == s_Windows.end())
  {
    printf("Couldn't find window\n");
    return;
  }

  WindowState & window = *itr->second;

  if (window.m_SDLWindow)
  {
    printf("Setting fullscreen to %d\n", enabled ? 1 : 0);
    window.m_FullScreen = enabled;
  }
  else
  {
    printf("Not SDL window\n");
  }
}

void WindowManager::SetWindowKeyboardFocused(uint32_t window_id, bool focused)
{
  auto itr = s_Windows.find(window_id);
  if (itr == s_Windows.end()) return;
  WindowState & window = *itr->second;
  window.m_KeyboardFocus = focused;
}

void WindowManager::SetWindowMouseFocused(uint32_t window_id, bool focused)
{
  auto itr = s_Windows.find(window_id);
  if (itr == s_Windows.end()) return;
  WindowState & window = *itr->second;
  window.m_MouseFocus = focused;
}

void WindowManager::SetWindowPos(uint32_t window_id, const Vector2 & pos)
{
  auto itr = s_Windows.find(window_id);
  if (itr == s_Windows.end()) return;
  WindowState & window = *itr->second;
  auto size = window.m_WindowGeo.m_End - window.m_WindowGeo.m_Start;
  window.m_WindowGeo.m_Start = pos;
  window.m_WindowGeo.m_End = pos + size;
}

void WindowManager::SetWindowSize(uint32_t window_id, const Vector2 & size)
{
  auto itr = s_Windows.find(window_id);
  if (itr == s_Windows.end()) return;
  WindowState & window = *itr->second;
  window.m_WindowGeo.m_End = window.m_WindowGeo.m_Start + size;
}


void WindowManager::AddWindowRef(uint32_t window_id)
{
  auto itr = s_Windows.find(window_id);
  if (itr == s_Windows.end()) return;
  WindowState & window = *itr->second;
  window.m_RefCount++;
}

void WindowManager::DecWindowRef(uint32_t window_id)
{
  auto itr = s_Windows.find(window_id);
  if (itr == s_Windows.end()) return;
  WindowState & window = *itr->second;
  window.m_RefCount--;

  if (itr->second->m_RefCount <= 0)
  {
    CloseWindow(window_id);
  }
}

void WindowManager::BindDefaultRenderTarget(uint32_t window_id)
{
  auto itr = s_Windows.find(window_id);
  if (itr == s_Windows.end()) return;
  WindowState & window = *itr->second;
  window.m_RefCount--;

  if (window.m_SDLWindow)
  {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
  }
  else
  {
    window.m_FakeWindow->m_BindDefaultRenderTargetDelegate();
  }

  auto window_size = window.m_WindowGeo.Size();
  glViewport(0, 0, window_size.x, window_size.y);
}

void WindowManager::Swap(uint32_t window_id)
{
  auto itr = s_Windows.find(window_id);
  if (itr == s_Windows.end()) return;
  WindowState & window = *itr->second;

  if (window.m_SDLWindow)
  {
    SDL_GL_SwapWindow(window.m_SDLWindow);
  }
  else
  {
    window.m_FakeWindow->m_SwapDelegate();
  }
}

void WindowManager::SetMousePos(uint32_t window_id, int x, int y)
{
  auto itr = s_Windows.find(window_id);
  if (itr == s_Windows.end()) return;
  WindowState & window = *itr->second;

  if (window.m_SDLWindow)
  {
    SDL_WarpMouseInWindow(window.m_SDLWindow, x, y);
  }
  else
  {
    window.m_FakeWindow->m_SetMousePosDelegate(x, y);
  }
}

void WindowManager::SetVsyncEnabled(uint32_t window_id, bool enabled)
{
  auto itr = s_Windows.find(window_id);
  if (itr == s_Windows.end()) return;
  WindowState & window = *itr->second;

  if (window.m_SDLWindow)
  {
    SDL_GL_MakeCurrent(window.m_SDLWindow, window.m_Context);
    SDL_GL_SetSwapInterval(enabled);
  }
}

void WindowManager::SetFullscreen(uint32_t window_id, bool enabled)
{
  auto itr = s_Windows.find(window_id);
  if (itr == s_Windows.end()) return;
  WindowState & window = *itr->second;

  if (window.m_SDLWindow)
  {
    printf("Changing full screen state to %d\n", enabled ? 1 : 0);
    SDL_SetWindowFullscreen(window.m_SDLWindow, enabled ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);

    window.m_FullScreen = enabled;

    int x, y;
    SDL_GetWindowPosition(window.m_SDLWindow, &x, &y);
    window.m_WindowGeo.m_Start = Vector2(x, y);
    SDL_GetWindowSize(window.m_SDLWindow, &x, &y);
    window.m_WindowGeo.m_End = window.m_WindowGeo.m_Start + Vector2(x, y);
  }
}

bool WindowManager::IsFullScreen(uint32_t window_id)
{
  auto itr = s_Windows.find(window_id);
  if (itr == s_Windows.end()) return false;
  WindowState & window = *itr->second;

  if (window.m_SDLWindow)
  {
    return window.m_FullScreen;
  }

  return false;
}

void WindowManager::UpdateWindow(uint32_t window_id)
{
  auto itr = s_Windows.find(window_id);
  if (itr == s_Windows.end()) return;
  WindowState & window = *itr->second;

  if (window.m_TextInputContext && window.m_SDLWindow && window.m_KeyboardFocus)
  {
    if (SDL_IsTextInputActive() == false)
    {
      SDL_StartTextInput();
    }
  }
  else if (window.m_KeyboardFocus)
  {
    SDL_StopTextInput();
  }

#ifdef _WEB
  bool update = false;
#else
  bool update = window.m_FakeWindow == nullptr;
#endif

  window.m_InputState->Update(window.m_KeyboardFocus, window.m_MouseFocus, (bool)window.m_TextInputContext, window.m_WindowGeo, update);

  if (window.m_SDLWindow)
  {
    int x, y;
    SDL_GetWindowPosition(window.m_SDLWindow, &x, &y);
    window.m_WindowGeo.m_Start = Vector2(x, y);
    SDL_GetWindowSize(window.m_SDLWindow, &x, &y);
    window.m_WindowGeo.m_End = window.m_WindowGeo.m_Start + Vector2(x, y);
  }
}

void WindowManager::MakeCurrent(uint32_t window_id)
{
  auto itr = s_Windows.find(window_id);
  if (itr == s_Windows.end()) return;
  WindowState & window = *itr->second;

  if (window.m_SDLWindow)
  {
    SDL_GL_MakeCurrent(window.m_SDLWindow, window.m_Context);
  }
  else
  {
    window.m_FakeWindow->m_MakeCurrentDelegate();
  }
}

void WindowManager::CloseWindow(uint32_t window_id)
{
  auto itr = s_Windows.find(window_id);
  if (itr == s_Windows.end()) return;
  WindowState & window = *itr->second;

  if (window.m_SDLWindow)
  {
    SDL_DestroyWindow(window.m_SDLWindow);
  }
  else
  {
    window.m_FakeWindow->m_CloseDelegate();
  }

  s_Windows.erase(itr);
}

void WindowManager::GrabMouse(uint32_t window_id)
{
  auto itr = s_Windows.find(window_id);
  if (itr == s_Windows.end()) return;
  WindowState & window = *itr->second;

  if (window.m_SDLWindow)
  {
    SDL_SetWindowGrab(window.m_SDLWindow, SDL_TRUE);
  }
  else
  {
    window.m_FakeWindow->m_GrabWindowDelegate();
  }
}

void WindowManager::ReleaseMouse(uint32_t window_id)
{
  auto itr = s_Windows.find(window_id);
  if (itr == s_Windows.end()) return;
  WindowState & window = *itr->second;

  if (window.m_SDLWindow)
  {
    SDL_SetWindowGrab(window.m_SDLWindow, SDL_FALSE);
  }
  else
  {
    window.m_FakeWindow->m_ReleaseWindowDelegate();
  }
}

Vector2 WindowManager::GetWindowSize(uint32_t window_id)
{
  auto itr = s_Windows.find(window_id);
  if (itr == s_Windows.end()) return{};
  WindowState & window = *itr->second;

  return window.m_WindowGeo.Size();
}

Box WindowManager::GetWindowGeometry(uint32_t window_id)
{
  auto itr = s_Windows.find(window_id);
  if (itr == s_Windows.end()) return{};
  WindowState & window = *itr->second;

  return window.m_WindowGeo;
}

void WindowManager::SetTextInputContext(uint32_t window_id, const std::shared_ptr<TextInputContext> & context, NullOptPtr<Box> input_box)
{
  auto itr = s_Windows.find(window_id);
  if (itr == s_Windows.end()) return;
  WindowState & window = *itr->second;
  window.m_TextInputContext = context;

  if (window.m_SDLWindow)
  {
    if (input_box)
    {
      SDL_Rect r;
      r.x = input_box->m_Start.x;
      r.y = input_box->m_Start.y;

      auto size = input_box->Size();
      r.w = size.x;
      r.h = size.y;

      SDL_SetTextInputRect(&r);
    }

    SDL_StartTextInput();
  }
  else
  {
    window.m_FakeWindow->m_StartImeDelegate(input_box);
  }
}

void WindowManager::ClearTextInputContext(uint32_t window_id, NotNullPtr<TextInputContext> context)
{
  auto itr = s_Windows.find(window_id);
  if (itr == s_Windows.end()) return;
  WindowState & window = *itr->second;
  if (window.m_TextInputContext.get() == context)
  {
    window.m_TextInputContext = {};

    if (window.m_SDLWindow)
    {
      if (window.m_KeyboardFocus)
      {
        SDL_StopTextInput();
      }
    }
    else
    {
      if (window.m_KeyboardFocus)
      {
        window.m_FakeWindow->m_StopImeDelegate();
      }
    }
  }
}

void WindowManager::ClearAllTextInputContext(uint32_t window_id)
{
  auto itr = s_Windows.find(window_id);
  if (itr == s_Windows.end()) return;
  WindowState & window = *itr->second;
  if (window.m_TextInputContext.get())
  {
    window.m_TextInputContext = {};

    if (window.m_SDLWindow)
    {
      if (window.m_KeyboardFocus)
      {
        SDL_StopTextInput();
      }
    }
    else
    {
      if (window.m_KeyboardFocus)
      {
        window.m_FakeWindow->m_StopImeDelegate();
      }
    }
  }
}

bool WindowManager::IsTextInputContextActive(uint32_t window_id, NotNullPtr<TextInputContext> context)
{
  auto itr = s_Windows.find(window_id);
  if (itr == s_Windows.end()) return false;
  WindowState & window = *itr->second;
  return window.m_TextInputContext.get() == context;
}

NullOptPtr<InputState> WindowManager::GetInputState(uint32_t window_id)
{
  auto itr = s_Windows.find(window_id);
  if (itr == s_Windows.end()) return nullptr;
  WindowState & window = *itr->second;
  return window.m_InputState.get();
}
