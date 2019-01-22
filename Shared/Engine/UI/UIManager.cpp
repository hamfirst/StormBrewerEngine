
#include "Engine/EngineCommon.h"
#include "Engine/UI/UIManager.h"
#include "Engine/UI/UIScriptLoader.h"
#include "Engine/UI/UIScriptInterface.h"
#include "Engine/UI/UITextureBinding.h"
#include "Engine/UI/UIClickable.refl.meta.h"
#include "Engine/UI/UITextInput.refl.meta.h"
#include "Engine/Input/InputState.h"
#include "Engine/Rendering/RenderState.h"
#include "Engine/Text/TextRenderMode.refl.meta.h"
#include "Engine/Shader/ShaderManager.h"
#include "Engine/Window/Window.h"

#include "Foundation/SkipField/SkipField.h"
#include "Foundation/Script/ScriptRegister.h"
#include "Foundation/Script/ScriptFuncs.h"
#include "Foundation/Lerp/LerpFuncs.h"

#include "Runtime/UI/UIDef.refl.h"

#include <sb/vector.h>

SkipField<UIClickable> s_UIClickableAllocator;

UIManager::UIManager(Window & container_window) :
  m_ContainerWindow(container_window),
  m_Paused(false)
{
  m_UpdateTimer.Start();
  m_WheelBinding = m_ContainerWindow.GetInputState()->BindScalarControl(CreateMouseWheelBinding(), 10,
          ControlBindingMode::kPassThrough, [this](float dv){ HandleMouseScroll((int)dv); });
}

UIManager::~UIManager()
{
  for(auto & elem : m_RootClickables)
  {
    TrashClickable(elem);
  }

  RemoveDeadClickables();
  m_Destroying = true;

  auto input_state = m_ContainerWindow.GetInputState();
  if(input_state)
  {
    input_state->UnbindScalarControl(m_WheelBinding.Value());
  }
}

