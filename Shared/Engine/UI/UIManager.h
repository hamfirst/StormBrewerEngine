#pragma once

#include "Engine/EngineCommon.h"
#include "Engine/UI/UIClickable.h"
#include "Engine/UI/UIClickablePtr.h"

#include "Foundation/Time/StopWatch.h"

#include "Foundation/Script/ScriptState.h"
#include "Foundation/Script/ScriptInterface.h"

#include "StormExpr/StormExprFunctionList.h"

class InputState;
class Window;

class UIScriptLoader;

template <typename Type>
class SkipField;

class UIManager
{
public:

  UIManager(Window & container_window);
  ~UIManager();

  void LoadScripts();
  bool FinishedLoading() const;

  void Update(InputState & input_state, RenderState & render_state, const Vector2 & clickable_offset = Vector2(0, 0));
  void Render(RenderState & render_state, RenderUtil & render_util);

  void Pause();
  void Unpause();

  void GrabMouse(NotNullPtr<UIClickable> clickable);
  void ReleaseMouse(NotNullPtr<UIClickable> clickable);

  UIClickablePtr AllocateClickable(const Box & active_area);

  bool HasSelectedElement() const;

protected:

  friend class UIClickable;

  void ReleaseClickable(NotNullPtr<UIClickable> clickable);
  void ProcessActiveAreas(InputState & input_state, RenderState & render_state, const Vector2 & clickable_offset);

private:
  Window & m_ContainerWindow;

  Optional<ScriptState> m_ScriptState;
  Optional<ScriptInterface> m_ScriptInterface;

  std::unique_ptr<UIScriptLoader> m_Loader;

  std::vector<NotNullPtr<UIClickable>> m_Clickables;

  NotNullPtr<UIClickable> m_GrabbedMouseClickable = nullptr;
  bool m_HasSelectedElement = false;

  StopWatch m_UpdateTimer;
  bool m_Paused;
};

