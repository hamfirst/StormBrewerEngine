
#pragma once


#include "StormRefl/StormRefl.h"

#include "Foundation/Script/ScriptClassRef.h"
#include "Foundation/Script/ScriptClassDelegate.h"
#include "Foundation/Script/ScriptInterface.h"

#include "Engine/Input/TextInputContext.h"

class UIManager;
class UIClickable;

class UITextInput : public ScriptClassInstanceBase<UITextInput>
{
public:
  STORM_REFL;
  STORM_REFL_FUNCS;
  STORM_REFL_NO_BASE;

  STORM_REFL_NODEFAULT;

public:

  UITextInput(NotNullPtr<UIManager> manager, std::shared_ptr<TextInputContext> && context);
  ~UITextInput();

  ScriptClassDelegate<bool, std::string> IsInvalidInput;
  ScriptClassDelegate<void> OnEnter;

  void STORM_REFL_FUNC MakeCurrent(ScriptClassRef<UIClickable> container);
  void STORM_REFL_FUNC MakeNotCurrent();
  bool STORM_REFL_FUNC IsCurrent();

  std::string STORM_REFL_FUNC GetText();
  void STORM_REFL_FUNC Clear();
  int STORM_REFL_FUNC GetCursorPos();

private:

  friend class UIScriptInterface;

  NotNullPtr<UIManager> m_Manager;
  std::shared_ptr<TextInputContext> m_TextInput;

};
