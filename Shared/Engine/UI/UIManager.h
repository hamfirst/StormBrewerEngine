#pragma once

#include "Engine/EngineCommon.h"
#include "Engine/Input/ScalarControlBinding.h"
#include "Engine/Asset/AssetReference.h"
#include "Engine/Asset/TextureAsset.h"

#include "Foundation/Time/StopWatch.h"

#include "Foundation/Script/ScriptState.h"
#include "Foundation/Script/ScriptInterface.h"
#include "Foundation/Script/ScriptClass.h"

#include "Runtime/UI/UIResource.h"

#include "StormExpr/StormExprFunctionList.h"

class InputState;
class Window;
class RenderState;

struct UIDef;
class UIScriptLoader;
class UIScriptInterface;

class UIClickable;
class UITextInput;
class UITextureBinding;

class UIManager
{
public:
  UIManager(Window & container_window);
  ~UIManager();

  void LoadScripts(const Vector2 & screen_size, bool immediate_load = false,
          Delegate<void> && load_complete_callback = {}, Delegate<void, czstr> && error_output = {});

  bool FinishedLoading() const;

  NotNullPtr<ScriptState> GetScriptState();
  NotNullPtr<const ScriptState> GetScriptState() const;

  void Update(float delta_time, InputState & input_state, RenderState & render_state);
  void Render(RenderState & render_state, const Optional<RenderVec2> & override_script_render_size = {});

  void Pause();
  void Unpause();

  void GrabMouse(NotNullPtr<UIClickable> clickable);
  void ReleaseMouse(NotNullPtr<UIClickable> clickable);

  ScriptClassRef<UIClickable> AllocateClickable();

  void PushUIDef(const UIDef & def);
  void PushUIDef(const UIResourcePtr & ui);
  void ClearUI();
  ScriptInterface & CreateGameInterface();
  void ClearGameInterface();

  bool Call(czstr name, NullOptPtr<ScriptValue> return_val = nullptr);
  bool Call(czstr name, std::initializer_list<ScriptValue> args, NullOptPtr<ScriptValue> return_val = nullptr);
  void SetGlobal(czstr name, const ScriptValue & value);

  bool HasSelectedElement() const;

  UITextureBinding CreateTextureBinding(czstr name, Delegate<NullOptPtr<const Texture>> && tex);

protected:

  friend class UIClickable;
  friend class UITextInput;
  friend class UITextureBinding;

  void AddClickableToRoot(const ScriptClassRef<UIClickable> & clickable);
  void RemoveClickableFromRoot(const ScriptClassRef<UIClickable> & clickable);
  void TrashClickable(NotNullPtr<UIClickable> clickable);
  void RemoveDeadClickables();

  void UpdateScriptGlobals(const Vector2 & screen_size);
  void HandleMouseScroll(int dv);

  void AddToClickableList(NotNullPtr<UIClickable> clickable, NullOptPtr<UIClickable> parent, std::vector<NotNullPtr<UIClickable>> & list);
  void ProcessActiveAreas(float delta_time, InputState & input_state, RenderState & render_state);

  void RelocateTextureBinding(int texture_id, NotNullPtr<UITextureBinding> binding);
  void ReleaseTextureBinding(int texture_id);

private:

  friend class UIScriptInterface;

  Window & m_ContainerWindow;

  std::unique_ptr<ScriptClass<UIClickable>> m_ClickableClass;
  std::unique_ptr<ScriptClass<UITextInput>> m_TextInputClass;

  Optional<ScriptState> m_ScriptState;
  Optional<ScriptInterface> m_UIInterfaceObject;
  Optional<ScriptInterface> m_GameInterfaceObject;

  std::unique_ptr<UIScriptLoader> m_ScriptLoader;
  std::unique_ptr<UIScriptInterface> m_ScriptInterface;

  std::vector<ScriptClassRef<UIClickable>> m_RootClickables;
  std::vector<NotNullPtr<UIClickable>> m_DeadClickables;

  NullOptPtr<UIClickable> m_CurrentInputClickable = nullptr;
  NullOptPtr<UITextInput> m_CurrentInputContext = nullptr;

  std::unordered_map<int, NotNullPtr<UITextureBinding>> m_Textures;
  int m_NextTextureId;

  std::string m_CleanupFunc;
  Vector2 m_PrevCursorPos = Vector2(-10000, -10000);

  NotNullPtr<UIClickable> m_GrabbedMouseClickable = nullptr;
  bool m_HasSelectedElement = false;

  StopWatch m_UpdateTimer;
  bool m_Paused = false;
  bool m_Destroying = false;

  Optional<ScalarControlHandle> m_WheelBinding;
  int m_MouseDelta = 0;
};

