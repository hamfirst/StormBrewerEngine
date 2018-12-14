
#include "Engine/EngineCommon.h"
#include "Engine/UI/UIManager.h"
#include "Engine/UI/UIScriptLoader.h"
#include "Engine/UI/UIScriptInterface.h"
#include "Engine/UI/UIClickable.refl.meta.h"
#include "Engine/Input/InputState.h"
#include "Engine/Rendering/RenderState.h"
#include "Engine/Shader/ShaderManager.h"
#include "Engine/Window/Window.h"

#include "Foundation/SkipField/SkipField.h"
#include "Foundation/Script/ScriptRegister.h"

#include <sb/vector.h>

SkipField<UIClickable> s_UIClickableAllocator;

UIManager::UIManager() :
  m_Paused(false)
{
  m_UpdateTimer.Start();
}

UIManager::~UIManager()
{
  m_InterfaceObject.Clear();
  m_ClickableClass.Clear();

  m_ScriptLoader.reset();
  m_ScriptInterface.reset();

  m_ScriptState.Clear();
  for(auto & elem : m_RootClickables)
  {
    TrashClickable(elem);
  }

  RemoveDeadClickables();
}

void UIManager::LoadScripts()
{
  m_ScriptState.Emplace();

  m_ClickableClass.Emplace("Clickable", m_ScriptState.GetPtr(),
          [this](){ auto clickable = new UIClickable(this); return clickable; },
          [this](void * ptr) { TrashClickable(static_cast<UIClickable *>(ptr)); });
  m_ClickableClass->Register();

  m_ScriptInterface = std::make_unique<UIScriptInterface>(this);
  m_InterfaceObject.Emplace(m_ScriptState.GetPtr());
  auto & ui_interface = m_InterfaceObject.Value();
  auto script_interface = m_ScriptInterface.get();

  BIND_SCRIPT_INTERFACE(ui_interface, script_interface, RenderTexture);
  BIND_SCRIPT_INTERFACE(ui_interface, script_interface, RenderTextureTint);
  BIND_SCRIPT_INTERFACE(ui_interface, script_interface, RenderTextureScale);
  BIND_SCRIPT_INTERFACE(ui_interface, script_interface, RenderTextureScaleTint);
  BIND_SCRIPT_INTERFACE(ui_interface, script_interface, PlayAudio);
  BIND_SCRIPT_INTERFACE(ui_interface, script_interface, PlayAudioVolumePan);
  BIND_SCRIPT_INTERFACE(ui_interface, script_interface, PlayMusic);
  BIND_SCRIPT_INTERFACE(ui_interface, script_interface, PlayMusicVolume);
  BIND_SCRIPT_INTERFACE(ui_interface, script_interface, FadeToMusic);
  BIND_SCRIPT_INTERFACE(ui_interface, script_interface, FadeToMusicVolume);
  BIND_SCRIPT_INTERFACE(ui_interface, script_interface, FadeOutMusic);
  BIND_SCRIPT_INTERFACE(ui_interface, script_interface, StopMusic);
  BIND_SCRIPT_INTERFACE(ui_interface, script_interface, DrawText);

  m_ScriptState->BindAsGlobal("ui", ui_interface.GetObject());

  m_ScriptLoader = std::make_unique<UIScriptLoader>(m_ScriptState.GetPtr());
  m_ScriptLoader->InitLoad();
}

bool UIManager::FinishedLoading() const
{
  return m_ScriptLoader && m_ScriptLoader->Complete();
}

