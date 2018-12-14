
#pragma once

#include "StormRefl/StormRefl.h"

#include "Foundation/Script/ScriptClassRef.h"
#include "Foundation/Script/ScriptClassDelegate.h"
#include "Foundation/Script/ScriptInterface.h"

class UIManager;

enum class UIClickableState
{
  kDisabled,
  kActive,
  kHover,
  kPressed,
};

class UIClickable
{
public:
  STORM_REFL;
  STORM_REFL_FUNCS;

  STORM_REFL_NODEFAULT;

public:

  UIClickable(NotNullPtr<UIManager> manager);
  ~UIClickable();

  int State = 0;
  int Priority = 0;

  ScriptClassDelegate<void, int, int> OnStateChange;
  ScriptClassDelegate<void> OnClick;
  ScriptClassDelegate<void, float> OnUpdate;
  ScriptClassDelegate<void> OnRender;

  int X = 0;
  int Y = 0;
  int Width = 0;
  int Height = 0;

  ScriptClassRef<UIClickable> STORM_REFL_FUNC GetParent();
  void STORM_REFL_FUNC SetParent(ScriptClassRef<UIClickable> & self, const ScriptClassRef<UIClickable> & parent);

  int STORM_REFL_FUNC GetNumChildren();
  ScriptClassRef<UIClickable> STORM_REFL_FUNC GetChild(int index);

private:

  friend class UIManager;

  void Destroy();

private:

  NotNullPtr<UIManager> m_Manager;
  ScriptClassRef<UIClickable> m_Parent;

  std::vector<ScriptClassRef<UIClickable>> m_Children;

  Optional<Box> m_ActiveArea;
  bool m_Dead = false;
};