#define BIND_EASING_FUNC(EasingType) \
m_ScriptState->SetGlobalFunction("EaseIn" #EasingType, ScriptFunctionBinder<float, float>::Process<EaseIn ## EasingType>()); \
m_ScriptState->SetGlobalFunction("EaseOut" #EasingType, ScriptFunctionBinder<float, float>::Process<EaseOut ## EasingType>()); \
m_ScriptState->SetGlobalFunction("EaseInOut" #EasingType, ScriptFunctionBinder<float, float>::Process<EaseInOut ## EasingType>()); \

void UIManager::LoadScripts(const Vector2 & screen_size, bool immediate_load,
        Delegate<void> && load_complete_callback, Delegate<void, czstr> && error_output)
{
  m_ClickableClass = std::make_unique<ScriptClass<UIClickable>>("Clickable",
                           [this](){ auto clickable = new UIClickable(this); return clickable; },
                           [this](ScriptClassRef<UIClickable> & ref) { AddClickableToRoot(ref); },
                           [this](void * ptr) { TrashClickable(static_cast<UIClickable *>(ptr)); });

  m_TextInputClass = std::make_unique<ScriptClass<UITextInput>>("TextInputContext",
                           [this](){ auto clickable = new UITextInput(m_ContainerWindow.CreateTextInputContext()); return clickable; },
                           [this](ScriptClassRef<UITextInput> & ref) { },
                           [this](void * ptr) { delete static_cast<UITextInput *>(ptr); });

  m_ScriptState.Emplace();
  UpdateScriptGlobals(screen_size);

  BIND_EASING_FUNC(Step);
  BIND_EASING_FUNC(Linear);
  BIND_EASING_FUNC(Sine);
  BIND_EASING_FUNC(Quadratic);
  BIND_EASING_FUNC(Cubic);
  BIND_EASING_FUNC(Quartic);
  BIND_EASING_FUNC(Quintic);
  BIND_EASING_FUNC(Bounce);
  BIND_EASING_FUNC(Elastic);

  if(error_output.IsValid())
  {
    m_ScriptState->SetErrorDelegate(std::move(error_output));
  }

  m_ClickableClass->Register(m_ScriptState.GetPtr());
  m_TextInputClass->Register(m_ScriptState.GetPtr());
  ScriptAddEnumAsGlobals<UIClickableState>(m_ScriptState.GetPtr());
  ScriptAddEnumAsGlobals<TextRenderMode>(m_ScriptState.GetPtr());

  m_ScriptInterface = std::make_unique<UIScriptInterface>(this);
  m_UIInterfaceObject.Emplace(m_ScriptState.GetPtr());
  auto & ui_interface = m_UIInterfaceObject.Value();
  auto script_interface = m_ScriptInterface.get();

  BIND_SCRIPT_INTERFACE(ui_interface, script_interface, ToggleFullscreen);
  BIND_SCRIPT_INTERFACE(ui_interface, script_interface, GetMousePos);
  BIND_SCRIPT_INTERFACE(ui_interface, script_interface, DrawTexture);
  BIND_SCRIPT_INTERFACE(ui_interface, script_interface, DrawTextureTint);
  BIND_SCRIPT_INTERFACE(ui_interface, script_interface, DrawTextureScale);
  BIND_SCRIPT_INTERFACE(ui_interface, script_interface, DrawTextureScaleTint);
  BIND_SCRIPT_INTERFACE(ui_interface, script_interface, GetTextureSize);
  BIND_SCRIPT_INTERFACE(ui_interface, script_interface, PlayAudio);
  BIND_SCRIPT_INTERFACE(ui_interface, script_interface, PlayAudioVolumePan);
  BIND_SCRIPT_INTERFACE(ui_interface, script_interface, GetAudioVolume);
  BIND_SCRIPT_INTERFACE(ui_interface, script_interface, SetAudioVolume);
  BIND_SCRIPT_INTERFACE(ui_interface, script_interface, PlayMusic);
  BIND_SCRIPT_INTERFACE(ui_interface, script_interface, PlayMusicVolume);
  BIND_SCRIPT_INTERFACE(ui_interface, script_interface, FadeToMusic);
  BIND_SCRIPT_INTERFACE(ui_interface, script_interface, FadeToMusicVolume);
  BIND_SCRIPT_INTERFACE(ui_interface, script_interface, FadeOutMusic);
  BIND_SCRIPT_INTERFACE(ui_interface, script_interface, StopMusic);
  BIND_SCRIPT_INTERFACE(ui_interface, script_interface, GetMusicVolume);
  BIND_SCRIPT_INTERFACE(ui_interface, script_interface, SetMusicVolume);
  BIND_SCRIPT_INTERFACE(ui_interface, script_interface, DrawText);
  BIND_SCRIPT_INTERFACE(ui_interface, script_interface, DrawCenteredText);
  BIND_SCRIPT_INTERFACE(ui_interface, script_interface, DrawTextScaled);
  BIND_SCRIPT_INTERFACE(ui_interface, script_interface, DrawCenteredTextScaled);
  BIND_SCRIPT_INTERFACE(ui_interface, script_interface, MeasureText);
  BIND_SCRIPT_INTERFACE(ui_interface, script_interface, MeasureTextScaled);
  BIND_SCRIPT_INTERFACE(ui_interface, script_interface, DrawTextInput);
  BIND_SCRIPT_INTERFACE(ui_interface, script_interface, DrawCenteredTextInput);
  BIND_SCRIPT_INTERFACE(ui_interface, script_interface, DrawTextInputScaled);
  BIND_SCRIPT_INTERFACE(ui_interface, script_interface, DrawCenteredTextInputScaled);
  BIND_SCRIPT_INTERFACE(ui_interface, script_interface, MeasureTextInput);
  BIND_SCRIPT_INTERFACE(ui_interface, script_interface, MeasureTextInputScaled);
  BIND_SCRIPT_INTERFACE(ui_interface, script_interface, GetLineHeight);
  BIND_SCRIPT_INTERFACE(ui_interface, script_interface, WrapText);
  BIND_SCRIPT_INTERFACE(ui_interface, script_interface, WrapTextScaled);
  BIND_SCRIPT_INTERFACE(ui_interface, script_interface, ClearCurrentTextInput);
  BIND_SCRIPT_INTERFACE(ui_interface, script_interface, DrawSprite);
  BIND_SCRIPT_INTERFACE(ui_interface, script_interface, FrameAdvance);
  BIND_SCRIPT_INTERFACE(ui_interface, script_interface, DrawAtlas);
  BIND_SCRIPT_INTERFACE(ui_interface, script_interface, DrawLine);
  BIND_SCRIPT_INTERFACE(ui_interface, script_interface, DrawLineThickness);
  BIND_SCRIPT_INTERFACE(ui_interface, script_interface, DrawRectangle);
  BIND_SCRIPT_INTERFACE(ui_interface, script_interface, DrawFilledRectangle);
  BIND_SCRIPT_INTERFACE(ui_interface, script_interface, DrawEllipse);
  BIND_SCRIPT_INTERFACE(ui_interface, script_interface, DrawFilledEllipse);
  BIND_SCRIPT_INTERFACE(ui_interface, script_interface, FlushGeometry);

  m_ScriptState->SetGlobal("ui", ui_interface.GetObject());

  m_ScriptLoader = std::make_unique<UIScriptLoader>(m_ScriptState.GetPtr());
  m_ScriptLoader->InitLoad(immediate_load, std::move(load_complete_callback));
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

  RemoveDeadClickables();

  if(m_ScriptLoader->Complete())
  {
    m_ScriptState->SetGlobal("ScreenWidth", render_state.GetRenderWidth());
    m_ScriptState->SetGlobal("ScreenHeight", render_state.GetRenderHeight());

    m_ScriptState->Call("ProcessLerps", { delta_time });
    RemoveDeadClickables();
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
  UpdateScriptGlobals(render_state.GetRenderSize());

  auto & shader = g_ShaderManager.GetDefaultScreenSpaceShader();
  auto render_size = (RenderVec2)render_state.GetRenderSize();

  render_state.BindShader(shader);
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_ScreenSize"), render_size);
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Color"), Color(255, 255, 255, 255));
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Matrix"), 1.0f, 0.0f, 0.0f, 1.0f);
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Offset"), 0.0f, 0.0f);
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Texture"), 0);
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Bounds"), RenderVec4{ -1, -1, 1, 1 });
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_ColorMatrix"), Mat4f());

  auto base_offset = RenderVec2{};

  static std::vector<UIClickable *> clickables;
  clickables.clear();


  for(auto & elem : m_RootClickables)
  {
    AddToClickableList(elem.Get(), nullptr, clickables);
  }

  auto invalid_area = Box::FromPoint(Vector2(-10000, -10000));

  m_ScriptInterface->BeginRendering(&render_state, &render_util);
  for(auto & elem : clickables)
  {
    if (elem->m_Dead == false)
    {
      Box active_area;

      if(elem->m_ActiveArea.IsValid() == false)
      {
        if(elem->Clip || elem->Enabled == false)
        {
          continue;
        }
        else
        {
          active_area = invalid_area;
        }
      }
      else
      {
        active_area = elem->m_ActiveArea.Value();
      }

      m_ScriptInterface->SetDrawArea(elem->m_DrawArea, active_area, elem->Clip);
      elem->OnDraw();
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

void UIManager::PushUIDef(const UIDef & def)
{
  if(m_CleanupFunc.empty() == false)
  {
    m_ScriptState->Call(m_CleanupFunc.c_str(), {});
  }

  RemoveDeadClickables();

  m_ScriptState->Call(def.m_InitFunction.c_str(), {});
  m_CleanupFunc = def.m_CleanupFunction;
  RemoveDeadClickables();
}

void UIManager::PushUIDef(const UIResourcePtr & ui)
{
  PushUIDef(*ui.GetData());
}

void UIManager::ClearUI()
{
  if(m_CleanupFunc.empty() == false)
  {
    m_ScriptState->Call(m_CleanupFunc.c_str(), {});
    m_CleanupFunc.clear();
  }

  RemoveDeadClickables();
}

ScriptInterface & UIManager::CreateGameInterface()
{
  m_GameInterfaceObject.Emplace(m_ScriptState.GetPtr());
  m_ScriptState->SetGlobal("game", m_GameInterfaceObject->GetObject());
  return m_GameInterfaceObject.Value();
}

bool UIManager::Call(czstr name, NullOptPtr<ScriptValue> return_val)
{
  bool success = m_ScriptState->Call(name, {}, return_val);
  RemoveDeadClickables();

  return success;
}

bool UIManager::Call(czstr name, std::initializer_list<ScriptValue> args, NullOptPtr<ScriptValue> return_val)
{
  bool success = m_ScriptState->Call(name, args, return_val);
  RemoveDeadClickables();

  return success;
}

void UIManager::SetGlobal(czstr name, const ScriptValue & value)
{
  m_ScriptState->SetGlobal(name, value);
}

bool UIManager::HasSelectedElement() const
{
  return m_HasSelectedElement;
}

UITextureBinding UIManager::CreateTextureBinding(czstr name, Delegate<NullOptPtr<const Texture>> && tex)
{
  assert(m_GameInterfaceObject.IsValid());
  m_GameInterfaceObject->AddVariable(name, m_NextTextureId | UIScriptLoader::kBoundTexture);

  UITextureBinding bind(this, m_NextTextureId, std::move(tex));
  m_NextTextureId++;

  return bind;
}

void UIManager::AddClickableToRoot(const ScriptClassRef<UIClickable> & clickable)
{
  m_RootClickables.push_back(clickable);
}

void UIManager::RemoveClickableFromRoot(const ScriptClassRef<UIClickable> & clickable)
{
  for(std::size_t index = 0, end = m_RootClickables.size(); index < end; ++index)
  {
    auto & elem = m_RootClickables[index];
    if(elem == clickable)
    {
      m_RootClickables.erase(m_RootClickables.begin() + index);
      break;
    }
  }
}

void UIManager::TrashClickable(NotNullPtr<UIClickable> clickable)
{
  if(m_Destroying)
  {
    return;
  }

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

void UIManager::UpdateScriptGlobals(const Vector2 & screen_size)
{
  m_ScriptState->SetGlobal("screen_width", screen_size.x);
  m_ScriptState->SetGlobal("screen_height", screen_size.y);
  m_ScriptState->SetGlobal("half_screen_width", screen_size.x / 2);
  m_ScriptState->SetGlobal("half_screen_height", screen_size.y / 2);

  auto screen_box = Box::FromFrameCenterAndSize({}, screen_size);

  m_ScriptState->SetGlobal("screen_start_x", screen_box.m_Start.x);
  m_ScriptState->SetGlobal("screen_start_y", screen_box.m_Start.y);
  m_ScriptState->SetGlobal("screen_end_x", screen_box.m_End.x);
  m_ScriptState->SetGlobal("screen_end_y", screen_box.m_End.y);
}

void UIManager::HandleMouseScroll(int dv)
{
  m_MouseDelta = dv;
}

void UIManager::AddToClickableList(NotNullPtr<UIClickable> clickable, NullOptPtr<UIClickable> parent, std::vector<NotNullPtr<UIClickable>> & list)
{
  clickable->m_DrawArea = Box::FromStartAndWidthHeight(clickable->X, clickable->Y, clickable->Width, clickable->Height);

  if(parent)
  {
    clickable->m_DrawArea = clickable->m_DrawArea.Offset(parent->m_DrawArea.m_Start);
  }

  if(clickable->Width <= 0 || clickable->Height <= 0 || clickable->Enabled == false)
  {
    clickable->m_ActiveArea.Clear();
  }
  else
  {
    if (parent)
    {
      if (parent->m_ActiveArea)
      {
        auto & parent_active_area = parent->m_ActiveArea.Value();

        auto active_area_start = parent_active_area.m_Start + Vector2(clickable->X, clickable->Y);
        auto active_area = Box::FromStartAndWidthHeight(active_area_start, Vector2(clickable->Width, clickable->Height));

        clickable->m_ActiveArea = ClipBox(active_area, parent_active_area);
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

  NullOptPtr<UIClickable> prev_hover_clickable = nullptr;
  NullOptPtr<UIClickable> prev_active_clickable = nullptr;
  for(auto itr = clickables.rbegin(), end = clickables.rend(); itr != end; ++itr)
  {
    auto & elem = *itr;
    if(elem->m_State == (int)UIClickableState::kHover || elem->m_State == (int)UIClickableState::kPressed)
    {
      prev_active_clickable = elem;
    }

    if(elem->m_State == (int)UIClickableState::kHover)
    {
      prev_hover_clickable = elem;
    }
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

    if(elem->m_State != (int)UIClickableState::kDisabled && elem->Enabled == false)
    {
      elem->OnStateChange(elem->m_State, (int)UIClickableState::kDisabled);
      elem->m_State = (int)UIClickableState::kDisabled;
    }
    else if(elem->m_State == (int)UIClickableState::kDisabled && elem->Enabled == true)
    {
      elem->OnStateChange(elem->m_State, (int)UIClickableState::kActive);
      elem->m_State = (int)UIClickableState::kActive;
    }

    if (elem->m_State == (int)UIClickableState::kPressed)
    {
      if (cur_pressed_clickable)
      {
        elem->OnStateChange(elem->m_State, (int)UIClickableState::kActive);
        elem->m_State = (int)UIClickableState::kActive;
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

  auto GetRelativePos = [&](UIClickable * clickable)
  {
    return ui_pos - clickable->m_ActiveArea->m_Start;
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
    else
    {
      CheckAllElements();
    }
  }

  if (cur_pressed_clickable)
  {
    for(auto itr = clickables.rbegin(), end = clickables.rend(); itr != end; ++itr)
    {
      auto & elem = *itr;
      if (elem->m_State == (int)UIClickableState::kHover)
      {
        elem->OnStateChange(elem->m_State, (int)UIClickableState::kActive);
        elem->m_State = (int)UIClickableState::kActive;
      }
    }

    if (pointer_state.m_InFocus == false)
    {
      if (cur_pressed_clickable && cur_pressed_clickable->Enabled)
      {
        cur_pressed_clickable->OnStateChange(cur_pressed_clickable->m_State, (int)UIClickableState::kActive);
        cur_pressed_clickable->m_State = (int)UIClickableState::kActive;
      }
    }
    else if (input_state.GetMouseButtonState(kMouseLeftButton) == false)
    {
      if (cur_hover_clickable && cur_hover_clickable->Enabled)
      {
        if (cur_hover_clickable == cur_pressed_clickable)
        {
          auto relative_pos = GetRelativePos(cur_hover_clickable);
          cur_pressed_clickable->OnClick(relative_pos.x, relative_pos.y);
          cur_pressed_clickable->OnStateChange(cur_pressed_clickable->m_State, (int)UIClickableState::kHover);
          cur_pressed_clickable->m_State = (int)UIClickableState::kHover;
        }
        else
        {
          cur_pressed_clickable->OnStateChange(cur_pressed_clickable->m_State, (int)UIClickableState::kActive);
          cur_pressed_clickable->m_State = (int)UIClickableState::kActive;

          cur_pressed_clickable->OnMouseLeave();
        }
      }
      else if(cur_pressed_clickable && cur_pressed_clickable->Enabled)
      {
        cur_pressed_clickable->OnStateChange(cur_pressed_clickable->m_State, (int)UIClickableState::kActive);
        cur_pressed_clickable->m_State = (int)UIClickableState::kActive;

        cur_pressed_clickable->OnMouseLeave();
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
      if (elem != cur_hover_clickable && elem->m_State == (int)UIClickableState::kHover)
      {
        elem->OnStateChange(elem->m_State, (int)UIClickableState::kActive);
        elem->m_State = (int)UIClickableState::kActive;
      }
    }

    if (cur_hover_clickable != nullptr && cur_hover_clickable->m_State != (int)UIClickableState::kHover && cur_hover_clickable->Enabled)
    {
      cur_hover_clickable->OnStateChange(cur_hover_clickable->m_State, (int)UIClickableState::kHover);
      cur_hover_clickable->m_State = (int)UIClickableState::kHover;
    }

    if (input_state.GetMousePressedThisFrame(kMouseLeftButton))
    {
      if (cur_hover_clickable != nullptr && cur_hover_clickable->Enabled)
      {
        cur_hover_clickable->OnStateChange(cur_hover_clickable->m_State, (int)UIClickableState::kPressed);
        cur_hover_clickable->m_State = (int)UIClickableState::kPressed;
      }
    }
  }

  if(prev_hover_clickable && prev_hover_clickable->m_Dead == false && prev_hover_clickable != cur_hover_clickable)
  {
    prev_hover_clickable->OnMouseLeave();
  }

  auto active_clickable = cur_pressed_clickable ? cur_pressed_clickable : cur_hover_clickable;
  if(active_clickable)
  {
    auto relative_pos = GetRelativePos(active_clickable);
    if(active_clickable != prev_active_clickable)
    {
      cur_hover_clickable->OnMouseEnter(relative_pos.x, relative_pos.y);
    }

    if(m_PrevCursorPos.x != ui_pos.x || m_PrevCursorPos.y != ui_pos.y)
    {
      active_clickable->OnMouseMove(relative_pos.x, relative_pos.y);
    }
  }

  if(cur_hover_clickable && cur_hover_clickable->Enabled && m_MouseDelta != 0)
  {
    cur_hover_clickable->OnMouseScroll(m_MouseDelta);
  }

  m_MouseDelta = 0;

  if ((cur_hover_clickable && cur_hover_clickable->Enabled) || (cur_pressed_clickable && cur_pressed_clickable->Enabled))
  {
    m_HasSelectedElement = true;
  }

  m_PrevCursorPos = ui_pos;
  RemoveDeadClickables();
}

void UIManager::RelocateTextureBinding(int texture_id, NotNullPtr<UITextureBinding> binding)
{
  m_Textures[texture_id] = binding;
}

void UIManager::ReleaseTextureBinding(int texture_id)
{
  m_Textures.erase(texture_id);
}