void UIManager::Update(float delta_time, InputState & input_state, RenderState & render_state)
{
  if(m_ScriptLoader)
  {
    m_ScriptLoader->Update();
  }

  auto update_time = m_UpdateTimer.GetTimeSinceLastCheck();
  if (m_Paused)
  {
    update_time = 0;
  }

  ProcessActiveAreas(delta_time, input_state, render_state);
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
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Bounds"), RenderVec4{ -1, -1, 1, 1 });

  auto base_offset = RenderVec2{};

  static std::vector<UIClickable *> clickables;
  clickables.clear();

  for(auto & elem : m_RootClickables)
  {
    AddToClickableList(elem.Get(), nullptr, clickables);
  }

  m_ScriptInterface->BeginRendering(&render_state, &render_util);
  for(auto & elem : clickables)
  {
    if (elem->m_Dead == false)
    {
      if(elem->m_ActiveArea)
      {
        m_ScriptInterface->SetActiveArea(elem->m_ActiveArea.Value());
        elem->OnRender();
      }
    }
  }
  m_ScriptInterface->EndRendering();

  RemoveDeadClickables();
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

ScriptClassRef<UIClickable> UIManager::AllocateClickable()
{
  return m_ClickableClass->CreateInstance();
}

bool UIManager::HasSelectedElement() const
{
  return m_HasSelectedElement;
}

void UIManager::AddClickableToRoot(ScriptClassRef<UIClickable> & clickable)
{
  m_RootClickables.push_back(clickable);
}

void UIManager::RemoveClickableFromRoot(NotNullPtr<UIClickable> clickable)
{
  for(std::size_t index = 0, end = m_RootClickables.size(); index < end; ++index)
  {
    auto & elem = m_RootClickables[index];
    if(elem.Get() == clickable)
    {
      m_RootClickables.erase(m_RootClickables.begin() + index);
      break;
    }
  }
}

void UIManager::TrashClickable(NotNullPtr<UIClickable> clickable)
{
  if(clickable == nullptr || clickable->m_Dead)
  {
    return;
  }

  clickable->m_Dead = true;
  m_DeadClickables.push_back(clickable);

  for(auto & elem : clickable->m_Children)
  {
    TrashClickable(elem.Get());
  }
}

void UIManager::RemoveDeadClickables()
{
  for(auto itr = m_DeadClickables.rbegin(), end = m_DeadClickables.rend(); itr != end; ++itr)
  {
    delete (*itr);
  }

  m_DeadClickables.clear();
}

void UIManager::AddToClickableList(NotNullPtr<UIClickable> clickable, NullOptPtr<UIClickable> parent, std::vector<NotNullPtr<UIClickable>> & list)
{
  if(clickable->Width <= 0 || clickable->Height <= 0)
  {
    clickable->m_ActiveArea.Clear();
  }
  else
  {
    if (parent)
    {
      if (parent->m_ActiveArea)
      {
        auto active_area_start = parent->m_ActiveArea->m_Start + Vector2(clickable->X, clickable->Y);
        auto active_area = Box::FromStartAndWidthHeight(active_area_start, Vector2(clickable->Width, clickable->Height));

        parent->m_ActiveArea = ClipBox(active_area, parent->m_ActiveArea.Value());
      }
      else
      {
        clickable->m_ActiveArea.Clear();
      }
    }
    else
    {
      clickable->m_ActiveArea = Box::FromStartAndWidthHeight(clickable->X, clickable->Y, clickable->Width, clickable->Height);
    }
  }

  list.push_back(clickable);

  for(auto & child : clickable->m_Children)
  {
    AddToClickableList(child.Get(), clickable, list);
  }
}

void UIManager::ProcessActiveAreas(float delta_time, InputState & input_state, RenderState & render_state)
{
  static std::vector<UIClickable *> clickables;
  clickables.clear();

  for(auto & elem : m_RootClickables)
  {
    AddToClickableList(elem.Get(), nullptr, clickables);
  }

  for(auto & elem : clickables)
  {
    if(elem->m_Dead == false)
    {
      elem->OnUpdate(delta_time);
    }
  }

  m_HasSelectedElement = false;

  NullOptPtr<UIClickable> cur_pressed_clickable = nullptr;
  for(auto itr = clickables.rbegin(), end = clickables.rend(); itr != end; ++itr)
  {
    auto & elem = *itr;
    if(elem->m_Dead)
    {
      continue;
    }

    if (elem->State == (int)UIClickableState::kPressed)
    {
      if (cur_pressed_clickable)
      {
        elem->OnStateChange(elem->State, (int)UIClickableState::kActive);
        elem->State = (int)UIClickableState::kActive;
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
    for(auto itr = clickables.rbegin(), end = clickables.rend(); itr != end; ++itr)
    {
      auto & elem = *itr;
      if(elem->m_Dead)
      {
        continue;
      }

      if(elem->m_ActiveArea)
      {
        auto box = elem->m_ActiveArea.Value();
        if (PointInBox(box, pointer_pos))
        {
          cur_hover_clickable = elem;
          break;
        }
      }
    }
  };

  if (pointer_state.m_InFocus)
  {
    if(m_GrabbedMouseClickable)
    {
      bool found = false;
      for (auto elem : clickables)
      {
        if(elem->m_Dead)
        {
          continue;
        }

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
        if(m_GrabbedMouseClickable->m_ActiveArea)
        {
          auto box = m_GrabbedMouseClickable->m_ActiveArea.Value();

          if (PointInBox(box, pointer_pos))
          {
            cur_hover_clickable = m_GrabbedMouseClickable;
          }
        }
      }
    }
  }

  if (cur_pressed_clickable)
  {
    for(auto itr = clickables.rbegin(), end = clickables.rend(); itr != end; ++itr)
    {
      auto & elem = *itr;
      if (elem->State == (int)UIClickableState::kHover)
      {
        elem->OnStateChange(elem->State, (int)UIClickableState::kActive);
        elem->State = (int)UIClickableState::kActive;
      }
    }

    if (pointer_state.m_InFocus == false)
    {
      if (cur_pressed_clickable)
      {
        cur_pressed_clickable->OnStateChange(cur_pressed_clickable->State, (int)UIClickableState::kActive);
        cur_pressed_clickable->State = (int)UIClickableState::kActive;
      }
    }
    else if (input_state.GetMouseButtonState(kMouseLeftButton) == false)
    {
      if (cur_hover_clickable != nullptr)
      {
        if (cur_hover_clickable == cur_pressed_clickable)
        {
          cur_pressed_clickable->OnClick();
          cur_pressed_clickable->OnStateChange(cur_pressed_clickable->State, (int)UIClickableState::kHover);
          cur_pressed_clickable->State = (int)UIClickableState::kHover;
        }
        else
        {
          cur_pressed_clickable->OnStateChange(cur_pressed_clickable->State, (int)UIClickableState::kActive);
          cur_pressed_clickable->State = (int)UIClickableState::kActive;
        }
      }
      else if(cur_pressed_clickable)
      {
        cur_pressed_clickable->OnStateChange(cur_pressed_clickable->State, (int)UIClickableState::kActive);
        cur_pressed_clickable->State = (int)UIClickableState::kActive;
      }
    }
  }
  else
  {
    if (input_state.GetMouseButtonState(kMouseLeftButton) && input_state.GetMousePressedThisFrame(kMouseLeftButton) == false)
    {
      cur_hover_clickable = nullptr;
    }

    for(auto itr = clickables.rbegin(), end = clickables.rend(); itr != end; ++itr)
    {
      auto & elem = *itr;
      if (elem != cur_hover_clickable && elem->State == (int)UIClickableState::kHover)
      {
        elem->OnStateChange(elem->State, (int)UIClickableState::kActive);
        elem->State = (int)UIClickableState::kActive;
      }
    }

    if (cur_hover_clickable != nullptr && cur_hover_clickable->State != (int)UIClickableState::kHover)
    {
      cur_hover_clickable->OnStateChange(cur_hover_clickable->State, (int)UIClickableState::kHover);
      cur_hover_clickable->State = (int)UIClickableState::kHover;
    }

    if (input_state.GetMousePressedThisFrame(kMouseLeftButton))
    {
      if (cur_hover_clickable != nullptr)
      {
        cur_hover_clickable->OnStateChange(cur_hover_clickable->State, (int)UIClickableState::kPressed);
        cur_hover_clickable->State = (int)UIClickableState::kPressed;
      }
    }
  }

  if (cur_hover_clickable || cur_pressed_clickable)
  {
    m_HasSelectedElement = true;
  }
}
