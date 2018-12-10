
#include "Engine/EngineCommon.h"
#include "Engine/UI/UIManager.h"
#include "Engine/UI/UIScriptLoader.h"
#include "Engine/Input/InputState.h"
#include "Engine/Rendering/RenderState.h"
#include "Engine/Shader/ShaderManager.h"
#include "Engine/Window/Window.h"

#include "Foundation/SkipField/SkipField.h"

#include <sb/vector.h>

SkipField<UIClickable> s_UIClickableAllocator;

UIManager::UIManager(Window & container_window) :
  m_ContainerWindow(container_window),
  m_Paused(false)
{
  m_UpdateTimer.Start();
}

UIManager::~UIManager()
{

}

void UIManager::LoadScripts()
{
  m_ScriptState.Emplace();
  m_ScriptInterface.Emplace(m_ScriptState.GetPtr());

  m_Loader = std::make_unique<UIScriptLoader>(m_ScriptState.GetPtr());
  m_Loader->InitLoad();
}

bool UIManager::FinishedLoading() const
{
  return m_Loader && m_Loader->Complete();
}

void UIManager::Update(InputState & input_state, RenderState & render_state, const Vector2 & clickable_offset)
{
  if(m_Loader)
  {
    m_Loader->Update();
  }

  auto update_time = m_UpdateTimer.GetTimeSinceLastCheck();
  if (m_Paused)
  {
    update_time = 0;
  }

  ProcessActiveAreas(input_state, render_state, clickable_offset);
}

void UIManager::Render(RenderState & render_state, RenderUtil & render_util)
{
  auto & shader = g_ShaderManager.GetDefaultScreenSpaceShader();
  auto render_size = (RenderVec2)render_state.GetRenderSize();

  render_state.BindShader(shader);
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_ScreenSize"), render_size);
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Color"), Color(255, 255, 255, 255));
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Matrix"), 1.0f, 0.0f, 0.0f, 1.0f);
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Offset"), 0.0f, 0.0f);
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Texture"), 0);

  auto base_offset = RenderVec2{};
}

void UIManager::Pause()
{
  m_Paused = true;
}

void UIManager::Unpause()
{
  m_Paused = false;
}

void UIManager::GrabMouse(NotNullPtr<UIClickable> clickable)
{
  m_GrabbedMouseClickable = clickable;
}

void UIManager::ReleaseMouse(NotNullPtr<UIClickable> clickable)
{
  if(clickable == m_GrabbedMouseClickable)
  {
    m_GrabbedMouseClickable = nullptr;
  }
}

UIClickablePtr UIManager::AllocateClickable(const Box & active_area)
{
  UIClickable::UIClickableConstructorTag crap;

  auto ptr = s_UIClickableAllocator.Allocate(crap);
  ptr->m_ActiveArea = active_area;
  ptr->m_Manager = this;

  m_Clickables.push_back(ptr);
  return UIClickablePtr(ptr);
}

bool UIManager::HasSelectedElement() const
{
  return m_HasSelectedElement;
}

void UIManager::ReleaseClickable(NotNullPtr<UIClickable> clickable)
{
  s_UIClickableAllocator.Release(clickable);
}

