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

class UIManager
{
public:

  UIManager(Window & container_window);
  ~UIManager();

  void LoadScripts();
  bool FinishedLoading() const;

  void Update(InputState & input_state, RenderState & render_state);
  void Render(RenderState & render_state, RenderUtil & render_util);

  void Pause();
  void Unpause();

  void GrabMouse(NotNullPtr<UIClickable> clickable);
  void ReleaseMouse(NotNullPtr<UIClickable> clickable);

  ScriptClassRef<UIClickable> AllocateClickable();

  bool HasSelectedElement() const;

protected:

  friend class UIClickable;

  void AddClickableToRoot(ScriptClassRef<UIClickable> & clickable);
  void RemoveClickableFromRoot(NotNullPtr<UIClickable> clickable);

  void AddToClickableList(NotNullPtr<UIClickable> clickable, NullOptPtr<UIClickable> parent, std::vector<NotNullPtr<UIClickable>> & list);
  void ProcessActiveAreas(InputState & input_state, RenderState & render_state);

private:

  Window & m_ContainerWindow;

  Optional<ScriptState> m_ScriptState;
  Optional<ScriptInterface> m_ScriptInterface;
  Optional<ScriptClass<UIClickable>> m_ClickableClass;

  std::unique_ptr<UIScriptLoader> m_Loader;

  std::vector<ScriptClassRef<UIClickable>> m_RootClickables;

  NotNullPtr<UIClickable> m_GrabbedMouseClickable = nullptr;
  bool m_HasSelectedElement = false;

  StopWatch m_UpdateTimer;
  bool m_Paused;
};

