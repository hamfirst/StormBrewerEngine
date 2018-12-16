#pragma once

#include "Engine/EngineCommon.h"
#include "Engine/UI/UIClickable.refl.h"

#include "Foundation/Time/StopWatch.h"

#include "Foundation/Script/ScriptState.h"
#include "Foundation/Script/ScriptInterface.h"
#include "Foundation/Script/ScriptClass.h"

#include "StormExpr/StormExprFunctionList.h"

class InputState;
class Window;
class RenderState;
class RenderUtil;

class UIScriptLoader;
class UIScriptInterface;

class UIManager
{
public:

  UIManager();
  ~UIManager();

  void LoadScripts();
  bool FinishedLoading() const;

  void Update(float delta_time, InputState & input_state, RenderState & render_state);
  void Render(RenderState & render_state, RenderUtil & render_util);

  void Pause();
  void Unpause();

  void GrabMouse(NotNullPtr<UIClickable> clickable);
  void ReleaseMouse(NotNullPtr<UIClickable> clickable);

  ScriptClassRef<UIClickable> AllocateClickable();

  bool HasSelectedElement() const;

protected:

  friend class UIClickable;

  void AddClickableToRoot(const ScriptClassRef<UIClickable> & clickable);
  void RemoveClickableFromRoot(NotNullPtr<UIClickable> clickable);
  void TrashClickable(NotNullPtr<UIClickable> clickable);
  void RemoveDeadClickables();

  void AddToClickableList(NotNullPtr<UIClickable> clickable, NullOptPtr<UIClickable> parent, std::vector<NotNullPtr<UIClickable>> & list);
  void ProcessActiveAreas(float delta_time, InputState & input_state, RenderState & render_state);

private:

  friend class UIScriptInterface;

  Optional<ScriptClass<UIClickable>> m_ClickableClass;

  Optional<ScriptState> m_ScriptState;
  Optional<ScriptInterface> m_InterfaceObject;

  std::unique_ptr<UIScriptLoader> m_ScriptLoader;
  std::unique_ptr<UIScriptInterface> m_ScriptInterface;

  std::vector<ScriptClassRef<UIClickable>> m_RootClickables;
  std::vector<NotNullPtr<UIClickable>> m_DeadClickables;

  NotNullPtr<UIClickable> m_GrabbedMouseClickable = nullptr;
  bool m_HasSelectedElement = false;

  StopWatch m_UpdateTimer;
  bool m_Paused = false;
  bool m_Destroying = false;
};