void UIManager::ProcessActiveAreas(InputState & input_state, RenderState & render_state, const Vector2 & clickable_offset)
{
  m_HasSelectedElement = false;

  NullOptPtr<UIClickable> cur_pressed_clickable = nullptr;
  for (auto elem : m_Clickables)
  {
    if (elem->m_State == UIClickableState::kPressed)
    {
      if (cur_pressed_clickable)
      {
        elem->m_OnStateChange(elem->m_State, UIClickableState::kActive);
        elem->m_State = UIClickableState::kActive;
      }
      else
      {
        cur_pressed_clickable = elem;
      }
    }
  }

  auto pointer_state = input_state.GetPointerState();
  auto pointer_pos = (Vector2)render_state.ScreenPixelsToRenderPixels(pointer_state.m_Pos);

  Vector2 ui_pos = pointer_pos;
  //ui_pos += render_state.GetRenderSize() / 2;

  UIClickable * cur_hover_clickable = nullptr;

  auto CheckAllElements = [&]()
  {
    for (auto elem : m_Clickables)
    {
      auto box = elem->m_ActiveArea;
      box.m_Start -= clickable_offset;
      box.m_End -= clickable_offset;

      if (PointInBox(box, pointer_pos))
      {
        cur_hover_clickable = elem;
        break;
      }
    }
  };


  if (pointer_state.m_InFocus)
  {
    if(m_GrabbedMouseClickable)
    {
      bool found = false;
      for (auto elem : m_Clickables)
      {
        if(elem == m_GrabbedMouseClickable)
        {
          found = true;
          break;
        }
      }

      if(found == false)
      {
        m_GrabbedMouseClickable = nullptr;
        CheckAllElements();
      }
      else
      {
        auto box = m_GrabbedMouseClickable->m_ActiveArea;
        box.m_Start -= clickable_offset;
        box.m_End -= clickable_offset;

        if (PointInBox(box, pointer_pos))
        {
          cur_hover_clickable = m_GrabbedMouseClickable;
        }
      }
    }
  }

  if (cur_pressed_clickable)
  {
    for (auto elem : m_Clickables)
    {
      if (elem->m_State == UIClickableState::kHover)
      {
        elem->m_OnStateChange(elem->m_State, UIClickableState::kActive);
        elem->m_State = UIClickableState::kActive;
      }
    }

    if (pointer_state.m_InFocus == false)
    {
      if (cur_pressed_clickable)
      {
        cur_pressed_clickable->m_OnStateChange(cur_pressed_clickable->m_State, UIClickableState::kActive);
        cur_pressed_clickable->m_State = UIClickableState::kActive;
      }
    }
    else if (input_state.GetMouseButtonState(kMouseLeftButton) == false)
    {
      if (cur_hover_clickable != nullptr)
      {
        if (cur_hover_clickable == cur_pressed_clickable)
        {
          cur_pressed_clickable->m_OnClick();
          cur_pressed_clickable->m_OnStateChange(cur_pressed_clickable->m_State, UIClickableState::kHover);
          cur_pressed_clickable->m_State = UIClickableState::kHover;
        }
        else
        {
          cur_pressed_clickable->m_OnStateChange(cur_pressed_clickable->m_State, UIClickableState::kActive);
          cur_pressed_clickable->m_State = UIClickableState::kActive;
        }
      }
      else if(cur_pressed_clickable)
      {
        cur_pressed_clickable->m_OnStateChange(cur_pressed_clickable->m_State, UIClickableState::kActive);
        cur_pressed_clickable->m_State = UIClickableState::kActive;
      }
    }
  }
  else
  {
    if (input_state.GetMouseButtonState(kMouseLeftButton) && input_state.GetMousePressedThisFrame(kMouseLeftButton) == false)
    {
      cur_hover_clickable = nullptr;
    }

    for (auto elem : m_Clickables)
    {
      if (elem != cur_hover_clickable && elem->m_State == UIClickableState::kHover)
      {
        elem->m_OnStateChange(elem->m_State, UIClickableState::kActive);
        elem->m_State = UIClickableState::kActive;
      }
    }

    if (cur_hover_clickable != nullptr && cur_hover_clickable->m_State != UIClickableState::kHover)
    {
      cur_hover_clickable->m_OnStateChange(cur_hover_clickable->m_State, UIClickableState::kHover);
      cur_hover_clickable->m_State = UIClickableState::kHover;
    }

    if (input_state.GetMousePressedThisFrame(kMouseLeftButton))
    {
      if (cur_hover_clickable != nullptr)
      {
        cur_hover_clickable->m_OnStateChange(cur_hover_clickable->m_State, UIClickableState::kPressed);
        cur_hover_clickable->m_State = UIClickableState::kPressed;
      }
    }
  }

  if (cur_hover_clickable || cur_pressed_clickable)
  {
    m_HasSelectedElement = true;
  }
}
