
#include "Engine/EngineCommon.h"
#include "Engine/Window/WindowManager.h"
#include "Engine/Input/InputState.h"

#include <SDL/SDL.h>

WindowManager g_WindowManager;

struct WindowManager::WindowState
{
  SDL_Window * m_SDLWindow;
  SDL_GLContext m_Context;

  int m_RefCount;
  bool m_InFocus;

  std::unique_ptr<InputState> m_InputState;
};


Window WindowManager::CreateNewWindow(czstr title, int width, int height)
{
  auto sdl_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
  if (sdl_window == nullptr)
  {
    return{};
  }

  auto context = SDL_GL_CreateContext(sdl_window);
  uint32_t id = SDL_GetWindowID(sdl_window);

  auto result = m_Windows.emplace(std::make_pair(id, WindowManager::WindowState{ sdl_window, context, 1, false }));
  WindowState & window = result.first->second;

  window.m_InputState = std::make_unique<InputState>();

  return Window(id);
}

void WindowManager::UpdateInput()
{
  for (auto & window_info : m_Windows)
  {
    auto & window = window_info.second;
    window.m_InputState->Update(window.m_InFocus);
  }
}

void WindowManager::HandleKeypressMessage(uint32_t window_id, int scan_code, bool pressed)
{
  auto itr = m_Windows.find(window_id);
  if (itr == m_Windows.end()) return;
  WindowState & window = itr->second;

  window.m_InputState->HandleKeypressMessage(scan_code, pressed);
}

void WindowManager::AddWindowRef(uint32_t window_id)
{
  auto itr = m_Windows.find(window_id);
  if (itr == m_Windows.end()) return;
  WindowState & window = itr->second;
  window.m_RefCount++;
}

void WindowManager::DecWindowRef(uint32_t window_id)
{
  auto itr = m_Windows.find(window_id);
  if (itr == m_Windows.end()) return;
  WindowState & window = itr->second;
  window.m_RefCount--;

  if (itr->second.m_RefCount <= 0)
  {
    SDL_DestroyWindow(window.m_SDLWindow);
    m_Windows.erase(itr);
  }
}

void WindowManager::Swap(uint32_t window_id)
{
  auto itr = m_Windows.find(window_id);
  if (itr == m_Windows.end()) return;
  WindowState & window = itr->second;
  SDL_GL_SwapWindow(window.m_SDLWindow);
}

void WindowManager::CloseWindow(uint32_t window_id)
{
  auto itr = m_Windows.find(window_id);
  if (itr == m_Windows.end()) return;
  WindowState & window = itr->second;

  SDL_DestroyWindow(window.m_SDLWindow);
  m_Windows.erase(itr);
}

NullOptPtr<InputState> WindowManager::GetInputState(uint32_t window_id)
{
  auto itr = m_Windows.find(window_id);
  if (itr == m_Windows.end()) return nullptr;
  WindowState & window = itr->second;
  return window.m_InputState.get();
}

void WindowManager::SetWindowFocused(uint32_t window_id, bool focused)
{
  auto itr = m_Windows.find(window_id);
  if (itr == m_Windows.end()) return;
  WindowState & window = itr->second;
  window.m_InFocus = focused;
}
