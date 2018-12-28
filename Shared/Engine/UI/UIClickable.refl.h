
#pragma once

#include "StormRefl/StormRefl.h"

#include "Foundation/Script/ScriptClassRef.h"
#include "Foundation/Script/ScriptClassDelegate.h"
#include "Foundation/Script/ScriptInterface.h"

class UIManager;

enum STORM_REFL_ENUM class UIClickableState
{
  kDisabled,
  kActive,
  kHover,
  kPressed,
};

class UIClickable : public ScriptClassInstanceBase<UIClickable>
{
public:
  STORM_REFL;
  STORM_REFL_FUNCS;
  STORM_REFL_NO_BASE;

  STORM_REFL_NODEFAULT;

public:

  UIClickable(NotNullPtr<UIManager> manager);
  ~UIClickable();


  ScriptClassDelegate<void, int, int> OnStateChange;
  ScriptClassDelegate<void, float> OnUpdate;
  ScriptClassDelegate<void> OnDraw;


  ScriptClassDelegate<void, int, int> OnMouseEnter;
  ScriptClassDelegate<void> OnMouseLeave;
  ScriptClassDelegate<void, int, int> OnMouseMove;
  ScriptClassDelegate<void, int, int> OnClick;

  bool Enabled = true;
  bool Clip = true;
  int X = 0;
  int Y = 0;
  int Width = 0;
  int Height = 0;

  int STORM_REFL_FUNC GetState();

  ScriptClassRef<UIClickable> STORM_REFL_FUNC GetParent();
  void STORM_REFL_FUNC SetParent(ScriptClassRef<UIClickable> & parent);

  int STORM_REFL_FUNC GetNumChildren();
  ScriptClassRef<UIClickable> STORM_REFL_FUNC GetChild(int index);

  void STORM_REFL_FUNC GrabMouse();
  void STORM_REFL_FUNC ReleaseMouse();

private:

  friend class UIManager;
  friend class UITextInput;

  void Destroy();
  Optional<Box> CalculateActiveArea();

private:

  NotNullPtr<UIManager> m_Manager;

  int m_State = 0;
  ScriptClassRef<UIClickable> m_Parent;

  std::vector<ScriptClassRef<UIClickable>> m_Children;

  Optional<Box> m_ActiveArea;
  bool m_Dead = false;
};
